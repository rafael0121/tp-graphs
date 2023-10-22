/**
 *
 * @author	Rafael Ramos
 * @version	1.0
 *
 */

/**
 * @brief	Linked List Data Structure.
 */

#ifndef LIST_H_
#define LIST_H_
	
	#include <object.h>
	#include <stdlib.h>
	#include <string.h>
    
	/**
	 * @brief	Struct from one node.
	 */
	struct lnode{
		struct lnode *next;	/*<Pointer to next node in list*/
		struct lnode *previous; /*<Pointer to previous node in list*/
        unsigned key; /*< Key*/
		object_s * obj_struct;	/*<Pointer to object's struct that will be storage*/
        
	}typedef lnode;
	
	/**
	 * @brief	Struct from one node.
	 */
	struct list{
		unsigned size;	/*<Current size of this list*/
		lnode *root;	/*<First list node*/
		lnode *leaf;	/*<Last list node*/
	}typedef list;

	
	 list * list_create();
	lnode * list_add_begin(list *, object_p, size_t);
	lnode * list_add_end(list *, object_p, size_t);
	lnode * list_remove_begin(list *);
	lnode * list_remove_end(list *);
	lnode * list_remove(list *, lnode *);
    lnode * list_search_node(list *, object_p);
	 list *	list_clear(list *);

	/**
	 * @brief Create node.
	 *
	 * @param obj Object that will storage in node.
	 */
	static lnode * node_create(object_p obj, size_t obj_size){
		lnode *node = malloc(sizeof(lnode));

		node->obj_struct = malloc(sizeof(object_s));
		node->obj_struct->obj_addr = malloc(sizeof(obj_size));
		
		memcpy(node->obj_struct->obj_addr, obj, obj_size);

		node->next = NULL;
		node->previous = NULL;

		return node;
	}
	
	/**
	 * @brief Delete node.
	 *
	 * @param *node Node that will be deleted.
	 */
	static lnode * node_delete(lnode *node){
		free(node->obj_struct->obj_addr);
		free(node->obj_struct);
		free(node);

		return NULL;
	}
	
#endif
