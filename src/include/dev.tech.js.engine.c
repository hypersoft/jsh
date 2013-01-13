/*

	Copyright (C) 2013, Triston J. Taylor

*/

#include "contributors.inc"

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "dyncall/dyncall.h"
#include "dyncall/dynload.h"
#include "dyncall/dyncall_signature.h"
#include "dyncall/license.inc"

#include "webkitgtk-js-unified.c"

/* =

Introductory Procedure Catalog

	Procedures and groups here, are too small for their own file. As procedures
	and groups become larger, they should be migrated to an own file.

	This is an essential location for testing. Groups need to have a unique
	prefix to assist with code re-factoring and analysis.

= */


JSContextRef   jscx;
JSObjectRef    jscx_global;

JSObjectRef    jscx_init_date;

JSValueRef     jscx_exception_value;
JSValueRef   * jscx_exception;

// convert object to value
JSObjectRef jsx_object_from(JSValueRef value) {
	return JSValueToObject(jscx, value, jscx_exception);
}

// call function
JSValueRef jsx_global_call(JSObjectRef function, JSValueRef arguments[]) {

	unsigned long count = 0;
	if (arguments) while (arguments[count++]);

	return JSObjectCallAsFunction(jscx,
		function, NULL, count, arguments,
	jscx_exception);

}

// call function on object
JSValueRef jsx_method_call(JSObjectRef who, JSObjectRef function, JSValueRef arguments[]) {

	unsigned long count = 0;
	if (arguments) while (arguments[count++]);

	return JSObjectCallAsFunction(jscx,
		function, who, count, arguments,
	jscx_exception);

}

// import C string
JSValueRef jsx_import_string(char * source) {
	JSStringRef string = JSStringCreateWithUTF8CString(source);
	JSValueRef result = JSValueMakeString(jscx, string);
	JSStringRelease(string);
	return result;
}

// export C string
char * jsx_export_string(JSValueRef source) {
	if (! source ) return NULL;
	JSStringRef string = JSValueToStringCopy(jscx, source, NULL);
	unsigned long size = JSStringGetMaximumUTF8CStringSize(string);
	char * result =  NULL;
	if (size) { result = malloc(size);
		JSStringGetUTF8CString(string, result, size);
		JSStringRelease(string);
	}
	return result;
}

JSObjectRef jsx_native_function(char * name, void * func) {
	JSStringRef string = JSStringCreateWithUTF8CString(name);
	JSObjectRef result = JSObjectMakeFunctionWithCallback(jscx, string, func);
	JSStringRelease(string);
	return result;
}

void jsx_evaluate(char * source, JSObjectRef this) {

	if (! jscx ) return;

	JSStringRef script = JSStringCreateWithUTF8CString(source);	
	JSEvaluateScript(jscx, script, this, NULL, 1, jscx_exception);
	JSStringRelease(script);

}

JSValueRef jsx_value_from_eval(char * source, JSObjectRef this) {

	if (! jscx ) return NULL;

	JSStringRef script = JSStringCreateWithUTF8CString(source);	
	JSValueRef result = JSEvaluateScript(jscx, 
		script, this, NULL, 1,
	jscx_exception);
	JSStringRelease(script);

	return result;

}

JSObjectRef jsx_object_from_eval(char * source, JSObjectRef this) {

	if (! jscx ) return NULL;

	JSStringRef script = JSStringCreateWithUTF8CString(source);	
	JSValueRef result = JSEvaluateScript(jscx, script, this, NULL, 1, jscx_exception);
	JSStringRelease(script);

	return JSValueToObject(jscx, result, jscx_exception);

}

#include "js/core.inc"
#include "js/common.inc"

#include "js/type/main.c"

void jsx_init(JSContextRef context) {

	jscx = context;

	jscx_init_date = jsx_object_from_eval("new Date();", NULL);

	jscx_global = JSContextGetGlobalObject(context);

	jscx_exception_value = jsx_value_from_eval("new Error()", NULL);
	jscx_exception = &jscx_exception_value;

	js_core_init();
	js_type_init();

}

