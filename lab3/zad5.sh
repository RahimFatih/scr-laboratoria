#!/bin/bash
trap "echo Przechwycono sygnal SIGINT" INT

trap "echo Przechwycono sygnal SIGQUIT" SIGQUIT

trap "echo Przechwycono sygnal SIGFPE" SIGFPE

trap "echo Przechwycono sygnal SIGILL" SIGILL





echo "pid to $$"
while (( COUNT < 1000  ))
do
    sleep 10
    (( COUNT ++ ))
    echo "$COUNT"
done
exit 0
