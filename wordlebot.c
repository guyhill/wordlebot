#include <stdlib.h>
#include <stdio.h>

#include "solver.h"

int LOG_LEVEL = 2;


int main(int argc, char **argv) {

    int n_words_active, n_words;
    char *wordlist = read_wordlist("wordle_words_active.txt", "wordle_words_allowed.txt", &n_words_active, &n_words);
    
    char *active = (char *) malloc(n_words * sizeof *active);
    for (int i=0; i<n_words; i++) {
        active[i] = (i < n_words_active);
    }

    char target[6];
    printf("Target word: ");
    scanf("%s", target);

    int n_guesses = solve(target, wordlist, active, n_words);

    if (n_guesses > 0) {
        printf("I win after %i guesses!", n_guesses);
    } else {
        printf("I'm flummoxed!");
    }
    return EXIT_SUCCESS;
}