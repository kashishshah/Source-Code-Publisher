/////////////////////////////////////////////////////////////////////////////
// Process.cpp - Demonstrates code pop-up in browser                       //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Lenovo Edge 15, Core i7, Windows 10                        //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
// Author:      Kashish Shah, kshah11@syr.edu                              //
/////////////////////////////////////////////////////////////////////////////

#include "Process.h"
#include <iostream>
#include <conio.h>

#ifdef TEST_PROCESS


int main()
{
	std::cout << "\n  Demonstrating code pop-up in firefox";
	std::cout << "\n ======================================";
	Process p;
	p.title("test application");
	std::ifstream infile;
	std::string fileContent;
	infile.open("../browser.txt"); // reads browser path from a file named browser.txt
	if (infile.fail())
		std::cout << "\n I/O failure opening file as browser.txt doesn't exist." << std::endl << "Create a file named browser.txt and insert the browser path as required." << std::endl;
	std::getline(infile, fileContent);
	std::cout << "\n Current browser path is: " + fileContent << std::endl;
	std::cout << "Enter a valid browser path in the file named browser.txt as per the requirement." << std::endl;
	std::string appPath = fileContent;  // path of application to start
	p.application(appPath);

	std::string htmlPath = "../convertedPages";  // asking firefox to display files present in the directory
	std::vector<std::string> htmlFiles = FileSystem::Directory::getFiles(htmlPath);

	std::cout << "\n  Will start firefox 5 times and each time wait for termination.";
	std::cout << "\n  You need to kill each window (upper right button) to continue.";
	std::cout << "\n  Press key to start";
	_getche();
	int counter = 0;
	int popupFiles = 5; // counter to control the number of files that pop-up

	for (auto html : htmlFiles) {
		if (counter < popupFiles) {
			std::string cmdLine = "/A " + htmlPath + "/" + html;
			p.commandLine(cmdLine);
			std::cout << "\n  starting process: \"" << appPath << "\"";
			std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
			p.create();
			CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
			p.setCallBackProcessing(callback);
			p.registerCallback();
			counter++;
			WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
		}
		else
			break;
	}
	std::cout << "\n  after OnExit";
	std::cout.flush();
	char ch;
	std::cin.read(&ch, 1);
  return 0;
}

#endif
