
$(document).ready(function() {
    $('.tabs').tabs();
    $('.accordion').accordion();
    $('.list').list();

    $.getJSON('/api/group/', function (data) {
        $.each(data, function (i, group) {
            $('#groups-list').list('append', group.id, group.name);
        });
    });

});

