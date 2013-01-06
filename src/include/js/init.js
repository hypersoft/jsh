var jsh = {
	bit: function(n) { return (1 << (n-1)); },
	type: {},
	native: {
		library: {
			error: {},
			mode: {},
		},
		vm: {}
	},
};

jsh.type.void = 	jsh.bit(1);
jsh.type.pointer =	jsh.bit(2);
jsh.type.unsigned = jsh.bit(3);
jsh.type.value = 	jsh.bit(4);
jsh.type.bool = 	jsh.bit(5);
jsh.type.char = 	jsh.bit(6);
jsh.type.short = 	jsh.bit(7);
jsh.type.int = 		jsh.bit(8);
jsh.type.long = 	jsh.bit(9);
jsh.type.int64 = 	jsh.bit(10);
jsh.type.float = 	jsh.bit(11);
jsh.type.double = 	jsh.bit(12);

jsh.type.string = 	(jsh.type.pointer | jsh.type.char);

jsh.type.uchar = 	(jsh.type.unsigned | jsh.type.char);
jsh.type.ushort = 	(jsh.type.unsigned | jsh.type.short);
jsh.type.uint = 	(jsh.type.unsigned | jsh.type.int);
jsh.type.ulong = 	(jsh.type.unsigned | jsh.type.long);
jsh.type.uint64 = 	(jsh.type.unsigned | jsh.type.int64);

jsh.type.bool.pointer = 	(jsh.type.pointer | jsh.type.bool);
jsh.type.char.pointer = 	(jsh.type.pointer | jsh.type.char);
jsh.type.short.pointer = 	(jsh.type.pointer | jsh.type.short);
jsh.type.int.pointer = 		(jsh.type.pointer | jsh.type.int);
jsh.type.long.pointer = 	(jsh.type.pointer | jsh.type.long);
jsh.type.int64.pointer = 	(jsh.type.pointer | jsh.type.int64);
jsh.type.float.pointer = 	(jsh.type.pointer | jsh.type.float);
jsh.type.double.pointer = 	(jsh.type.pointer | jsh.type.double);

jsh.type.uchar.pointer = (jsh.type.pointer | jsh.type.unsigned | jsh.type.char);
jsh.type.ushort.pointer = (jsh.type.pointer | jsh.type.unsigned | jsh.type.short);
jsh.type.uint.pointer = (jsh.type.pointer | jsh.type.unsigned | jsh.type.int);
jsh.type.ulong.pointer = (jsh.type.pointer | jsh.type.unsigned | jsh.type.long);
jsh.type.uint64.pointer = (jsh.type.pointer | jsh.type.unsigned | jsh.type.int64);

jsh.hack = function(l) {
	try { return l; } catch(e) {
		return null;
	}
}

Gio = jsh.hack(imports.gi.Gio);
Gtk = jsh.hack(imports.gi.Gtk);
WebKit = jsh.hack(imports.gi.WebKit);
GObject = jsh.hack(imports.gi.GObject);
Gdk = jsh.hack(imports.gi.Gdk);
Pango = jsh.hack(imports.gi.Pango);

var argv = [];

(function() {
	var i=0; while (i < Seed.argv.length) ARGV[i] = Seed.argv[i++];
});

jsh;
