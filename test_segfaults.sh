#!/bin/bash

MINISHELL="./minishell"
COMMAND_FILE="/mnt/c/Users/ingoo/OneDrive/Bureau/final_minishell/commands.txt"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

START_LINE=${1:-1}
END_LINE=${2:-999999}

if [[ ! -x "$MINISHELL" ]]; then
    echo -e "${RED}Error: minishell not found or not executable at $MINISHELL${NC}"
    exit 1
fi

if [[ ! -f "$COMMAND_FILE" ]]; then
    echo -e "${RED}Error: Command file not found at $COMMAND_FILE${NC}"
    exit 1
fi

echo -e "${YELLOW}Testing minishell for segfaults...${NC}"
echo "Minishell: $MINISHELL"
echo "Command file: $COMMAND_FILE"
echo "Testing lines $START_LINE to $END_LINE"
echo ""

total_tests=0
passed_tests=0
failed_tests=0
segfault_tests=0
current_line=0

while IFS= read -r raw_line || [[ -n "$raw_line" ]]; do
    ((current_line++))
    if (( current_line < START_LINE || current_line > END_LINE )); then
        continue
    fi

    cmd="$raw_line"
    [[ -z "$cmd" ]] && continue

    ((total_tests++))
    echo -n "Test #$current_line: $cmd ... "

    printf "%s\n" "$cmd" > /tmp/minishell_input.txt
    timeout 5s "$MINISHELL" < /tmp/minishell_input.txt > /dev/null 2>&1
    exit_status=$?

    case $exit_status in
        0)
            echo -e "${GREEN}[OK]${NC}"
            ((passed_tests++))
            ;;
        124)
            echo -e "${YELLOW}[TIMEOUT]${NC}"
            ((failed_tests++))
            ;;
        139)
            echo -e "${RED}[SEGFAULT]${NC}"
            ((segfault_tests++))
            ((failed_tests++))
            ;;
        *)
            echo -e "${YELLOW}[EXIT $exit_status]${NC}"
            ((failed_tests++))
            ;;
    esac

done < "$COMMAND_FILE"

echo ""
echo "========== SUMMARY =========="
echo "Total tests: $total_tests"
echo -e "Passed: ${GREEN}$passed_tests${NC}"
echo -e "Failed: ${RED}$failed_tests${NC}"
echo -e "Segfaults: ${RED}$segfault_tests${NC}"

if (( segfault_tests > 0 )); then
    echo -e "${RED}WARNING: $segfault_tests segfault(s) detected!${NC}"
    exit 1
elif (( failed_tests > 0 )); then
    echo -e "${YELLOW}$failed_tests test(s) failed (non-zero exit or timeout)${NC}"
    exit 1
else
    echo -e "${GREEN}All tests passed! No segfaults detected.${NC}"
    exit 0
fi
