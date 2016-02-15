#include "../include/header.hpp"

#include <fstream>
#include <functional>
#include <iostream>
#include <string>


using namespace std;

Header buildHead( const string& rootDirectory ){
    Header head;

    auto getFileSize = [](const string& fn){
        ifstream file(fn, ios::in);
        file.seekg(0, ios::end);
        return file.tellg();
    };

    std::function<void (const string& , int , const string& )>
        build = [&head,&getFileSize,&build](const string& parentdir, int parentId, const string& dirname)
    {
        string cdir = parentdir + "/" + dirname;
        //cout << cdir << endl;

        vector<string> list;
        listIn( list, cdir );


        int nFile = 0;
        for( auto it = list.begin(); it != list.end(); ++ it ){
            string cfile = cdir + "/" + *it;
            if( isFile(cfile) ){
                head.files.push_back(File(*it, getFileSize(cfile)));
                ++ nFile;
            }
        }

        int cid = head.folders.size();
        head.folders.push_back(Folder(dirname,parentId,nFile));

        for( auto it = list.begin(); it != list.end(); ++ it ){
            string cfile = cdir + "/" + *it;
            if( !isFile(cfile) ){
                build(cdir,cid,*it);
            }
        }
    };

    build( rootDirectory,-1,"");

    return head;
}


string getFullDir( Folder *fl, Header *header ){
    if( fl->parent == -1 ) return "";

    return getFullDir(&(header->folders[fl->parent]), header) + "/" + fl->folderName;
}

void printHead( Header& header ){
    int fileidx = 0;
    for( auto& fl : header.folders ){
        string cdir = getFullDir(&fl,&header);
        cout << cdir << "/ (" << fl.numOfFile <<")\n";
        for(int limit = fileidx + fl.numOfFile; fileidx < limit; ++ fileidx )
            cout << cdir << "/" << header.files[fileidx].fileName << endl;
    }
}

void Bin2Header( Header& header, const string& fn ){
    ifstream myfile (fn);
    int num = 0;
    int size;
    char *str = (char*)&num;
    myfile.seekg(0, ios::beg);
    myfile.read(str, 4);
    size = num;
    cout << size << endl;
    for( int i = 0; i < size; ++ i ){
        Folder folder;
        char c;
        myfile >> c;
        while(c != '\0'){
            folder.folderName += c;
            myfile >> c;
        }
        myfile >> str[0] >> str[1] >> str[2] >> str[3];
        folder.parent = num;
        myfile >> str[0] >> str[1] >> str[2] >> str[3];
        folder.numOfFile = num;
        cout << folder.folderName << "\t" << folder.parent << "\t" << folder.numOfFile << endl;
        header.folders.push_back(folder);
    }
    myfile.close();
}

void Header2Bin( Header& header, const string& fn ){
    ofstream myfile;
    myfile.open (fn, ios::out | ios::binary);

    // writting num of folder
    int num = header.folders.size();
    char *str = (char*)&num;
    myfile << str[0] << str[1] << str[2] << str[3];


    // writting folders block
    for( auto& folder : header.folders ){
        cout << folder.folderName << "\t" << folder.parent << "\t" << folder.numOfFile << endl;
        for( auto& c : folder.folderName ){
            myfile << c;
        }
        myfile << '\0';
        num = folder.parent;
        myfile << str[0] << str[1] << str[2] << str[3];
        num = folder.numOfFile;
        myfile << str[0] << str[1] << str[2] << str[3];
    }

    cout << "--------------------------------------\n";

    myfile.close();

}

