#include "../include/archieve.hpp"

#include <iostream>
#include <windows.h>
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
//            myfile << infile.rdbuf();
//            infile.tellg(0,ios::beg);
            infile.unsetf(ios_base::skipws);
            char c;
            while(true){
                infile >> c;
                if( infile.eof() ) break;
                myfile << c;
            }
            infile.close();
        }
    }
}

void buildFolder( Header& head, const string& ftarget ){
    cout << "R\n";
    for( auto& fl : head.folders ){
        string cdir = ftarget + '\\' +getFullDir(&fl,&head);
        cout << cdir << endl;
        CreateDirectory(cdir.c_str(),NULL);
    }
}

