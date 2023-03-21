#!/bin/bash

# create log file
logfile="session.log"
touch $logfile

# start shell session and log input/output to file
script -f $logfile

# read from log file and print output to terminal
cat $logfile
