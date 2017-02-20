(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('AlertsController', AlertsController);

    AlertsController.$inject = ['$scope', '$rootScope', 'AlertsService'];
    function AlertsController($scope, $rootScope, AlertsService) {

        $scope.closeAlert = function(index) {
            fadeOut(index, AlertsService.closeAlert);
        };

        function fadeOut(index, callback) {
            $("#alert-" + index).fadeTo(2000, 500).slideUp(500, function(){
                    $("#alert-" + index).slideUp(500);
                    callback(index);
            });
        }
    }
})();
