/*
function list(object, change) {
    object.addClass('ui-widget-content').addClass('ui-corner-bottom').addClass('ui-corner-top').
        addClass('ui-state-active').children().
            addClass('ui-state-default').hover(
                function(event){if($(event.target).hasClass('ui-state-default'))
                    $(event.target).removeClass('ui-state-default').addClass('ui-state-hover')},
                function(event){if($(event.target).hasClass('ui-state-hover'))
                    $(event.target).removeClass('ui-state-hover').addClass('ui-state-default');}).
            click(function(event){if($(event.target).hasClass('ui-state-hover')) {
                object.children().removeClass('ui-state-active').addClass('ui-state-default');
                $(event.target).removeClass('ui-state-hover').removeClass('ui-state-default').
                    addClass('ui-state-active');
                    change(event)}});
}

function add_item(object, text, id) {
    $('<div>').text(text).attr('id', id).addClass('ui-
}
*/
$(document).ready(function() {
    $('.tabs').tabs();
    $('.accordion').accordion();
    list($('.list'))

    $.getJSON('/api/group/', function (data) {
        $.each(data, function (i, group) {
            $('<div>').addClass('item').
                addClass('ui-state-default').text(group.name).appendTo($('#groups-list')).hover(
                    function(event) {$(event.target).removeClass('ui-state-default').addClass('ui-state-hover');},
                    function(event) {$(event.target).removeClass('ui-state-hover').addClass('ui-state-default');});
        });
    });

});

