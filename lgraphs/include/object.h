/**
 *
 * @author	Rafael Ramos
 * @version	1.0
 *
 */

/**
 * @brief	Object library to handle the objects in data structures.
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdlib.h>

typedef void * object_p;

/**
 * @brief Struct for save size and address of the item referenced by * void
 */
struct object_s{
	object_p obj_addr;	//<Object address
	size_t obj_size; 	//<Object size
}typedef object_s;

#endif
