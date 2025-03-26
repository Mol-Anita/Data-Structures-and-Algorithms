#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"


#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();
	testGetValueRange();
	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


