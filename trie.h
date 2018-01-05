/*
Graham Arnold
CSE374 HW 5
1230751
5/12/17
*/

#ifndef	TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_CHAR 128
#define MAX_LINE_LENGTH 501

typedef struct trieNode {
	int isWord;
	struct trieNode *children[MAX_NUM_CHAR];
} trieNode;

trieNode* createNode();
trieNode* buildTrie(FILE *file, trieNode* root);
trieNode* addWord(trieNode* root, char* string, int endWord);
int printTrie(trieNode* root);
void searchTrie(trieNode* root, char* stem);
trieNode* findTargetNode(trieNode* root, char* stem);
int depthFirstSearch(trieNode* root, char* output);
void freeTrie(trieNode* root);
#endif

	