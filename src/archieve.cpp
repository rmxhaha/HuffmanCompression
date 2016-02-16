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

void extractArchieve( Header& header, ifstream& myfile, const string& ftarget ){
    int fileidx = 0;
    for( auto& fl : header.folders ){
        string cdir = getFullDir(&fl,&header);
        cout << cdir << "\\ (" << fl.numOfFile <<")\n";
        for(int limit = fileidx + fl.numOfFile; fileidx < limit; ++ fileidx ){
            string fullPath = ftarget + "\\" + cdir + "\\" + header.files[fileidx].fileName;
            int size = header.files[fileidx].size;
            cout << fullPath << " " << size << endl;
            ofstream outfile( fullPath );
//            myfile << infile.rdbuf();
//            infile.tellg(0,ios::beg);
            outfile.unsetf(ios_base::skipws);
            char c;
            int i = 0;
            for(;i < size;++i){
                myfile >> c;
                if( myfile.eof() ) break;
                outfile << c;
            }
            outfile.close();
        }
    }
}

void buildFolder( Header& head, const string& ftarget ){
    for( auto& fl : head.folders ){
        string cdir = ftarget + '\\' +getFullDir(&fl,&head);
        CreateDirectory(cdir.c_str(),NULL);
    }
}

