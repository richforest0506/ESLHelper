#include "dictionary.h"
#include "session.h"

int main()
{
	list_node* synonym_list = NULL;
	list_node* antonym_list = NULL;

    load_dictionary(&synonym_list, &antonym_list);
    srand((int)time(0));
    
    char user_name[20];
    printf("What's your name?\n");
    scanf("%s", user_name);

    float sum_weight_syno = 0;
    float sum_weight_anto = 0;
    load_session(user_name, synonym_list, antonym_list, &sum_weight_syno, &sum_weight_anto);

    while (true)
    {
        char str[20];
        memset(str, 0, 20);

        node_data* syno_node = get_word_from_list(synonym_list, sum_weight_syno);
        printf("What is the synonyms of %s?\n", syno_node->word);
        scanf("%s", str);
        if (strcmp(str, "exit") == 0)
            break;
		check_word(syno_node, str);

		node_data* anto_node = get_word_from_list(antonym_list, sum_weight_anto);
		printf("What is the antonyms of %s?\n", anto_node->word);
		scanf("%s", str);
		if (strcmp(str, "exit") == 0)
			break;
		check_word(anto_node, str);
    }

    save_dictionary(synonym_list, antonym_list);
    save_session(user_name, synonym_list, antonym_list);
    free_dictionary(synonym_list, antonym_list);
    return 0;
}

