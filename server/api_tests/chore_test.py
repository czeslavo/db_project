#!/usr/bin/python

import unittest
import requests as req
import subprocess
import os
import json

class Payload:

    login = open('./bodies/login.json').read()
    create_chore = open('./bodies/addChore.json').read()
    remove_chore = open('./bodies/removeNote.json').read()
    update_chore = open('./bodies/updateChore.json').read()
    get_chore_by_id = open('./bodies/getChoreById.json').read()
    schedule_chore = open('./bodies/scheduleChore.json').read()


class Urls:

    api_url = 'http://localhost:9080/v1'

    login = api_url + '/user/login'
    create_chore = api_url + '/chore/add'
    remove_chore = api_url + '/chore/remove/1/1'
    update_chore = api_url + '/chore/update'
    get_chores_for_flat = api_url + '/chore/get_for_flat/1'
    get_chore_by_id = api_url + '/chore/get/2'
    schedule_chore = api_url + '/chore/schedule/2'
    get_scheduled_chores_for_flat = api_url + '/chore/get_scheduled/1'
    reset_scheduled = api_url + '/chore/reset_scheduled/1/2'
    toggle_done = api_url + '/chore/toggle_done/1/2/1800481458'


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

    def create_chore(self):
        r = req.post(Urls.create_chore, data=Payload.create_chore, headers=Headers.auth_token, timeout=1)
        self.assertEqual(self.get_resp(r), 'Successfully created chore')

    def remove_chore(self):
        r = req.delete(Urls.remove_chore, data=Payload.remove_chore, headers=Headers.auth_token, timeout=1)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully removed chore')

    def update_chore(self):
        r = req.put(Urls.update_chore, data=Payload.update_chore, headers=Headers.auth_token, timeout=1)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully updated chore')

    def get_chores_for_flat(self):
        r = req.get(Urls.get_chores_for_flat, headers=Headers.auth_token, timeout = 1)
        self.assertRegexpMatches(self.get_resp(r), 'Got chores for flat')

    def get_chore_by_id(self):
        r = req.get(Urls.get_chore_by_id, data=Payload.get_chore_by_id, headers=Headers.auth_token, timeout = 1)
        self.assertRegexpMatches(self.get_resp(r), 'Got chore by id')

    def schedule_chore(self):
        r = req.post(Urls.schedule_chore, data=Payload.schedule_chore, headers=Headers.auth_token, timeout = 1)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully scheduled chore')

    def get_scheduled_chores_for_flat(self):
        r = req.get(Urls.get_scheduled_chores_for_flat, headers=Headers.auth_token, timeout=1)
        self.assertRegexpMatches(self.get_resp(r), 'Got chores for flat')
        print(json.dumps(r.json()['chores'], indent=4))

    def reset_scheduled(self):
        r = req.put(Urls.reset_scheduled, headers=Headers.auth_token, timeout=1)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully reset chore schedule')

    def toggle_done(self):
        r = req.put(Urls.toggle_done, headers=Headers.auth_token, timeout=1)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully toggled chore\'s done flag')


    def test_chores(self):
        self.login()
        self.create_chore()
        self.remove_chore()
        self.update_chore()
        self.get_chores_for_flat()
        self.get_chore_by_id()
        self.schedule_chore()
        self.get_scheduled_chores_for_flat()
        self.reset_scheduled()
        self.schedule_chore()
        self.toggle_done()

if __name__ == '__main__':
    unittest.main()

