#include "common.h"
#include "list.h"

/* Creates a list (node) and returns it
 * Arguments: The data the list will contain or NULL to create an empty
 * list/node
 */
list_node* list_create(node_data *data)
{
	list_node *l = malloc(sizeof(list_node));
	if (l != NULL) {
		l->next = NULL;
		l->data = data;
	}

	return l;
}

/* Completely destroys a list
 * Arguments: A pointer to a pointer to a list
 */
void list_destroy(list_node **list)
{
	if (list == NULL) return;
	while (*list != NULL) {
		list_remove(list, *list);
	}
}

/* Creates a list node and inserts it after the specified node
 * Arguments: A node to insert after and the data the new node will contain
 */
list_node* list_insert_after(list_node *node, node_data *data)
{
	list_node *new_node = list_create(data);
	if (new_node) {
		new_node->next = node->next;
		node->next = new_node;
	}
	return new_node;
}

/* Creates a new list node and inserts it in the beginning of the list
 * Arguments: The list the node will be inserted to and the data the node will
 * contain
 */
list_node* list_insert_beginning(list_node *list, node_data *data)
{
	list_node *new_node = list_create(data);
	if (new_node != NULL) { new_node->next = list; }
	return new_node;
}

/* Creates a new list node and inserts it at the end of the list
 * Arguments: The list the node will be inserted to and the data the node will
 * contain
 */
list_node* list_insert_end(list_node *list, node_data *data)
{
	list_node *new_node = list_create(data);
	if (new_node != NULL) {
		for(list_node *it = list; it != NULL; it = it->next) {
			if (it->next == NULL) {
				it->next = new_node;
				break;
			}
		}
	}
	return new_node;
}

/* Removes a node from the list
 * Arguments: The list and the node that will be removed
 */
void list_remove(list_node **list, list_node *node)
{
	list_node *tmp = NULL;
	if (list == NULL || *list == NULL || node == NULL) return;

	if (*list == node) {
		*list = (*list)->next;
		int idx = 0;
		while (node->data->r_word[idx])
		{
			free(node->data->r_word[idx]);
			idx++;
		}
		free(node->data->r_word);
		free(node->data->word);
		free(node->data);
		free(node);		
		node = NULL;
	} else {
		tmp = *list;
		while (tmp->next && tmp->next != node) tmp = tmp->next;
		if (tmp->next) {
			tmp->next = node->next;
			int idx = 0;
			while (node->data->r_word[idx])
			{
				free(node->data->r_word[idx]);
				idx++;
			}
			free(node->data->r_word);
			free(node->data->word);
			free(node->data);
			free(node);
			node = NULL;
		}
	}
}

/* Removes an element from a list by comparing the data pointers
 * Arguments: A pointer to a pointer to a list and the pointer to the data
 */
void list_remove_by_data(list_node **list, node_data *data)
{
	if (list == NULL || *list == NULL || data == NULL) return;
	list_remove(list, list_find_by_data(*list, data));
}

/* Find an element in a list by the pointer to the element
 * Arguments: A pointer to a list and a pointer to the node/element
 */
list_node* list_find_node(list_node *list, list_node *node)
{
	while (list) {
		if (list == node) break;
		list = list->next;
	}
	return list;
}

/* Finds an element in a list by the data pointer
 * Arguments: A pointer to a list and a pointer to the data
 */
list_node* list_find_by_data(list_node *list, node_data *data)
{
	while (list) {
		if (list->data == data) break;
		list = list->next;
	}
	return list;
}

/* Finds an element in a list by the word
 * Arguments: A pointer to a list and a word
 */
list_node* list_find_by_word(list_node* list, char* word)
{
	while (list) {
		if (strcmp(list->data->word, word) == 0) break;
		list = list->next;
	}
	return list;
}
/* Finds an element in a list by the word
 * Arguments: A pointer to a list and a word
 */
list_node* list_find_by_rand(list_node* list, float sum_weight)
{
	float r = (rand() % 1000) / 1000.0f;
	float rand_weight = r * sum_weight;
	
	list_node* first = list;
	while (list) {
		if (rand_weight < list->data->weight)
			return list;
		rand_weight -= list->data->weight;
		list = list->next;
		if (!list)
			list = first;	
	}
	return list;
}
/* Finds an element in the list by using the comparison function
 * Arguments: A pointer to a list, the comparison function and a pointer to the
 * data
 */
list_node* list_find(list_node *list, int(*func)(list_node*, node_data*), node_data *data)
{
	if (!func) return NULL;
	while(list) {
		if (func(list, data)) break;
		list = list->next;
	}
	return list;
}

