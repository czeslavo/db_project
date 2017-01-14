(function () {
    'use strict';

    angular
        .module('flatMate', ['ngRoute', 'ngCookies'])
        .config(config)
        .run(run);

    config.$inject = ['$routeProvider', '$locationProvider'];
    function config($routeProvider, $locationProvider) {
        $routeProvider
            .when('/flats', {
                controller: 'FlatController',
                templateUrl: 'app/flat/flats.view.html'
            })

            .when('/flat/:id', {
                controller: 'FlatController',
                templateUrl: 'app/flat/flat.view.html'
            })

            .when('/flat/create', {
                controller: 'FlatController',
                templateUrl: 'app/flat/create_flat.view.html'
            })

            .when('/login', {
                controller: 'LoginController',
                templateUrl: 'app/login/login.view.html',
                controllerAs: 'vm'
            })

            .when('/register', {
                controller: 'RegisterController',
                templateUrl: 'app/register/register.view.html',
                controllerAs: 'vm'
            })

            .otherwise({ redirectTo: '/login' });
    }

    run.$inject = ['$rootScope', '$location', '$cookies', '$http'];
    function run($rootScope, $location, $cookies, $http) {
        $rootScope.globals = $cookies.getObject('globals') || {};
        console.log('in run function');
        if ($rootScope.globals.currentUser) {
            $http.defaults.headers.common['Auth-Token'] = $rootScope.globals.currentUser.mail + ':' +
                $rootScope.globals.currentUser.token;
        }

        $rootScope.$on('$locationChangeStart', function (event, next, current) {
            var restrictedPage = $.inArray($location.path(), ['/login', '/register']) === -1;
            var loggedIn = $rootScope.globals.currentUser;
            if (restrictedPage && !loggedIn) {
                $location.path('/login');
            }
        });
    }

})();
