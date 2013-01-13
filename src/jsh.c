
#include "include/dev.tech.js.engine.c"

/* given a zero terminated array of zero terminated strings, combine them into a unit */
char * hypersoft_combine_string_array(char * array[]) {

	char * item;
	register unsigned long length = 0, index = 0, count = 0;

	while (item = array[count++]); if (! count ) return NULL;

	unsigned long record_length[count];
	while (item = array[index]) length += (record_length[index++] = strlen(item));

	if (! length ) return NULL;

	count = index = 0;
	char * result = malloc(length + 1);
	result[length] = 0; // null terminate
	
	while (item = array[index]) {
		strcpy(result+count, item);
		count += record_length[index++];
	}

	return result;

}


int main(int argc, char *argv[], char *envp[]) {
	void * ctx = JSGlobalContextCreate(NULL);

	JSGlobalContextRelease(ctx);
	return 0;
}
