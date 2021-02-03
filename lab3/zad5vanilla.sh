#!/bin/bash
# SIGINT(2), SIGQUIT(3), ale także SIGFPE(8), SIGILL(4)
echo "pid to $$"
while (( COUNT < 1000  ))
do
    sleep 10
    (( COUNT ++ ))
    echo "$COUNT"
done
exit 0