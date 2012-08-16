var groups = [];
var people = [];

$(document).ready(function() {
    $('.tabs').tabs();
    $('.accordion').accordion();
    $('.list').list();
    
    $('#add-person').dialog({
    	autoOpen: false,
    	resizable: false,
    	modal: true,
    	width: 'auto',
    	buttons: {
    		'Добавить человека': function() {
//    			$.ajax({
//    				url: '/api/person/',
//    				type: 'CREATE',
//    				data: {
//    				}
//    				});
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
//    			$.ajax({
//   				url: '/api/person/' + id,
//    				type: "DELETE",
//    				success: function() {
//	    				$('#del-person').dialog('close');
//	    			}
//	    		});
    		},
    		'Нет': function() {
    			$('#del-person').dialog('close');
    		}
    	}
    });
    
    $('#add-person-start').click(function() {
    	$('#add-person').dialog('open');
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
            $('<option value="' + group.id + '">' + group.name + '</option>').appendTo($('#link-group'));
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
		$('<tr>' +
			'<td><input type="text" class="data-name"></td>' +
			'<td><input type="text" name="empty"></td>' +
			'<td><button class="del-field" type="button">Del</button></td>' +
			'</tr>').
			appendTo($('#add-person-form'));
		$('.del-field').click(function(event) {
			$(event.target).parents('tr').remove();
		});
	});
});

