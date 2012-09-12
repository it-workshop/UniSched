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
            var input = $('<input class="ui-corner-all">').val(text).appendTo(td).change(function(event) {
                object.update(field, input.val());
            });
        }
        this.element.empty();
        $.each(object.data, function (k, val) {
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

