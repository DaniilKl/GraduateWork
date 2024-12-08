#!/bin/bash

testing_data=$(find "$1" -type f)
echo "Testing data:"
echo "$testing_data"
output_directory="$2"

IFS=$'\n'       # Set Internal Field Separator to newline
for line in $testing_data; do
    echo "Using: $line"

    load_factor=$(echo "$line" | sed -E 's|.*/||; s|\.json$||')

    ./insert.py ../LM3S6965_GCC_QEMU/src/main.c_sample $line ../LM3S6965_GCC_QEMU/src/main.c

    cd ../LM3S6965_GCC_QEMU/
    make
    cd -

    # Launch Qemu and generate data:
    timeout 15s qemu-system-arm -kernel ../LM3S6965_GCC_QEMU/build/FreeRTOS_QEMU.elf -s -machine lm3s6965evb -nographic -d exec -D qemu.log < /dev/null &
    sleep 17s
    # Parse data:
    ./parse.py 2500 ./qemu.log $output_directory/parsing-results-$load_factor.json 1> /dev/null
    # Analyze data:
    ./analyze.py $line 10 $output_directory/parsing-results-$load_factor.json $output_directory/analyzing-results-$load_factor.json
done

echo "Done!"
ls $output_directory
