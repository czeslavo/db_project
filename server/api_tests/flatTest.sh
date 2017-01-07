#!/bin/bash

./run_server &

python ./../../scripts/execute_sql.py ./../../scripts/init_db.sql
python ./../../scripts/execute_sql.py ./../../scripts/fill_db.sql

http POST localhost:9080/v1/user/login mail=czeslavo@gmail.com password=pass
http POST localhost:9080/v1/flat/create --verbose < bodies/createFlat.json
http POST localhost:9080/v1/flat/adduser --verbose < bodies/addFlatUser.json
http GET localhost:9080/v1/flat/2/getusers --verbose < bodies/getFlatUsers.json

kill $(ps -ef | grep -m 1 "run_server" | awk '{print $2}')
