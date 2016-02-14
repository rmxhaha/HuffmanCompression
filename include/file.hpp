#ifndef _FILE_H
#define _FILE_H

#include <string>

using namespace std;

struct File {
	File();
	File( const string&, unsigned );
	string fileName;
	unsigned size;
};

#endif
