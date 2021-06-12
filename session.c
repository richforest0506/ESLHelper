#include "session.h"
bool load_session(char* user_name, list_node* synonym_list, list_node* antonym_list, float* sum_weight_syno, float* sum_weight_anto)
{
	char file_name[50];
	sprintf(file_name, "%s.worddat", user_name);
	FILE* fp = fopen(file_name, "r");
	if (fp == NULL)
		return false;
	list_node* first;
	char buff[100];
	while (fgets(buff, 100, fp))
	{
		if (buff[0] == '=')
			first = synonym_list;
		else if (buff[0] == '!')
			first = antonym_list;
		else
			continue;
		char* po = buff + 1;
		char* token = strtok(po, ":");
		list_node* list = list_find_by_word(first, token);
		token = strtok(0, ":");
		list->data->correct = atoi(token);
		token = strtok(0, ":");
		list->data->incorrect = atoi(token);
		if (list->data->correct != 0 || list->data->incorrect != 0)
			list->data->weight = 1.0f / (list->data->correct + list->data->incorrect)
			- (list->data->correct == 0 ? 0 : 0.3f * list->data->correct / (list->data->correct + list->data->incorrect))
			+ (list->data->incorrect == 0 ? 0 : 0.7f * list->data->incorrect / (list->data->correct + list->data->incorrect));
		else
			list->data->weight = 1;
		if (first == synonym_list)	*sum_weight_syno += list->data->weight;
		else *sum_weight_anto += list->data->weight;
	}
	fclose(fp);
	return true;
}

bool save_session(char* user_name, list_node* synonym_list, list_node* antonym_list)
{
	char file_name[50];
	sprintf(file_name, "%s.worddat", user_name);
	FILE* fp = fopen(file_name, "w");
	if (fp == NULL)
		return false;
	list_node* list;
	list = synonym_list;
	while (list)
	{
		if (list->data->correct != 0 || list->data->incorrect != 0)
			fprintf(fp, "=%s:%d:%d\n", list->data->word, list->data->correct, list->data->incorrect);
		list = list->next;
	}

	list = antonym_list;
	while (list)
	{
		if (list->data->correct != 0 || list->data->incorrect != 0)
			fprintf(fp, "!%s:%d:%d\n", list->data->word, list->data->correct, list->data->incorrect);
		list = list->next;
	}

	fclose(fp);
	return true;
}