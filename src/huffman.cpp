#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<char,int> pci;

class HuffmanTree {
public:
    HuffmanTree(){
        possibleCh = "";
        left = right = nullptr;
    }

    ~HuffmanTree(){
        if(left) delete left;
        if(right) delete right;
    }

    string possibleCh;
    HuffmanTree *left, *right;
};

class HuffmanElmt {
public:
    HuffmanElmt(){
        count = 0;
        ctree = new HuffmanTree();
    }

    int count;
    HuffmanTree *ctree;
};


void generateHuffmanTree(HuffmanTree** root, const string& data ){
    *root = nullptr;

    map<char, int> wcount;
    for( int i = 0; i < data.size(); ++ i ){
        wcount[ data[i] ] ++;
    }

    vector<HuffmanElmt> HuffmanTable;
    for( auto it = wcount.begin(); it != wcount.end(); ++ it ){
        HuffmanElmt elm;
        elm.count = it->second;
        elm.ctree->possibleCh += it->first;

        HuffmanTable.push_back(elm);
    }

    auto cmp = [](const HuffmanElmt& a, const HuffmanElmt& b){
        return a.count > b.count;
    };

    while( HuffmanTable.size() > 1 ){
        sort(HuffmanTable.begin(),HuffmanTable.end(), cmp );


        HuffmanElmt last = HuffmanTable.back();
        HuffmanTable.pop_back();

        HuffmanElmt secondlast = HuffmanTable.back();
        HuffmanTable.pop_back();


        // combine
        HuffmanElmt combinedElmt;
        combinedElmt.ctree->possibleCh = last.ctree->possibleCh + secondlast.ctree->possibleCh;
        combinedElmt.ctree->left = last.ctree;
        combinedElmt.ctree->right = secondlast.ctree;

        HuffmanTable.push_back( combinedElmt );
    }

    *root = HuffmanTable.back().ctree;
}

void printTree( HuffmanTree* root, int tab ){
    for ( int i = 0; i < tab; ++ i ) cout << " ";
    cout << root->possibleCh << endl;
    if( root->left )
        printTree(root->left, tab + 1);
    if( root->right )
        printTree(root->right,tab + 1);
}


int main(){
    string sample = "baaaaacccccc";
    HuffmanTree *root;
    generateHuffmanTree(&root,sample);
    printTree(root,0);

    return 0;
}
