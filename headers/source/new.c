#include <stdlib.h>
#ifndef STDARG_H
	#include <stdarg.h>
#endif
#include "../New.h"
//#include "../New.r"

void* new(const void* _call, ...) {
	const struct Class *class = _call;
	void* pointer = calloc(1, class->size);

	* (const struct Class **) pointer = class;
	
	return class->ctor(pointer);
}