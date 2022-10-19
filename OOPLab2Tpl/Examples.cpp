#include <iostream>
#include <fstream>
#include <clocale>
#include <string.h>
#include "Examples.h"

using namespace std;

void binaryView(char a) {
	int b[8];

	memset(b, 0, sizeof(b));

	b[0] = a & 0b10000000 ? 1 : 0;
	b[1] = a & 0b01000000 ? 1 : 0;
	b[2] = a & 0b00100000 ? 1 : 0;
	b[3] = a & 0b00010000 ? 1 : 0;
	b[4] = a & 0b00001000 ? 1 : 0;
	b[5] = a & 0b00000100 ? 1 : 0;
	b[6] = a & 0b00000010 ? 1 : 0;
	b[7] = a & 0b00000001 ? 1 : 0;

	for (int i = 0; i < 8; i++) {
		cout << b[i];
	}
	cout << "\n";
}

void Exercise1(){

	int a, b, c, d, x, y;

	cout << "Введіть цілі числа a, b, c, d: " ;
	cin >> a >> b >> c >> d;

	cout << "x = ( 17*a + 312*c ) / 32 - b*120 + d*127 \n";
	cout << "x = ( a+16*a + (256*c + 64*c - 8*c) ) / 32 - (b*128 - b*8) + (128*d - d) \n";
	cout << "x = ( a+ (2^4)*a + ((2^8)*c + (2^6)*c - (2^3)*c) ) / (2^5) - (b*(2^7) - b*(2^3)) + ((2^7)*d - d) \n\n";

	cout << "x = ((a + (a << 4) + (c << 8) + (c << 6) - (c << 3)) >> 5) - ((b << 7) - (b << 3)) + ((d << 7)-d); \n";
	cout << "y = (17 * a + 312 * c) / 32 -b * 120 + d*127; \n\n";

	x = ((a + (a << 4) + (c << 8) + (c << 6) - (c << 3)) >> 5) - ((b << 7) - (b << 3)) + ((d << 7)-d);
	y = (17 * a + 312 * c) / 32 -b * 120 + d*127;

	cout << "Значення Х = " << x << endl;  
	cout << "Значення Y = " << y << endl;
	cout << "Значення a, b, c, d = " << a << "  " << b << "  " << c << "  " << d << endl << endl;

	cin.get();
	cin.get();
	return;
}

void ReadArrayTextFile(int sizeMax, unsigned char* pA){

	int size = 64;
	ifstream fin;
	fin.open("C:\\Users\\Admin\\Documents\\GitHub\\ooplab2_u-VasyaSuper\\file1.txt");
	if (fin.fail()) return ;
	if (size <= 0) return ;

	for (int i = 0; i < size; i++)
	{
		fin >> pA[i];
		cout << i + 1 << ") Element arrays:" << pA[i] << "\n";
	}
	fin.close();

	return;
}

void WriteArrayTextFile1(int size, unsigned char* pA) {

	ofstream fout("C:\\Users\\Admin\\Documents\\GitHub\\ooplab2_u-VasyaSuper\\file2.bin");
	if (!fout) cout << "Erorr";

	else {
		for (int i = 0; i < size; i++) {
			fout << pA[i];
		}
	}

	fout.close();

	return;
}

void encryptArray(unsigned char* text, unsigned char* destination) {
	for (unsigned char i = 0; i < 8; i++) {
		for (unsigned char j = 0; j < 16; j += 2) {
			destination[(i << 4) + j] = (i << 5) | (j << 1) | ((i << 5) & 0b01000000 ? 0b00000010 : 0) | (text[(i << 3) + (j >> 1)] >> 7);
			destination[(i << 4) + j + 1] = (text[(i << 3) + (j >> 1)] << 1) | ((text[(i << 3) + (j >> 1)] << 1) & 0b00000010 ? 1 : 0);
		}  //00110001
	}
}

void decryptArray(unsigned char* text, unsigned char* destination) {
	unsigned char row;
	unsigned char collum;
	for (unsigned char i = 0; i < 8; i++) {
		for (unsigned char j = 0; j < 16; j += 2) {
			row = (text[(i << 4) + j] >> 5) & 0b00000111;
			collum = (text[(i << 4) + j] >> 2) & 0b00000111;
			destination[(row << 3) + collum] = ((text[(i << 4) + j] << 7) & 0b10000000) | (text[(i << 4) + j + 1] >> 1);
		}
	}
}

struct optio3 {
	unsigned char row : 3;
	unsigned char collum : 3;
	unsigned char pairing0_1 : 1;
	unsigned char half1 : 1;
	unsigned char half2 : 7;
	unsigned char pairing14 : 1;
};

void Print_text(unsigned char* text, unsigned char* encryptedText, unsigned char* decrypted) {

	for (int i = 0; i < 64; i++) {  // basic
		cout <<text[i];
	}
	cout << "\n\n";
	for (int i = 0; i < 128; i++) { // encrypted
		binaryView(encryptedText[i]);
		if ((i % 2) != 0)
			cout << "\n";
		if (i == 63) cout << '\n';
	}
	cout << "\n\n";
	for (int i = 0; i < 64; i++) {  // decrypted
		cout << decrypted[i];
	}
	cout << "\n\n";
	return;
}

void Exercise2() {

	unsigned char text[65];
	unsigned char encrypted[128];
	unsigned char decrypted[64];
	unsigned char* encryptedText = encrypted;

	ReadArrayTextFile(64, text);
	WriteArrayTextFile1(64, text);

	encryptArray(text, encryptedText);
	decryptArray(encryptedText, decrypted);
	
	Print_text(text, encryptedText, decrypted);

	return;
}

void Exercise3() {
	optio3 enc[64];
	unsigned char* encryptedText = (unsigned char*)enc;

	unsigned char text[65];
	unsigned char encrypted[128];
	unsigned char decrypted[64];

	ReadArrayTextFile(64, text);
	WriteArrayTextFile1(64, text);

	encryptArray(text, encryptedText);
	decryptArray(encryptedText, decrypted);

	Print_text(text, encryptedText, decrypted);

	return;
}

// | або там або там 
// & і там і там


void Exercise4() {
	//0000 0000 0000 0000 0000 0000

	int a, b, c, d, e;
	char p[3]; 
	p[0] = 0; 
	p[1] = 0; 
	p[2] = 0;

	//cin >> a >> b >> c >> d >> e;

	do {
		cout << "\nВведіть ціле число a: ";
		cin >> a;
	} while ((a < 0) || (a > 12));

	do {
		cout << "\nВведіть ціле число b: ";
		cin >> b;
	} while ((a < 0) && (b > 9));

	do {
		cout << "\nВведіть ціле число c: ";
		cin >> c;
	} while ((c < 1940) && (c > 2065));

	do {
		cout << "\nВведіть ціле число d: ";
		cin >> d;
	} while ((d < 0) && (d > 31));

	do {
		cout << "\nВведіть ціле число e: ";
		cin >> e;
	} while ((a < 0) && (e > 1));
	
	
	p[0] = a << 4;
	p[0] = p[0] | (b & 0b00001111);

	p[2] = d << 3;

	p[1] = e << 7;
	p[1] = p[1] | ((c-1940) & 0b01111111);

	cout << "    ";
	binaryView(p[0]);
	cout << "    ";
	binaryView(p[1]);
	cout << "    ";
	binaryView(p[2]);

	int a1 = (p[0] & 0b11110000) >> 4;
	int b1 = (p[0] & 0b00001111);
	int c1 = (p[1] & 0b01111111);
	int d1 = (p[1] & 0b11111000) >> 3;
	int e1 = (p[1] & 0b10000000) >> 7;

	cout << "    a = " << a1 <<  " binary a = ";
	binaryView(a1);
	cout << "    b = " << b1 <<  " binary b = ";
	binaryView(b1);
	cout << "    c = " << c1 + 1940 << " binary c = ";
	binaryView(c1);
	cout << "    d = " << d1 << " binary d = ";
	binaryView(d1);
	cout << "    e = " << e1 << " binary e = ";
	binaryView(e1);

	cin.get();
	cin.get();
	return;
}
