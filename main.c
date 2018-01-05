/*
Graham Arnold
CSE374 HW 5
1230751
5/12/17

Autocomplete program which builds a trie from a given dictionary
then accepts user input to search for all completions of a given
word stem
*/

#include "trie.h"

int main(int argc, char *argv[]) {
	//add open error check
	if (argc < 2) {
		perror("Error: No dictionary file given");
	}
	FILE* file = fopen(argv[1], "r");
	trieNode* root = 0;
	root = buildTrie(file, root);
	//printTrie(root);
	char input[MAX_LINE_LENGTH];
	while (scanf("%s", input) != EOF) {
		searchTrie(root, input);
	}
	freeTrie(root);
	return 1;

}