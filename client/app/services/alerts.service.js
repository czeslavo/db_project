(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('AlertsService', AlertsService);

    AlertsService.$inject = ['$rootScope'];
    function AlertsService($rootScope) {
        var service = {};

        $rootScope.alerts = [];

        service.add = function(type, message) {
            $rootScope.alerts.push({'type': type, 'message': message});
            console.log("In AlertSErvice add");
        };

        service.closeAlert = function(index) {
            $rootScope.alerts.splice(index, 1);
            console.log("In alert service close");
        };

        return service;
    }
})();
