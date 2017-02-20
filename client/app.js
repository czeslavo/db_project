(function () {
    'use strict';

    angular
        .module('flatMate', ['ngRoute', 'ngCookies', 'ui.bootstrap'])
        .config(config)
        .run(run);

    config.$inject = ['$routeProvider', '$locationProvider'];
    function config($routeProvider, $locationProvider) {
        $routeProvider
            .when('/flats', {
                controller: 'FlatsController',
                templateUrl: 'app/flat/flats.view.html'
            })

            .when('/flats/create', {
                controller: 'FlatsController',
                templateUrl: 'app/flat/create_flat.view.html'
            })

            .when('/flat/:id', {
                controller: 'FlatController',
                templateUrl: 'app/flat/flat.view.html'
            })

            .when('/flat/:id/chores', {
                controller: 'ChoresController',
                templateUrl: 'app/chores/chores.view.html'
            })

            .when('/flat/:id/chores/add', {
                controller: 'ChoresController',
                templateUrl: 'app/chores/add_chore.view.html'
            })

            .when('/flat/:id/chores/edit/:chore_id', {
                controller: 'ChoreEditionController',
                templateUrl: 'app/chores/edit_chore.view.html'
            })

            .when('/flat/:id/chores/schedule/:chore_id', {
                controller: 'ScheduleController',
                templateUrl: 'app/chores/schedule.view.html'
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

    run.$inject = ['$rootScope', '$location', '$cookies', '$http', 'AuthService'];
    function run($rootScope, $location, $cookies, $http, AuthService) {
        $rootScope.globals = $cookies.getObject('globals') || {};
        console.log('in run function');
        if ($rootScope.globals.currentUser) {
            $http.defaults.headers.common['Auth-Token'] = $rootScope.globals.currentUser.mail + ':' +
                $rootScope.globals.currentUser.token;
        }

        $rootScope.$on('$locationChangeStart', function (event, next, current) {
            var restrictedPage = $.inArray($location.path(), ['/login', '/register']) === -1;

            if (restrictedPage) {
                AuthService.Ping();
            }

            var loggedIn = $rootScope.globals.currentUser;
            if (restrictedPage && !loggedIn) {
                $location.path('/login');
            }
        });

        $rootScope.$on('userLoggedOut', function(event, next, current) {
            $location.path('/login');
        });
    }
})();
