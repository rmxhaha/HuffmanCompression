#include <iostream>
#include <fstream>
#include "../include/HuffmanTree.hpp"
using namespace std;

// Constructor
HuffmanTree::HuffmanTree() {
	nNYT = 513;
	n = &arrOrder[513];
	n->weight = 0;
	n->order = 513;
	n->NYT = true;
	n->c = '@';
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	for (int i = 0; i < 256; i++) {
		loct[i] = NULL;
	}
}
	
// Destructor
HuffmanTree::~HuffmanTree() {
}

// Mengembalikan node pohon
node* HuffmanTree::getNode() {
	return n;
}

// Mengecek apakah _n merupakan daun
bool HuffmanTree::isLeaf(node *_n) {
	if ((_n->left == NULL) && (_n->right == NULL)) {
		return true;
	} else {
		return false;
	}
}

// Mengubah dan meng-outputkan karakter input ke dalam karakter penyimpanan
void HuffmanTree::char_Bit (unsigned char c, unsigned char &x, int &count, ostream &output) {
	if (count == 0) {
		output.write((char*) &c, sizeof(char));
	} else {
		// Proses pengisian karakter penymipanan
		for (int i=0; i<8; i++) {
			x = x << 1;
			x &= ~(1);
			x |= (c >> (7-i)) & 1;
			count++;
			// Karakter penyimpan sudah penuh
			if (count == 8) {
				output.write((char*) &x, sizeof(char));
				count = 0;
			}
		}
	}
}

// Mengubah dan meng-outputkan karakter input ke dalam karakter penyimpanan
void HuffmanTree::char_Bit_decode (unsigned char c, unsigned char &x, int &count, ostream &output, unsigned char &z) {
	if (count == 0) {	
		z = c;
		x = c;
		output.write((char*) &x, sizeof(char));
	} else {
		// Proses pengisian karakter penyimpanan
		x = x >> (8-count);
		for (int i=0; i<(8-count); i++) {
			x = x << 1;
			x &= ~(1);
			x |= ((c >> (7-i)) & 1);
		}	
		output.write((char*) &x, sizeof(char));
		z = x;
		x = c << (8-count);
	}
}

// Menambahkan karakter baru pada pohon
void HuffmanTree::addNewChar(unsigned char _c) {
	// Mengambil node NYT
	node *_n = &arrOrder[nNYT];
	
	// Membuat node baru (kiri dan kanan)
	_n->left = &arrOrder[(_n->order)-2];
	_n->right = &arrOrder[(_n->order)-1];
	
	node *Left = _n -> left;
	node *Right = _n -> right;
	
	// Konstruktor node
	_n -> c = '@';
	_n -> NYT = false;
	
	Left -> left = NULL;
	Left -> right = NULL;
	Left -> parent = _n;
	Left -> NYT = true;
	Left -> weight = 0;
	Left -> order = (_n -> order) - 2; // Order left, -2 dari order NYT lama
	Left -> c = 'z'; // NYT dituliskan sebagai karakter 'z'
	
	Right -> left = NULL;
	Right -> right = NULL;
	Right -> parent = _n;
	Right -> NYT = false;
	Right -> weight = 1;
	Right -> order = (_n -> order) - 1;  // Order left, -1 dari order NYT lama
	Right -> c = _c; // Pengisian karakter pada Right
	
	loct[_c] = Right;
	nNYT = nNYT - 2; // NYT baru
	update(_n); // Update NYT lama
}

// Menambahkan karakter yang sudah ada
void HuffmanTree::addExistingChar(unsigned char _c) {
	update(loct[_c]); // Update node dengan karakter _c
}

// Update sebuah node P dan seluruh parentnya
void HuffmanTree::update(node *P) {
	while (P) {
		P->weight++; // Tambahkan weight		
		if (P->parent != NULL) {
			int i = P->order+1;
			// Cek node yang mungkin di swap
			while ((i < 513) && (P->weight > arrOrder[i].weight)) {
				i++;
			}
			// Memenuhi syarat swap
			if ((P->weight > arrOrder[i-1].weight) && (P->parent != &arrOrder[i-1])) {
				// Prosedur swap
				
				// Pertukaran node left dan right
				if (!isLeaf(P)) {
						P->left->parent = &arrOrder[i-1];
						P->right->parent = &arrOrder[i-1];
					if (!isLeaf(&arrOrder[i-1])) {
						arrOrder[i-1].left->parent = P;
						arrOrder[i-1].right->parent = P;
					} else {
						loct[arrOrder[i-1].c] = P;
					}
				} else {
					if (!isLeaf(&arrOrder[i-1])) {
						arrOrder[i-1].left->parent = P;
						arrOrder[i-1].right->parent = P;
						loct[P->c] = &arrOrder[i-1];
					} else {
						loct[P->c] = &arrOrder[i-1];
						loct[arrOrder[i-1].c] = P;
					}
				}	
				
				// Pertukaran letak node dalam array order
				node temp = arrOrder[P->order];
				arrOrder[P->order] = arrOrder[i-1];
				arrOrder[i-1] = temp;
				
				// Pertukaran nilai order
				int temp2 = P->order;
				P->order = arrOrder[i-1].order;
				arrOrder[i-1].order = temp2;

				// Pertukaran parent node
				node *temp3 = arrOrder[P->order].parent;
				arrOrder[P->order].parent = arrOrder[i-1].parent;
				arrOrder[i-1].parent = temp3;
				
				// Set node yang akan diupdate selanjutnya
				P = &arrOrder[i-1];				
			}
		}
		// Lakukan update untuk parent
		P = P->parent;
	}
}

// Mencari path ke sebuah karakter dalam pohon, meyimpan dan mengoutputkan hasil dalam
// karakter penyimpanan
void HuffmanTree::searchNum(unsigned char c, unsigned char &x, int &count, ostream &output) {
	node *_n = loct[c]; int temp = 0; int arr;
	// Mencari path
	while ((_n -> parent) != NULL) {
		if ((_n -> parent -> left) == _n) {
			temp++;
			arr = arr << 1;
			arr &= ~(1);
		} else {
			temp++;
			arr = arr << 1;
			arr |= 1;
		}
		_n = _n -> parent;
	}
	// Menyimpan dan mengoutputkan path
	for (int i = 0; i < temp; i++) {
		x = x << 1;
		x &= -2;
		x |= ((arr >> i) & 1);
		count++;
		if (count == 8) {
			output.write((char*) &x, sizeof(char));
			count = 0;
		}
	}
}

// Mencari path ke node NYT dalam pohon, meyimpan dan mengoutputkan hasil dalam
// karakter penyimpanan
void HuffmanTree::searchNum(unsigned char &x, int &count, ostream &output) {
	node *_n = &arrOrder[nNYT]; int temp = 0; int arr;
	// Mencari path
	while ((_n -> parent) != NULL) {
		if ((_n -> parent -> left) == _n) {
			temp++;
			arr = arr << 1;
			arr &= ~(1);
		} else {
			temp++;
			arr = arr << 1;
			arr |= 1;
		}
		_n = _n -> parent;
	}
	// Menyimpan dan mengoutputkan path
	for (int i = 0; i < temp; i++) {
		x = x << 1;
		x &= -2;
		x |= ((arr >> i) & 1);
		count++;
		if (count == 8) {
			output.write((char*) &x, sizeof(char));
			count = 0;
		}
	}	
}

// Prosedur pemampatan Adaptive Huffman FGK
void HuffmanTree::compress(int &size) {
	unsigned char c; 
	unsigned char x;
	int count = 0; 
	ifstream input("coba.bmp", ios::binary | ios::in);
	ofstream output("output", ios::binary | ios::out);
	if (input != NULL)
	{
		input.read((char*) &c, sizeof(char));
		addNewChar(c);
		size+=1;
		char_Bit(c,x,count,output);
		input.read((char*) &c, sizeof(char));
		while (!(input.eof())) {
			// update pohon dan mengenkripsi
			if (loct[c] != NULL) {
				// karakter sudah ada
				searchNum(c,x,count,output);
				addExistingChar(c);
				size+=1;
				UI -> size / filesize
			} else {
				// karakter belum ada
				searchNum(x,count,output);
				char_Bit(c,x,count,output);
				addNewChar(c);
				size+=1;
			}
			// Pembacaan karakter baru
			input.read((char*) &c, sizeof(char));
		} 
		if (count != 0) {
			// Menyelesaikan bit yang belum diubah dengan menambahkan
			// '0' sampai membentuk 8 bit
			x = x << (8 - count);
			output.write((char*) &x, sizeof(char));
		}
	} else {
		printf("File tidak dapat dibuka.\n");
	}
	input.close();
	output.close();
}

// Prosedur penirmampatan Adaptive Huffman FGK
void HuffmanTree::decompress(int size) {
	unsigned char x; unsigned char c; 
	node *_n;
	int count;
	int read;
	ifstream input("output", ios::binary | ios::in);
	ofstream output("HASIL.bmp", ios::binary | ios::out);
	input.read((char*) &x, sizeof(char));	
	output.write((char*) &x, sizeof(char));
	addNewChar(x);
	count = 0; read = 1; _n = n;
	// Membaca sampai size sesuai size file awal
	while (read < size) {
		if (!(input.eof())) {
			input.read((char*) &x, sizeof(char));
			// Mengubah karakter ke bit (array of boolean)
			count = 8;
		}
		// Mengubah beberapa karakter yang telah dibaca menjadi bit
		// menjadi karakter untuk di outputkan
		while (count > 0)
		{
			// Keluar apabila sudah menghasilkan bit yang sesuai saat dibaca
			if (read >= size) {
				break;
			}
			// Apabila merupakan daun, outputkan karakter
			if (isLeaf(_n)) {
				read += 1;
				if ((_n->NYT)==true) {
						unsigned char z;
						input.read((char*) &c, sizeof(char));
						char_Bit_decode(c,x,count,output,z);
						addNewChar(z);
						_n = n;
				} else {
					unsigned char z;
					z = _n->c;
					output.write((char*) &z, sizeof(char));
					addExistingChar(z);
					_n = n;
				}
			}
			// Bergeser sesuai pohon dan bit yang diterima
			if (((x >> 7) & 1) == 0) {
				x = x << 1;
				_n = (_n-> left);
				count--;
			} else {
				x = x << 1;
				_n = (_n -> right);
				count--;
			}
		}
	}
	input.close();
	output.close();
}
