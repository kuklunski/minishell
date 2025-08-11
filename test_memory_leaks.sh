#!/bin/bash

MINISHELL="./minishell"
COMMAND_FILE="/mnt/c/Users/ingoo/OneDrive/Bureau/final_minishell/commands.txt"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Parse optional start/end line arguments
START_LINE=${1:-1}
END_LINE=${2:-999999}

# Check if minishell exists
if [[ ! -x "$MINISHELL" ]]; then
    echo -e "${RED}Error: minishell not found or not executable at $MINISHELL${NC}"
    exit 1
fi

# Check if command file exists
if [[ ! -f "$COMMAND_FILE" ]]; then
    echo -e "${RED}Error: Command file not found at $COMMAND_FILE${NC}"
    exit 1
fi

# Check if valgrind is installed
if ! command -v valgrind &> /dev/null; then
    echo -e "${RED}Error: valgrind is not installed or not in PATH${NC}"
    echo "Please install valgrind: sudo apt-get install valgrind"
    exit 1
fi

echo -e "${YELLOW}Testing minishell for memory leaks with valgrind...${NC}"
echo "Minishell: $MINISHELL"
echo "Command file: $COMMAND_FILE"
echo "Testing lines $START_LINE to $END_LINE"
echo -e "${BLUE}Note: This will be slower due to valgrind overhead${NC}"
echo ""

total_tests=0
passed_tests=0
failed_tests=0
leak_tests=0
error_tests=0
current_line=0

# Create temporary directory for valgrind logs
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

while IFS= read -r raw_line || [[ -n "$raw_line" ]]; do
    ((current_line++))
    # Skip lines outside requested range
    if (( current_line < START_LINE || current_line > END_LINE )); then
        continue
    fi

    # Use the command directly since $> prefix has been removed
    cmd="$raw_line"
    [[ -z "$cmd" ]] && continue

    # Skip commands that are just comments or contain special characters that might cause issues
    if [[ "$cmd" =~ ^[[:space:]]*$ ]] || [[ "$cmd" =~ "Ctlr-" ]] || [[ "$cmd" =~ "faire" ]] || [[ "$cmd" =~ "!!!!" ]]; then
        continue
    fi

    ((total_tests++))
    
    echo -n "Test #$current_line: ${cmd:0:50}... "
    
    # Create unique log file for this test
    LOG_FILE="$TEMP_DIR/valgrind_$current_line.log"
    
    # Run the command with valgrind
    echo "$cmd" | timeout 10s valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --error-exitcode=42 \
        --log-file="$LOG_FILE" \
        "$MINISHELL" > /dev/null 2>&1
    
    exit_status=$?
    
    # Parse valgrind output
    if [[ -f "$LOG_FILE" ]]; then
        # Check for errors (invalid reads/writes, etc.)
        error_count=0
        if grep -q "ERROR SUMMARY:" "$LOG_FILE"; then
            # Extract the number of errors from "ERROR SUMMARY: X errors from Y contexts"
            errors=$(grep "ERROR SUMMARY:" "$LOG_FILE" | grep -o '[0-9]\+ errors' | grep -o '[0-9]\+' | head -1)
            errors=${errors:-0}
        else
            errors=0
        fi
        
        # Check for memory leaks
        definitely_lost=$(grep "definitely lost:" "$LOG_FILE" | grep -o '[0-9,]\+ bytes' | tr -d ',' | grep -o '[0-9]\+' | head -1)
        indirectly_lost=$(grep "indirectly lost:" "$LOG_FILE" | grep -o '[0-9,]\+ bytes' | tr -d ',' | grep -o '[0-9]\+' | head -1)
        possibly_lost=$(grep "possibly lost:" "$LOG_FILE" | grep -o '[0-9,]\+ bytes' | tr -d ',' | grep -o '[0-9]\+' | head -1)
        
        # Default to 0 if not found
        definitely_lost=${definitely_lost:-0}
        indirectly_lost=${indirectly_lost:-0}
        possibly_lost=${possibly_lost:-0}
        errors=${errors:-0}
        
        total_leaked=$((definitely_lost + indirectly_lost))
        
        # Determine test result
        if [[ $exit_status -eq 124 ]]; then
            echo -e "${YELLOW}[TIMEOUT]${NC}"
            ((failed_tests++))
        elif [[ $errors -gt 0 ]]; then
            echo -e "${RED}[ERRORS: $errors]${NC}"
            ((error_tests++))
            ((failed_tests++))
        elif [[ $total_leaked -gt 0 ]]; then
            echo -e "${RED}[LEAK: ${total_leaked}B]${NC}"
            ((leak_tests++))
            ((failed_tests++))
        elif [[ $possibly_lost -gt 0 ]]; then
            echo -e "${YELLOW}[POSSIBLE: ${possibly_lost}B]${NC}"
            ((failed_tests++))
        else
            echo -e "${GREEN}[OK]${NC}"
            ((passed_tests++))
        fi
    else
        echo -e "${RED}[NO LOG]${NC}"
        ((failed_tests++))
    fi

done < "$COMMAND_FILE"

echo ""
echo "========== MEMORY LEAK SUMMARY =========="
echo "Total tests: $total_tests"
echo -e "Passed: ${GREEN}$passed_tests${NC}"
echo -e "Failed: ${RED}$failed_tests${NC}"
echo -e "Memory leaks: ${RED}$leak_tests${NC}"
echo -e "Memory errors: ${RED}$error_tests${NC}"

# Show detailed results for failed tests if any
if (( failed_tests > 0 )); then
    echo ""
    echo -e "${YELLOW}=== DETAILED LEAK REPORT ===${NC}"
    
    current_line=0
    while IFS= read -r raw_line || [[ -n "$raw_line" ]]; do
        ((current_line++))
        if (( current_line < START_LINE || current_line > END_LINE )); then
            continue
        fi
        
        # Use the command directly since $> prefix has been removed
        cmd="$raw_line"
        [[ -z "$cmd" ]] && continue
        
        if [[ "$cmd" =~ ^[[:space:]]*$ ]] || [[ "$cmd" =~ "Ctlr-" ]] || [[ "$cmd" =~ "faire" ]] || [[ "$cmd" =~ "!!!!" ]]; then
            continue
        fi
        
        LOG_FILE="$TEMP_DIR/valgrind_$current_line.log"
        
        if [[ -f "$LOG_FILE" ]]; then
            # Check if this test had leaks or errors
            if grep -q "definitely lost:" "$LOG_FILE" && ! grep -q "definitely lost: 0 bytes" "$LOG_FILE"; then
                echo -e "${RED}Line $current_line: $cmd${NC}"
                grep "definitely lost:" "$LOG_FILE"
                echo ""
            elif grep -q "ERROR SUMMARY:" "$LOG_FILE" && ! grep -q "ERROR SUMMARY: 0 errors" "$LOG_FILE"; then
                echo -e "${RED}Line $current_line: $cmd${NC}"
                grep "ERROR SUMMARY:" "$LOG_FILE"
                echo ""
            fi
        fi
    done < "$COMMAND_FILE"
fi

if (( leak_tests > 0 )); then
    echo -e "${RED}WARNING: $leak_tests memory leak(s) detected!${NC}"
    exit 1
elif (( error_tests > 0 )); then
    echo -e "${RED}WARNING: $error_tests memory error(s) detected!${NC}"
    exit 1
elif (( failed_tests > 0 )); then
    echo -e "${YELLOW}$failed_tests test(s) failed (timeouts or possible leaks)${NC}"
    exit 1
else
    echo -e "${GREEN}All tests passed! No memory leaks detected.${NC}"
    exit 0
fi
