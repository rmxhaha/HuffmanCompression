#include "../include/header.hpp"
#include <fstream>
#include <functional>
#include <iostream>

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

Header parseHead( const string& bin );

string Header2Bin( Header& header );

