#!/bin/bash

# Function to generate the structure section
generate_structure() {
    echo "## Project Structure"
    echo
    echo "\`\`\`"
    # Use tree to generate structure, excluding specific files and directories
    tree -I "node_modules|.git|*.exe|tempCodeRunnerFile.cpp" --dirsfirst \
         -L 3 \
         --noreport \
        | sed '1d' \
        | sed 's/^//' \
        | while IFS= read -r line; do
        # Add comments for main directories and files
        case "$line" in
            *"BinTree/"*)
                echo "$line                    # Binary Tree Implementations"
                ;;
            *"Graphic/"*)
                echo "$line                    # Graph Data Structures"
                ;;
            *"LinearList/"*)
                echo "$line                 # Linear List Implementations"
                ;;
            *"Queue/"*)
                echo "$line                      # Queue Implementations"
                ;;
            *"Set/"*)
                echo "$line                       # Set Data Structures"
                ;;
            *"Stack/"*)
                echo "$line                     # Stack Implementations"
                ;;
            *"clean.sh"*)
                echo "$line                  # Utility script to remove executable files"
                ;;
            *"update_readme.sh"*)
                echo "$line             # Script to update README structure"
                ;;
            *"README.md"*)
                echo "$line                 # This file"
                ;;
            *)
                echo "$line"
                ;;
        esac
    done
    echo "\`\`\`"
    echo
}

# Path to README.md
README_FILE="README.md"
TEMP_FILE="README.temp.md"

# Create temporary file
touch "$TEMP_FILE"

# Read README.md and update the structure section
{
    # Copy everything before the structure section
    sed -n '1,/^## Project Structure$/p' "$README_FILE" | sed '$d'
    
    # Generate new structure
    generate_structure
    
    # Copy everything after the first ``` after Project Structure
    sed -n '/^```$/,$ p' "$README_FILE" | sed '1,/^```$/d'
} > "$TEMP_FILE"

# Replace old README with new one
mv "$TEMP_FILE" "$README_FILE"

echo "README.md structure has been updated!"
