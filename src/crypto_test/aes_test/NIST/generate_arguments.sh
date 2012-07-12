#!/bin/bash
while read input_line; do
    # \3 is ciphertext
    # \4 is plaintext
    #generate ciphertext from plaintext
    ciphertext=$(echo $input_line |sed 's/^KEY = \([^ ]*\) IV = \([^ ]*\) [A-Z]\+ = \([^ ]*\) [A-Z]\+ = \([^ ]*\).*$/-e \1 \2 \3/g')
    #generate plaintext from ciphertext
    plaintext=$(echo $input_line |sed 's/^KEY = \([^ ]*\) IV = \([^ ]*\) [A-Z]\+ = \([^ ]*\) [A-Z]\+ = \([^ ]*\).*$/-d \1 \2 \4/g')
    echo $ciphertext
    echo $plaintext

done
