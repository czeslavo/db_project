(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('ChoresService', ChoresService);

    ChoresService.$inject = ['$http'];
    function ChoresService($http) {
        var service = {};
        var api = 'http://localhost:9090/v1/chore';

        service.getFlatChores = getFlatChores;
        service.addChore = addChore;
        service.removeChore = removeChore;

        return service;

        function getFlatChores(flatId, successCallback, failureCallback) {
            $http.get(api + '/getforflat/' + flatId).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.chores);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function addChore(chore, flatId, successCallback, failureCallback) {
            var body = {flat_id: flatId,
                        chore: chore};

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

        function removeChore(chore, flatId, successCallback, failureCallback) {
            $http.delete(api + '/remove/' + flatId + '/' + chore.id).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }
    }

})();
