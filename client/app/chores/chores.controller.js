(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('ChoresController', ChoresController);

    ChoresController.$inject = ['$scope', '$route', '$routeParams', '$location', '$rootScope', 'FlatService', 'ChoresService'];
    function ChoresController($scope, $route, $routeParams, $location, $rootScope, FlatService, ChoresService) {
        var flatId = +$routeParams.id;

        $scope.removeChore = removeChore;
        $scope.goToAddChore = goToAddChore;
        $scope.addChore = addChore;
        $scope.goToEditChore = goToEditChore;

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

        function getChores() {
            ChoresService.getFlatChores(flatId,
                function(chores) {
                    console.log(chores);
                    $scope.chores = chores;
                },
                function(resp) {
                    console.log(resp);
                    $scope.chores = [];
                }
            );
        }

        function removeChore(chore) {
            ChoresService.removeChore(chore, flatId,
                function(success) {
                    getChores();
                },
                function(failure) {
                }
            );
        }

        function goToAddChore() {
            $location.path('/flat/' + flatId + '/chores/add');
        }

        function addChore() {
            var newChore = {
                name: $scope.chore.name,
                frequency_id: $scope.chore.frequency_id,
                flat_id: flatId
            };

            ChoresService.addChore(newChore, flatId,
                function(success) {
                    $location.path('/flat/' + flatId + '/chores');
                },
                function(failure) {

                }
            );
        }

        function goToEditChore(chore_id) {
            var destinationPath = '/flat/' + flatId + '/chores/edit/' + chore_id;
            console.log(destinationPath);
            $location.path(destinationPath);
        }

        (function initController() {
            getFlatInfo();
            getChores();
        })();
    }

})();
