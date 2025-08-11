#!/usr/bin/env bash
# Locate clang-format (try unversioned then common versioned names)
CF=$(command -v clang-format 2>/dev/null \
     || command -v clang-format-13 2>/dev/null \
     || command -v clang-format-12 2>/dev/null \
     || command -v clang-format-11 2>/dev/null)
if [ -z "$CF" ]; then
    echo "Error: clang-format not found. Please install clang-format." >&2
    exit 1
fi

# Apply clang-format in‐place to all C & header files
find . -type f \( -name "*.c" -o -name "*.h" \) -exec "$CF" -i {} +

echo "All .c/.h files have been reformatted."
