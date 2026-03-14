#!/bin/bash

failed=0
i=0

while ((i < 100)); do
	sleep 1
	if ! ./so_long ; then
		((failed++))
	fi
	((i++))
done

echo "Runs: $i"
echo "Failures: $failed"