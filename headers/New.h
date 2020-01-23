#ifndef STDARG_H
	#include <stdarg.h>
#endif

#ifndef NEW_H
	#define NEW_H
	void* new(const void* type, ...);
	void delete(void* item);
#endif

#ifndef	CLASS_R
	#define	CLASS_R

	struct Class {
		size_t size;
		void* (* ctor)(void* self);
		void* (* dtor)(void* self);
	};
#endif