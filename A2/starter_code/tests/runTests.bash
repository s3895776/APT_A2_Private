#!/bin/bash
# NOTE : Run this script from the /tests/ directory, or it won't work

echo "Running Tests"

FILES="*.input"
for f in $FILES
do
    E=${f%.*}
    echo "test: $f"

    ../scrabble < $f > "$E.gameout"
    #echo "Writing results to $E.gameout"

    differences=`diff -w $E.output $E.gameout`
    echo "Differences: ${#differences}"

    # take action on each file. $f store current file name
    #cat "$f"
done