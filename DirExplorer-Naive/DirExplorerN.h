#pragma once
/////////////////////////////////////////////////////////////////////////////
// DirExplorerN.h - Naive Directory Navigator                              //
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
/*
 * Module Operations:
 * ==================
 * DirExplorerN provides a class, of the same name, that executes a
 * depth first search of a directory tree rooted at a specified path.
 * Each time it enters a directory, it invokes its member function
 * doDir, and for every file in that directory, it invokes doFile.
 *
 * We call this a "Naive Directory Explorer" because, while it carries
 * out its assigned responsibilities well, there is no way to change
 * what its doDir and doFile functions do, without changing the class
 * itself.  It would be much better to provide a mechanism to allow
 * a using application to supply this processing without changing
 * the Directory Navigator.
 *
 * - DirExplorer-Naive (this project):
 *     Implements basic processing well, but applications have to
 *     change its code to affect how files and directories are
 *     handled.
 *
 * We'll be using the Repository/Cpp solution to illustrate techniques
 * for building flexible software.
 *
 * The patterns and regexes are taken into consideration and the matching
 * files are used for conversion by the Converter package.
 *
 * Public Interface:
 * =================
 * DirExplorerN de(pcl.path());
 * de.addPattern(patt);
 * de.recurse();
 * de.search();
 * find(path_)
 * doDir(fpath);
 * doFile(f);
 * std::vector<std::string> filesToConvert = de.getFilesToProcess(pcl.regexes());
 * filesToConvert = DirExplorerN::getFilesFound();
 * DirExplorerN::searchFiles(reg);
 * filesToConvert = DirExplorerN::getFilesToConvert();
 * de.showStats();
 *
 * Required Files:
 * ===============
 * DirExplorerN.h, DirExplorerN.cpp
 * FileSystem.h, FileSystem.cpp      // Directory and Path classes
 * StringUtilities.h                 // Title function
 * CodeUtilities.h                   // ProcessCmdLine class
 *
 * Maintenance History:
 * ====================
 * ver 1.5 : 2 Feb 2019
 * - Added functionality to get files that match the given regex in command line.
 * ver 1.4 : 24 Jan 2019
 * - Removed all projects except those needed for DirExplorerN.
 * ver 1.3 : 19 Aug 2018
 * - Removed some options to make this version simple.  Those are
 *   implemented in the more advanced navigators, presented here.
 * ver 1.2 : 17 Aug 2018
 * - Moved method definitions to inlines, below the class declaration.
 * ver 1.1 : 16 Aug 2018
 * - Made no recursion default, added option /s for recursion.
 * ver 1.0 : 11 Aug 2018
 * - first release
 */

#include <vector>
#include <iostream>
#include "../FileSystem/FileSystem.h"
#include <regex>

namespace FileSystem
{
  class DirExplorerN
  {
  public:
    using patterns = std::vector<std::string>;
	using files = std::vector<std::string>;

    static std::string version() { return "ver 1.5"; }

    DirExplorerN(const std::string& path);

    // set options for analysis

    void addPattern(const std::string& patt);
    void recurse(bool doRecurse = true);

    // conduct depth first search

    void search();
    void find(const std::string& path);

    // define what happens when a file or dir is encountered

    void doFile(const std::string& filename);
    void doDir(const std::string& dirname);

	// filter out the files that match the given regex in the command line

	void searchFiles(std::vector<std::string> reg);
	void findFiles(const std::vector<std::string> files, const std::vector<std::string> reg);

    // extract traversal statistics 

    size_t fileCount();
    size_t dirCount();
    void showStats();

	// returns files that match given patterns
	
	files getFilesFound();

	//return files that match given regex

	files getFilesToConvert();

	// extract files given empty regex or/and pattern

	std::vector<std::string> getFilesToProcess(const std::vector<std::string> reg);

	

  private:
    std::string path_;
    patterns patterns_;
	files files_;
	files filesConvert_;
    size_t dirCount_ = 0;
    size_t fileCount_ = 0;
    bool recurse_ = false;
  };

  //----< construct DirExplorerN instance with default pattern >-----

  inline DirExplorerN::DirExplorerN(const std::string& path) : path_(path)
  {
    patterns_.push_back("*.*");
  }
  //----< add specified patterns for selecting file names >----------

  inline void DirExplorerN::addPattern(const std::string& patt)
  {
    if (patterns_.size() == 1 && patterns_[0] == "*.*")
      patterns_.pop_back();
    patterns_.push_back(patt);
  }

  //----< set option to recusively walk dir tree >-------------------

  inline void DirExplorerN::recurse(bool doRecurse)
  {
    recurse_ = doRecurse;
  }
  //----< start Depth First Search at path held in path_ >-----------

  inline void DirExplorerN::search()
  {
    find(path_);
  }
  //----< search for directories and their files >-------------------
  /*
    Recursively finds all the dirs and files on the specified path,
    executing doDir when entering a directory and doFile when finding a file
  */

  inline void DirExplorerN::find(const std::string& path)
  {
    // show current directory
    std::string fpath = FileSystem::Path::getFullFileSpec(path);
    doDir(fpath);

    for (auto patt : patterns_)
    {
      std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
      for (auto f : files)
      {
        doFile(f);  // show each file in current directory
			files_.push_back(fpath + "\\" + f);
      }
    }

    std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
    for (auto d : dirs)
    {
      if (d == "." || d == "..")
        continue;
      std::string dpath = fpath + "\\" + d;
      if (recurse_)
      {
        find(dpath);   // recurse into subdirectories
      }
      else
      {
        doDir(dpath);  // show subdirectories
      }
    }
  }
  //----< start searching files that match the regex >---------------

  inline void DirExplorerN::searchFiles(std::vector<std::string> reg)
  {
	  findFiles(files_, reg);
  }
  //----< filters file based on regex matching >---------------------
  /*
	Finds all the files from the vector that matches with the regexes in 
	the command line.
  */

  inline void DirExplorerN::findFiles(const std::vector<std::string> files, const std::vector<std::string> reg)
  {

	  for (auto regex_str : reg)
	  {
		  std::regex r(regex_str);
		  std::vector<std::string> files = files_;
		  for (auto f : files)
		  {
			  std::string fname = FileSystem::Path::getName(f);
			  if (std::regex_match(fname, r))
				  filesConvert_.push_back(f);
		  }
	  }
  }

  //----< an application changes to enable specific file ops >-------

  inline void DirExplorerN::doFile(const std::string& filename)
  {
    ++fileCount_;
    //std::cout << "\n  --   " << filename;
  }
  //----< an application changes to enable specific dir ops >--------

  inline void DirExplorerN::doDir(const std::string& dirname)
  {
    ++dirCount_;
    //std::cout << "\n  ++ " << dirname;
  }
  //----< return number of files processed >-------------------------

  inline size_t DirExplorerN::fileCount()
  {
    return fileCount_;
  }
  //----< return number of directories processed >-------------------

  inline size_t DirExplorerN::dirCount()
  {
    return dirCount_;
  }
  //----< show final counts for files and dirs >---------------------

  inline void DirExplorerN::showStats()
  {
	std::cout << "\n\n Statistics for Naive Directory Navigator: ";
    std::cout << "\n\n  processed " << fileCount_ << " files in " << dirCount_ << " directories";
  }
  //----< return number of files that match patterns >---------------

  inline DirExplorerN::files DirExplorerN::getFilesFound()
  {
	  return files_;
  }
  //----< return number of files that match regexes >----------------

  inline DirExplorerN::files DirExplorerN::getFilesToConvert()
  {
	  return filesConvert_;
  }
  //----< return files that are to be converted >--------------------
  /*
	Returns the files that are to be processed and converted. If
	no regex is passed then files matching the patterns are returned
	and if regex given then filtered matching files are returned.
	If no match found then empty vector returned which is used to
	print error message.
  */

  inline std::vector<std::string> DirExplorerN::getFilesToProcess(const std::vector<std::string> reg)
  {
	  std::vector<std::string> filesToConvert;

	  if (reg.empty())
		  filesToConvert = DirExplorerN::getFilesFound();
	  else {
		  DirExplorerN::searchFiles(reg);
		  filesToConvert = DirExplorerN::getFilesToConvert();
	  }
	  return filesToConvert;
  }

  
}