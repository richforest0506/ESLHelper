#ifndef _SESSION_H_
#define _SESSION_H_

#include "common.h"
#include "list.h"

bool load_session(char* user_name, list_node* synonym_list, list_node* antonym_list, float* sum_weight_syno, float* sum_weight_anto);
bool save_session(char* user_name, list_node* synonym_list, list_node* antonym_list);
#endif //_SESSION_H_
