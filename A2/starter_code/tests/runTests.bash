#!/bin/bash
# NOTE : Run this script from the /tests/ directory, or it won't work

FILES="./tests/*.input"
FAILS=0

if [ -e "./scrabble"  ] 
then
    echo "=========================="
    echo "Running Tests"
    for f in $FILES
    do
        echo "---------------------------"
        E=${f%.*}
        #echo "test: $f"
        ./scrabble < $f > "$E.gameout"
        #echo "Writing results to $E.gameout"

        differences=`diff -w $E.output $E.gameout`

        #echo ${#differences}

        if [ ${#differences} == "0" ]
        then
            echo -e "\e[32;5m$E PASSED!\e[0m"
        else
            echo -e "\e[31m$E FAILED!\e[0m"
            ((FAILS=FAILS+1))
            #echo "!     Differences: ${#differences}     !"
            diff -w --color $E.output $E.gameout
            
        fi
        echo ""   

        # take action on each file. $f store current file name
        #cat "$f"
    done

else
    echo -e "\e[31mTests FAILED to run!\e[0m"
    echo "Scrabble.exe not found"
    ((FAILS=1))
fi

echo $FAILS
exit $FAILS