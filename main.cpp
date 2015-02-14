#include <iostream>
#include "XMLToHTMLTable.h"

using std::cerr;

int main(int argc, char** argv)
{
	if(argc < 2) {
		cerr << "Please provide input xml file name\n";
		return 1;
	}
	XMLToHTMLTable xmltohtmltable(argv[1]);
	xmltohtmltable.runConversion();

	return 0;
}
