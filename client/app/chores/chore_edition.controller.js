(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('ChoreEditionController', ChoreEditionController);

    ChoreEditionController.$inject = ['$scope', '$route', '$routeParams', '$location', '$rootScope',
        'FlatService', 'ChoresService', 'AlertsService'];
    function ChoreEditionController($scope, $route, $routeParams, $location, $rootScope,
        FlatService, ChoresService, AlertsService) {
        var flatId = +$routeParams.id;
        var choreId = +$routeParams.chore_id;

        $scope.updateChore = updateChore;

        function getFlatInfo() {
            FlatService.getById(flatId,
                function(flat) {
                    $scope.flat = flat;
                },
                function()
                {
                    $scope.flat = {};
                }
            );
        }

        function getChore() {
            ChoresService.getChoreById(choreId,
                function(chore) {
                    console.log(chore);
                    $scope.chore = chore;
                },
                function(resp) {
                    console.log(resp);
                    $scope.chore = {};
                }
            );
        }

        function updateChore() {
            ChoresService.updateChore($scope.chore, flatId,
                function(success) {
                    AlertsService.add("success", "Successfully updated chore: " + $scope.chore.name);
                    $location.path('/flat/' + flatId + '/chores');
                },
                function(failure) {
                    AlertsService.add("danger", "Failed updating chore");
                }
            );
        }

        (function initController() {
            getFlatInfo();
            getChore();
        })();
    }

})();
