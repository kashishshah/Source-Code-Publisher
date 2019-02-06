#pragma once
/////////////////////////////////////////////////////////////////////////////
// Convert.h - Convert files to HTML                                       //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Lenovo Edge 15, Core i7, Windows 10                        //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Author:      Kashish Shah, kshah11@syr.edu                              //
/////////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * Convert provides a class of same name which on execution converts
 * the file/s that are extracted in DirExplorerN.h to HTML files with
 * the same name. This class appends the html tags to the content
 * of the code and replaces the escape sequences with the valid
 * strings. This conversion will result into all the converted html files 
 * getting stored in convertedPages directory which can be later used by
 * Display package to pop-up these files in browser.
 *
 * Public Interface:
 * =================
 * Convert cvt;
 * cvt.convertToHtml(file);
 * convertFileContent(c)
 *
 * Required Files:
 * ===============
 * FileSystem.h, FileSystem.cpp // Directory and Path classes
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 26 Jan 2019
 * - first release
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "../FileSystem/FileSystem.h"

class Convert {
public:
	Convert() {};
	
	// does conversion of the file to .html 
	void convertToHtml(const std::string& filesToConvert);
	
	// replaces escape sequences
	
	std::string convertFileContent(char& c);
};
//----< convert the file to .html file >---------------------
/*
	Converts the entire file to html file with .html extension and
	inserting the tags for html.
*/

void Convert::convertToHtml(const std::string& fileToConvert)
{
	try {
		std::string filename = fileToConvert;
		std::string filename1 = FileSystem::Path::getName(fileToConvert);;
		std::string outputname;

		char c;
		std::ifstream inStream;
		std::ofstream outStream;

		inStream.open(filename.c_str());
		if (inStream.fail()) {
			std::cout << "I/O failure opening file." << std::endl;
			exit(1);
		}

		outputname = "../convertedPages/" + filename1 + ".html"; // Creating output file
		outStream.open(outputname.c_str());

		outStream << "<HTML>" << std::endl;
		outStream << "<TITLE>" << filename1 << "</TITLE>" << std::endl;
		outStream << "<BODY>" << std::endl;
		outStream << "<PRE>" << std::endl;

		while (!inStream.eof()) {
			inStream.get(c);  
			outStream << Convert::convertFileContent(c);
		}
		
		outStream << "</PRE>" << std::endl;
		outStream << "</BODY>" << std::endl << "</HTML>" << std::endl;
		inStream.close();
		outStream.close();
		std::cout << "\n";
		std::cout << "Conversion of " + FileSystem::Path::getName(fileToConvert) + " successful.  Results are in file " << FileSystem::Path::getFullFileSpec(outputname) << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
}
//----< replace the escape sequences with valid string >-----
/*
	While iterating through the contents of the file, replace
	'<' with "&lt" and '>' with "&gt".
*/

std::string Convert::convertFileContent(char& c) {
	try {
		if (c == '<')
			return "&lt;";
		else if (c == '>')
			return "&gt;";
		else if (c == '&')
			return "&amp";
		else
		{
			std::string s(1, c);
			return s;
		}
	}
	catch (std::exception e) {
		std::cout << e.what();
		return "";
	}
}