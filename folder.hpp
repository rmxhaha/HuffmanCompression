#ifndef FOLDER_H
#define FOLDER_H

#include <string>

struct Folder {
	Folder();
	Folder(const string&, int, int );
	string folderName;
	int parent;
	int numOfFile;
};

#endif

