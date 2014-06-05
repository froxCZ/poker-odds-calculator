# Texas holdem poker odds calculator #

Based on input (my hand and table cards) the program calculate the odds of winning. The method used for calculating odds is Monte Carlo. As we enter input the program randomly assigns 2 cards to all other players and up to 5 cards to table if necessary. Then, it calculates rank of best figure that each player has and founds a winner. This is repeated thousands of times and the chance of us winning is equal to number of times we had the best figure divided by number of played games. Program is fully finished in serial version.

## Program Interaction ##
Whole program is controlled over command line by typing commands like “new”, “smlt” (simulate), “add” (..card). Cards are entered in format where first character (capital or number) is rank followed by suit (first letter of suit’s name). It starts by prompting for 2 cards on hand, when entered, it starts computing chance. It can be stopped by ctrl + C key press and then it listens for next commands so user can use "add" command to enter flop, turn or river cards. 

## Card representation ##
There is CardSet class that keeps track of assigned (or randomly assigned) cards. For easier evaluation of best figure, it has array of suits (counts how many same colors it has), array of ranks (counts how many same ranks it has) and then 2D bool array with one dimension for suit and one dimension for rank (stores which cards I have).
Each Game has playersN +1 CardSets. +1 for table, but that is just for printing. Every card in table is also duplicated to each CardSet. Card itself is represented by two ints: suits and ranks.

## Hand evaluation ##
Evaluating starts by checking from best to worst figure if it is present. Best is Straight Flush, so it checks if 5 consecutive cards of same suit are present. It always checks from best card to worst, since in case of 2 Straight Flush, the highest Flush wins. When figure is found, it returns STRAIGH_FLUSH constant + highest rank of flush sequence. Then we can just compare the scores of all hands and even if there is a tie, the truly best figure will win (because of the added value of card rank)
What about figure like full house? In case of 2 full houses, simple adding of pair and three cards value won’t work. We have to be able to say that 33322 is better than 22233. If we just added the card ranks it would be 5 and a tie. What I do is shifting the card rank to left by its significance * 4 bits. Times 4 because card rank takes 4 bits. In case of 33322 full house, the added value fo figure to FULL_HOUSE constant would be 3<<(4*1)+ 2. 
Worst case for card significance is the highest card, when we have to represent 5 best cards by score number. That means highest card will be shifted 16 times to left, second highest 12times,8 times, 4 times and last one zero times.
Just a note, that FIGURE constants must be higher than 12(ACE)<<16 and also gaps between all FIGURE constants must be higher than 12(ACE)<<16. Int is enough for that.
When all players’s hands are evaluated and computed score, it just finds the maximum and returns if the user won the game.

## Conclusion ##
After implementing serial version of this I found out that actually no parallelization is needed. Even with 8 players, the computed chance of winning in first 5 seconds stayed roughly the same for the rest of the computation. How to make it harder? I will change to regular poker where user have to discard cards and implement algorithm, that will tell the user which card to discard. I think about using monte carlo minimax (but not sure if it gives any major advantage and is suitable for it, yet) I need to think about it more.