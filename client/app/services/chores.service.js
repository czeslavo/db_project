(function () {
    'use strict';

    angular
        .module('flatMate')
        .factory('ChoresService', ChoresService);

    ChoresService.$inject = ['$http'];
    function ChoresService($http) {
        var service = {};
        var api = 'http://localhost:9090/v1/chore';

        service.getFlatChores = getFlatChores;
        service.addChore = addChore;
        service.removeChore = removeChore;
        service.updateChore = updateChore;
        service.getChoreById = getChoreById;
        service.getScheduledFlatChores = getScheduledFlatChores;
        service.scheduleChore = scheduleChore;
        service.resetScheduleForChore = resetScheduleForChore;
        service.toggleChoreDone = toggleChoreDone;
        service.getRecentlyDoneChoresForFlat = getRecentlyDoneChoresForFlat;

        return service;

        function getFlatChores(flatId, successCallback, failureCallback) {
            $http.get(api + '/get_for_flat/' + flatId).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.chores);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function getScheduledFlatChores(flatId, successCallback, failureCallback) {
            $http.get(api + '/get_scheduled/' + flatId).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.chores);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function getRecentlyDoneChoresForFlat(flatId, successCallback, failureCallback) {
            $http.get(api + '/get_recently_done/' + flatId).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.chores);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function getChoreById(choreId, successCallback, failureCallback) {
            $http.get(api + '/get/' + choreId).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data.chore);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function addChore(chore, flatId, successCallback, failureCallback) {
            var body = {flat_id: flatId,
                        chore: chore};

            $http.post(api + '/add', body).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function removeChore(chore, flatId, successCallback, failureCallback) {
            $http.delete(api + '/remove/' + flatId + '/' + chore.id).then(
                function(successResp) {
                    console.log(successResp);
                    successCallback(successResp.data);
                },
                function(failureResp) {
                    failureCallback(failureResp);
                }
            );
        }

        function updateChore(chore, flatId, successCallback, failureCallback) {
            var body = {flat_id: flatId, chore: chore};

            $http.put(api + "/update", body).then(
                function(success) {
                    successCallback(success);
                },
                function(failure) {
                    failureCallback(failure);
                }
            );
        }

        function scheduleChore(choreId, from, to, successCallback, failureCallback) {
            var body = {from: from, to: to};

            $http.post(api + "/schedule/" + choreId, body).then(
                function(success) {
                    successCallback(success);
                },
                function(failure) {
                    failureCallback(failure);
                }
            );
        }

        function resetScheduleForChore(flatId, choreId, successCallback, failureCallback) {
            $http.put(api + "/reset_scheduled/" + flatId + "/" + choreId).then(
                function(success) {
                    successCallback(success);
                },
                function(failure) {
                    failureCallback(failure);
                }
            );
        }

        function toggleChoreDone(flatId, choreId, date, successCallback, failureCallback) {
            var target =
            $http.put(api + "/toggle_done/" + flatId + "/" + choreId + "/" + date).then(
                function(success) {
                    successCallback(success);
                },
                function(failure) {
                    failureCallback(failure);
                }
            );
        }
    }

})();
