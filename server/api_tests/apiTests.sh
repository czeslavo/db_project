#!/bin/bash

../artifacts/run_server &
sleep 2

python -m unittest discover --verbose . "*_test.py"

kill $(ps -ef | grep -m 1 "run_server" | awk '{print $2}')
