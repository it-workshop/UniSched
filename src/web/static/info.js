(function ($) {

$.widget('ui.info', {

    option: {
        object: null
    },

    _create: function () {
        this.element.addClass('ui-widget-content').addClass('ui-corner-all');
    },

    _setOption: function (key, value) {
        $.Widget.prototype._setOption.apply(this, arguments);
    },

    set_object: function (object, arrays) {
        var _self = this;
        function add(field, text) {
            var tr = $('<tr></tr>').appendTo(_self.element);
            var th = $('<th>' + field + '</th>').appendTo(tr);
            var td = $('<td></td>').appendTo(tr);
            var input = $('<input class="ui-corner-all">').val(text).appendTo(td).change(function(event) {
                object.update(field, input.val());
            });
        }
        function add_lists(field, array) {
            var tr = $('<tr></tr>').appendTo(_self.element);
            var td = $('<td colspan=2></td>').appendTo(tr);
            var h = $('<h3>' + field + '</h3>').appendTo(td);
            var left_list = $('<ul class="list column"></ul>').list().appendTo(td);
            var tools = $('<div class=column></div>').appendTo(td);
            var to_right = $('<button class=tool><div class="ui-icon ui-icon-arrowthick-1-e"></button>').click(function() {
                var o2 = objects[/object-([0-9]+)/.exec(left_list.children('.ui-state-active').attr('id'))[1]];
                $.ajaxSetup({async: false});
                if (object.disconnect_way(field)) {
                    object.disconnect(o2);
                } else {
                    o2.disconnect(object);
                }
                $.ajaxSetup({async: true});
                _self.set_object(object, arrays);
            }).appendTo(tools);
            $.each(array, function (i, id) {
                left_list.list('append', 'object-' + id, objects[id].display_text());
            });
            var to_left = $('<button class=tool><div class="ui-icon ui-icon-arrowthick-1-w"></button>').click(function() {
                $.ajaxSetup({async: false});
                var o2 = objects[/object-([0-9]+)/.exec(right_list.children('.ui-state-active').attr('id'))[1]];
                if (object.disconnect_way(field)) {
                    object.connect(o2);
                } else {
                    o2.connect(object);
                }
                $.ajaxSetup({async: true});
                _self.set_object(object, arrays);
            }).appendTo(tools);
            var right_list = $('<ul class="list column"></ul>').list().appendTo(td);
            $.each(objects, function(i, o) {
                if (!(o instanceof arrays[field])) {
                    return true;
                }
                var found = false;
                $.each(array, function(i, used) {
                    if (o.id == used) {
                        found = true;
                        return false;
                    }
                });
                if (found) {
                    return true;
                }
                right_list.list('append', 'object-' + o.id, o.display_text());
            });
            refresh_tools();
        }
        this.element.empty();
        $.each(object.data, function (k, val) {
            if (typeof(val) == 'string') {
                add(k, val);
                return true;
            }
            if (typeof(val) == 'object') {
                add_lists(k, val);
                return true;
            }
        });
    },

    destroy: function () {
        $.Widget.prototype.destroy.call(this);
    }
});

}(jQuery));

