/*
Graham Arnold
CSE374 HW 5
1230751
5/12/17

Autocomplete program which builds a trie from a given dictionary
then accepts user input to search for all completions of a given
word stem

Trie API which allows a client program
to build a trie from a provided file of words
the user can then search the trie for all completions
of a specified string
*/
#include "trie.h"

//Creates a new trieNode with no children
//returns a pointer to the new node
trieNode* createNode(int isWord) {
	trieNode* newNode = (trieNode *)malloc(sizeof(trieNode));
	//newNode->value = nodeVal;
	for(int i = 0; i < MAX_NUM_CHAR; i++) {
		newNode->children[i] = 0;
	}
	return newNode;
}

//accepts an input file and root node
//Reads from input file, parses line by line
//adds each word into the trie
//returns a pointer to the root of the built tree
trieNode* buildTrie(FILE *file, trieNode* root) {
	//trieNode* root = NULL;

	//char lineBuffer[MAX_LINE_LENGTH];
	//printf("hit1");
	char* lineBuffer = (char *)malloc(sizeof(char *) * MAX_LINE_LENGTH);

	if (lineBuffer == NULL) {
        printf("Error allocating memory for line buffer.");
        exit(1);
    }
	
   while(fgets(lineBuffer,MAX_LINE_LENGTH,file) != NULL) {
		strtok(lineBuffer, "\n");	
		//printf("%s \n",lineBuffer);	
		//printf("%d \n", strlen(lineBuffer));
		//lineLength = strlen(lineBuffer);
		if (root == NULL) {
			root = createNode(1);
		}
		root = addWord(root,lineBuffer,1);
	}

	free(lineBuffer);
   	return root;
}

//adds one word into the tree
//receives a pointer to the current tree node and a string
//to add into the string
//the third parameter "endWord" marks the node as an
//end of a valid word
//returns a pointer to the current root
trieNode* addWord(trieNode* root, char* string, int endWord) {
	if (strlen(string) == 0) {
		return root;
	}
	int stringLength = strlen(string);
	trieNode* currNode = root;
	for(int i = 0; i < stringLength; i++) {
		int currChar = (int) string[i];
		//printf("%d",currChar);
		if (currNode->children[currChar] == NULL) {
			//printf("%c\n", (char) currChar);
			//ADD RETURN STATUS CHECK!!!!!!
			currNode->children[currChar] = (trieNode *)malloc(sizeof(trieNode)); ///MAYBE USE CREATE NODE FOR THIS PART
		}
		currNode = currNode->children[currChar];
	}
	currNode->isWord = endWord;
	return root;
}

//helper function to print a tree
//prints in a post-order traversal
//accepts a pointer to the tree root
//returns a int sucess flag
int printTrie(trieNode* root) {
	if (root == NULL) {
		return 0;
		printf("BRANCH END \n");
	}
	for(int i = 0; i < MAX_NUM_CHAR; i++) {
		char nodeChar = '\0';
		if (root->children[i] != NULL) {
			nodeChar = i;
			//printf("hit2");
		}
		if(nodeChar != '\0') {
			printf("%c\n", nodeChar);	
		}
		if(root->isWord == 1) {
			printf("branch end");
		} else {
			printTrie(root->children[i]);
		}
		
	}
	return 1;	
}

//begins a search on the given trie for all completions
//of the given word stem
void searchTrie(trieNode* root, char* stem) {
	trieNode* targetNode = findTargetNode(root, stem);
	if (targetNode != NULL) {
		int stemLen = strlen(stem);
		char* output = (char*)malloc(sizeof(char*)*stemLen);
		strcpy(output,stem); 
		depthFirstSearch(targetNode, output);
	}
}

//search helper function to find the target node
//that completes the provided word stem
//if no stem is found in the trie the program does nothing
//returns a pointer to the target node
trieNode* findTargetNode(trieNode* root, char* stem) {
	int stemLen = strlen(stem);
	trieNode* currNode = root;
	for (int i = 0; i < stemLen; i++) {
		int currChar = (int) stem[i];
		if (currNode->children[currChar] == NULL) {
			return NULL;
		} else {
			currNode = currNode->children[currChar];
		}
	}
	return currNode;
}

//Performs a depth first search of the given root's branches
//an output string is built recursively and 
//the matching word is printing when the function reaches a valid
//word leaf
//returns a success code
int depthFirstSearch(trieNode* root, char* output) {
	char temp[MAX_LINE_LENGTH];
	if (root != NULL) {
		char nodeChar[1];
		for (int i = 0; i < MAX_NUM_CHAR; i++) {
			nodeChar[0] = i;
			strncpy(temp,output,MAX_LINE_LENGTH);
			strncat(temp,nodeChar,1);
			depthFirstSearch(root->children[i],temp);
				
		}
		if (root->isWord == 1) {
			printf("%s\n",output);	
		}	
	}
	return 1;
}

//Recursively deletes the trie connected to the provided
//root. Frees all allocated memory
void freeTrie(trieNode* root) {
  if (root != NULL) {
    for (int i = 0; i < MAX_NUM_CHAR; i++) {
      if (root->children[i] != NULL) {
        freeTrie(root->children[i]);
        root->children[i] = NULL;
      }
    }
    free(root);
  }
}		
