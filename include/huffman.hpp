#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../include/BitReader.hpp"
#include "../include/BitWriter.hpp"

#include <iostream>
#include <fstream>

using namespace std;

struct node
{
	unsigned char c; //karakter pada daun
	int weight; //frekuensi kemunculan karakter
	int order; //nomor node
	bool NYT;
	node *left;
	node *right;
	node *parent;
};

class HuffmanTree {
public:

	// Constructor
	HuffmanTree();

	// Destructor
	~HuffmanTree();
private:
	void dealokasi(node *P);

public:
	// Mengecek apakah _n merupakan daun
	bool isLeaf(node *_n);

	/* Getter */

	// Mengembalikan node pohon
	node *getNode();

	// Menambahkan karakter pada pohon
	void addNextChar(unsigned char _c);

	// Menambahkan karakter baru pada pohon
	void addNewChar(unsigned char _c);

	// Menambahkan karakter yang sudah ada
	void addExistingChar(unsigned char _c);

    // Update posisi node P
    void update(node *P);

	// Cek apakah node P dapat ditukar
	bool check(node *P);

	// Menukar parent dari P dan _P
    void swapParent(node *P, node *_P);

	// Menukar dua node
    void swap(node *P, node *_P);

	/* Fungsi dan Prosedur Pencarian */

	// Mengecek apakah ada node yang merupakan NYT
	bool bSearch(node *P);

	// Mengecek apakah ada node dengan order tertentu
	bool bSearch(node *P, int _order);

	// Mengecek apakah ada node degnan karakter tertentu
	bool bSearch(node *P, unsigned char _c);

	// Mengembalikan node yang merupakan NYT
	node *search(node *P);

	// Mengembalikan node dengan order tertentu
	node *search(node *P, int _order);

	// Mengembalikan node dengan karakter tertentu
	node *search(node *P, unsigned char _c) ;
	// Membentuk array of boolean berupa letak karater _c pada pohon
	void searchNum(node *P, unsigned char _c, unsigned char &x, int &count, ostream &output) ;
	// Membentuk array of boolean berupa letak karater _c pada pohon
	void searchNum(node *P, unsigned char &x, int &count, ostream &output);
	// Prosedur dekode, c berupa masukan karakter (hasil enkode), curr_c
	// merupakan karakter yang sedang dibaca, size merupakan panjang
	// array of karakter tersebut
	void decode(BitReader& reader, int size);
	// Mengubah char menjadi bit (array of boolean)
	void char_Bit_decode (unsigned char c, unsigned char &x, int &count, ostream &output, unsigned char &z);
	// Mengubah char menjadi bit (array of boolean)
	void char_Bit (unsigned char c, unsigned char &x, int &count, ostream &output) ;
	// Proses enkode adaptive huffman, arr_c merupakan hasil dari enkode,
	// disimpan menjadi array karakter, curr_c merupakan indeks c, dan
	// size merupakan banyaknya bit yang di enkode
	void encode(BitWriter& writer, int &size);
private:
	// Data
	node *n;
	node *nNYT;
	node *location[256];
};



#endif
