#!/usr/bin/python

import unittest
import requests as req
import subprocess
import os

class Payload:

    login = open('./bodies/login.json').read()
    create_flat = open('./bodies/createFlat.json').read()
    add_user = open('./bodies/addFlatUser.json').read()
    get_users = open('./bodies/getFlatUsers.json').read()

class Urls:

    api_url = 'http://localhost:9080/v1'

    login = api_url + '/user/login'
    create_flat = api_url + '/flat/create'
    add_user = api_url + '/flat/adduser'
    get_users = api_url + '/flat/2/getusers'


class FlatApiTests(unittest.TestCase):

    def setUp(self):
        FNULL = open(os.devnull, 'w')
        init_result = subprocess.call(['../artifacts/run_initializer'], \
            stdout=FNULL, stderr=FNULL)
        self.assertEqual(init_result, 0)

    def get_resp(self, resp):
        try:
            return resp.json()['response']
        except:
            return ''

    def login(self):
        r = req.post(Urls.login, data=Payload.login)
        self.assertEqual(self.get_resp(r), 'Successfully logged in')

    def create_flat(self):
        r = req.post(Urls.create_flat, data=Payload.create_flat)
        self.assertEqual(self.get_resp(r), 'Successfully created flat')

    def add_user(self):
        r = req.post(Urls.add_user, data=Payload.add_user)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully added user')

    def get_users(self):
        r = req.get(Urls.get_users, data=Payload.get_users)
        self.assertRegexpMatches(self.get_resp(r), 'Got users of flat')

    def test_shouldCreateFlatAndAddUsers(self):
        self.login()
        self.create_flat()
        self.add_user()
        self.get_users()


if __name__ == '__main__':
    unittest.main()

