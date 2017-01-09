(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('AuthService', AuthService);

    AuthService.$inject = ['$http', '$cookies', '$rootScope', 'UserService'];
    function AuthService($http, $cookies, $rootScope, UserService) {
        var service = {};
        var api = 'http://localhost:9090/v1/user'

        service.Login = Login;
        service.SetCredentials = SetCredentials;
        service.ClearCredentials = ClearCredentials;

        return service;

        function Login(mail, password, successCallback, failureCallback) {
            var data = {mail: mail, password: password};
            $http.post(api + '/login', data).then(
                function(response) {
                    successCallback(response);
                },
                function(response) {
                    failureCallback(response);
                }
            );
        }

        function SetCredentials(mail, token) {
            $rootScope.globals = {
                currentUser: {
                    mail: mail,
                    token: token
                }
            };

            // set default auth header for http requests
            $http.defaults.headers.common['Auth-Token'] = mail + ':' + token;

            // store user details in globals cookie that keeps user logged in for 1 week (or until they logout)
            var cookieExp = new Date();
            cookieExp.setDate(cookieExp.getDate() + 7);
            $cookies.putObject('globals', $rootScope.globals, { expires: cookieExp });
        }

        function ClearCredentials() {
            $rootScope.globals = {};
            $cookies.remove('globals');
            $http.defaults.headers.common['Auth-Token'] = '';
        }
    }
})();
