# Game of life

Have you heard about the game of life ? If you have, you can skip to STEP 2 !

## STEP 1

Didn't you eer dreamed about simulating life ? Well, this is what this game is all about !
The game of life simulate the life of small 2D cells living in a grid. The rules followed for the simulation are the following :

- Each cell on the grid is either alive or dead
- When a cell is isolated (have only one or no neighbor), it will die
- When a cell is overcrowded (have stricly more than 3 neighbors), it will die
- If a dead cell have three (no more, no less) alive cells next to it, it will be alive

We call adjacent cells the ones which are next to each other either diagonaly or straitforward
As an exemple the following grid :

o o o x o
x o o o x
o x x x x

will evolve in

o o o o o
o x o o x
o x x x x

## STEP 2
Now that you know the rules, you know what you need to do !
You will write a function named 'step' which will compute one step of the game of life board.

Specification :

Input :
- %rdi : hight of the map
- %rsi : width of the map
- %rdx : pointer to the table

Output :
- %rax : pointer to the map updated

Table encoding :
- Each element of the table is coded on one byte
- The table is store in a line. To access the character 3 of the line 2, you have to jump to the location %rdx+2*%rsi+3
- The dead cells are represented by 0, alive one by 1
