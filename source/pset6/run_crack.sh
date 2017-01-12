#!/bin/bash

inputFile=$1

while IFS= read line
do
	echo $line | cut -d ':' -f 2 | xargs py crack.py

done < "$inputFile"

