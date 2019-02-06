#pragma once
/////////////////////////////////////////////////////////////////////////////
// Executive.h - Fulfills Requirements of Execution                        //
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
 * Executive showcases the fulfillment of various requirements of the entire
 * project of Source Code Publisher.
 * It is also used to remove the pre-existing files from the convertedPages
 * directory.
 *
 * Public Interface:
 * =================
 * Executive exec;
 * exec.requirements12();
 * exec.requirements34();
 * exec.requirements56();
 * exec.requirements7();
 * exec.requirements8();
 * exec.deleteExistingFiles();
 *
 * Required Files:
 * ===============
 * FileSystem.h, FileSystem.cpp // Directory and Path classes
 * DirExplorerN.h
 * Display.h
 * Convert.h
 * CodeUtilities.h
 * StringUtilities.h
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 3 Feb 2019
 * - first release
 */
#include<iostream>
#include "../DirExplorer-Naive/DirExplorerN.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h" 
#include "../Display/Display.h"
#include "../Convert/Convert.h"

using namespace Utilities;
using namespace FileSystem;

class Executive
{
public:
	Executive() {};
	static std::string version() { return "ver 1.0"; }

	// Show requirements 

	void requirement12();
	void requirement34();
	void requirement56();
	void requirement7();
	void requirement8();

	// Delete files already present in "convertedPages" directory

	void deleteExistingFiles();
	
};
//----< Show requirement 1 and 2 >------------------------------------------

inline void Executive::requirement12()
{
	std::cout << "\n\nFullfilling Requirement 1: " << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "This Source Code Publisher uses Visual Studio 2017 and its C++ Windows Console Projects." << std::endl;

	std::cout << "\n\nFullfilling Requirement 2: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "The project uses standard streams libraries for all I/O and operators new and delete for ";
	std::cout << "memory management" << std::endl;
}

//----< Show requirement 3 and 4 >-----------------------------------------

inline void Executive::requirement34()
{
	std::cout << "\n\nFullfilling Requirement 3: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Provided Executive, Convert and Display Packages" << std::endl;
	std::cout << "The packages present in the project are: " << std::endl;
	std::vector<std::string> dirs = FileSystem::Directory::getDirectories("..");
	for (auto dir : dirs) 
	{
		if (FileSystem::File::exists("../" + dir + "/" + dir + ".vcxproj") || FileSystem::File::exists("../" + dir + "/" + dir + ".sln"))
			std::cout << dir << std::endl;
	}

	std::cout << "\n\nFullfilling Requirement 4: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Path of the files to be analysed and regular expressions to select filename are accepted ";
	std::cout << "from the command line." << std::endl;
	
}
//----< Show requirement 5 and 6 >-----------------------------------------

inline void Executive::requirement56()
{
	std::cout << "\n\nFullfilling Requirement 5: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "If no file is found, an error message will be displayed." << std::endl;
	std::cout << "Patterns are *.h and *.cpp and regex is [Q](.*)" << std::endl;
	DirExplorerN de("../");
	de.addPattern("*.h");
	de.addPattern("*.cpp");
	de.recurse();
	de.search();
	std::vector<std::string> filesToConvert = de.getFilesToProcess({ "[Q](.*)"});
	if (filesToConvert.empty())
		std::cout << "\n No files found" << std::endl;


	std::cout << "\n\nFullfilling Requirement 6: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Each matching file is converted to a valid html file along with the file text and saved to ";
	std::cout << " folder named convertedPages." << std::endl;
}
//----< Show requirement 7 >------------------------------------------------

inline void Executive::requirement7()
{
	std::cout << "\n\nFullfilling Requirement 7: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Each converted file is displayed in the browser using the child process ";
	std::cout << "and it waits for the child process to exit before displaying the next file." << std::endl;
}
//----< Show requirement 8 >------------------------------------------------

inline void Executive::requirement8()
{
	std::cout << "\n\nFullfilling Requirement 8: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Includes an automated test that demonstrates all the requirements are satisfied." << std::endl;
}
//----< Remove files from convertedPages directory>--------------------------
/*
   Deleting previously converted html files to that running the application
   lead to correct output.
*/

inline void Executive::deleteExistingFiles()
{
	std::string dirPath = "../convertedPages";
	std::vector<std::string> prevFiles = FileSystem::Directory::getFiles(dirPath);
	for (auto files : prevFiles)
		FileSystem::File::remove(dirPath + "/" + files);
}
