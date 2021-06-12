#ifndef _LIST_H_
#define _LIST_H_

typedef struct _node_data {
	char *word;
	int correct;
	int incorrect;
	float weight;
	char **r_word;
} node_data;

typedef struct _list_node {
	node_data *data;
	struct _list_node* next;
} list_node;

/* linked list */
list_node* list_create(node_data *data);
void list_destroy(list_node **list);
list_node* list_insert_after(list_node *node, node_data *data);
list_node* list_insert_beginning(list_node *list, node_data *data);
list_node* list_insert_end(list_node *list, node_data *data);
void list_remove(list_node **list, list_node *node);
void list_remove_by_data(list_node **list, node_data *data);
list_node* list_find_node(list_node *list, list_node *node);
list_node* list_find_by_data(list_node *list, node_data *data);
list_node* list_find_by_word(list_node* list, char* word);
list_node* list_find_by_rand(list_node* list, float sum_weight);
list_node* list_find(list_node *list, int(*func)(list_node*, node_data*), node_data *data);

#endif //_LIST_H_

