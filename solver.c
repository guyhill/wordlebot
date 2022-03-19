#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// LOG_LEVEL = 0 --> don't log anything except the result
// LOG_LEVEL = 1 --> log guesses, results, number of active words
// LOG_LEVEL = 2 --> log list of active words, best guess candidates in addition to LOG_LEVEL 1
extern int LOG_LEVEL;

long filelen(FILE *f) {
    long cur, len;

    cur = ftell(f);
    fseek(f, 0L, SEEK_END);
    len = ftell(f);
    fseek(f, cur, SEEK_SET);

    return len;
}


char *read_wordlist(const char *fname_active, const char *fname_allowed, int *n_words_active, int *n_words) {

    FILE *factive = fopen(fname_active, "r");
    FILE *fallowed = fopen(fname_allowed, "r");

    long len_active = filelen(factive);
    long len_allowed = filelen(fallowed);

    char *wordlist = (char *) malloc((len_active + len_allowed + 1) * sizeof *wordlist);
    fread(wordlist, 1, len_active, factive);
    fread(wordlist + len_active, 1, len_allowed, fallowed);
    wordlist[len_active + len_allowed] = '\0'; // Make it a C string

    *n_words_active = len_active / 5;
    *n_words = (len_active + len_allowed) / 5;
    return wordlist;
}


int match_word(const char *guess, const char *target) {

    int gused[5] = {0};
    int tused[5] = {0};

    int i, j;
    int match = 0;

    int base = 1;
    for (i=0; i<5; i++) {
        if (guess[i] == target[i]) {
            gused[i] = 1;
            tused[i] = 1;
            match += 2 * base;
        }
        base *= 3;
    }

    base = 1;
    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            if (i != j && gused[i] == 0 && tused[j] == 0 && guess[i] == target[j]) {
                match += 1 * base;
                tused[j] = 1;
                break;
            }
        }
        base *= 3;
    }

    return match;
}


void print_match(int match) {
    char letter[] = "BYG";

    for (int i=0; i<5; i++) {
        printf("%c", letter[match % 3]);
        match /= 3;
    }
    printf("\n");
}


int find_largest_remainder(char *guess, char *wordlist, char *active) {

    char *word;
    int counts[243] = {0};
    int i;

    for (word = wordlist, i = 0; *word; word += 5, i++) {
        if (active[i]) {
            int match = match_word(guess, word);
            counts[match] += 1;
        }
    }

    int max_count = 0;
    for (int i=0; i<243; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
        }
    }

    return max_count;
}


void print_guess(char *guess) {

    for (int i=0; i<5; i++) {
        printf("%c", guess[i]);
    }
    printf("\n");
}


char *find_best_guess(char *wordlist, char *active) {

    int min_max_count = 1000000, i;
    char *best_guess = NULL, *guess;

    for (guess = wordlist, i = 0; *guess; guess += 5, i++) {
        int max_count = find_largest_remainder(guess, wordlist, active);
        if (max_count < min_max_count || (max_count == min_max_count && active[i])) {
            if (LOG_LEVEL > 1) {
                printf("%i, %i, %i: ", max_count, min_max_count, active[i]);
                print_guess(guess);
            }
            // Favour words that have smaller remaining number of active words,
            // But for words with the same remaining number of active words, favour words that are themselves active
            min_max_count = max_count;
            best_guess = guess;
        }
    }

    return best_guess;
}


void filter_words(char *guess, int match, char *wordlist, char *active) {

    int i;
    char *word;
    for (word = wordlist, i = 0; *word; word += 5, i++) {
        if (active[i]) {
            int cur_match = match_word(guess, word);
            if (cur_match != match) {
                active[i] = 0;
            } 
        }
    }
}


void print_active_words(char *wordlist, char *active) {

    int i;
    char *word;
    for (word = wordlist, i = 0; *word; word += 5, i++) {
        if (active[i]) {
            print_guess(word);
        }
    }
}


int scan_match() {

    char input[256];
    
    printf("What is the result: ");
    scanf("%5s", &input);

    int base = 1, result = 0;
    for (int i=0; i<5; i++) {
        char letter = toupper(input[i]);
        switch (letter) {
            case 'B': // Black, meaning no match
                break;
            case 'Y': // Yellow, meaning matching letter but no matching position
                result += 1 * base;
                break;
            case 'G': // Green, meaning matching letter and position
                result += 2 * base;
                break;
        }
        base *= 3;
    }
    return result;
}


int count_active(char *active, int n_words) {

    int sum = 0;
    for (int i=0; i<n_words; i++) {
        sum += (int) active[i];
    }
    return sum;
}


int solve(char *target, char *wordlist, char *active, int n_words) {

    int n_guesses = 0;
    for (;;) {
        char *best_guess;
        int n_active = count_active(active, n_words);
        if (LOG_LEVEL > 1) {
            print_active_words(wordlist, active);
        }
        if (LOG_LEVEL > 0) {
            printf("Number of possible words: %i\n", n_active);
        }
        if (n_active == 0) {
            return -1;
        }
        best_guess = find_best_guess(wordlist, active);
        if (LOG_LEVEL > 0) {
            printf("I'm guessing: ");
            print_guess(best_guess);
        }
        n_guesses += 1;

        int result_match;
        if (target[0] == '?') {
            result_match = scan_match();
        } else {
            result_match = match_word(best_guess, target);
            if (LOG_LEVEL > 0) {
                printf("Result: ");
                print_match(result_match);
            }
        }
        if (result_match == 242) {  
            return n_guesses;
        }
        filter_words(best_guess, result_match, wordlist, active);
    }
}
