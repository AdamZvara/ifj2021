#!/bin/bash

INPUT_FILES=$(ls scanner-tests | grep .input)
TEST_DIR=scanner-tests/

for f in $INPUT_FILES; do
    TEST_NAME=$(echo $f | cut -d'.' -f1)
    INPUT=$TEST_DIR$f
    OUTPUT=$TEST_DIR$(echo $f | cut -d'.' -f1).output
    EXPECTED=$TEST_DIR$(echo $f | cut -d'.' -f1).expected
    DIFF=$TEST_DIR$(echo $f | cut -d'.' -f1).diff

    # Run tests
    ./scanner-helper < $TEST_DIR$f > $OUTPUT

    # Check output
    diff $OUTPUT $EXPECTED > $DIFF
    echo "Testing: $TEST_NAME"
    if [ $? -eq 0 ]; then
        echo "PASS"
    else
        echo "FAIL - CHECK .diff FILE"
    fi
done