#include "../include/folder.hpp"
#include "dirent.h"

int isFile( const string& name )
{
    DIR* directory = opendir(name.c_str());

    if(directory != NULL)
    {
     closedir(directory);
     return 0;
    }

    if(errno == ENOTDIR)
    {
     return 1;
    }

    return -1;
}

vector<string> listIn( const string& dirname ){
	DIR           *d;
	struct dirent *dir;
	d = opendir(dirname.c_str());
	vector<string> fileList;

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			fileList.push_back( dir->d_name );
		}

		closedir(d);
	}

	return fileList;
}

Folder::Folder(){
    folderName = '';
    parent = -1;
    numOfFile = 0;
}

Folder::Folder(const string& Fn, int p, int n){
    folderName = Fn;
    parent = p;
    numOfFile = n;
}
