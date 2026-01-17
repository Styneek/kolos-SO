#!/bin/bash

if ! [ $# -eq 1 ]; then
    echo "Blad"
    exit 1
fi

CZAS=$1
sleep $CZAS &
PID=$! 

echo "nadzorca"

wait $PID
WYNIK=$?

if [ $WYNIK -eq 0 ]; then
    echo "zadanie zakonczone sukcesem"
elif [ $WYNIK -gt 128 ]; then
    echo "zadananie przerwane"
else 
    echo "blad"
fi