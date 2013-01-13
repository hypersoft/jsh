/*

	js.type

	Copyright (C) 2013, Triston J. Taylor

*/

#include "pointer.class.c"

void js_type_init() {

	JSObjectRef type = jsx_object_from_eval("js.type = {};", NULL);

	js_type_pointer_init(type);

}
