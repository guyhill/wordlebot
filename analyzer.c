#include <stdlib.h>
#include <stdio.h>

#include "solver.h"

int LOG_LEVEL = 0;


int main(int argc, char **argv) {

    int n_words_active, n_words;
    char *wordlist = read_wordlist("wordle_words_active.txt", "wordle_words_allowed.txt", &n_words_active, &n_words);
    char *active = (char *) malloc(n_words * sizeof *active);
    
    int total_guesses = 0, total_words = 0;
    for (int i=0; i<n_words_active; i++) {
        char *target = wordlist + 5 * i;

        for (int i=0; i<n_words; i++) {
            active[i] = (i < n_words_active);
        }

        int n_guesses = solve(target, wordlist, active, n_words);

        printf("%i: ", n_guesses);
        print_guess(target);

        total_guesses += n_guesses;
        total_words += 1;
    }

    printf("Average number of guesses: %f\n", (double) total_guesses / (double) total_words);
    return EXIT_SUCCESS;
}