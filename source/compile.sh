#!/bin/sh

echo ""
echo "Compiling the program..."

g++ main.cpp parse.cpp -o parse

echo "Finished compiling..."
echo ""

echo "List of trace files in your current working directory: "
ls -1 | grep '.trace\|.tr'

echo ""
echo "To run the program:"
echo "./parse [OPTIONS] < YOUR_TRACE_FILE.trace"
echo ""