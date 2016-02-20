#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <vector>

using namespace std;

struct Folder {
	Folder();
	Folder(const string& path, int, int );
	string folderName;
	string parentPath;
	string folderPath;
	/**
        in normal case such as
        E:\abc\def\
        folderName = def
        folderPath = E:\abc\def\
        parentPath = E:\abc\

        in edge case scenario such as
        E:\
        folderName = E
        folderPath = E:\
        parentPath = E:
	*/

    bool isDrivePath; // special case
	int parent;
	int numOfFile;
};

int isFile( const string& name );

void listIn( vector<string>& list, const string& dirname );

#endif

