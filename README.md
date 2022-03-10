# wordlebot
A simple bot for solving Wordle.

This bot uses a list of 5 letter words to generate good guesses for Wordle. Unless the Wordle Word of the Day is not in its word list, 
the bot will typically solve a Wordle in 4 guesses or less.

Edit: I found two lists of 5 letter words in the Wordle sitecode. All past wordle Words of the Day are part of the first list, while all words from 
the second list that I tried are allowed as guesses in Wordle. Based on this I suspect that the first list contains all words that can be Words of the Day, 
while the second list contains all words that are allowed as guesses. I added these lists to wordlebot, so that its word lists should now be in sync with Wordle itself and illegal guesses or words that cannot be found should no longer happen.
