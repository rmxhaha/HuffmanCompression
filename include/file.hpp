#ifndef FILE_H
#define FILE_H

#include <string>

struct File {
	File();
	File( const string&, unsigned );
	string fileName;
	unsigned size;
};

#endif