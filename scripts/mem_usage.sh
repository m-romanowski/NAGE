#!/bin/bash

runtime="1 minute"
endtime=$(date -ud "$runtime" +%s)
DIR=result
FILE='memusage'
PID=$(pgrep -f QNAGE)

mkdir -p $DIR

while [[ $(date -u +%s) -le $endtime ]]
do
	date +"%T" && cat /proc/$PID/status | grep VmRSS | grep -E -o "[0-9]+" >> $DIR/$FILE
	sleep 1
done
