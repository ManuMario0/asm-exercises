# Lets get started with the assembly language !
Here, we will learn the assembly language named x86_64.

# File structure
A assembly file is divided into sections. There are mainly two types of sections : text and data sections.
The text section is for your code and the data section for your data.
But you need to be careful, the data put in the data sections are in read-only mode, so if you want variables, 
put them into the text section. So the basic aspect of an assembly file is :

		.text

	some-code .....

		.data

	some-data .....

# Data
In assembly language, constants are declared as followed :

	label: .type value

So for exmaple, if you want to have a string constant, you use :

	my-const: .string "hello world !"

The main types are :
- int : integer (4 bytes)
- unsigned : unsigned integer (4 bytes)
- double : floating point number (8 bytes)
- string : a string
- char : a charactere / unsigned interger (1 byte)
- short : integer (2 bytes)
- long : integer (8 bytes)

# Code structure
Lets take a look at the code part. You should think of it as a continuous segment of code, there is code every where.
So to distinguish the different parts of the code, we use labels ! For example, you want to tell the compiler wherethe first instruction is.
This is what the main function/label is used for. This tells the commpiler "Hey ! The program start here !".
Labels have a very simple syntax :

	label:
		code ...

This will set a label to the first line of code you write behind it. Unfortunatly, this not enough for the compile, because right now, the label is only visible by
other functions in the file, but not outside the file. So your 'main' label can't be seen by the compiler. To solve this problem, you have to tell somewhere in the file
that this label must be avalable outside the file. To do so, just use the small key word globl :
	.globl main

Great ! Now you have a peace of code which you can compile (using a makefile you wrote of courlse, I don't want to see any compiling 'by hand') !

# Some general functionality
Most commands you'll use can be presised with a suffix. This suffix is mostly used to specifie the size of the operands when it is unclear. For example, if you
want to increment the value stored at the location pointed by %rax, you can use :
	incb	(%rax)
to precise the size of the data, here a byte. The suffix are :
- b : 1 byte
- w : 2 bytes (this is the size of what is called a word)
- d : 4 bytes - stands for double word
- l : 4 bytes - stands for long (l and d are mostly interchangable)
- q : 8 bytes - stands for quad word

The registers also follows there own convention, but it's more subtile.

	6                             3               1
	4                             2               6       8
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| %rax                        | %eax          | %ax   | %al   |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

And follow the same ideas for the %rbx, %rcx, %rdx, %rsi, %rdi, %rdi, %rbp.
For the %r- registers, it's much more easier because they follow the same convention as the intructions :

	6                             3               1
	4                             2               6       8
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| %r-                         | %r-d          | %r-w  | %r-b  |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

# Register use
Most registers have special uses. We will start slowly starting with the ones you should be the most carefull with.

## %rsp (register stack pointer)
When the OS load your program into memory, it reserve some space for a pile. This pile works very strangely because it goes from the higher memory adress and go to the lower ones.
The %rsp register is a pointer to the top of the pile, i.e. it stores the adress of the top of the pile. This register is very important ! You must keep it the same at the begining and at the
end of your functions. This is called a callee saved register because the caller don't have to bother himself to store the value since it won't be modified.
The reason this is so important is because when you call a function with :
	call	foo
you will you current position in the code on the pile so when you call the ret function, the processor will know where to jump to. So if the %rsp register is modified,
if it's value is not restored, the processor will not depile the right adress and your program will crash.

The pile is a very usefull tool when you code, this is where you can put most of the variables you use ! We will go trough some examples in other exercices, don't worry about it right now.

## %rbp (register base pointer)
As well as the top of the pile, this register stores information on the pile, but not the top of the pile but the bottom ! This will become very handy later to use this register !

## %rax (register a extended - or accumulator register)
There are some conventions you should be familiar with. When you code some assembly code, you can almost manage the registers the way you want, but most of the time you
have to interface you funcitons with other languages. Thats why some conventions have been created. This register is used to store the return value of a function.
If you want your function to produce some results and send it back to the caller, you use this register ! So you can trivially infer that this register is not callee saved at all !
So you most use it only for temporary results, never store on a long period data on this register or you'll have some surprise ! You usually use it for arithmetic operations.

## %rdi (register destination index)
The name of this register came from the fact that this register was one used for copy, but now, this register is used to store the first integer arguments of a function. By integer I mean
everything which is not a floating point value. As I said, this is only a convention, if you right function call within you assembly file, you are not forced to follow them, but since
assembly language is already difficult to understand and read, it's easier for other peaple to go through your code if you follow those conventions.

## %rsi (register source index)
This store the second parameter.

## %rdx (register d extended - or data register)
This register store the third parameter.
The other use of this register is for some instructions which operates on extended data, constructing data of the form %rdx:%rax.

## %rcx (register c extended - or count register)
I'll let you guess what this register is used for ...
You usually use this register for counter in loops, but it's just usually and not really a followed convention.

## %r8
Oh my god, the 5th argument ! (don't ask me why the 5th arguments is put in a register called r8 ...)

## %r9
6th and last argument !
"And if I want to give more than 6 arguments to the function ?"
Oops ! Well hopefully there is a way out, those arguments are put on the stack (you'll see later how it works, don't be so impatient !).

## %rbx (register b extended - or base pointer register)
Used for indexed adressing, i.e. to store where you are in a table. The only things to be aware of is the fact that this register is CALLEE SAVED. So just be careful with it, you always have
to restore its value.

## %r10-15
Some registers you can play with. The only thing is that registers 13 to 15 are callee saved.

# Some basic functions
I think this time for you to code a bit ! Because I just gave you a all bunch of information and the only way for you to memorise at least some of it is by practicing.
Lets go with some basics :
- mov : used to move instructions from anything to registers of from registers to everything
- add : used to add the first operand (which can be everything) to the second operand (a register)
- sub : I'll let you guess ...
- imul : ...
- cmp : compare the second operand with the first one and set the flags so that you can use the next instructions
- Jcc : conditional jump. You can replace 'cc' with the following :
	1. e : equal
	2. ne : not equal
	3. g : greater
	4. ge : greater or equal
	5. l : less
	6. le : less or equal
- jmp : jump to the label
- call : function call (when you use this function, you should always return and it will come back to the next instruction)
