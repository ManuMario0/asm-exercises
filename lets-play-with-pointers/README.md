# Lets play with pointers !
Welcome the show ! Here you'll learn to use pointers !

# But wait, what is a pointer ?
Well, good quesiton. A pointer is an adress ! This is exactly and only an adress !

"But how do I use it in assembly ?"

Suppose you've got the pointer to an integer in %rdi. To copy the value pointed by %rdi in %rax, you'll use the command :

	movq	(%rdi), %rax

So what you tell by putting parentethis is that you don't want the value in %rdi but the value in the memory location stored in %rdi !
Suppose now you've got a table of char (the size of 1 byte) and the location of the first element of the table is stored in %rdi. If you
want to access to the 5th element of the table, you can just write :

	movb	5(%rdi), %al

(just be carefull to use the right suffix for the mov instruction :)

# Trrreeeeeeeeeees !!!
Okay so this one is very tricky, but don't panic ! You can do it ! And if your stuck, always remember that there are hints to help you figured it out !

## The structure used
We will store each element of our tree in the following way :

	0                   64                      128
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| value (integer)   | left child (pointer)  | right child (pointer) |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

There are no left (resp. right) if the pointer is NULL (= 0).

## The task
You'll be given a tree. I want you to reorder the tree, conserving the root, so that it became a research binary tree.

Specifications :

Your function should be called 'order'

Input:
- %rdi : pointer to the root of the tree

Output:
- %rax : pointer to the tree reordered
