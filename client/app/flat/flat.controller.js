(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('FlatController', FlatController);

    FlatController.$inject = ['$scope', '$location', 'FlatService'];
    function FlatController($scope, $location, FlatService) {

        $scope.getUsersFlats = getUsersFlats;
        $scope.createFlat = createFlat;
        $scope.startCreating = startCreating;

        function startCreating() {
            $location.path('/flat/create');
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
                },
                function(failureResp) {
                    console.log('Couldn\'t create flat');
                });
        }

        (function initController() {
            getUsersFlats();
        })();
    }

})();
