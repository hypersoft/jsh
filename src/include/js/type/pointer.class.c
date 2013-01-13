/*

	js.type.pointer

	Copyright (C) 2013, Triston J. Taylor

*/

JSClassRef js_type_pointer_class = 0;

typedef struct js_type_pointer_class_private {

	void * address;
	void * type;
	unsigned long count;
	bool allocated;

} js_type_pointer_class_private;

static void js_type_pointer_finalize (JSObjectRef object) {
	js_type_pointer_class_private * private = JSObjectGetPrivate(object);
	if (private->allocated) free(private->address);
	free(private);
}

void * js_type_pointer_get_address(JSObjectRef pointer) {

	if (JSValueIsObjectOfClass (jscx, pointer, js_type_pointer_class)) {
		js_type_pointer_class_private * private = JSObjectGetPrivate(pointer);
		return private->address;
	}
	return NULL;

}

JSObjectRef js_type_pointer_create(void * address) {

  js_type_pointer_class_private * private = malloc(sizeof(js_type_pointer_class_private));
  private->address = address;
  private->allocated = false;

  return JSObjectMake (jscx, js_type_pointer_class, private);

}

JSClassDefinition js_type_pointer = {
  0,				/* Version, always 0 */
  0,
  "pointer",		/* Class Name */
  NULL,				/* Parent Class */
  NULL,				/* Static Values */
  NULL,				/* Static Functions */
  NULL,
  js_type_pointer_finalize,
  NULL,				/* Has Property */
  0,
  NULL,				/* Set Property */
  NULL,				/* Delete Property */
  NULL,
  NULL,				/* Call As Function */
  NULL,				/* Call As Constructor */
  NULL,				/* Has Instance */
  NULL				/* Convert To Type */
};

void js_type_pointer_init(JSObjectRef parent) {

  js_type_pointer_class = JSClassCreate (&js_type_pointer);
	
}
