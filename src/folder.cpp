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

void listIn(vector<string>& fileList, const string& dirname ){
	DIR           *d;
	struct dirent *dir;
	d = opendir(dirname.c_str());

    int x = 0; // ignore . and .. (the first 2)
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
		    if( x++ >= 2 )
                fileList.push_back( dir->d_name );
		}

		closedir(d);
	}
}

Folder::Folder(){
    folderName = "";
    parent = -1;
    numOfFile = 0;
}

Folder::Folder(const string& Fn, int p, int n){
    folderName = Fn;
    parent = p;
    numOfFile = n;
}
