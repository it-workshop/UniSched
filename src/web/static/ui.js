(function() {
    Person.prototype.display_text = function () {
        return this.read('name') + ' ' + this.read('surname');
    }
    Person.prototype.on_create = function () {
        $('#people-list').list('append', this.id, this.display_text());
    }
    Person.prototype.on_update = function () {
        $('#' + this.id).text(this.display_text());
    }
    Person.prototype.on_remove = function () {
        $('#' + this.id).remove();
    }

    Group.prototype.display_text = function () {
        return this.read('name');
    }
    Group.prototype.on_create = function () {
        $('#groups-list').list('append', this.id, this.display_text());
    }
    Group.prototype.on_update = function () {
        $('#' + this.id).text(this.display_text());
    }
    Group.prototype.on_remove = function () {
        $('#' + this.id).remove();
    }
} ());

$(document).ready(function() {
    $('.tabs').tabs();
    $('.datepicker').datepicker({ dateFormat: "@" });
    $('.accordion').accordion({ fillSpace: true });
    $('.list').list();
    $('.info').info();

    $('.toolbar').children().addClass('ui-corner-all');
    $('.search').addClass('ui-widget-content').children().css('border', 'none').css('display', 'inline-block');
    $('.tool').addClass('ui-widget').addClass('ui-state-default').hover(
        function (event) {
            if ($(event.target).hasClass('ui-state-default')) {
                $(event.target).removeClass('ui-state-default').addClass('ui-state-hover');
            }
        },
        function (event) {
            if ($(event.target).hasClass('ui-state-hover')) {
                $(event.target).removeClass('ui-state-hover').addClass('ui-state-default');
            }
        });
    var make_create_dialog = function($div, type, $list, $start) {
        var close_dialog = function() {
            $div.find('.editable').remove();
            $div.find('input.default-field[type="text"]').val('');
            $div.dialog('close');
        }
        $div.dialog({
            autoOpen: false,
            resizable: false,
            modal: true,
            width: 'auto',
            buttons: {
                'OK': function () {
                    var field = {};
                    $($div.find('input.default-field[type="text"]'),
                        $div.find('input.default-field:checked')).
                        each(function (i, v) {
                        v = $(v);
                        field[v.attr('name')] = v.val();
                    });
                    $div.find('.editable').each(function(i, v) {
                        v = $(v);
                        field[v.find('input.data-name').val()] = v.find('input.data').val();
                    });
                    var object = create(type);
                    $.each(field, function (k, v) {
                        object.update(k, v);
                    });
                    close_dialog();
                },
                'Cancel': close_dialog
            }
        });
        $start.click(function(event) {
            $div.dialog('open');
        });
        $div.find('.add-field').click(function (event) {
            var tr = 
            $('<tr class=editable><th><input type=text class=data-name></th><td><input type=text class=data></td><td><button>Del</button></td></tr>').
                appendTo($div.find('table'));
            tr.find('button').click(function (event) {
                tr.remove();
            });
        });
    };

    make_create_dialog($('#add-group'), 'group', $('#groups-list'), $('#add-group-start'));

    make_create_dialog($('#add-person'), 'person', $('#people-list'), $('#add-person-start'));
    
    $('#del-person').dialog({
    	autoOpen: false,
    	resizable: false,
    	modal: true,
    	buttons: {
    		'Да': function() {
    			var id = $('#people-list li[class="ui-state-active"]').attr('id');
    			objects[id].remove();
                $('#del-person').dialog('close');
    		},
    		'Нет': function() {
    			$('#del-person').dialog('close');
    		}
    	}
    });
    
    $('#del-group').dialog({
    	autoOpen: false,
    	resizable: false,
    	modal: true,
    	buttons: {
    		'Да': function() {
    			var id = $('#groups-list li[class="ui-state-active"]').attr('id');
                objects[id].remove();
                $('#del-group').dialog('close');
    		},
    		'Нет': function() {
    			$('#del-group').dialog('close');
    		}
    	}
    });
    
    $('#del-group-start').click(function() {
    	$('#del-group').dialog('open');
    	return false;
    a
    });
    
    $('#del-person-start').click(function() {
    	$('#del-person').dialog('open');
    	return false;
    });
	
    $('#groups-list').list({change: function(event, target) {
        $('#group-info').info('set_object', objects[$(target).attr('id')]);
    }});

    var make_search = function (field, list, type) {
        field.change(function(event) {
            if (field.val() == '') {
                list.children().show();
            } else {
                list.children().hide();
                $.each(search(field.val(), type), function(i, o) {
                    list.find('#' + o.id).show();
                });
            }
        });
    };

    make_search($('#search-group'), $('#groups-list'), 'group');
    
    $('#people-list').list({change: function(event, target) {
        $('#person-info').info('set_object', objects[$(target).attr('id')]);
    }});

    make_search($('#search-person'), $('#people-list'), 'person');
});
