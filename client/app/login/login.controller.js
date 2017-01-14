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
            AuthService.ClearCredentials();
        })();

        function login() {
            vm.dataLoading = true;
            AuthService.Login(vm.mail, vm.password,
                function (successResponse) {
                    AuthService.SetCredentials(vm.mail, successResponse.data['apiToken']);
                    $location.path('/flats');

                }, function(failureResponse) {
                    vm.dataLoading = false;
                });

        }
    }

})();
