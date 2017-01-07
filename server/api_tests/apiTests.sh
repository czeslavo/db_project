#!/bin/bash

../artifacts/run_server &>/dev/null &

#http POST localhost:9080/v1/user/login mail=czeslavo@gmail.com password=pass
#http POST localhost:9080/v1/flat/create --verbose < bodies/createFlat.json
#http POST localhost:9080/v1/flat/adduser --verbose < bodies/addFlatUser.json
#http GET localhost:9080/v1/flat/2/getusers --verbose < bodies/getFlatUsers.json

python -m unittest discover --verbose . "*_test.py"

kill $(ps -ef | grep -m 1 "run_server" | awk '{print $2}')
