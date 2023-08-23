# Snakes And Ladders
Design an application to mock the game of Snakes And Ladders
# Rules of the Game
- It’s a multiplayer game which has a 10x10 board(numbered 1 to 100), a unique colored
pin(something to indicate the players’ position on the board) for each player and a
dice(values 1 to 6) to be rolled which tells the next place for the current player’s pin.
- All the pins are initially kept outside of the board. The players participate in a round-robin
manner i.e., they initially agree upon a sequence to throw the dice and take subsequent turns
- The dice value indicates the next position the pin should move to. If the new position has a
snake head, the player ends up at the square indicated by the snake tail. If it’s a ladder head,
the player pin ends up at the other ladder head.
- Ladders are meant to be “climbed up”. It helps a player to reach the number 100 faster.
Snakes are meant to do the opposite. For instance, if a player is at position 61, and gets the
number 3 as the dice value, s/he moves the pin to the number 64. If there’s a snake head at
64, the snake tail would always point to a number lesser than 64. The player should move
the pin to the corresponding value. The situation is vice-versa for ladders, in which the player
always moves the pin to a higher value.
- The player who(whose pin) reaches the number 100 first, wins the game. If the dice rolled
points to a number greater than 100, the move is not counted and the turn is passed.
# Assumptions
- There’s at least one possible way to win the game.
- A board block/cell can either have one of the types: snake head, snake tail, any of the ladder
ends or nothing
# Application requirements
- Snakes, Ladders and number of players are decided before the game begins. Once the game
begins, these can’t be changed.
- A rolled dice should have a random value.
- The game ends when a player reaches the number 100.
- After the game ends, the system should display the final values of each player and also declare the winner.
# Class Diagram 
![Screenshot (797)](https://github.com/hksirya/LowLevelDesign/assets/104431269/d23205e5-429a-460c-ab49-638b5187c93c)
# Output

![Screenshot (798)](https://github.com/hksirya/LowLevelDesign/assets/104431269/247d15d2-789f-4ffe-a50a-2e5eb19149ba)
![Screenshot (799)](https://github.com/hksirya/LowLevelDesign/assets/104431269/41eac158-abb7-45fe-984c-5e4ceb16fcc4)

- **Random Key Generating Different Winners**


