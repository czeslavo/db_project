(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('FlatsController', FlatsController);

    FlatsController.$inject = ['$scope', '$route', '$location', 'FlatService'];
    function FlatsController($scope, $route, $location, FlatService) {

        $scope.getUsersFlats = getUsersFlats;
        $scope.createFlat = createFlat;
        $scope.startCreating = startCreating;
        $scope.goToFlat = goToFlat;
        $scope.removeFlat = removeFlat;

        function startCreating() {
            $location.path('/flats/create');
        }

        function getUsersFlats() {
            FlatService.getUsersFlats(
                function onSuccess(resp) {
                    $scope.flats = resp.data.flats;
                    console.log(resp);
                },
                function onFailure(resp) {
                    $scope.flats = [];
                    console.log(resp);
                }
            );
        }

        function createFlat() {
            var data = {flat: $scope.flat};

            FlatService.create(data,
                function(successResp) {
                    $location.path('/flats');
                    getUsersFlats();
                    AlertsService.add("success", "Successfully created flat: " + $scope.flat.name);
                },
                function(failureResp) {
                    console.log('Couldn\'t create flat');
                });
        }

        function goToFlat(flatId) {
            $location.path('/flat/' + flatId);
        }

        function removeFlat(flatId) {
            FlatService.remove(flatId,
                function(successResp) {
                    $route.reload();
                    AlertsService.add("success", "Successfully removed flat");
                },
                function(failureResp) {

                }
            );
        }

        (function initController() {
            getUsersFlats();
        })();
    }

})();
