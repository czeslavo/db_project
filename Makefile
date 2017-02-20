all: compile ut api_tests

run_server: compile
	./server/artifacts/run_server

server/build:
	mkdir server/build

compile: server/build
	cd server/build && cmake .. && make install

ut: compile
	cd server/build && env GTEST_COLOR=1 ctest -V

api_tests: compile
	cd ./server/api_tests/ && ./apiTests.sh

clean: server/build
	cd server/build && make clean

deep-clean: server/build
	rm -rf server/build

deploy_client:
	rm -rf /data/www/flat_mate && mkdir /data/www/flat_mate && cp -r client/* /data/www/flat_mate

list_targets:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make database/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$' | xargs

.PHONY: compile ut clean deep-clean api_tests deploy_client list_targets
