// COMP2521 Assignment 1
// DO NOT MODIFY THIS FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#include "invertedIndex.h"

#define MAX_FILE 100
#define MAX_CHAR 100
#define MAX_WORD 1000


char *myStrdup(const char *s1);
//Normalises a given string
char *normaliseWord(char *str);
// create new inverted index node
InvertedIndexBST newInvertedIndexNode(char *key);
// create new fileList
FileList newFileListNode(char *filename); 
// search for key in the tree
InvertedIndexBST findKeyRecur(InvertedIndexBST node, char *key);
// find the right position to insert node2 into the tree
void cmp2insertRecur(InvertedIndexBST node1, InvertedIndexBST node2);
// insert filename into the node->fileList in the right order
void insertFileListNode(InvertedIndexBST node, char *filename, int N);
// Outputs the given inverted index to a file named invertedIndex.txt
void printInvertedIndex(InvertedIndexBST tree); 
// put the whole tree into array buffer
int putTreeIntoArrayRecur(InvertedIndexBST t, char buffer[][MAX_CHAR], int nitem);
// sort the array buffer in ascending lexicographical order
void arraySortAscendLexi(char buffer[][MAX_CHAR], int i);
// print into invertedindex.txt
void loopThroughArrayNprintii(char buffer[][MAX_CHAR], int nitem, InvertedIndexBST node, FILE *fp);
// update the value tf into the fileList
void updateTf(InvertedIndexBST node, char *filename, int N);
// Returns  an  ordered list where each node contains a filename and the corresponding tf-idf value for a given searchWord
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D);
// create Tfidf list
TfIdfList newTfIdfList(char *filename);
// sorted tfidf in the decend tfidf
TfIdfList tfidfSortedDes (TfIdfList head);
TfIdfList deleteTfIdfNode (TfIdfList node, TfIdfList head);
// Returns  an  ordered list where each node contains a filename and the
//summation of tf-idf values of all the matching search words for  that
//file.
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D);
TfIdfList findMinTfidf (TfIdfList head);

// count document in collectionFileName
int countDoc(char *filename);
// count fileName presented in the fileLIst
double countFileName (FileList head);
// print tfidfList
void printTfIdfList (TfIdfList node);
// print fileLIst of node
void printFileList(InvertedIndexBST node); 
// print the whole tree 
int printTreeRecur(InvertedIndexBST node);

int main(void) {
    char *collectionFileName = "collection.txt";
    int numDoc = countDoc (collectionFileName);
    InvertedIndexBST tree = generateInvertedIndex(collectionFileName);
    printInvertedIndex (tree);
    TfIdfList testTfidf = calculateTfIdf(tree, "moon", numDoc);
    printTfIdfList (testTfidf);
    // InvertedIndexBST testBST = findKeyRecur (tree, "moon");
    // printFileList (testBST);
    return 0;
}

// TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D);

// Returns  an  ordered list where each node contains a filename and the corresponding tf-idf value for a given searchWord
TfIdfList calculateTfIdf (InvertedIndexBST tree, char *searchWord, int D) {
    InvertedIndexBST searchNode = findKeyRecur (tree, searchWord);
    // calculate idf ; idf = log (d / D) ; d == number of file in which a word present
    // D == number of filename in collection.txt
    // so we have to calculate d -> counting number of filename presented in the fileList
    double d = countFileName (searchNode->fileList);
    double idf = log(d / D) * 0.434294481903;
    // printf ("idf is %lf\n", idf);
    // copy fileList to TfIdfList
    TfIdfList tfidfHead = newTfIdfList(searchNode->fileList->filename);
    tfidfHead->tfIdfSum = searchNode->fileList->tf * idf;
    TfIdfList TFcurr = tfidfHead;
    FileList FLcurr = searchNode->fileList->next;
    while (FLcurr != NULL) {
        TFcurr->next = newTfIdfList (FLcurr->filename);  
        TFcurr->next->tfIdfSum = FLcurr->tf * idf;      
        TFcurr = TFcurr->next;
        FLcurr = FLcurr->next;     
    }
    TfIdfList sortedTfidfList = tfidfSortedDes (tfidfHead);
    return tfidfHead;
}

TfIdfList tfidfSortedDes (TfIdfList head) {
    // firstly, create a copy of tfidfList 
    TfIdfList newHead = findMinTfidf (head);
    // printf ("%s", newHead->filename);
    TfIdfList copyHead = newTfIdfList (newHead->filename);
    copyHead->tfIdfSum = newHead->tfIdfSum;
    // head = deleteTfIdfNode (newHead, head);
    // TfIdfList curr = copyHead;
    // while (head != NULL) {
    //     TfIdfList minNode = findMinTfidf (head);
    //     curr->next = newTfIdfList (minNode->filename);
    //     curr->next->tfIdfSum = minNode->tfIdfSum;
    //     head = deleteTfIdfNode (minNode, head);
    //     curr = curr->next;
    // }
    return copyHead; 
}

TfIdfList findMinTfidf (TfIdfList head) {
    TfIdfList minTfidf = head;
    TfIdfList curr = head;
    TfIdfList cmp = head;
    while (curr != NULL) {
        while (cmp != NULL) {
            if (minTfidf > cmp) {
                minTfidf = cmp->next;
            }
            cmp = cmp->next;
        }
        curr = curr->next;
        cmp = curr;
    }
    return minTfidf;
}


TfIdfList deleteTfIdfNode (TfIdfList node, TfIdfList head) {
    TfIdfList curr = head;
    TfIdfList currPrev = head;
    while (curr != NULL) {
        // node to delete is the first node in the list
        int cmp = strcmp (curr->filename, node->filename);
        if (cmp == 0) {
            if (curr == head) {
                if (curr->next == NULL) {
                    free (curr);
                    return NULL;
                }
                head = head->next;
                free (node);
            } else if (curr->next == NULL) { // middle node
                currPrev->next = NULL;
                free (curr);
            } else { // node in the middle
                currPrev->next = curr->next;
                free (curr);            
            }
        }
        currPrev = curr;
        curr = curr->next;
    }
    return head;
}

double countFileName (FileList head) {
    double count = 0;
    FileList curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

int countDoc (char *filename) {
    double numFile = 0;
    char str[MAX_CHAR];
    FILE *fp = fopen (filename, "r");
    while (fscanf(fp, "%s", str) != EOF) {
        numFile++;
    }
    fclose (fp);
    return numFile;
}

TfIdfList newTfIdfList (char *filename) {
    TfIdfList node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->filename = filename;
    node->tfIdfSum = 0; 
    node->next = NULL;
    return node;
}
 
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    FILE *fp1, *fp2, *fp3, *fp4;
    char str1[MAX_CHAR], str2[MAX_CHAR], str3[MAX_CHAR], str4[MAX_CHAR];
    int wordCount[MAX_FILE];
    int numfile = 0;
    fp1 = fopen(collectionFilename, "r");
    InvertedIndexBST containRoot = newInvertedIndexNode("containRoot");
    while (fscanf(fp1, "%s", str1) != EOF) {
        int numWord = 0;
        numfile++;
        char *newstr1 = myStrdup(str1);
        fp3 = fopen(newstr1, "r");
        while (fscanf(fp3, "%s", str3) != EOF) {
            numWord++;
        }
        wordCount[numfile-1] = numWord;
        fclose (fp3);
        fp2 = fopen(newstr1, "r");
        while (fscanf(fp2, "%s", str2) != EOF) {
            char *newstr2 = myStrdup(str2);
            if (strcmp(normaliseWord(newstr2), "design") == 0) {}
            if (containRoot->right == NULL) {
                containRoot->right = newInvertedIndexNode(normaliseWord(newstr2)); 
                containRoot->right->fileList = newFileListNode(newstr1);         
                updateTf (containRoot->right, newstr1, numWord);    
            } else {
                InvertedIndexBST temp = findKeyRecur(containRoot->right, newstr2);
                if (temp == NULL) {
                    InvertedIndexBST node = newInvertedIndexNode(normaliseWord(newstr2));
                    node->fileList = newFileListNode(newstr1);
                    updateTf (node, newstr1, numWord);
                    cmp2insertRecur(containRoot->right, node); 
                } else {
                    insertFileListNode(temp, newstr1, numWord);
                    updateTf(temp, newstr1, numWord);
                }
            }
        }
        fclose(fp2);
    }
    fclose(fp1);
    return containRoot->right;
}

void printTfIdfList (TfIdfList node) {
    TfIdfList curr = node;
    while (curr != NULL) {
        printf("%s\n", curr->filename);
        printf("%lf\n", curr->tfIdfSum);
        curr = curr->next;
    }
}

void printFileList(InvertedIndexBST node) {
    FileList curr = node->fileList;
    while (curr != NULL) {
        printf("%s\n", curr->filename);
        printf("%lf\n", curr->tf);
        curr = curr->next;
    }
}

// N is the number of words in the file with filename
void updateTf(InvertedIndexBST node, char *filename, int N) {
    FileList curr = node->fileList;
    while (curr != NULL) {
        if (strcmp(curr->filename, filename) == 0) {
            curr->tf = curr->tf / N;
            return;
        } 
        curr = curr->next;
    }
}

void insertFileListNode(InvertedIndexBST node, char *filename, int N) {
    //loop to find the right order 
    FileList curr_prev, curr = node->fileList;
    while (curr != NULL) {
        // compare filename with the exist file name to insert in the right order
        int cmp = strcmp(filename, curr->filename);
        if (cmp == 0) {
            // now that our curr->tf is not n bc tf == n/N
            // so as to make it n again we * N
            curr->tf = curr->tf * N;
            // curr->tf back to n
            curr->tf++;
            return;
        } else if (cmp < 0) { // insert 
            // check if the node to insert is the first node of the fileList
            if (node->fileList == curr) {
                FileList temp = node->fileList;
                node->fileList = newFileListNode(filename);
                node->fileList->next = temp;
                return;
            } else { // in the middle
                curr_prev->next = newFileListNode(filename);
                curr_prev->next->next = curr;
                return;
            }
        } else if (cmp > 0) {
            if (curr->next == NULL) {
                curr->next = newFileListNode(filename);
                return;
            }
        }
        curr_prev = curr;
        curr = curr->next;
    }
}

void printInvertedIndex(InvertedIndexBST tree) {
    char buffer[MAX_WORD][MAX_CHAR];
    int nitem = 0; 
    nitem = putTreeIntoArrayRecur(tree, buffer, nitem);
    arraySortAscendLexi(buffer, nitem);
    FILE *fp = fopen("invertedIndex.txt", "w");
    loopThroughArrayNprintii(buffer, nitem, tree, fp);
}


InvertedIndexBST findKeyRecur(InvertedIndexBST node, char *key) {
    if (node == NULL) {
        return NULL;
    }
    int cmp = strcmp(node->word, key);
    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        return findKeyRecur(node->left, key);
    } else if (cmp > 0) {
        return findKeyRecur(node->right, key);
    }
    return NULL;
}

void loopThroughArrayNprintii(char buffer[][MAX_CHAR], int nitem, InvertedIndexBST tree, FILE *fp) {
    // find the smallest value in tree recursively
    for (int k = 0; k < nitem; k++) {
        InvertedIndexBST temp = findKeyRecur(tree, buffer[k]);
        fprintf(fp, "%s ", temp->word);
        FileList curr = temp->fileList;
        while (curr != NULL) {
            fprintf(fp, "%s ", curr->filename);
            curr = curr->next;
        }
        fprintf(fp, "%c", '\n');
    }
}

void arraySortAscendLexi(char buffer[][MAX_CHAR], int i) {
    char temp [MAX_CHAR];
    for (int k = 0; k < i; ++k) {
            for (int j = k + 1; j < i; ++j) {
                if (strcmp(buffer[k], buffer[j]) > 0) {
                    strcpy(temp, buffer[k]);
                    strcpy(buffer[k], buffer[j]);
                    strcpy(buffer[j], temp);
                }
            }
        }
}

int putTreeIntoArrayRecur(InvertedIndexBST t, char buffer[][MAX_CHAR], int nitem) {
    strcpy(buffer[nitem], t->word);
    nitem++;
    if (t->left != NULL) {
        nitem = putTreeIntoArrayRecur(t->left, buffer, nitem);
    }
    if (t->right != NULL) {
        nitem = putTreeIntoArrayRecur(t->right, buffer, nitem);
    }
    if (t->left == NULL && t->right == NULL) {
        return nitem;
    }
    return nitem;
}


void cmp2insertRecur(InvertedIndexBST node1, InvertedIndexBST node2) {
    if (node1 == NULL) {
        return;
    } else {
        int cmp = strcmp(node1->word, node2->word);
        if (cmp < 0) {
            if (node1->left == NULL) {
                node1->left = node2;
                return;
            } else {
                cmp2insertRecur(node1->left, node2);
            }
        } else if (cmp > 0) {
            if (node1->right == NULL) {
                node1->right = node2;
                return;
            } else {
                cmp2insertRecur(node1->right, node2);
            }
        }
    }
}

FileList newFileListNode(char *filename) {
    FileList node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->filename = filename;
    node->tf = 1; 
    node->next = NULL;
    return node;
}

InvertedIndexBST newInvertedIndexNode(char *key) {
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

char *myStrdup(const char *s1) {
    char *str;
    size_t size = strlen(s1) + 1;
    str = malloc(size);
    if (str) {
        memcpy(str, s1, size);
    }
    return str;
}

int printTreeRecur(InvertedIndexBST node) {
    if (node == NULL) {
        return 0;
    } else {
        printf("%s\n", node->word);
        int goLeft = printTreeRecur(node->left); 
        int goRight = printTreeRecur(node->right);
        return goLeft + goRight;
    }
}
