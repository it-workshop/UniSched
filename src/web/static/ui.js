var groups = [];
var people = [];

$(document).ready(function() {
    $('.tabs').tabs();
    $('.accordion').accordion();
    $('.list').list();

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
    				'id': Number($('#people-list li:last').attr('id')) + 1,
    				'name': $('#add-person-form input[name="name"]').attr('value'),
    				'surname': $('#add-person-form input[name="surname"]').attr('value'),
//    				'groups': $('#choose-groups input[checked]'),
    				'sex': $('#add-person-form input[name="sex"]["checked"]').attr('value')
    			};
    			if (field.id == "NaN") {
    				field.id = 0;
    			}
    			$('#add-person-form .editable').each(function(i, elem) {
    				field[$(elem).children('.data-name').attr('value')] = $(elem).children('.data').attr('value');
    			});
    			$.ajax({
    				url: '/api/person/' + field.id,
    				type: 'CREATE',
    				data: field
    			});
    			$('#people-list').list('append', field.id, field.surname + ' ' + field.name);
            	people[field.id] = field;
    			$('#add-person').dialog('close');
    		},
    		'Отмена': function() {
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
            	groups[field.id] = field;
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
        var group = groups[$(target).attr('id')];
        $('#group-info').empty();
        $.each(group, function (key, value) {
            if ( key != 'id' && key != 'type' ) {
                if (typeof(value) != 'object') {
                    $('<tr id=field-' + 
                        key + '><th>' + key +
                        '</th><td><input type=text class="ui-corner-all ui-widget-content" value="'+
                        value +'"></td></tr>').
                        appendTo($('#group-info'));
                } else {
                    $('<tr id=field-' +
                        key + '><th>' + key +
                        '</th><td>' + value.length + '</td></tr>').
                        appendTo($('#group-info'));
                }
            }
        });
    }});

    $.getJSON('/api/group/', function (data) {
        $.each(data, function (i, group) {
            $('#groups-list').list('append', group.id, group.name);
            $('<input name="choose-groups" type="checkbox" value="' + group.id + '">' + group.name + '<br>').appendTo($('#choose-groups'));
            groups[group.id] = group;
        });
    });
    
    $('#people-list').list({change: function(event, target) {
        var person = people[$(target).attr('id')];
        $('#person-info').empty();
        $.each(person, function (key, value) {
            if ( key != 'id' && key != 'type' ) {
                if (typeof(value) != 'object') {
                    $('<tr id=field-' + 
                        key + '><th>' + key +
                        '</th><td><input type=text class="ui-corner-all ui-widget-content" value="'+
                        value +'"></td></tr>').
                        appendTo($('#person-info'));
                } else {
                    $('<tr id=field-' +
                        key + '><th>' + key +
                        '</th><td>' + value.length + '</td></tr>').
                        appendTo($('#person-info'));
                }
            }
        });
    }});

    $.getJSON('/api/person/', function (data) {
        $.each(data, function (i, person) {
            $('#people-list').list('append', person.id, person.surname + ' ' + person.name);
            people[person.id] = person;
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
				people.forEach(function(person) {
					$('#people-list li[id=' + person.id + ']').attr('hidden', false);
				});
			}
			else {
				people.forEach(function(person) {
					if (search != person.name.toLowerCase() &&
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
});

