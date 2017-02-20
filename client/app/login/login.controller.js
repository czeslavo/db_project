(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('LoginController', LoginController);

    LoginController.$inject = ['$location', 'AuthService', 'AlertsService'];
    function LoginController($location, AuthService, AlertsService) {
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
                    AlertsService.add("success", "Successfully logged in. Welcome " + vm.mail + "!");

                }, function(failureResponse) {
                    vm.dataLoading = false;
                    AlertsService.add("danger", "Couldn't log in: " + failureResponse.data['response']);
                });

        }
    }

})();
