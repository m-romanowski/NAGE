#!/bin/bash

EXECUTABLE=QNAGE
RUNTIME="1 minute"
ENDTIME=$(date -ud "$RUNTIME" +%s)
DIR=result
FILE='memusage'
PID=$(pgrep -f $EXECUTABLE)

mkdir -p $DIR

while [[ $(date -u +%s) -le $ENDTIME ]]
do
	date +"%T" && cat /proc/$PID/status | grep VmRSS | grep -E -o "[0-9]+" >> $DIR/$FILE
	sleep 1
done
