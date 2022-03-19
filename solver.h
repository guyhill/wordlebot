char *read_wordlist(const char *fname_active, const char *fname_allowed, int *n_words_active, int *n_words);
int solve(char *target, char *wordlist, char *active, int n_words);
void print_guess(char *guess);