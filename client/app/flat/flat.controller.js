(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('FlatController', FlatController);

    FlatController.$inject = ['$scope', '$route', '$routeParams', '$location', 'FlatService', 'NotesService'];
    function FlatController($scope, $route, $routeParams, $location, FlatService, NotesService) {
        var flatId = $routeParams.id;

        $scope.addNote = addNote;

        function addNote() {
            $scope.notes.push({content: "Please fill and save me.",
                               author_mail: "mariusz@weq.pl",
                               date: Date.now()});
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
