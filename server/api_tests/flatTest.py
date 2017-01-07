#!/usr/bin/python

import unittest
import requests
import subprocess
import time
import os


class FlatApiTest(unittest.TestCase):

    def shouldCreateFlatAndAddUsers(self):
        pass

if __name__ == '__main__':
    api = subprocess.Popen(["./run_server"])
    time.sleep(3)

    unittest.main()

    api.terminate()
    pid = api.pid
    try:
        os.kill(pid, 0)
        p.kill()
        print "Forced kill"
    except OSError, e:
        print "Terminated gracefully"

