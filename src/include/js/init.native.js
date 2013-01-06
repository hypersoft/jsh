
jsh.library = function(path, alias) {
	// if the library does not have an "awesome" symbolic name,
	// provide an alias! The path excluding '.*' must be a valid
	// JS Identifer String
	this.path = path;
	this.alias = alias || path.slice(0, path.indexOf('.'));
	this.handle = jsh.native.library.load(path);
	this.symbol = {};
	jsh[this.alias] = this;
}

jsh.library.prototype.toString = function () {
	return this.alias;
};

jsh.library.prototype.unload = function() {
	delete this.path;
	delete jsh[this.alias];
	delete this.alias
	delete this.symbol;
	jsh.native.library.free(this.handle);
	delete this.handle;
};

jsh.library.prototype.find = function(name) {
	return new jsh.library.symbol(this, name);	
};

jsh.library.symbol = function(lib, name) {
	this.name = name;
	this.lib = lib.alias;
	this.handle = jsh.native.library.find(lib.handle, name);
	lib.symbol[name] = this;
};

jsh.library.symbol.prototype.toString = function () { return this.name; };

jsh.native.tostring = function() {
	return "function anonymous() {\n    [native code]\n}";
};

jsh.native.code = function(code) {
	var f = new Function(code);
	//f.toString = jsh.native.tostring;
	return f;
};

jsh.library.symbol.prototype.declare = function () {

	// The generated function supports automatic string buffer handling...
	// If you must obtain results from a buffer, first, create the buffer using jsh.native.buffer
	// and declare the function signature's argument type as a jsh.type.pointer...

	var returnType = arguments[0]; var i = 1;

	var body = "\n\n    var vm = jsh.native.vm.create(4096);\n";
	     body += "    var i = 0; var value; var buffer = []; var x = 0;\n\n";

	while (i < arguments.length) {
		if (arguments[i] == jsh.type.string) {
			body += "    buffer[x] = jsh.native.string(arguments[i], arguments[i++].length);\n";
			body += "    jsh.native.vm.push(vm, " + jsh.type.pointer + ", buffer[x++]);\n";
			i++;
		} else {
			body += "    jsh.native.vm.push(vm, " + arguments[i++] + ", arguments[i++]);\n";
		}
	}

	  body += '\n    value = jsh.native.vm.exec(vm, ' + returnType + ', jsh.' + this.lib + '.symbol.' + this.name + '.handle);\n\n';

	  body += '    while (buffer.length) jsh.native.release(buffer.pop());\n\n';

	  body += '    jsh.native.vm.free(vm);\n    return value;\n';

	return jsh.native.code(body);

};
