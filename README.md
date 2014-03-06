resolution_method
=================

This project is implemented in C++ and solves simples logic problem using the resolution method.
This is a result of a work for the Logic for Computer Science classes at Universidade Federal de Sergipe.
You can analyse its code to learn a little bit more of how Resolution Method works.

Compilation:

extract all files in one directory, or git clone the project on a separate directory and run this command on this directory:

  g++ -o resolution main.cpp -I .

Execution:

To execute then, its simple, just type ./resolution.
On execution time, you may enter any formula in its clausal form, example: {{~a},{a}} or {{a1,a2},{~a3,~a1}}
The program accepts ~ as not operator, and an atom will be anything inside the inner bracket having an ~ operator or not. for example: {{~a,~b},{a,b}} is a formula that results in (¬a v ¬b) ^ (a v b), being a and b atoms.

if the final line of the result is an empty bracket, AKA, {}, it means this formula is an absurd, meaning all its interpretations are false.
