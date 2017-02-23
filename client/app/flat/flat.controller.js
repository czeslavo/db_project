(function () {
    'use strict';

    angular
        .module('flatMate')
        .controller('FlatController', FlatController);

    FlatController.$inject = ['$scope', '$route', '$routeParams', '$location', '$rootScope', 'FlatService',
        'NotesService', 'ChoresService'];
    function FlatController($scope, $route, $routeParams, $location, $rootScope, FlatService, NotesService,
        ChoresService) {
        var flatId = +$routeParams.id;

        $scope.addNote = addNote;
        $scope.removeNote = removeNote;
        $scope.updateNote = updateNote;
        $scope.goToChores = goToChores;
        $scope.addFlatMate = addFlatMate;

        $scope.newFlatMate = {
            mail: ""
        };

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

        function checkIfIsFlatAdmin() {
            FlatService.isFlatAdmin(flatId,
                function(success) {
                    $scope.isFlatAdmin = success.data.isAdmin;
                },
                function (failure) {
                    $scope.isFlatAdmin = false;
                }
            );
        }

        function getFlatUsers() {
            FlatService.getFlatUsers(flatId,
                function(success) {
                    $scope.users = success.data.users;
                },
                function(failure) {
                    $scope.users = [];
                }
            );
        }

        function addFlatMate() {
            FlatService.addFlatUser(flatId, $scope.newFlatMate.mail,
                function(success) {
                    getFlatUsers();
                    AlertsService.add("success", "Successfully added flat mate: " + $scope.newFlatMate.mail);
                },
                function(failure) {
                    AlertsService.add("danger", "Failed to add flat mate: " + $scope.newFlatMate.mail + ". New flat mate has to already registered.");
                }
            );
        }

        function getScheduledChores() {
            ChoresService.getScheduledFlatChores(flatId,
                function(chores) {
                    console.log(chores);
                    $scope.choresToDo = chores;
                },
                function(resp) {
                    console.log(resp);
                    $scope.choresToDo = [];
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

        (function initController() {
            getFlatInfo();
            getNotes();
            checkIfIsFlatAdmin();
            getFlatUsers();
            getScheduledChores();
            getRecentlyDoneChores();
        })();
    }

})();
