#include <stdlib.h>
#include <glib.h>
#include <seed.h>
#include <JavaScriptCore/JavaScript.h>

/* HAPPY HACKERS  <---+--->  GOTTA LUV 'EM */
   #include "dyncall/dyncall.h"
   #include "dyncall/dynload.h"
   #include "dyncall/dyncall_signature.h"
/* ====================================== */

SeedValue jsh_get_object_property(void * ctx, SeedObject base, char *property) {
	void *jstemp = 0;
 	void * jshobj = (void *) JSObjectGetProperty(ctx, base, 
		jstemp = JSStringCreateWithUTF8CString(property), NULL
	);  JSStringRelease(jstemp);
	return jshobj;
}

void jsh_register_native(void *context, void *object, const char * name, void * function, void * exception) {

	JSStringRef fname = JSStringCreateWithUTF8CString(name);
	JSObjectSetProperty(context, object, fname,
		seed_make_function(context, function, name),
		kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete, exception
	);  JSStringRelease(fname);

}

#include "include/init.inc"
#include "include/init.native.inc"
#include "include/init.etc.inc"

#include "include/jsh.native.c"

SeedScript * jsh_initialize(char * binary, SeedContext ctx, SeedObject global) {

	SeedScript * initScript = seed_make_script(
		ctx, jsh_init_script, "jsh/init.js", 1
	);

	jsh_define_natives(ctx,
		seed_evaluate(ctx, initScript, global),
		seed_script_exception(initScript)
	);

	SeedScript * nativeScript = seed_make_script(
		ctx, jsh_init_native_script, "jsh/init.native.js", 1
	);

	seed_evaluate(ctx, nativeScript, global);

	SeedScript * etcScript = seed_make_script(
		ctx, jsh_init_etc_script, "jsh/init.etc.js", 1
	);

	seed_evaluate(ctx, etcScript, global);

	return initScript;

}

int main(int argc, char *argv[], char *envp[]) {
 
    /* Initialize the Seed engine */

    SeedEngine * jse = seed_init(&argc, &argv);
	SeedObject global = seed_context_get_global_object(jse->context);

	SeedScript * init = jsh_initialize(argv[0], jse->context, global);

	seed_simple_evaluate(jse->context, "while (Seed.repl());", seed_script_exception(init));
 
    return 0;
}
