// COMP2521 Assignment 1
// DO NOT MODIFY THIS FILE

#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "invertedIndex.h"

#define MAXCHAR 100

//Normalises a given string
char *normaliseWord(char *str);
//create a set
Set newSet();
// create new inverted index node
InvertedIndexBST newInvertedIndexNode(char *key);
// create new fileList
FileList newFileListNode(char *filename); 
// search for key in the tree
InvertedIndexBST findKeyRecur(char *key);

int main(void) {
    char *collectionFilename = "collection.txt";
    
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    file *fp;
    char str1[MAXCHAR], str2[MAXCHAR];
    fp = fopen(collectionFilename, "r");
    InvertedIndexBST rootRoot = newInvertedIndexNode("rootRoot");
    while (fscanf(fp1, "%s", str1) != EOF) {
        char *newstr1 = strdup(str1);
        fp2 = fopen(newstr1, "r");
        while (fscanf(fp2, "%s", str2) != EOF) {
            char *newstr2 = strdup(str2);
            if (rootRoot->right == NULL) {
                rootRoot->right = newInvertedIndexNode (normaliseWord(newstr2)); 
                rootRoot->right->FileList = newFileListNode (newstr1);              
            } else {
                InvertedIndexBST temp = findKeyRecur(rootRoot->right, newstr2);
                if (temp == NULL) {
                    InvertedInvertedBST node = newInvertedIndexNode(normaliseWord(newstr2));
                    node->fileList = newFileListNode(newstr1);
                    compareKey2insertRecur(rootRoot->right, node); 
                } else {
                    insertFileListNode(temp, newstr1);       
                }
            }
        }
        fclose(fp2);
    }
    flcose(fp1);
    return rootRoot->right;
}

InvertedIndexBST findKeyRecur(char *key) {
    int cmp = strcmp(key, node->word);
    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        return findKeyRecur(node->left, key);
    } else if (cmp > 0) {
        return findKeyRecur(node->right, key);
    }
    return NULL;
}

FileList newFileListNode(char *filename) {
    FileList node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->filename = filename;
    node->tf = 0; 
    node->next = NULL;
    return node;
}

InvertedIndexBST newInvertedIndexNode (char *key) {
    InvertedIndexBST node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->word = key;
    node->fileList = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

char *normaliseWord(char *str) {
    int i = 0;
    int lead = 0;
    int trail = strlen(str) - 1;
    // loops through the string and counts the leading whitespaces
    while (isspace((unsigned char)str[lead])) {
        lead++;
    }
    // loops through the string and counts the trailing whitespaces
    while ((trail >= lead) && isspace((unsigned char)str[trail])) {
        trail--;
    }
    // shifts all characters back to the start of the string array
    i = lead;
    while (i <= trail) {
        str[i - lead] = str[i];
        i++;
    }
    // null terminate string
    str[i - lead] = '\0';
    i = 0;
    // loops through the given string
    while (str[i] != '\0') {
        // if the loop encounters any capital letters, lowercase them
        if (str[i] >= 'A' && str[i] < 'Z') {
            str[i] = tolower(str[i]);
        }
        i++;
    }
    int j = str[strlen(str) - 1];
    // if there is punctuation at the end of the string, replace it 
    // with a null character
    if (j == '.' || j == ',' || j == ';' || j == '?') {
        str[strlen(str) - 1] = '\0';
    }
    return str;
}

void printInvertedIndex(InvertedIndexBST tree) {

}


TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {

}

TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {

}