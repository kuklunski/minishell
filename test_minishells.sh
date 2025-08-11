#!/bin/bash

MINISHELL1="/mnt/c/Users/ingoo/OneDrive/Bureau/final_minishell/minishell"
MINISHELL2="/mnt/c/Users/ingoo/OneDrive/Bureau/mcombeau/minishell"

COMMAND_FILE="/mnt/c/Users/ingoo/OneDrive/Bureau/MY_MINISHELL/commands.txt"

OUT1="/tmp/minishell1.out"
OUT2="/tmp/minishell2.out"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Parse optional start/end line arguments
START_LINE=${1:-1}
END_LINE=${2:-999999}

# Function to normalize output: remove ANSI codes, fix spacing, trim lines
normalize_output() {
    sed -E 's/\x1B\[[0-9;]*[a-zA-Z]//g' "$1" | \
    sed -E 's/Minishell>\$ ?exit/Minishell>\$ exit/' | \
    sed -E 's/Minishell>\$[[:space:]]*$/Minishell>\$/' | \
    sed -E 's/[[:space:]]+$//' | \
    sed -E 's/^[[:space:]]+//' > "$1.norm"
}

# Extract COMMAND NODE block
extract_command_node() {
    awk '/------------ COMMAND NODE ------------/,/^>>>/' "$1.norm" | grep -v '^>>> ' > "$1.cmd"
}

i=1
current_line=0

while IFS= read -r raw_line || [[ -n "$raw_line" ]]; do
    ((current_line++))
    # Skip lines outside requested range
    if (( current_line < START_LINE || current_line > END_LINE )); then
        continue
    fi

    # Use the command directly since $> prefix has been removed
    cmd="$raw_line"
    [[ -z "$cmd" ]] && continue

    echo "Test #$current_line: $cmd"

    echo "$cmd" | "$MINISHELL1" > "$OUT1" 2>&1
    echo "$cmd" | "$MINISHELL2" > "$OUT2" 2>&1

    normalize_output "$OUT1"
    normalize_output "$OUT2"

    extract_command_node "$OUT1"
    extract_command_node "$OUT2"

    if diff -u "$OUT1.cmd" "$OUT2.cmd" > /dev/null; then
        echo -e "${GREEN}[OK]${NC} Command nodes match."
    else
        echo -e "${RED}[FAIL]${NC} Command nodes differ:"
        echo "----- minishell 1 -----"
        cat "$OUT1.cmd"
        echo "----- minishell 2 -----"
        cat "$OUT2.cmd"
    fi

    echo ""
    ((i++))
done < "$COMMAND_FILE"

rm -f "$OUT1.norm" "$OUT2.norm" "$OUT1.cmd" "$OUT2.cmd"
