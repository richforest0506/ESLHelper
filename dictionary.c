#include "dictionary.h"

list_node* load_synonyms()
{
	FILE* fp = NULL;
	char buff[200];
	list_node* first = NULL;
	fp = fopen("synonyms.txt", "r");
	if (fp == NULL)
	{
		printf("Can't find Synonyms Dictionary file.");
		return NULL;
	}
	while (fgets(buff, 200, fp))
	{
		char* po = strstr(buff, "=");
		if (!po) 
		{
			printf("Synonyms Dictionary Syntax Error!");
			continue;
		}
		*po = 0;
		po++;
		trim(po);
		if (strlen(po) == 1)
		{
			printf("Synonyms Dictionary Syntax Error!");
			continue;
		}		
		node_data *data = malloc(sizeof(node_data));
		if (data)
		{
			data->word = strdup(trim(buff));
			data->r_word = str_split(po, " ");
			data->correct = 0;
			data->incorrect = 0;
			data->weight = 1;
		}
		if (first)
			list_insert_end(first, data);
		else
			first = list_create(data);
	}
	fclose(fp);
	return first;
}

list_node* load_antonyms()
{
	FILE* fp = NULL;
	char buff[200];
	list_node* first = NULL;
	fp = fopen("antonyms.txt", "r");
	if (fp == NULL)
	{
		printf("Can't find Antonyms Dictionary file.");
		return false;
	}
	while (fgets(buff, 200, fp))
	{
		char* po = strstr(buff, "<>");
		if (!po)
		{
			printf("Antonyms Dictionary Syntax Error!");
			continue;
		}
		*po = 0;
		po+=2;
		trim(po);
		if (strlen(po) == 1)
		{
			printf("Antonyms Dictionary Syntax Error!");
			continue;
		}
		node_data* data = malloc(sizeof(node_data));
		if (data)
		{
			data->word = strdup(trim(buff));
			data->r_word = str_split(po, " ");
			data->correct = 0;
			data->incorrect = 0;
			data->weight = 1;
		}
		if (first)
			list_insert_end(first, data);
		else
			first = list_create(data);
	}
	fclose(fp);
	return first;
}

bool add_word_to_node(node_data* node, char* word)
{
	int count = 0;
	while (node->r_word[count++]);
	char** new_r_word = malloc(sizeof(char*) * (count + 1));
	if (new_r_word)
	{
		memcpy(new_r_word, node->r_word, sizeof(char*) * count);
		new_r_word[count - 1] = strdup(word);
		new_r_word[count] = 0;
		free(node->r_word);
		node->r_word = new_r_word;
		return true;
	}
	else
		return false;
}

node_data* get_word_from_list(list_node* list, float sum_weight)
{
	node_data* node = list_find_by_rand(list, sum_weight)->data;
	return node;
}

bool check_word(node_data* node, char* word)
{
	int idx = 0;
	while (node->r_word[idx])
	{
		if (strcmp(node->r_word[idx], word) == 0)
		{
			printf("Correct!\n");
			node->correct++;
			return true;
		}		
		idx++;
	}
	printf("Incorrect!\nDo you want to add it to the list as a new word?(y/n)\n");
	char c = getchar();
	getchar();
	if (c == 'y' && add_word_to_node(node, word))
		printf("Added.\n");
	node->incorrect++;
	return false;
}

bool load_dictionary(list_node** po_synonyms_list, list_node** po_antonyms_list)
{
	*po_synonyms_list = load_synonyms();
	*po_antonyms_list = load_antonyms();
	return *po_synonyms_list && *po_antonyms_list;
}

bool save_synonyms(list_node* synonym_list)
{
	FILE* fp = NULL;
	fp = fopen("synonyms.txt", "w");
	if (fp == NULL)
	{
		printf("Can't Save Synonyms Dictionary.");
		return false;
	}
	list_node* list = synonym_list;
	while (list)
	{
		fprintf(fp, "%s =", list->data->word);
		int idx = 0;
		while (list->data->r_word[idx])
		{
			fprintf(fp, " %s", list->data->r_word[idx]);
			idx++;
		}
		fprintf(fp, "\n");
		list = list->next;
	}
	fclose(fp);
	return true;
}

bool save_antonyms(list_node* antonym_list)
{
	FILE* fp = NULL;
	fp = fopen("antonyms.txt", "w");
	if (fp == NULL)
	{
		printf("Can't Save Antonyms Dictionary.");
		return false;
	}
	list_node* list = antonym_list;
	while (list)
	{
		fprintf(fp, "%s <>", list->data->word);
		int idx = 0;
		while (list->data->r_word[idx])
		{
			fprintf(fp, " %s", list->data->r_word[idx]);
			idx++;
		}
		fprintf(fp, "\n");
		list = list->next;
	}
	fclose(fp);
	return true;
}

bool save_dictionary(list_node* synonyms_list, list_node* antonyms_list)
{
	return save_synonyms(synonyms_list) && save_antonyms(antonyms_list);
}

void free_dictionary(list_node* synonyms_list, list_node* antonyms_list)
{
	list_destroy(&synonyms_list);
	list_destroy(&antonyms_list);
}