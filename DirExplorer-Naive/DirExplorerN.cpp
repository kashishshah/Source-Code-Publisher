/////////////////////////////////////////////////////////////////////////////
// DirExplorerN.cpp - Demonstrates Naive Directory Navigator               //
// ver 1.5                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Lenovo Edge 15, Core i7, Windows 10                        //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
// Author:      Kashish Shah, kshah11@syr.edu                              //
/////////////////////////////////////////////////////////////////////////////

#ifdef TEST_DIREXPLORERN  // only compile the following when defined

#include "DirExplorerN.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"

using namespace Utilities;
using namespace FileSystem;

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

int main(int argc, char *argv[])
{
  Title("Demonstrate DirExplorer-Naive, " + DirExplorerN::version());

  ProcessCmdLine pcl(argc, argv);
  pcl.usage(customUsage());

  preface("Command Line: ");
  pcl.showCmdLine();
  putline();

  if (pcl.parseError())
  {
    pcl.usage();
    std::cout << "\n\n";
    return 1;
  }

  DirExplorerN de(pcl.path());
  for (auto patt : pcl.patterns())
	  de.addPattern(patt);

  if (pcl.hasOption('s'))
	  de.recurse();

  de.search();
  de.showStats();
  std::string dirPath = "../convertedPages";
  std::vector<std::string> prevFiles = FileSystem::Directory::getFiles(dirPath);
  for (auto files : prevFiles)
	  FileSystem::File::remove(dirPath + "/" + files);

  std::vector<std::string> filesToConvert = de.getFilesToProcess(pcl.regexes());
  std::cout << "Regexes in command line are: ";
  pcl.showRegexes();
  std::cout << "\nFiles that match the given regex/es are: " << std::endl;
  for (auto file : filesToConvert)
	  std::cout << "\n" + FileSystem::Path::getName(file) << std::endl;

  if (filesToConvert.empty())
	  std::cout << "No files found";
  else
  {	
	  std::cout << "\n Files to convert to html are: " << std::endl;
	  for (auto file : filesToConvert)
		  std::cout << "\n" + file << std::endl;
  }
  std::cout << "\n\n";
  return 0;
}

#endif