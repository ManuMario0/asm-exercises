# Great-or-less
You certainly heard a bit about this game. This is a small game where you have to guess a number between 0 and 1000.
Your task, should you choose to accept it, is to make a small function called 'compare' in assembly language to compare the value entered by the user and the value to guess.

Input :
- %edi : value to guess
- %esi : value enter by the user

Output :
- %eax : -1 if the value is too small, 1 if to big and 0 if equal

Small help :
To compile, use the following command :
	$ gcc main.c your-asm-file.s -o output


PS : and just so you remember, you have to make a Makefile !
