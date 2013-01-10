/* REQUIRES <stdlib.h> */

/*

	Things to do

		1. Work towards an immutable API
		2. Structure support
		3. Callback support

*/

// This is used to de-reference a pointer as the desired type
#define DEREFAS(T, V) *((T*)V)

#define BIT(n) (1 << (n - 1))

typedef enum JSH_TYPE {

	JSH_TYPE_VOID = 		BIT(1),	// RETURN TYPE ONLY
	JSH_TYPE_POINTER = 		BIT(2),	// VOID POINTER
	JSH_TYPE_UNSIGNED =		BIT(3),
	JSH_TYPE_VALUE =		BIT(4), // ELLIPSIS ARGUMENTS *COULD* CARRY THIS BIT
	JSH_TYPE_BOOL =			BIT(5),
	JSH_TYPE_CHAR =			BIT(6),
	JSH_TYPE_SHORT =		BIT(7), // emulated, Seed has not this type
	JSH_TYPE_INT =			BIT(8),
	JSH_TYPE_LONG =			BIT(9),
	JSH_TYPE_LONG_LONG =	BIT(10),
	JSH_TYPE_FLOAT =		BIT(11),
	JSH_TYPE_DOUBLE =		BIT(12),

	// COMPLEX TYPES
	JSH_TYPE_UNSIGNED_CHAR =		(JSH_TYPE_CHAR | JSH_TYPE_UNSIGNED),
	JSH_TYPE_UNSIGNED_SHORT = 		(JSH_TYPE_SHORT | JSH_TYPE_UNSIGNED),
	JSH_TYPE_UNSIGNED_INT = 		(JSH_TYPE_INT | JSH_TYPE_UNSIGNED),
	JSH_TYPE_UNSIGNED_LONG = 		(JSH_TYPE_LONG | JSH_TYPE_UNSIGNED),
	JSH_TYPE_UNSIGNED_LONG_LONG = 	(JSH_TYPE_LONG_LONG | JSH_TYPE_UNSIGNED),

	JSH_TYPE_BOOL_POINTER =			(JSH_TYPE_BOOL | JSH_TYPE_POINTER),
	JSH_TYPE_CHAR_POINTER =			(JSH_TYPE_CHAR | JSH_TYPE_POINTER),
	JSH_TYPE_SHORT_POINTER =		(JSH_TYPE_SHORT | JSH_TYPE_POINTER),
	JSH_TYPE_INT_POINTER =			(JSH_TYPE_INT | JSH_TYPE_POINTER),
	JSH_TYPE_LONG_POINTER =			(JSH_TYPE_LONG | JSH_TYPE_POINTER),
	JSH_TYPE_LONG_LONG_POINTER =	(JSH_TYPE_LONG_LONG | JSH_TYPE_POINTER),
	JSH_TYPE_FLOAT_POINTER =		(JSH_TYPE_FLOAT | JSH_TYPE_POINTER),
	JSH_TYPE_DOUBLE_POINTER =		(JSH_TYPE_DOUBLE | JSH_TYPE_POINTER),

	JSH_TYPE_UNSIGNED_CHAR_POINTER = 		(JSH_TYPE_CHAR | JSH_TYPE_UNSIGNED | JSH_TYPE_POINTER),
	JSH_TYPE_UNSIGNED_SHORT_POINTER = 		(JSH_TYPE_SHORT | JSH_TYPE_UNSIGNED | JSH_TYPE_POINTER),
	JSH_TYPE_UNSIGNED_INT_POINTER = 		(JSH_TYPE_INT | JSH_TYPE_UNSIGNED | JSH_TYPE_POINTER),
	JSH_TYPE_UNSIGNED_LONG_POINTER = 		(JSH_TYPE_LONG | JSH_TYPE_UNSIGNED | JSH_TYPE_POINTER),
	JSH_TYPE_UNSIGNED_LONG_LONG_POINTER = 	(JSH_TYPE_LONG_LONG | JSH_TYPE_UNSIGNED | JSH_TYPE_POINTER),

	// SPECIAL TYPES
	JSH_TYPE_STRING =	(JSH_TYPE_CHAR | JSH_TYPE_POINTER),

	// COMPOUND TYPES (STRUCT, UNION): UNSUPPORTED, WRAP THEM IN A LIB FOR BEST USE
	// AVOID STRUCTS AS RETURN TYPES AND PARAMETERS. USE POINTERS INSTEAD.

	// FUTURE RESOLUTIONS ARE POSSIBLE, YET NOT A WORTHY EFFORT OF A CONCEPT PROTOTYPE

} JSH_TYPE;

int jsh_native_internal_type_size(int type) {

	if (type & JSH_TYPE_POINTER) return sizeof(void *);
	else if (type & JSH_TYPE_BOOL) return sizeof(bool);
	else if (type & JSH_TYPE_CHAR) return sizeof(char);
	else if (type & JSH_TYPE_SHORT) return sizeof(short);
	else if (type & JSH_TYPE_INT) return sizeof(int);
	else if (type & JSH_TYPE_LONG) return sizeof(long);
	else if (type & JSH_TYPE_LONG_LONG) return sizeof(long long);
	else if (type & JSH_TYPE_FLOAT) return sizeof(float);
	else if (type & JSH_TYPE_DOUBLE) return sizeof(double);

}

JSValueRef jsh_native_internal_unbuffer_pointer(SeedContext ctx, int type, void * value) {

	if (type & JSH_TYPE_POINTER) return seed_make_pointer(ctx, DEREFAS(void *, value));
	else if (type & JSH_TYPE_BOOL) return JSValueMakeBoolean(ctx, DEREFAS(bool, value));
	else if (type & JSH_TYPE_FLOAT) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(float, value));
	else if (type & JSH_TYPE_DOUBLE) return JSValueMakeNumber(ctx, DEREFAS(double, value));			
	else if (type & JSH_TYPE_UNSIGNED) {
		if (type & JSH_TYPE_CHAR) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(unsigned char, value));
		else if (type & JSH_TYPE_SHORT) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(unsigned short, value));
		else if (type & JSH_TYPE_INT) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(unsigned int, value));
		else if (type & JSH_TYPE_LONG) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(unsigned long, value));
		else if (type & JSH_TYPE_LONG_LONG) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(unsigned long long, value));
	} else {
		if (type & JSH_TYPE_CHAR) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(char, value));
		else if (type & JSH_TYPE_SHORT) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(short, value));
		else if (type & JSH_TYPE_INT) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(int, value));
		else if (type & JSH_TYPE_LONG) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(long, value));
		else if (type & JSH_TYPE_LONG_LONG) return JSValueMakeNumber(ctx, (gdouble) DEREFAS(long long, value));
	}

}

// returns a caller owned pointer of the specified type and optional count
SeedValue jsh_native_buffer(SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if ( argumentCount != 2 ) return seed_make_null(ctx);

	SeedValue result = NULL;	// what we will return with

	void * buffer = NULL; // where we will write the new buffer

	unsigned long elements = 1, size = 0;

	unsigned int type = seed_value_to_int(ctx, arguments[0], exception);

	if ( argumentCount == 2 ) {
		elements = seed_value_to_long(ctx, arguments[1], exception);
	}

	// get the type size
	size = jsh_native_internal_type_size(type);

	if (elements && size) {

		buffer = g_malloc((elements * size));
		result = seed_make_pointer(ctx, buffer);

		// this property tells us what type of data is held in the buffer
		seed_object_set_property(ctx, result, "type",
			seed_value_from_int(ctx, type, exception)
		);
		// this property tells us how to "unbuffer" the data: 1 value, > 1 array
		seed_object_set_property(ctx, result, "elements",
			seed_value_from_int(ctx, elements, exception)
		);

		return result;

	} else return seed_make_pointer(ctx, NULL);

}

SeedValue jsh_native_unbuffer(SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if ( argumentCount != 1 ) return seed_make_null(ctx);

	void * buffer = seed_pointer_get_pointer(ctx, arguments[0]);

	if ( ! buffer ) return seed_make_undefined(ctx);

	unsigned int type = seed_value_to_int(ctx, 
		seed_object_get_property(ctx, arguments[0], "type"), exception
	);

	/* unset pointer bit on strings to convert to char[] */
	if (type & JSH_TYPE_STRING) type &= ~JSH_TYPE_POINTER;

	register unsigned long elements = seed_value_to_long(ctx, 
		seed_object_get_property(ctx, arguments[0], "elements"), exception
	),  index = 0, size = jsh_native_internal_type_size(type);

	SeedValue element[elements];

	while (index < elements) {
		element[index++] = (const SeedValue) jsh_native_internal_unbuffer_pointer(ctx, type, buffer + (index * size));
	}

	free(buffer);

	return seed_make_array(ctx, element, elements, NULL);
	
}

// This is needed in cases where the buffer is trash and unbuffering is not needed
SeedValue jsh_native_release(SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	g_free(seed_pointer_get_pointer(ctx, arguments[0]));

	return seed_make_undefined(ctx);

}

SeedValue jsh_native_string(SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	void * buffer = seed_value_to_string(ctx, arguments[0], NULL);

	SeedValue result = seed_make_pointer(ctx, buffer);

	// this property tells us what type of data is held in the buffer
	seed_object_set_property(ctx, result, "type",
		seed_value_from_int(ctx, JSH_TYPE_STRING, exception)
	);

	// this property tells us how to "unbuffer" the data: 1 value, > 1 array
	seed_object_set_property(ctx, result, "elements",
		seed_object_get_property(ctx, arguments[0], "length")
	);

	return result;

}

SeedValue jsh_native_unstring(SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 2) return seed_make_null(ctx);

	unsigned long size = seed_value_to_long(ctx, 
		seed_object_get_property(ctx, arguments[0], "elements"), exception
	);

	void * buffer = seed_pointer_get_pointer(ctx, arguments[0]);

	SeedValue result = seed_value_from_binary_string(ctx, buffer, size, NULL);

	free(buffer);
	return result;

}

SeedValue jsh_native_library_load (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	gchar * path = seed_value_to_string(ctx, arguments[0], exception);

	SeedValue result = seed_make_pointer(ctx, dlLoadLibrary(path));

	g_free(path);

	return result;

}

SeedValue jsh_native_library_free (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	void * p = seed_pointer_get_pointer(ctx, arguments[0]);

	dlFreeLibrary(p);

	return seed_make_undefined(ctx);

}

SeedValue jsh_native_library_find (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 2) return seed_make_null(ctx);

	void * lib = seed_pointer_get_pointer(ctx, arguments[0]);
	gchar * symbol = seed_value_to_string(ctx, arguments[1], exception);

	SeedValue result = seed_make_pointer(ctx, dlFindSymbol(lib, symbol));

	g_free(symbol);

	return result;

}

void jsh_native_define_library(SeedContext ctx, SeedObject object, SeedException * exception) {
	jsh_register_native(ctx, object, "load", jsh_native_library_load, exception);
	jsh_register_native(ctx, object, "free", jsh_native_library_free, exception);
	jsh_register_native(ctx, object, "find", jsh_native_library_find, exception);
}

SeedValue jsh_native_vm_create (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	long size = seed_value_to_long(ctx, arguments[0], exception);

	return seed_make_pointer(ctx, dcNewCallVM(size));

}

SeedValue jsh_native_vm_free (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	void * vm = seed_pointer_get_pointer(ctx, arguments[0]);

	dcFree(vm);

	return seed_make_undefined(ctx);

}

SeedValue jsh_native_vm_error (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	void * vm = seed_pointer_get_pointer(ctx, arguments[0]);

	return seed_value_from_int(ctx, dcGetError(vm), exception);

}

SeedValue jsh_native_vm_mode (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 2) return seed_make_null(ctx);

	void * vm = seed_pointer_get_pointer(ctx, arguments[0]);
	int mode = seed_value_to_int(ctx, arguments[1], exception);

	dcMode(vm, mode);

	return seed_make_undefined(ctx);

}

SeedValue jsh_native_vm_reset (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 1) return seed_make_null(ctx);

	void * vm = seed_pointer_get_pointer(ctx, arguments[0]);

	dcReset(vm);

	return seed_make_undefined(ctx);

}

SeedValue jsh_native_vm_push (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 3) return seed_make_null(ctx);

	void * vm = seed_pointer_get_pointer(ctx, arguments[0]);
	int type = seed_value_to_int(ctx, arguments[1], exception);

	if (type & JSH_TYPE_POINTER) dcArgPointer(vm, seed_pointer_get_pointer(ctx, arguments[2]));
	else if (type & JSH_TYPE_BOOL) dcArgBool(vm, seed_value_to_boolean(ctx, arguments[2], exception));
	else if (type & JSH_TYPE_FLOAT) dcArgFloat(vm, seed_value_to_float(ctx, arguments[2], exception));
	else if (type & JSH_TYPE_DOUBLE) dcArgDouble(vm, seed_value_to_double(ctx, arguments[2], exception));		
	else if (type & JSH_TYPE_CHAR) dcArgChar(vm, seed_value_to_char(ctx, arguments[2], exception));
	else if (type & JSH_TYPE_SHORT) dcArgShort(vm, (short) seed_value_to_int(ctx, arguments[2], exception));
	else if (type & JSH_TYPE_INT) dcArgInt(vm, seed_value_to_int(ctx, arguments[2], exception));
	else if (type & JSH_TYPE_LONG) dcArgLong(vm, seed_value_to_long(ctx, arguments[2], exception));
	else if (type & JSH_TYPE_LONG_LONG) dcArgLongLong(vm, seed_value_to_int64(ctx, arguments[2], exception));

	return seed_make_undefined(ctx);

}

JSValueRef jsh_native_vm_exec (SeedContext ctx, SeedObject function, SeedObject thisObject, gsize argumentCount, const SeedValue arguments[], SeedException * exception) {

	if (argumentCount != 3) return seed_make_null(ctx);

	void * vm = seed_pointer_get_pointer(ctx, arguments[0]);
	int type = seed_value_to_int(ctx, arguments[1], exception);
	void * func = seed_pointer_get_pointer(ctx, arguments[2]);

	if (type & JSH_TYPE_POINTER) return seed_make_pointer(ctx, dcCallPointer(vm, func));
	else if (type & JSH_TYPE_BOOL) return JSValueMakeBoolean(ctx, dcCallBool(vm, func));
	else if (type & JSH_TYPE_FLOAT) return JSValueMakeNumber(ctx, (gdouble) dcCallFloat(vm, func));
	else if (type & JSH_TYPE_DOUBLE) return JSValueMakeNumber(ctx, dcCallDouble(vm, func));			
	else if (type & JSH_TYPE_UNSIGNED) {
		if (type & JSH_TYPE_CHAR) return JSValueMakeNumber(ctx, (gdouble) (unsigned char) dcCallChar(vm, func));
		else if (type & JSH_TYPE_SHORT) return JSValueMakeNumber(ctx, (gdouble) (unsigned short) dcCallShort(vm, func));
		else if (type & JSH_TYPE_INT) return JSValueMakeNumber(ctx, (gdouble) (unsigned int) dcCallInt(vm, func));
		else if (type & JSH_TYPE_LONG) return JSValueMakeNumber(ctx, (gdouble) (unsigned long) dcCallLong(vm, func));
		else if (type & JSH_TYPE_LONG_LONG) return JSValueMakeNumber(ctx, (gdouble) (unsigned long long)dcCallLongLong(vm, func));
	} else {
		if (type & JSH_TYPE_CHAR) return JSValueMakeNumber(ctx, (double) dcCallChar(vm, func));
		else if (type & JSH_TYPE_SHORT) return JSValueMakeNumber(ctx, (double) dcCallShort(vm, func));
		else if (type & JSH_TYPE_INT) return JSValueMakeNumber(ctx, (double) dcCallInt(vm, func));
		else if (type & JSH_TYPE_LONG) return JSValueMakeNumber(ctx, (double) dcCallLong(vm, func));
		else if (type & JSH_TYPE_LONG_LONG) return JSValueMakeNumber(ctx, (double) dcCallLongLong(vm, func));
	}

	dcCallVoid(vm, func);
	return seed_make_undefined(ctx);

}

void jsh_native_define_vm(SeedContext ctx, SeedObject object, SeedException * exception) {

	jsh_register_native(ctx, object, "create", jsh_native_vm_create, exception);
	jsh_register_native(ctx, object, "free", jsh_native_vm_free, exception);
	jsh_register_native(ctx, object, "error", jsh_native_vm_error, exception);
	jsh_register_native(ctx, object, "mode", jsh_native_vm_mode, exception);
	jsh_register_native(ctx, object, "reset", jsh_native_vm_reset, exception);
	jsh_register_native(ctx, object, "push", jsh_native_vm_push, exception);
	jsh_register_native(ctx, object, "exec", jsh_native_vm_exec, exception);

	SeedObject error = jsh_get_object_property(ctx, object, "error");

	seed_object_set_property(ctx, error, "none",
		seed_value_from_int(ctx, DC_ERROR_NONE, exception)
	);

	seed_object_set_property(ctx, error, "unsupported",
		seed_value_from_int(ctx, DC_ERROR_UNSUPPORTED_MODE, exception)
	);

	SeedObject mode = jsh_get_object_property(ctx, object, "mode");

	seed_object_set_property(ctx, mode, "default",
		seed_value_from_int(ctx, DC_CALL_C_DEFAULT, exception)
	);

	seed_object_set_property(ctx, mode, "ellipsis",
		seed_value_from_int(ctx, DC_CALL_C_ELLIPSIS, exception)
	);

}

jsh_define_natives(SeedContext ctx, SeedObject jshObject, SeedException * exception) {

	SeedObject jsh, jshNative, jshNativeLibrary, jshNativeVM;

	jsh = jshObject;

	jshNative = jsh_get_object_property(ctx, jsh, "native");
	jsh_register_native(ctx, jshNative, "buffer", jsh_native_buffer, exception);
	jsh_register_native(ctx, jshNative, "unbuffer", jsh_native_unbuffer, exception);
	jsh_register_native(ctx, jshNative, "string", jsh_native_string, exception);
	jsh_register_native(ctx, jshNative, "unstring", jsh_native_unstring, exception);
	jsh_register_native(ctx, jshNative, "release", jsh_native_release, exception);

	jshNativeLibrary = jsh_get_object_property(ctx, jshNative, "library");
	jsh_native_define_library(ctx, jshNativeLibrary, exception);

	jshNativeVM = jsh_get_object_property(ctx, jshNative, "vm");
	jsh_native_define_vm(ctx, jshNativeVM, exception);

}
