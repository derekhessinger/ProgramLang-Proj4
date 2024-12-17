/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 11/10/24
 * 
 * Counts the number of word occurences in a txt
 *
 * gcc -o wordcounter wordcounter.c
 * ./wordcounter wordcountertest.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist.c"

// Structure to hold word and count
typedef struct {
    char word[50];
    int count;
} WordCount;

// Comparison function for finding words
int compare_words(void* target, void* node_data) {
    WordCount* target_word = (WordCount*)target;
    WordCount* node_word = (WordCount*)node_data;
    return (strcasecmp(target_word->word, node_word->word) == 0);
}

// Function to clean a word (remove punctuation and convert to lowercase)
void clean_word(char* dest, const char* src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (isalpha(src[i])) {
            dest[j] = tolower(src[i]);
            j++;
        }
    }
    dest[j] = '\0';
}

// Comparison function for sorting words by frequency
int compare_frequency(const void* a, const void* b) {
    WordCount* word1 = *(WordCount**)a;
    WordCount* word2 = *(WordCount**)b;
    // Sort by count in descending order
    return word2->count - word1->count;
}

// Function to print word data
void print_word(void* data) {
    WordCount* word_data = (WordCount*)data;
    printf("%s: %d\n", word_data->word, word_data->count);
}

// Function to free word data
void free_word(void* data) {
    free(data);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Create linked list
    LinkedList* word_list = ll_create();
    char buffer[50];
    char cleaned_word[50];


    // Read words from file
    while (fscanf(fp, "%s", buffer) == 1) {
        // Clean the word
        clean_word(cleaned_word, buffer);
        if (strlen(cleaned_word) == 0) continue;

        // Create a temporary WordCount for searching
        WordCount temp = {0};
        strcpy(temp.word, cleaned_word);


        // Try to find the word in the list
        WordCount* existing = ll_find(word_list, &temp, compare_words);

        if (existing) {
            existing->count++;
        } else {
            WordCount* new_word = malloc(sizeof(WordCount));
            if (!new_word) {
                printf("Memory allocation failed\n");
                continue;
            }
            strncpy(new_word->word, cleaned_word, sizeof(new_word->word) - 1);
            new_word->word[sizeof(new_word->word) - 1] = '\0';
            new_word->count = 1;
            ll_push(word_list, new_word);  // Using ll_push instead of ll_append
        }
    }
    fclose(fp);

    // Create array for sorting
    int total_words = ll_size(word_list);
    WordCount** word_array = malloc(total_words * sizeof(WordCount*));
    
    // Copy words to array
    Node* current = word_list->head_ptr;
    for (int i = 0; i < total_words; i++) {
        word_array[i] = current->data_ptr;
        current = current->next_ptr;
    }

    // Sort array by frequency
    qsort(word_array, total_words, sizeof(WordCount*), compare_frequency);

    // Print top 20 words (or all if less than 20)
    printf("\nTop %d words by frequency:\n", (total_words < 20) ? total_words : 20);
    printf("------------------------\n");
    for (int i = 0; i < total_words && i < 20; i++) {
        printf("%s: %d\n", word_array[i]->word, word_array[i]->count);
    }

    // Cleanup
    free(word_array);
    ll_clear(word_list, free_word);
    free(word_list);

    return 0;
}