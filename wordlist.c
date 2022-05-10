#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordlist.h"


/* Read the words from a filename and return a linked list of the words.
 *   - The newline character at the end of the line must be removed from
 *     the word stored in the node.
 *   - You an assume you are working with Linux line endings ("\n").  You are
 *     welcome to also handle Window line endings ("\r\n"), but you are not
 *     required to, and we will test your code on files with Linux line endings.
 *   - The time complexity of adding one word to this list must be O(1)
 *     which means the linked list will have the words in reverse order
 *     compared to the order of the words in the file.
 *   - Do proper error checking of fopen, fclose, fgets
 */
struct node *read_list(char *filename) {
    FILE *f = fopen(filename, "r");

    // Return an error if there was an issue opening the file
    if (f==NULL){
        perror("fopen");
        exit(1);
    }

    // Initialize the tail end of the list
    char word[SIZE];
    struct node *current = NULL;

    // Attach the new node to the front of the list
    while(fgets(word, SIZE+1, f)){
        struct node *node = malloc(sizeof(struct node));
        strncpy(node->word, word, WORDLEN);
        node->next = current;

        current = node;
    }

    if(fclose(f) == 0){
        return current;
    }

    return NULL;
}

/* Print the words in the linked-list list one per line
 */
void print_dictionary(struct node *list) {
    struct node *temp;
    
    // Check if the list is empty
    if (list == NULL){
        printf("List is empty.");

        return;
    }

    temp = list;

    // Traverse the list
    while(temp!=NULL){
        printf("%s\n", temp->word);

        temp = temp->next;
    }
}

/* Free all of the dynamically allocated memory in the dictionary list 
 */
void free_dictionary(struct node *list) {
    struct node *temp = list;
    
    // Traverse each node and free each one
    while(list != NULL){
        temp = list;
        list = list->next;

        free(temp);
    }

}
