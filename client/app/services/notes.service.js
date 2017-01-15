(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('NotesService', NotesService);

    NotesService.$inject = ['$http'];
    function NotesService($http) {
        var service = {};
        var api = 'http://localhost:9090/v1/note';

        service.getFlatNotes = getFlatNotes;
        service.createNote = createNote;
        service.removeNote = removeNote;
        service.updateNote = updateNote;

        return service;

        function getFlatNotes(flatId, successCallback, failureCallback) {
            $http.get(api + '/getforflat/' + flatId).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.notes);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function createNote(note, successCallback, failureCallback) {
            var body = {flat_id: note.flat_id,
                        note: note};

            $http.post(api + '/add', body).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function updateNote(note, successCallback, failureCallback) {
            var body = {flat_id: note.flat_id,
                        note: note};

            $http.put(api + '/update', body).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function removeNote(note, successCallback, failureCallback) {
            $http.delete(api + '/remove/' + note.flat_id + '/' + note.id).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.notes);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }
    }

})();
