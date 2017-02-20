(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('UserService', UserService);

    UserService.$inject = ['$http'];
    function UserService($http) {
        var service = {};
        var api = 'http://burzynski.it:9090/v1/user';

        service.getByMail = getByMail;
        service.register = register;
        service.login = login;

        return service;

        function login(mail, password) {
            var data = {mail: mail, password: password};
            return $http.post(api + '/login', data);
        }

        function register(user) {
            return $http.post(api + '/signup', user).then(handleSuccess, handleError('Error signing up'))
        }

        function getByMail(mail) {
            return $http.get(api + '/').then(handleSuccess, handleError('Error getting user by mail'));
        }

        // private functions

        function handleSuccess(res) {
            return res.data;
        }

        function handleError(error) {
            return function () {
                return { success: false, message: error };
            };
        }
    }

})();
