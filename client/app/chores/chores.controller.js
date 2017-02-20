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
        $scope.goToSchedule = goToSchedule;
        $scope.resetScheduleForChore = resetScheduleForChore;
        $scope.toggleChoreDone = toggleChoreDone;


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
                    getScheduledChores();
                    getRecentlyDoneChores();
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
            $location.path(destinationPath);
        }

        function goToSchedule(chore_id) {
            var destinationPath = '/flat/' + flatId + '/chores/schedule/' + chore_id;
            $location.path(destinationPath);
        }

        function getScheduledChores() {
            ChoresService.getScheduledFlatChores(flatId,
                function(chores) {
                    console.log(chores);
                    $scope.scheduledChores = chores;
                },
                function(resp) {
                    console.log(resp);
                    $scope.chores = [];
                }
            );
        }

        function getRecentlyDoneChores() {
            ChoresService.getRecentlyDoneChoresForFlat(flatId,
                function(chores) {
                    console.log(chores);
                    $scope.recentlyDoneChores = chores;
                },
                function(resp) {
                    console.log(resp);
                    $scope.recentlyDoneChores = [];
                }
            );
        }

        function resetScheduleForChore(choreId) {
            ChoresService.resetScheduleForChore(flatId, choreId,
                function(success) {
                    getScheduledChores();
                },
                function(failure) {
                }
           );
        }

        function toggleChoreDone(chore) {
            ChoresService.toggleChoreDone(flatId, chore.id, chore.date,
                function(success) {
                    getScheduledChores();
                    getRecentlyDoneChores();
                },
                function(failure) {
                }
            );
        }

        (function initController() {
            getFlatInfo();
            getChores();
            getScheduledChores();
            getRecentlyDoneChores();
        })();
    }

})();
