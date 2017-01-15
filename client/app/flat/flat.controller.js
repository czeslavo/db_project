(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('FlatController', FlatController);

    FlatController.$inject = ['$scope', '$routeParams', '$location', 'FlatService', 'NotesService'];
    function FlatController($scope, $routeParams, $location, FlatService, NotesService) {
        var flatId = $routeParams.id;

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

        function getNotes() {
            NotesService.getFlatNotes(flatId,
                function(notes) {
                    console.log(notes);
                    $scope.notes = notes;
                },
                function(resp) {
                    console.log(resp);
                    $scope.notes = [];
                }
            );
        };

        (function initController() {
            getFlatInfo();
            getNotes();
        })();
    }

})();
