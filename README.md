# wordlebot
A simple bot for solving Wordle (https://www.nytimes.com/games/wordle/index.html).

This bot uses a list of 5 letter words to generate good guesses for Wordle. Unless the Wordle Word of the Day is not in its word list, 
the bot will typically solve a Wordle in 4 guesses or less.

Edit: I found two lists of 5 letter words in the Wordle sitecode. All past wordle Words of the Day are part of the first list, while all words from 
the second list that I tried are allowed as guesses in Wordle. Based on this I suspect that the first list contains all words that can be Words of the Day, 
while the second list contains all words that are allowed as guesses. I added these lists to wordlebot, so that its word lists should now be in sync with Wordle itself and illegal guesses or words that cannot be found should no longer happen.

Edit: the bot has to do 3.55 guesses on average to find any word on the list of potential Words of the Day. Here's a list of the number of words found in the indicated number of guesses:

1 guess - 1 word
2 guesses - 67 words
3 guesses - 970 words
4 guesses - 1188 words
5 guesses - 83 words

Not a single word requires more than 5 guesses. This means that wordlebot can guess all words within Wordle's 6 guess limit.
