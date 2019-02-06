#pragma once
/////////////////////////////////////////////////////////////////////////////
// Display.h - Display Processes                                           //
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
/*
 * Module Operations:
 * ==================
 * Display provides a class having the same name, which creates a 
 * process and pops up an application to display the files.
 * On invoking displayFiles() function, files present at the path are
 * displayed in a browser (currently firefox). The path of the browser 
 * application can be changed from browser.txt file.
 * The files are displayed by the child processes and it wait for the previous 
 * process to kill before displaying the next html file.
 *
 * Public Interface:
 * =================
 * Display dis;
 * dis.displayFiles();
 *
 * Required Files:
 * ===============
 * * FileSystem.h, FileSystem.cpp  // Directory and Path classes
 * Process.h                       // Process class
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 31 Jan 2019
 * - first release
 */

#include "../Process/Process.h"
#include "../FileSystem/FileSystem.h"
#include <conio.h>


class Display
{
public:
	Display() {};

	// display code files pop-up

	void displayFiles();
};
// ----< Showcase code pop-up in an application (firefox) >---------
void Display::displayFiles()
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
	std::getline(infile,fileContent);
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

	for(auto html : htmlFiles){
		if (counter < popupFiles){
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
}
