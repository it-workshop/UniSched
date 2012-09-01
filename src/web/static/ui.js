var objects = [];

$(document).ready(function() {
    $('.tabs').tabs();
    $('.accordion').accordion();
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
    var make_create_dialog = function($div, type, $list, name, $start) {
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
                    var object;
                    $div.find('.editable').each(function(i, v) {
                        v = $(v);
                        field[v.find('input.data-name').val()] = v.find('input.data').val();
                    });
                    $.ajax({
                        url: '/api/' + type + '/',
                        type: 'CREATE',
                        async: false,
                        success: function (data) {
                            object = data;
                        },
                        error: function (jqXHR, message, exception) {
                            object = $.parseJSON(jqXHR.responseText);
                            if (object.error) {
                                alert(object.error);
                                close_dialog();
                            }
                        }
                    });
                    $.each(field, function (k, v) {
                        $.ajax({
                            url: '/api/' + type + '/' + object.id,
                            type: 'POST',
                            async: false,
                            data: {
                                name: k,
                                value: v
                            },
                            success: function (data) {
                                object = data;
                            }
                        });
                    });
                    $list.list('append', object.id, name(object));
                    objects[object.id] = object;
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

    make_create_dialog($('#add-group'), 'group', $('#groups-list'), function (object) { return object.name; }, $('#add-group-start'));

    make_create_dialog($('#add-person'), 'person', $('#people-list'), function (object) { return object.surname + ' ' + object.name; }, $('#add-person-start'));
    
    $('#del-person').dialog({
    	autoOpen: false,
    	resizable: false,
    	modal: true,
    	buttons: {
    		'Да': function() {
    			var id = $('#people-list li[class="ui-state-active"]').attr('id');
    			$.ajax({
   					url: '/api/person/' + id,
    				type: 'DELETE',
    				success: function() {
    					$('#person-info').empty();
    					$('#people-list li[class="ui-state-active"]').remove();
	    				$('#del-person').dialog('close');
	    			}
	    		});
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
    			$.ajax({
   					url: '/api/group/' + id,
    				type: 'DELETE',
    				success: function() {
    					$('#group-info').empty();
    					$('#groups-list li[class="ui-state-active"]').remove();
	    				$('#del-group').dialog('close');
	    			}
	    		});
    		},
    		'Нет': function() {
    			$('#del-group').dialog('close');
    		}
    	}
    });
    
    $('#del-group-start').click(function() {
    	$('#del-group').dialog('open');
    	return false;
    });
    
    $('#del-person-start').click(function() {
    	$('#del-person').dialog('open');
    	return false;
    });
	
    $('#groups-list').list({change: function(event, target) {
        $('#group-info').info('set_object', objects[$(target).attr('id')]);
    }});

    $.getJSON('/api/group/', function (data) {
        $.each(data, function (i, group) {
            $('#groups-list').list('append', group.id, group.name);
            $('<input name="choose-groups" type="checkbox" value="' + group.id + '">' + group.name + '<br>').appendTo($('#choose-groups'));
            objects[group.id] = group;
        });
    });

    var make_search = function (field, list, type) {
        field.change(function(event) {
            if (field.val() == '') {
                list.children().show();
            } else {
                list.children().hide();
                $.getJSON('/api/' + type + '/?q=' + encodeURIComponent(field.val()), function (data) {
                    $.each(data, function (i, v) {
                        $('#' + v.id).show();
                    });
                });
            }
        });
    };

    make_search($('#search-group'), $('#groups-list'), 'group');
    
    $('#people-list').list({change: function(event, target) {
        $('#person-info').info('set_object', objects[$(target).attr('id')]);
    }});

    $.getJSON('/api/person/', function (data) {
        $.each(data, function (i, person) {
            $('#people-list').list('append', person.id, person.surname + ' ' + person.name);
            objects[person.id] = person;
        });
    });

    make_search($('#search-person'), $('#people-list'), 'person');
	
	$('option:first-child').attr("selected", "true");
	
	$('#add-field').click(function() {
		$('<tr class="editable">' +
			'<td><input type="text" class="data-name"></td>' +
			'<td><input type="text" class="data"></td>' +
			'<td><button class="del-field" type="button">Del</button></td>' +
			'</tr>').
			appendTo($('#add-person-form'));
		$('.del-field').click(function(event) {
			$(event.target).parents('tr').remove();
		});
	});
});

