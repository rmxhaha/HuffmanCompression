#include "../include/archieve.hpp"

#include <iostream>
using namespace std;

void fillArchieve( Header& header, ofstream& myfile, const string& ftarget ){
    int fileidx = 0;
    for( auto& fl : header.folders ){
        string cdir = getFullDir(&fl,&header);
        cout << cdir << "\\ (" << fl.numOfFile <<")\n";
        for(int limit = fileidx + fl.numOfFile; fileidx < limit; ++ fileidx ){
            string fullPath = ftarget + "\\" + cdir + "\\" + header.files[fileidx].fileName;
            cout << fullPath << " " << (header.files[fileidx].size) << endl;
            ifstream infile( fullPath );
            myfile << infile.rdbuf();
            infile.close();
        }
    }
}

