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
        service.createChore = createChore;
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

        function createChore(chore, successCallback, failureCallback) {
            var body = {flat_id: chore.flat_id,
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

        function removeChore(chore, successCallback, failureCallback) {
            $http.delete(api + '/remove/' + chore.flat_id + '/' + chore.id).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.chores);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }
    }

})();
