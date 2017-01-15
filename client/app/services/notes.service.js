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
        };



    }

})();
