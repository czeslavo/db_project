(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('ScheduleController', ScheduleController);

    ScheduleController.$inject = ['$scope', '$route', '$routeParams', '$location', '$rootScope', 'FlatService',
        'ChoresService', 'uibDateParser', 'AlertsService'];
    function ScheduleController($scope, $route, $routeParams, $location, $rootScope, FlatService, ChoresService,
        uibDateParser, AlertsService) {
        var flatId = +$routeParams.id;
        var choreId = +$routeParams.chore_id;

        $scope.schedule = schedule;
        $scope.openTo = openTo;
        $scope.openFrom = openFrom;

        $scope.popupFrom = {
            opened: false
        };

        $scope.popupTo = {
            opened: false
        };

        $scope.format = 'dd-MM-yyyy';

        $scope.dateOptions = {
            formatYear: 'yyyy',
            maxDate: new Date(2020, 5, 22),
            minDate: new Date(),
            startingDay: 1
        };

        function openFrom() {
            $scope.popupFrom.opened = true;
        }

        function openTo() {
            $scope.popupTo.opened = true;
        }

        function schedule() {
            var from = Math.round($scope.from / 1000);
            var to = Math.round($scope.to / 1000);

            ChoresService.scheduleChore(choreId, from, to,
                function(success) {
                    console.log(success);
                    $location.path('/flat/' + flatId + '/chores');
                    AlertsService.add("success", "Successfully scheduled chore: " + $scope.chore.name);
                },
                function(failure) {
                    console.log(failure);
                }
            );
        }

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

        (function initController() {
            getFlatInfo();
            getChore();
        })();
    }

})();
