#!/usr/bin/python

import unittest
import requests as req
import subprocess
import os
import json

class Payload:

    login = open('./bodies/login.json').read()
    create_note = open('./bodies/addNote.json').read()
    remove_note = open('./bodies/removeNote.json').read()
    update_note = open('./bodies/updateNote.json').read()
    get_notes_for_flat = open('./bodies/getNotesForFlat.json').read()
    get_note_by_id = open('./bodies/getNoteById.json').read()


class Urls:


    api_url = 'http://localhost:9080/v1'

    login = api_url + '/user/login'
    create_note = api_url + '/note/add'
    remove_note = api_url + '/note/remove'
    update_note = api_url + '/note/update'
    get_notes_for_flat = api_url + '/note/getforflat'
    get_note_by_id = api_url + '/note/get'


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

    def create_note(self):
        r = req.post(Urls.create_note, data=Payload.create_note, headers=Headers.auth_token, timeout=1)
        self.assertEqual(self.get_resp(r), 'Successfully created note')

    def remove_note(self):
        r = req.delete(Urls.remove_note, data=Payload.remove_note, headers=Headers.auth_token, timeout=1)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully removed note')

    def update_note(self):
        r = req.put(Urls.update_note, data=Payload.update_note, headers=Headers.auth_token, timeout=1)
        self.assertRegexpMatches(self.get_resp(r), 'Successfully updated note')

    def get_notes_for_flat(self):
        r = req.get(Urls.get_notes_for_flat, data=Payload.get_notes_for_flat, headers=Headers.auth_token, timeout = 1)
        self.assertRegexpMatches(self.get_resp(r), 'Got notes for flat')

    def get_note_by_id(self):
        r = req.get(Urls.get_note_by_id, data=Payload.get_note_by_id, headers=Headers.auth_token, timeout = 1)
        self.assertRegexpMatches(self.get_resp(r), 'Got note by id')

    def test_notes(self):
        self.login()
        self.create_note()
        self.remove_note()
        self.update_note()
        self.get_notes_for_flat()
        self.get_note_by_id()

if __name__ == '__main__':
    unittest.main()

