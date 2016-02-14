#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <vector>

using namespace std;

struct Folder {
	Folder();
	Folder(const string&, int, int );
	string folderName;
	int parent;
	int numOfFile;
};

int isFile( const string& name );

vector<string> listIn( const string& dirname );

#endif

