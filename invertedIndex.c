// COMP2521 Assignment 1
// DO NOT MODIFY THIS FILE

#include <string.h>
#include <ctype.h>

#include "invertedIndex.h"

// Functions for Part 1

/**
 * Normalises a given string. See the spec for details. Note: you should
 * modify the given string - do not create a copy of it.
 */
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

/**
 * This function opens the collection file with the given name, and then
 * generates an inverted index from those files listed in the collection
 * file,  as  discussed  in  the spec. It returns the generated inverted
 * index.
 */
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {

}

/**
 * Outputs  the  given inverted index to a file named invertedIndex.txt.
 * The output should contain one line per word, with the  words  ordered
 * alphabetically  in ascending order. Each list of filenames for a word
 * should be ordered alphabetically in ascending order.
*/
void printInvertedIndex(InvertedIndexBST tree) {

}

// Functions for Part-2

/**
 * Returns  an  ordered list where each node contains a filename and the 
 * corresponding tf-idf value for a given searchWord. You only  need  to
 * include documents (files) that contain the given searchWord. The list
 * must  be  in  descending order of tf-idf value. If there are multiple
 * files with same  tf-idf  value,  order  them  by  their  filename  in
 * ascending order.
*/
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {

}

/**
 * Returns  an  ordered list where each node contains a filename and the
 * summation of tf-idf values of all the matching search words for  that
 * file.  You only need to include documents (files) that contain one or
 * more of the given search words. The list must be in descending  order
 * of summation of tf-idf values (tfIdfSum). If there are multiple files
 * with  the  same tf-idf sum, order them by their filename in ascending
 * order.
 */
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {

}