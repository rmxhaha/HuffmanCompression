#include "../include/archieve.hpp"

#include <iostream>
#include <windows.h>
#include "../include/HuffmanTree.hpp"

using namespace std;



void fillArchieve( Header& header, BitWriter& writer, const string& ftarget ){
    int fileidx = 0;
    for( auto& fl : header.folders ){
        string cdir = fl.folderPath;
        //getFullDir(&fl,&header);
//        cout << cdir << "\\ (" << fl.numOfFile <<")\n";
        for(int limit = fileidx + fl.numOfFile; fileidx < limit; ++ fileidx ){
            string fullPath = cdir + "\\" + header.files[fileidx].fileName;
            int size = (header.files[fileidx].size);
//            cout << fullPath << " " << (header.files[fileidx].size) << endl;
            /*
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
            */
            writer.resetCounter();

            HuffmanTree T;
            T.compress(writer,fullPath);

            double ratio = (double) (writer.getBitCount() / 8) / (double) size;
        }
    }
}

void extractArchieve( Header& header, BitReader& reader, const string& ftarget ){
    int fileidx = 0;
    for( auto& fl : header.folders ){
        string cdir = getFullDir(&fl,&header);
//        cout << cdir << "\\ (" << fl.numOfFile <<")\n";
        for(int limit = fileidx + fl.numOfFile; fileidx < limit; ++ fileidx ){
            string fullPath = ftarget + "\\" + cdir + "\\" + header.files[fileidx].fileName;
            int size = header.files[fileidx].size;
//            cout << fullPath << " " << size << endl;
//            myfile << infile.rdbuf();
//            infile.tellg(0,ios::beg);

            HuffmanTree T;
            T.decompress(reader,fullPath,size);

            /*
            ofstream outfile( fullPath );
            outfile.unsetf(ios_base::skipws);
            char c;
            int i = 0;
            for(;i < size;++i){
                myfile >> c;
                if( myfile.eof() ) break;
                outfile << c;
            }
            outfile.close();
            }*/

        }
    }
}

void buildFolder( Header& head, const string& ftarget ){
    for( auto& fl : head.folders ){
        string cdir = ftarget + '\\' +getFullDir(&fl,&head);
        CreateDirectory(cdir.c_str(),NULL);
    }
}


void buildArchieve( const string& ftarget, const vector<string>& cmprsList, const string& output_file ){
    ofstream outfile(output_file, ios::out | ios::binary );
    Header head = buildHead(ftarget, cmprsList);


    Header2Bin(head, outfile);
    BitWriter writer(outfile);
//    printHead(head);
    fillArchieve(head, writer, ftarget);
    writer.flush();
    outfile.close();
}

void expandArchieve( const string& input_file, const string& outputPath ){
    Header head2;
    ifstream cfile(input_file, ios::in | ios::binary );
    Bin2Header(head2,cfile);

    BitReader reader(cfile);
    buildFolder(head2,outputPath);
    extractArchieve(head2, reader, outputPath);

    cfile.close();
}

