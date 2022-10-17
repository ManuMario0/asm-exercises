# Lets get started with the assembly language !
# Here, we will learn the assembly language named x86_64.

## STEP 1
# A assembly file is divided into sections. There are mainly two types of sections : text and data sections.
# The text section is for your code and the data section for your data.
# But you need to be careful, the data put in the data sections are in read-only mode, so if you want variables, 
# put them into the text section. So the basic aspect of an assembly file is :

	.text

some-code .....

	.data

some-data .....

## STEP 2
# In assembly language, constants are declared as followed :

label: .type value

# So for exmaple, if you want to have a string constant, you use :

my-const: .string "hello world !"

# The main types are :
# - int : integer (4 bytes)
# - unsigned : unsigned integer (4 bytes)
# - double : floating point number (8 bytes)
# - string : a string
# - char : a charactere / unsigned interger (1 byte)
# - short : integer (2 bytes)
# - long : integer (8 bytes)

## STEP 3

# Lets take a look at the code part. You should think of it as a continuous segment of code, there is code every where.
# So to distinguish the different parts of the code, we use labels ! For example, you want to tell the compiler wherethe first instruction is.
# This is what the main function/label is used for. This tells the commpiler "Hey ! The program start here !".
# Labels have a very simple syntax :

label:
	code ...

# This will set a label to the first line of code you write behind it. Unfortunatly, this not enough for the compile, because right now, the label is only visible by
# other functions in the file, but not outside the file. So your 'main' label can't be seen by the compiler. To solve this problem, you have to tell somewhere in the file
# that this label must be avalable outside the file. To do so, just use the small key word globl :
	.globl main

# Great ! Now you have a peace of code which you can compile (using a makefile you write of courlse, I don't want to see any compiling 'by hand') !
