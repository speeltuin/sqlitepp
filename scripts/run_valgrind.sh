#!/bin/bash

valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --verbose --log-file=valgrind-out-%p.txt "$@"
fgrep "ERROR SUMMARY" valgrind-out-*.txt | fgrep -v " 0 errors from 0 contexts"
