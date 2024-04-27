#ifndef FILEWRITE_H
#define FILEWRITE_H
#include "binary_data.h"
#include <iostream>
#include <fstream>
using namespace std;
void Extrcat_File(string filename){	//ÊÍ·ÅÎÄ¼þ
	int size = sizeof(binary_bin);
	ofstream output_file(filename,ios::binary);
	output_file.write(reinterpret_cast<const char *>(binary_bin), size);
	output_file.close();
}
#endif
