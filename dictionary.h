#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include "common.h"
#include "list.h"

bool add_word_to_node(node_data* list, char* word);
node_data* get_word_from_list(list_node* list, float sum_weight);
bool check_word(node_data* list, char* word);
bool load_dictionary(list_node** po_synonyms_list, list_node** po_antonyms_list);
bool save_dictionary(list_node* synonyms_list, list_node* antonyms_list);
void free_dictionary(list_node* synonyms_list, list_node* antonyms_list);

#endif //_DICTIONARY_H_