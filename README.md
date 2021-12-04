# WinKey---A-Simple-C-Keylogger
A simple C++ keystroke logger built for windows

NOTE: 
(1) This is an improvement of the code found here: https://geekviews.tech/how-to-make-a-c-keylogger/
I realized that when replicated, the code did not execute correctly, so I rewrote it to work correctly. Some of the changes I made are that I modified it to use ASCII characters and to use memory addresses in conjunction with GetAsyncKeyState(). I did extensive research on the functions used in this program. Therefore not all of the code present is mine, and much of the credit is due to the author of the above article.
(2) This is PURELY for educational purposes. I learned a lot in writing this software and have included extensive comments in my code so that others may learn from it as well.

HOW IT WORKS:
The keylogger collects alphanumeric inputs (but not input from the num buttons on the right side of the keyboard, although they can easily be added). This includes spaces " ", tabs "  ", and enters "\n". 

The program treats a char, inp, as an ascii value that is read by the filestream and appears as cleartext in the log.txt file. This program takes advantage of C++'s implicit type conversions as inp is used as an int that represents a corresponding ascii value.

It tracks the user's key inputs using (GetAsyncKeyState() & 0x0001). This checks if the least significant bit is set for GetAsyncKeyState(), which tells us if the key has been pressed and whether it is being held down. This allows us to collect what I refer to as 'real' key inputs. A common problem with GetAsyncKeyState is that if a user presses a key for more than a short moment, it will continuously collect key presses until they lift their finger off of the key. By checking the least significant bit for GetAsyncKeyState(), we check to see if the key has been pressed since the last query, allowing for a pause between 'real' inputs.

One particular challenge for this program was the backspace key. There aren't many efficient/clear solutions in common C++ libraries for dealing with deleting the last char of a txt file, so the solution employed makes use of functions that were probably written with C and UNIX in mind. The solution to this problem is commented in some detail in the source code (which is included in this repository). It boils down to truncating the file size by 1 byte (which is the size of an ASCII char).
