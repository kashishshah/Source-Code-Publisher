/////////////////////////////////////////////////////////////////////////////
// Convert.cpp - Demonstrate conversion of files to HTML                   //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Lenovo Edge 15, Core i7, Windows 10                        //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Author:      Kashish Shah, kshah11@syr.edu                              //
/////////////////////////////////////////////////////////////////////////////

#include "Convert.h"
#ifdef TEST_CONVERT // only compile the following when defined

int main()
{
	std::string dirPath("../convertedPages");
	std::vector<std::string> prevFiles = FileSystem::Directory::getFiles(dirPath);
	for (auto files : prevFiles)
		FileSystem::File::remove(dirPath + "/" + files);

	Convert cvt;
	cvt.convertToHtml("../Executive/Executive.h");
	cvt.convertToHtml("../Executive/Executive.cpp");
	return 0;
}
#endif