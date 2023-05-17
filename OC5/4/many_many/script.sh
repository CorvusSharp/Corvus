#!/bin/bash

for i in {1..5}
	do
	    ./4_1 "from${i}.txt" "to${i}.txt" &
    done

    wait

