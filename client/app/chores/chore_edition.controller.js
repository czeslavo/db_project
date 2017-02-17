(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('ChoreEditionController', ChoreEditionController);

    ChoreEditionController.$inject = ['$scope', '$route', '$routeParams', '$location', '$rootScope', 'FlatService', 'ChoresService'];
    function ChoreEditionController($scope, $route, $routeParams, $location, $rootScope, FlatService, ChoresService) {
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
                    $location.path('/flat/' + flatId + '/chores');
                },
                function(failure) {
                }
            );
        }

        (function initController() {
            getFlatInfo();
            getChore();
        })();
    }

})();
