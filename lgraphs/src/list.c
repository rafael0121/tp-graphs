#include <list.h>
#include <object.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Create list and initialize variables.
 *
 * @param obj Pointer to object.
 *
 * @param obj_size Object size.
 */

list * list_create(){
	list *list = malloc(sizeof(list));

	list->size = 0;
	list->root = NULL;
	list->leaf = NULL;
	
	return list;
}

/**
 * @brief Add object in list begin.
 *
 * @param list List where the object will be added.
 *
 * @param obj Pointer to object.
 *
 * @param obj_size Object size.
 */

lnode * list_add_begin(list *list, object_p obj, size_t obj_size){
	lnode *node = node_create(obj, obj_size);

    if(list->size == 0){
        list->root = node;
        list->leaf = node;
        list->size++;

        return node;
    }

    lnode *old_root = list->root;

    list->root = node;

	old_root->previous = list->root;
	list->root->next = old_root;
	
	list->size++;

	return node;
}

/**
 * @brief Add object in list end.
 *
 * @param list List which the object will be added.
 *
 * @param obj Pointer to object.
 *
 * @param obj_size Object Size.
 */

lnode * list_add_end(list *list, object_p obj, size_t obj_size){
	
    if(list->size == 0){
        return list_add_begin(list, obj, obj_size);
    }

    lnode *node = node_create(obj, obj_size);

	list->leaf->next = node;
	node->previous = list->leaf;
	list->leaf = node;
	list->size++;

	return node;
}

/**
 * @brief Remove object at the list begin.
 *
 * @param list List which the object will be remeved.
 */

lnode * list_remove_begin(list *list){
	lnode *old_root = list->root;
    
    if(list->size == 0){
        return NULL;
    };

    if(list->size == 1){
        list->root = NULL;
        list->size--;
	    return node_delete(old_root); 
    };
	
	list->root = old_root->next;
	list->root->previous = NULL;
	old_root->next = NULL;
	list->size--;

	return node_delete(old_root); 

}

/**
 * @brief Remove object in list end.
 *
 * @param list List which the object will be removed.
 */
lnode * list_remove_end(list *list){
	lnode *old_leaf	= list->leaf;
	
	if(list->size > 0){
		list->leaf = old_leaf->previous;
	    list->leaf->next = NULL;

	    list->size--;

    	return node_delete(old_leaf);
	}else{
		list->leaf = NULL;
        list->root = NULL;

	    list->size--;

        return NULL;
	}
}

/**
 * @brief Remove node from list.
 *
 * @param list List which the remove operation wiil be made in.
 *
 * @param node Node which will be removed.
 */

lnode * list_remove (list *list, lnode *node){
    if(list->root == node) return list_remove_begin(list);
    if(list->leaf == node) return list_remove_end(list);

    lnode * node_previous = node->previous;
    lnode * node_next = node-> next;

    if(node_previous != NULL) node_previous->next = node_next;
    if(node_next != NULL) node_next->previous = node_previous;

    return node_delete(node);
}

/**
 * @brief Clear the list. Remove all nodes.
 *
 * @param list List which wiil be clear.
 *
 */

list * list_clear(list *list){
	for(lnode *node = list->leaf; node!=NULL; node = list->leaf){
        list_remove_end(list);
	}

	return list;
}

/**
 * @brief Serach a node on the list.
 *
 * @param list List which will be searched.
 * @param obj_addr Address to the object solicited.
 *
 */
lnode * list_search_node(list *list, object_p obj_addr){
    lnode *node = NULL;
    void *node_obj_addr = NULL;

    for(node; node != NULL; node = node->next){
        node_obj_addr = node->obj_struct->obj_addr;
        if(node_obj_addr == obj_addr){
            return node;
        }
    }

    return NULL;
}
