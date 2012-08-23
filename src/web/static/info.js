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

    set_object: function (object) {
        var _self = this;
        var add = function (field, text) {
            var tr = $('<tr></tr>').appendTo(_self.element);
            var th = $('<th>' + field + '</th>').appendTo(tr);
            var td = $('<td></td>').appendTo(tr);
            var input = $('<input class="ui-corner-all">').val(text).
                change(function (event) {
                    $.ajax({
                        type: 'POST',
                        data: {
                            name: field,
                            value: $(this).val()
                        },
                        url: '/api/object/' + object.id,
                        success: function (data) {
                            objects[object.id] = data;
                        },
                        error: function (data) {
                            alert($.parseJSON(data.responseText).error);
                            input.val(text);
                        }
                    });
                }
            ).appendTo(td);
        }
        this.element.empty();
        $.each(object, function (k, val) {
            if (k == 'id' || k == 'type') {
                return true;
            }
            if (typeof(val) == 'string') {
                add(k, val);
                return true;
            }
            if (typeof(val) == 'object') {
                $('<tr><th>' + k + '</th><td>' + val.length + '</td></tr>').appendTo(_self.element);
                return true;
            }
        });
    },

    destroy: function () {
        $.Widget.prototype.destroy.call(this);
    }
});

}(jQuery));

