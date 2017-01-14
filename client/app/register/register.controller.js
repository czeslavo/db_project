(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('RegisterController', RegisterController);

    RegisterController.$inject = ['UserService', '$location', '$rootScope'];

    function RegisterController(UserService, $location, $rootScope) {
        var vm = this;

        vm.register = register;

        function register() {
            vm.dataLoading = true;
            var response = UserService.register(vm.user);
            console.log(response);
            $location.path('/login');


        }

    }

})();


