(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('LoginController', LoginController);

    LoginController.$inject = ['$location', 'AuthService'];
    function LoginController($location, AuthService) {
        var vm = this;

        vm.login = login;

        (function initController() {
            // reset login status
            AuthService.ClearCredentials();
        })();

        function login() {
            vm.dataLoading = true;
            AuthService.Login(vm.mail, vm.password,
                // success
                function (response) {
                    AuthService.SetCredentials(vm.mail, vm.password);
                    $location.path('/');
                // failure
                }, function(response) {
                    console.log('slabo');
                    vm.dataLoading = false;
                });

        }
    }

})();