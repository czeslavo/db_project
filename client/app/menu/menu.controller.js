(function() {
    'use strict';

    angular
        .module('flatMate')
        .controller('MenuController', MenuController);

    MenuController.$inject = ['$scope', '$rootScope', '$location', 'AuthService'];

    function MenuController($scope, $rootScope, $location, AuthService) {
        var vm = this;
        $scope.loggedIn = $rootScope.globals.currentUser ? true : false;

        $scope.logout = function() {
            AuthService.Logout();
            $scope.loggedIn = false;
            $location.path('#!/login');
        }

        $scope.$on('userLoggedIn', function() {
            console.log('handling userLoggedIn event');
            $scope.loggedIn = true;
        });

        $scope.$on('userLoggedOut', function() {
            $scope.loogedIn = false;
        });


    }
})();
