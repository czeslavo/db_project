(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('AuthService', AuthService);

    AuthService.$inject = ['$http', '$cookies', '$rootScope', 'UserService', '$location'];
    function AuthService($http, $cookies, $rootScope, UserService, $location) {
        var service = {};
        var api = 'http://burzynski.it:9090/v1/user'

        service.Login = Login;
        service.SetCredentials = SetCredentials;
        service.ClearCredentials = ClearCredentials;
        service.Logout = Logout;
        service.Ping = Ping

        return service;

        function Login(mail, password, successCallback, failureCallback) {
            var data = {mail: mail, password: password};
            $http.post(api + '/login', data).then(
                function(response) {
                    $rootScope.$broadcast('userLoggedIn');
                    successCallback(response);
                },
                function(response) {
                    failureCallback(response);
                }
            );
        }

        function Logout() {
            $http.post(api + '/logout').then(
                function(successResp) {
                    console.log('Successfully logged out');
                },
                function(failureResp) {
                    console.log('Couldnt logout');
                });
            ClearCredentials();
        }

        function SetCredentials(mail, token) {
            $rootScope.globals = {
                currentUser: {
                    mail: mail,
                    token: token
                }
            };

            $http.defaults.headers.common['Auth-Token'] = mail + ':' + token;

            var cookieExp = new Date();
            cookieExp.setDate(cookieExp.getDate() + 7);
            $cookies.putObject('globals', $rootScope.globals, { expires: cookieExp });
        }

        function ClearCredentials() {
            $rootScope.globals = {};
            $cookies.remove('globals');
            $http.defaults.headers.common['Auth-Token'] = '';
            $rootScope.$broadcast('userLoggedOut');
        }

        function Ping() {
            $http.get(api + '/ping').then(
                function(success) {
                    console.log('Ping successfully');
                },
                function(failure) {
                    console.log('Ping not ok, clearing credentials');
                    ClearCredentials();
                    $location.path('/login');
                }
            );
        }
    }
})();
