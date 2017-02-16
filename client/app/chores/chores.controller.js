(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('ChoresController', ChoresController);

    ChoresController.$inject = ['$scope', '$route', '$routeParams', '$location', '$rootScope', 'FlatService', 'NotesService'];
    function ChoresController($scope, $route, $routeParams, $location, $rootScope, FlatService, NotesService) {
        var flatId = +$routeParams.id;

        $scope.addNote = addNote;
        $scope.removeNote = removeNote;
        $scope.updateNote = updateNote;
        $scope.goToChores = goToChores;

        function addNote() {
            var newNote = {
                content: "Please fill me.",
                author_mail: $rootScope.globals.currentUser.mail,
                date: Date.now(),
                active: true,
                flat_id: flatId
            }

            createNote(newNote);
        }

        function createNote(note) {
            NotesService.createNote(note,
                function(successResp) {
                    console.log("Added note");
                    getNotes();
                },
                function(failureResp) {
                    console.log("Failed to add note");
                }
            );
        }

        function removeNote(note) {
            NotesService.removeNote(note,
                function(successResp) {
                    console.log("Removed note");
                    getNotes();
                },
                function(failureResp) {
                    console.log("Couldn't remove note");
                }
            );
        }

        function updateNote(note) {
            NotesService.updateNote(note,
                function(successResp) {
                    console.log("Updated note");
                    getNotes();
                },
                function(failureResp) {
                    console.log("Couldn't update note");
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

        function getNotes() {
            NotesService.getFlatNotes(flatId,
                function(notes) {
                    console.log(notes);
                    for (var i = 0; i < notes.length; i++)
                    {
                        notes[i].date *= 1000;
                    }

                    $scope.notes = notes;
                },
                function(resp) {
                    console.log(resp);
                    $scope.notes = [];
                }
            );
        }

        function goToChores() {
            $location.path('/flat/' + flatId + '/chores/');
        }

        (function initController() {
            getFlatInfo();
            getNotes();
        })();
    }

})();
