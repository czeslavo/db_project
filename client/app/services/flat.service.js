(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('FlatService', FlatService);

    FlatService.$inject = ['$http'];
    function FlatService($http) {
        var service = {};
        var api = 'http://localhost:9090/v1/flat';

        service.getUsersFlats = getUsersFlats;
        service.create = create;
        service.remove = remove;

        return service;

        function getUsersFlats(successCallback, failureCallback) {
            return $http.get(api + '/getforuser').then(
                function(response) {
                    successCallback(response);
                    console.log(response.data);
                },
                function(response) {
                    failureCallback(response);
                }
            );
        }

        function create(data, successCallback, failureCallback) {
            return $http.post(api + '/create', data).then(
                function(response) {
                    successCallback(response);
                    console.log(response.data);
                },
                function(response) {
                    failureCallback(response);
                }
            );
        }

        function remove(id, successCallback, failureCallback) {
            return $http.delete(api + '/remove/' + id).then(
                function(response) {
                    successCallback(response);
                    console.log(response.data);
                },
                function(response) {
                    failureCallback(response);
                }
            );
        }

    }

})();
