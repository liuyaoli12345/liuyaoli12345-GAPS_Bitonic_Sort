#!/bin/bash

# Function to print the current time in a readable format
print_current_time() {
    date +"%Y-%m-%d %H:%M:%S"
}

# Function to measure time and display output
measure_time() {
    local file=$1
    local output_file=$2
    local start_time
    local end_time
    
    echo "Testing $file"
    
    start_time=$(print_current_time)
    
    # Measure the time of compilation and running
    { time (clang++ test.cpp "$file" && ./a.out) } 2> "$output_file"
    
    end_time=$(print_current_time)
    echo "Start time: $start_time"
    echo "End time: $end_time"
}

# Temporary files to hold the time output
temp_file1=$(mktemp)
temp_file2=$(mktemp)
temp_file3=$(mktemp)

# Measure time for each test and display outputs
measure_time "v1_segBitonicSort.cpp" "$temp_file1"
echo "Time for v1_segBitonicSort.cpp:"
cat "$temp_file1"

measure_time "v2_segBitonicSort.cpp" "$temp_file2"
echo "Time for v2_segBitonicSort.cpp:"
cat "$temp_file2"

measure_time "v3_segBitonicSort.cpp" "$temp_file3"
echo "Time for v3_segBitonicSort.cpp:"
cat "$temp_file3"

# Clean up temporary files
rm "$temp_file1" "$temp_file2" "$temp_file3"