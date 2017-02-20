#!/usr/bin/python

import unittest
import requests as req
import subprocess
import os
import json

class Payload:

    login = open('./bodies/login.json').read()
    create_flat = open('./bodies/createFlat.json').read()
    add_user = open('./bodies/addFlatUser.json').read()
    get_users = open('./bodies/getFlatUsers.json').read()


class Urls:

    api_url = 'http://localhost:9080/v1'

    ping = api_url + '/user/ping'
    login = api_url + '/user/login'
    logout = api_url + '/user/logout'
    create_flat = api_url + '/flat/create'
    add_user = api_url + '/flat/adduser'
    get_users = api_url + '/flat/2/getusers'
    get_users_flats = api_url + '/flat/getforuser'
    is_flat_admin = api_url + '/flat/1/is_admin'


class Headers:

    auth_token = {'Auth-Token': 'czeslavo@gmail.com:dummyapitoken'}


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
            print resp.text
            return ''

    def login(self):
        r = req.post(Urls.login, data=Payload.login)
        self.assertEqual(self.get_resp(r), 'Successfully logged in')

    def logout(self):
        r = req.post(Urls.logout, headers=Headers.auth_token)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully')

    def create_flat(self):
        r = req.post(Urls.create_flat, data=Payload.create_flat, headers=Headers.auth_token)
        self.assertEqual(self.get_resp(r), 'Successfully created flat')

    def add_user(self):
        r = req.post(Urls.add_user, data=Payload.add_user, headers=Headers.auth_token)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully added user')

    def get_users(self):
        r = req.get(Urls.get_users, data=Payload.get_users, headers=Headers.auth_token)
        self.assertRegexpMatches(self.get_resp(r), 'Got users of flat')

    def get_users_flats(self):
        r = req.get(Urls.get_users_flats, headers=Headers.auth_token)
        self.assertRegexpMatches(self.get_resp(r), 'Got user\'s flats')

    def is_flat_admin(self):
        r = req.get(Urls.is_flat_admin, headers=Headers.auth_token)
        self.assertRegexpMatches(self.get_resp(r), "Is user flat admin response")
        self.assertEqual(r.json()['isAdmin'], True)

    def ping(self):
        r = req.get(Urls.ping, headers=Headers.auth_token)
        self.assertRegexpMatches(self.get_resp(r), "You're logged in")

    def ping_fail(self):
        r = req.get(Urls.ping, headers=Headers.auth_token)
        self.assertRegexpMatches(self.get_resp(r), "Not logged in")

    def test_shouldCreateFlatAndAddUsers(self):
        self.login()
        self.create_flat()
        self.add_user()
        self.get_users()
        self.get_users_flats()
        self.is_flat_admin()
        self.ping()
        self.logout()
        self.ping_fail()


if __name__ == '__main__':
    unittest.main()

