#!/bin/bash

c=5
for((i=0; i < c; i++)); do
    ./fork
done

echo "Done"