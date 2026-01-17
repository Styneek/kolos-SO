#!/bin/bash

FIFO="system_log.fifo"


trap 'rm -f "$FIFO"; kill $PID 2>/dev/null; exit' SIGINT EXIT

mkfifo "$FIFO"

( while true; do read l < "$FIFO" && echo "[LOG]: $l"; done ) &
PID=$!

sleep 1
echo "Start" > "$FIFO"
sleep 1
echo "Logowanie" > "$FIFO"
sleep 1
echo "Blad" > "$FIFO"
