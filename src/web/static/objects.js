/* Public functions */
var create, search;

/* Public variables */
var objects = [];

/* Public classes */
var Person, Group, Event;

/* Public Functions:
 * create(type), type = 'person' || 'group' || 'event'
 * search(q[, type]), typeof q = 'string' || 'object'
 *
 * Object methods:
 * update(name, value)
 * read(name)
 * connect(o)
 * disconnect(o)
 * remove()
 *
 * Object private methods:
 * linkfield(o);
 * backlinkfield(o);
 * disconnect_way(name);
 * 
 * Object callbacks:
 * on_create
 * on_update
 * on_connect
 * on_disconnect
 * on_remove
 */

/* Conclusion */
(function () {
    /* settings */
    var api_prefix = '/api/';

    /* private variables */
    var patches = [];


    /* private functions */
    function run_callback(o, callback) {
        if (callback && callback instanceof Function) {
            callback.call(o);
        }
    }
    function do_create(type, id) {
        var o;
        console.log('<- create(' + type + ', ' + id + ')');
        switch(type) {
        case 'person':
            o = new Person(id);
            break;
        case 'group':
            o = new Group(id);
            break;
        case 'event':
            o = new Event(id);
            break;
        }
        run_callback(o, o.on_create);
        objects[id] = o;
        return o;
    }

    function do_connect(o1, o2) {
        console.log('<- connect(' + o1.id + ', ' + o2.id + ')');
        var to_name = o1.linkfield(o2);
        var from_name = o2.backlinkfield(o1);
        var found = false;
        $.each(o1.data[to_name], function(i, o) {
            if (o == o2) {
                found = true;
                return false;
            }
        });
        if (found) {
            return;
        }
        o1.data[to_name].push(o2.id);
        o2.data[from_name].push(o1.id);
        run_callback(o1, o1.on_connect);
        run_callback(o2, o2.on_connect);
    }
    function do_disconnect(o1, o2) {
        console.log('<- disconnect(' + o1.id + ', ' + o2.id + ')');
        var to_name = o1.linkfield(o2);
        var from_name = o2.backlinkfield(o1);
        var found = false;
        $.each(o1.data[to_name], function(i, o) {
            if (o == o2.id) {
                found = true;
                o1.data[to_name].splice(i, 1);
                return false;
            }
        });
        if (!found) {
            return;
        }
        $.each(o2.data[from_name], function (i, o) {
            if (o == o1.id) {
                o2.data[from_name].splice(i, 1);
            }
        });
        run_callback(o1, o1.on_disconnect);
        run_callback(o2, o2.on_disconnect);
    }
    function do_remove(o) {
        console.log('<- remove(' + o.id + ')');
        objects[o.id] = undefined;
        $.each(o.data, function(k, v) {
            if (v instanceof Array) {
                if (o.disconnect_way(k)) {
                    $.each(v, function(i, id) {
                        do_disconnect(o, objects[id]);
                    });
                } else {
                    $.each(v, function(i, id) {
                        do_disconnect(objects[id], o);
                    });
                }
            }
        });
        run_callback(o, o.on_remove);
        delete o;
    }
    function do_update(o, name, value) {
        console.log('<- update(' + o.id + ', ' + name + ', ' + value + ')');
        o.data[name] = value;
        run_callback(o, o.on_update);
    }

    /* Conclusion */
    (function () {
        /* Private functions */

        /* Private classes */
        function Obj() {
        }
        Obj.prototype = {
            update: function(name, value) {
                if (!name || !value) {
                    return;
                }
                console.log('-> update(' + this.id + ', ' + name + ', ' + value + ')');
                var _self = this;
                $.ajax({
                    type: 'POST',
                    url: api_prefix + 'object/' + _self.id,
                    data: {
                        name: name,
                        value: value
                    },
                    success: function (data) {
                        do_update(_self, name, data[name]);
                        patches.push({
                            method: 'update',
                            object: _self.id,
                            name: name,
                            value: data[name]
                        });
                    }
                });
            },
            read: function(name) {
                return this.data[name];
            },
            connect: function(o, connect) {
                if (!(o instanceof Obj)) {
                    return;
                }
                connect = connect == undefined ? true : connect;
                var _self = this;
                console.log('-> connect(' + this.id + ', ' + o.id + ', ' + connect + ')');
                $.ajax({
                    type: connect ? 'LINK' : 'UNLINK',
                    url: api_prefix + 'object/' + _self.id,
                    headers: {
                        Location: api_prefix + 'object/' + o.id
                    },
                    success: function () {
                        if (connect) {
                            do_connect(_self, o);
                        } else {
                            do_disconnect(_self, o);
                        }
                        patches.push({
                            method: 'connect',
                            connect: connect,
                            object: _self.id,
                            'with': o.id
                        });
                    }
                });
            },
            disconnect: function(o) {
                this.connect(o, false);
            },
            remove: function() {
                var _self = this;
                console.log('-> remove(' + this.id + ')');
                $.ajax({
                    type: 'DELETE',
                    url: api_prefix + 'object/' + _self.id,
                    success: function () {
                        patches.push({
                            method: 'remove',
                            object: _self.id
                        });
                        do_remove(_self);
                    }
                });
            }
        };
        function AbstractGroup() {
        }
        AbstractGroup.prototype = new Obj();
        AbstractGroup.prototype.linkfield = function(o) {
            if (o instanceof Person) {
                return 'people';
            }
            if (o instanceof Group) {
                return 'children_groups';
            }
        }
        AbstractGroup.prototype.backlinkfield = function(o) {
            if (o instanceof Person) {
                return 'people';
            }
        }
        AbstractGroup.prototype.disconnect_way = function(name) {
            return true;
        }

        /* Public classes */
        Person = function (id) {
            this.id = id;
            this.data = {};
        }
        Person.prototype = new Obj();
        Person.prototype.linkfield = function(o) {
            if (o instanceof AbstractGroup) {
                return 'groups'
            }
        }
        Person.prototype.backlinkfield = Person.prototype.linkfield;
        Person.prototype.disconnect_way = function(name) {
            return true;
        }
        Group = function (id) {
            this.id = id;
            this.data = {};
        }
        Group.prototype = new AbstractGroup();
        Group.prototype.backlinkfield = function(o) {
            if (o instanceof AbstractGroup) {
                return 'parent_groups';
            }
            return this.prototype.backlinkfield.call(this, o);
        }
        Group.prototype.disconnect_way = function(name) {
            return name != 'parent_groups';
        }
        Event = function (id) {
            this.id = id;
            this.data = {};
        }
        Event.prototype = new AbstractGroup();
    } ());

    /* public functions */
    create = function(type) {
        var o;
        console.log('-> create(' + type +')');
        $.ajax({
            async: false,
            type: 'CREATE',
            url: api_prefix + type,
            success: function (data) {
                o = do_create(data.type, data.id);
                patches.push({
                    method: 'create',
                    object: o.id,
                    type: data.type
                });
            }
        });
        return o;
    }
    search = function(q, type) {
        if (type == undefined) {
            type = 'object';
        }
        var request = '/?';
        if (typeof q == 'string') {
            request += 'q=' + q;
        }
        var res = [];
        $.ajax({
            async: false,
            url: api_prefix + type + request,
            success: function(data) {
                $.each(data, function(i, o) {
                    res.push(objects[o.id]);
                });
            }
        });
        return res;
    }

    /* loading */
    $(document).ready(function() {
        $.getJSON(api_prefix + 'object', function(data) {
            $.each(data, function(i, obj) {
                var o = do_create(obj.type, obj.id);
                o.data = obj;
                obj.id = undefined;
                obj.type = undefined;
                run_callback(o, o.on_update);
            });
        });
        var state;
        $.getJSON(api_prefix + 'log', function(data) {
            state = data.length + 1;
        });
        $(document).everyTime('15s', 'update-timer', function (i) {
            console.log('-> log(' + state + ')');
            $.getJSON(api_prefix + 'log/' + state, function (data) {
                $.each(data, function(i, patch) {
                    var found = false;
                    $.each(patches, function(i, v) {
                        if (patch.method == v.method
                            && patch.object == v.object) {
                            switch(patch.method) {
                            case 'create':
                            case 'remove':
                                found = true;
                                break;
                            case 'update':
                                if (patch.name == v.name
                                    && patch.value == v.value) {
                                    found = true;
                                }
                                break;
                            case 'connect':
                                if (patch.connect == v.connect
                                    && patch['with'] == v['with']) {
                                    return true;
                                }
                                break;
                            }
                            if (found) {
                                patches.splice(i, 1);
                                return false;
                            }
                        }
                    });
                    if (found) {
                        return true;
                    }
                    var o = objects[patch.object];
                    switch(patch.method) {
                    case 'create':
                        do_create(patch.type, patch.object);
                        break;
                    case 'remove':
                        do_remove(o);
                        break;
                    case 'update':
                        do_update(o, patch.name, patch.value);
                        break;
                    case 'connect':
                        if (patch.connect) {
                            do_connect(o, objects[patch['with']]);
                        } else {
                            do_disconnect(o, objects[patch['with']]);
                        }
                    }
                });
                state += data.length;
            });
        });
    });
} ());
