Source Code Publisher
===============================================================================================
Overview:

- This application takes a path, patterns (*.h, *.cpp) and regex ([A-K](.*)) in the input and 
  recursively searches in all the directories present in that provided path and finds all the 
  files that match the given patterns.
  
- Thereafter, these files are further filtered out to obtain the files matching to the regular
  expressions.
  
- These files are then converted into html files, with all its contents intact. To perform 
  this conversion efficiently and correctly, the escape sequences are replaced by their
  corresponding strings (for eg. '<' with "&lt", '>' with "&gt", '&' with "&amp").
  
- After performing this conversion, the files are displayed in the browser using one after the 
  other i.e. it waits for the window to be killed to pop-up the next file in the browser which
  is done through processes.
  
- The "browser.txt" file contains the path of the browser which is to be used. To use another 
  browser, give its path in "browser.txt" file.
  
===============================================================================================

***************The application is developed in Microsoft Visual Studio 2017 C++ ***************
  
===============================================================================================
Package Information:

Information about the packages can be found in the .h files of that particular package.
  
===============================================================================================
  How to run the application?
  
  - clean.bat : cleans the unwanted temporary files from the project directory 
                (Use it before compiling).
  - compile.bat : compiles all the packages.
  - run.bat : Used to run the application.
  
 ===============================================================================================
