# Market Making Dice Game by Raj
## Overview
The objective of the game is to gain the most profit over the long run using simple probabilistic reasoning. <br><br>
The game works by rolling 3 die, of which anywhere between 0-3 of them may have visible results. The game will generate a bid and an ask price in the format, "the market maker quotes X at Y." Here X is the bid, or the price the market maker is willing to buy at, and Y is the ask, or the price the market maker is willing to sell at. <br><br>
Using the information given to you, determine whether you'd like to go short, buy, or skip the turn. You must also determine what quantity you'd like to purchase; purchasing a quantity beyond the limits of your balance will result in a $50 deduction from your balance. <br><br>
If you don't skip the turn, the game will reveal the dice's values, at which point you must determine how much profit (or loss) was accrued during the round. Failing to properly calculate your profit will result in a $50 deduction (or an additional $50 in the case of a loss). Otherwise, your balance will be adjusted for the round's winnings/losses. <br><br>
If you do skip the turn, or if the round is played through, a new round will begin. The game will continue forever unless your balance reaches $0 (or lower). <br><br>

## Inputs
Please only input "short", "buy", or "skip". <br>
Please only input integer values. <br>
To close out of the program, press control + C (on macOS). <br>

## Improvements
For any feedback, concerns, advice, etc. please email raj.bala2800@gmail.com. <br>
### Future Updates:
* player's turn will be timed
* random events may occur during gameplay
* the game will shift from text-based to 2D graphics
