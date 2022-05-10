#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "constraints.h"

/* Create and initialize a constraints struct. 
 * Sets the fields to 0 or empty string.
 * Return a pointer to the newly created constraints struct.
 */
struct constraints *init_constraints() {
    struct constraints *c  = malloc(sizeof(struct constraints));
    
    // Iterate over the array and set to ""
    for (int i = 0; i < SIZE; i++){
        strcpy(c->must_be[i], "");
    }

    // Set cannot_be to ""
    strcpy(c->cannot_be, "");
    return c;
}

/* Update the "must_be" field at "index" to be a string 
 * containing "letter"
 * The tile at this index is green, therefore the letter at "index"
 * must be "letter"
 */
void set_green(char letter, int index, struct constraints *con) {
    assert(islower(letter));
    assert(index >= 0 && index < SIZE);
    
    // Add the letter to must_be
    char row[2];
    row[0] = letter;
    row[1] = '\0';
    strncpy(con->must_be[index], row, 2);
}

/* Update "con" by adding the possible letters to the string at the must_be 
 * field for "index".
 * - index is the index of the yellow tile in the current row to be updated
 * - cur_tiles is the tiles of this row
 * - next_tiles is the tiles of the row that is one closer to the solution row
 * - word is the word in the next row (assume word is all lower case letters)
 * Assume cur_tiles and next_tiles contain valid characters ('-', 'y', 'g')
 * 
 * Add to the must_be list for this index the letters that are green in the
 * next_tiles, but not green in the cur_tiles or green or yellow in the 
 * next_tiles at index.
 * Also add letters in yellow tiles in next_tiles.
 */
void set_yellow(int index, char *cur_tiles, char *next_tiles, 
                char *word, struct constraints *con) {

    assert(index >=0 && index < SIZE);
    assert(strlen(cur_tiles) == WORDLEN);
    assert(strlen(next_tiles) == WORDLEN);
    assert(strlen(word) == WORDLEN);

    char belongs_in[SIZE];
    int curr_ind = 0;

    for(int i=0;i<WORDLEN;i++){
        // Check for the conditions
        if (next_tiles[i] == 'g' && cur_tiles[i] != 'g'){
            if (i != index){
            belongs_in[curr_ind] = word[i];
            curr_ind++;
            }
        // Check for yellows
        } else if (next_tiles[i] == 'y'){
            belongs_in[curr_ind] = word[i];
            curr_ind++;
        }
    }

    belongs_in[curr_ind] = '\0';
    strncpy(con->must_be[index], belongs_in, SIZE);
}

/* Add the letters from cur_word to the cannot_be field.
 * See the comments in constraints.h for how cannot_be is structured.
 */
void add_to_cannot_be(char *cur_word, struct constraints *con) {
    assert(strlen(cur_word) <= WORDLEN);
    int index = 0;

    // Change all characters in word in cannot_be to 1
    for(int i=0; i < strlen(cur_word); i++){
        index = cur_word[i] - 'a';
        con->cannot_be[index] = 1;
    }
}

void print_constraints(struct constraints *c) {
    printf("cannot_be: ");

    // Iterate over cannot be and print characters that are 1
    for (int i=0; i < ALPHABET_SIZE; i++){
        if (c->cannot_be[i] == 1){
            printf("%c ", i + 'a');
        }
    } 
    
    printf("\nmust_be\n");

    int current_char = 0;

    // Iterate over each row and index and print the characters
    for (int i=0; i < WORDLEN; i++){
        printf("[%d] ", i);
        while(c->must_be[i][current_char] != '\0'){
            printf("%c ", c->must_be[i][current_char]);
            current_char++;
        }

        if (i != WORDLEN - 1){
            printf("\n");
        }
        current_char=0;
    }

    printf("\n");
}

/* Free all dynamically allocated memory pointed to by c
 */
void free_constraints(struct constraints *c) {
    free(c);
}