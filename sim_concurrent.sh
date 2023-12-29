#!/bin/bash

for i in {1..1000}
do
    echo "Hello from Client $i" | nc localhost 3408 &
done

wait

