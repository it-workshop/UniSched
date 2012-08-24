var objects = [];

$(document).ready(function() {
    $('.tabs').tabs();
    $('.datepicker').datepicker({ dateFormat: "@" });
    $('.accordion').accordion({ fillSpace: true });
    $('.list').list();
    $('.info').info();

    $('.toolbar').children().addClass('ui-corner-all');
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
    
    $('#add-person').dialog({
    	autoOpen: false,
    	resizable: false,
    	modal: true,
    	width: 'auto',
    	buttons: {
    		'Добавить человека': function() {
                var field = {
                    name: $('#add-person-form input[name="name"]').val(),
                    surname: $('#add-person-form input[name="surname"]').val(),
                    sex: $('#add-person-form input:checked').val()
                };
                var object;
    			$('#add-person-form .editable').each(function(i, elem) {
    				field[$(elem).children('.data-name').val()] = $(elem).children('.data').val();
    			});
    			$.ajax({
    				url: '/api/person/',
    				type: 'CREATE',
                    async: false,
                    success: function (data) {
                        object = data;
                    },
                    error: function (jqXHR, message, exception) {
                        object = $.parseJSON(jqXHR.responseText);
                        if (object.error) {
                            alert(object.error);
                            $('#add-person-form .editable').remove();
                            $('#add-person').dialog('close');
                        }
                    }
    			});
                $.each(field, function (k, v) {
                    $.ajax({
                        url: '/api/person/' + object.id,
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
                $('#people-list').list('append', object.id, object.surname + ' ' + object.name);
                objects[object.id] = object;
                $('#add-person-form .editable').remove();
    			$('#add-person').dialog('close');
    		},
    		'Отмена': function() {
                $('#add-person-form .editable').remove();
    			$('#add-person').dialog('close');
    		}
    	}
    });
    
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
    
    $('#add-group').dialog({
    	autoOpen: false,
    	resizable: false,
    	modal: true,
    	buttons: {
    		'Добавить группу': function() {
    			var field = {
    				'id': Number($('#groups-list li:last').attr('id')) + 1,
    				'name': $('#add-group-form input[name="name"]').attr('value')
    			};
    			$.ajax({
   					url: '/api/group/' + field.id,
    				type: 'CREATE',
    				data: field
	    		});
	    		$('#groups-list').list('append', field.id, field.name);
            	objects[field.id] = field;
    			$('#add-group').dialog('close');
    		},
    		'Отмена': function() {
    			$('#add-group').dialog('close');
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
    
    $('#add-person-start').click(function() {
    	$('#add-person').dialog('open');
    	return false;
    });
    
    $('#del-group-start').click(function() {
    	$('#del-group').dialog('open');
    	return false;
    });
    
    $('#add-group-start').click(function() {
    	$('#add-group').dialog('open');
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
    
    $('#people-list').list({change: function(event, target) {
        $('#person-info').info('set_object', objects[$(target).attr('id')]);
    }});

    $.getJSON('/api/person/', function (data) {
        $.each(data, function (i, person) {
            $('#people-list').list('append', person.id, person.surname + ' ' + person.name);
            objects[person.id] = person;
        });
    });
	
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

	$('#search-person').keypress(function(event) {
		if (event.which == 13) {
			var search = $(event.target).attr('value').toLowerCase();
			/* Old search
			$('#people-list li:contains(' + search + ')').removeClass('ui-state-default');
			$('#people-list li:contains(' + search + ')').removeClass('ui-state-active');
			$('#people-list li:contains(' + search + ')').addClass('ui-state-hover');
			$('#people-list li:contains(' + search + ')').click();
			*/
			if (search == '') {
				objects.forEach(function(person) {
                    $('#people-list li[id=' + person.id + ']').attr('hidden', false);
				});
			}
			else {
				objects.forEach(function(person) {
					if (person.type == 'person' &&
                        search != person.name.toLowerCase() &&
						search != person.surname.toLowerCase() &&
						search != person.name.toLowerCase() + ' ' + person.surname.toLowerCase() &&
						search != person.surname.toLowerCase() + ' ' + person.name.toLowerCase()
						) {
						$('#people-list li[id=' + person.id + ']').attr('hidden', true);
					}
				});
			}
		}
	});
	
	$('#events-list').list({change: function(event, target) {
        $('#event-info').info('set_object', objects[$(target).attr('id')]);
    }});
	
	$.getJSON('/api/event/', function (data) {
        $.each(data, function (i, event) {
            $('<div id=' + event.id + '>' + event.name +
            	'<div id="start">' + event.start + '</div>' +
            	'<div id="duration">' + event.duration + '</div>' +
            	'</div>').appendTo('#timeline');
			$('#events-list').list('append', event.id, event.name);
            objects[event.id] = event;
        });
    });
});
