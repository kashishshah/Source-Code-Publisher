/////////////////////////////////////////////////////////////////////////////
// Executive.cpp - Execute working of Source Code Publisher                //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Lenovo Edge 15, Core i7, Windows 10                        //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Author:      Kashish Shah, kshah11@syr.edu                              //
/////////////////////////////////////////////////////////////////////////////

#include "Executive.h"
#include <iostream>
#ifdef TEST_EXECUTIVE 

ProcessCmdLine::Usage customUsage()
{
	std::string usage;
	usage += "\n  Command Line: path [/option]* [/pattern]*";
	usage += "\n    path is relative or absolute path where processing begins";
	usage += "\n    [/option]* are one or more options of the form:";
	usage += "\n      /s - walk directory recursively";
	usage += "\n    [pattern]* are one or more pattern strings of the form:";
	usage += "\n      *.h *.cpp *.cs *.txt or *.*";
	usage += "\n";
	return usage;
}

int main(int argc, char* argv[]){	
	try{
		Title("Demonstrating Executive for Source Code Publisher, " + Executive::version());
		ProcessCmdLine pcl(argc, argv);
		pcl.usage(customUsage());
		if (pcl.parseError()){
			pcl.usage();
			return 1;
		}
		DirExplorerN de(pcl.path());
		for (auto patt : pcl.patterns())
			de.addPattern(patt);
		if (pcl.hasOption('s'))
			de.recurse();
		Executive exec;
		exec.requirement12();
		de.search();
		de.showStats();
		exec.deleteExistingFiles();
		std::vector<std::string> filesToConvert = de.getFilesToProcess(pcl.regexes());
		exec.requirement34();
		preface("Command Line: ");
		pcl.showCmdLine();
		putline();
		pcl.showRegexes();
		std::cout << "\n\nRegexes in command line are: ";
		pcl.showRegexes();
		std::cout << "\nFiles that match the given regex/es are: " << std::endl;
		for (auto file : filesToConvert)
			std::cout << "\n" << FileSystem::Path::getName(file) << std::endl;
		exec.requirement56();
		if (filesToConvert.empty())
			std::cout << "\n\nNo matching files found.";
		else{
			Convert cvt;
			for (auto file : filesToConvert)
				cvt.convertToHtml(file);
			Display dis;
			exec.requirement7();
			dis.displayFiles();
		}
		exec.requirement8();
		return 0;
	}
	catch (std::exception e){
		std::cout << e.what();
		return 0;
	}
}
#endif
