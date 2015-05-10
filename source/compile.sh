#!/bin/sh

echo ""
echo "Compiling the program..."

g++ main.cpp parse.cpp part2.cpp part3.cpp -o project

echo "Finished compiling..."
echo ""

echo "List of trace files in your current working directory: "
ls -1 | grep '.trace\|.tr'

echo ""
echo "To run the program:"
echo "./project [OPTIONS] < YOUR_TRACE_FILE.trace"
echo ""
