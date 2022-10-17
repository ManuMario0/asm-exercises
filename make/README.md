# Welcome to the initiation of make !
Here you'll learn some basic principals.

First of all, I want you to understand how a makefile works, because it's so usefull and you'll need it in the next challenges
The tool 'make', when used, searche the file name 'Makefile' in the current directory to fetch the instructions.

So first step, just create a empty makefile :

	$ touch Makefile

Great ! Now you have your own Makefile ! But it doesn't do anything for now. Let's populate the file a bit !
You'll find a file named 'main.c' in the current diretory. This is a small C 'hello world !' program. I want you to compile it using the Makefile !
But don't worry, I'll help you !

# STEP 1
I'll talk a bit on the structure of a makefile
The structure of a make file is the following :

	target: depedence
		instruction

So, if you want to build the file 'my-fancy-program' from the file 'my-fancy-program.ml', you would write :

	my-fancy-program: my-fancy-program.ml
		ocamlopt my-fancy-program.ml -o my-fancy-program

Basicaly, what make will do is
1. Look for the my-fancy-program.ml file
2. Check if the file has been modified since the last build
3. If this is the case, then use the commands bellow to rebuild it

# STEP 2
You must have use a bit the target 'all' like :

	all: my-fancy-program

This target is a special target. This target tells make what to do when you just specify the target you want to build.
To be more clear, in the precedent example, if you've typed :

	$ make

It would compile nothing but if you typed :

	$ make my-fancy-program

it would build the target 'my-fancy-program'.
The target all is here to enable you to build all the targets you want.

# STEP 3
Now, you'll have some work to do !
Try to build the file 'main.c' !
Hint : the command to compile a C file is :

	$ gcc sourcefile -o output

Great ! You know how to use a Makefile now !
