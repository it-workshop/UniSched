(function($) {

$.widget( "ui.list" , {

    options: {
        change: null
    },

    _create: function () {
        this.element.
            addClass('ui-widget').
            addClass('ui-corner-all').
            addClass('ui-widget-content').
            addClass('ui-helper-reset');
        this.element.children().
            addClass('ui-helper-reset').
            addClass('ui-corner-all');
        this.refresh();
    },

    refresh: function () {
        var _self = this;
        this.element.children().
            removeClass('ui-state-active').
            removeClass('ui-state-hover').
            addClass('ui-state-default').
            hover(
            function(event) {
                if ($(event.target).hasClass('ui-state-default')) {
                    $(event.target).
                        removeClass('ui-state-default').
                        addClass('ui-state-hover');
                }
            },
            function(event) {
                if ($(event.target).hasClass('ui-state-hover')) {
                    $(event.target).
                        removeClass('ui-state-hover').
                        addClass('ui-state-default');
                }
            }).click(function (event) {
                if ($(event.target).hasClass('ui-state-hover')) {
                    _self.element.children().
                        removeClass('ui-state-active').
                        addClass('ui-state-default');
                    $(event.target).
                        removeClass('ui-state-hover').
                        removeClass('ui-state-default').
                        addClass('ui-state-active');
                    _self._trigger("change", event, [event.target]);
                }
            });
    },

    _setOption: function(key, value) {
        $.Widget.prototype._setOption.apply(this, arguments);
    },

    _destroy: function () {
    },

    append: function (id, text) {
        $('<li id=' + id + '>' + text + '</li>').appendTo(this.element);
        this.refresh();
    }
});

} (jQuery));
