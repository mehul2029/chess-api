#include <iostream>
#include "board.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	Board b;
	if (b.move("1d", "1e")) {
		cout << "FAIL" << " 1d 1e" << endl;
	}
	if (!b.move("1d", "1c")) {
		cout << "FAIL" << " 1d 1c" << endl;
	}
	if (!b.move("1c", "2c")) {
		cout << "FAIL" << " 1c 2c" << endl;
	}
	if (!b.move("2c", "2d")) {
		cout << "FAIL" << " 2c 2d" << endl;
	}
	if (!b.move("2d", "1d")) {
		cout << "FAIL" << " 2d 1d" << endl;
	}
	if (!b.move("1e", "3e")) {
		cout << "FAIL" << " 1e 3e" << endl;
	}
	if (!b.move("3e", "3g")) {
		cout << "FAIL" << " 3e 3f" << endl;
	}
	if (!b.move("3g", "1e")) {
		cout << "FAIL" << " 3g 1e" << endl;
	}
	if (b.move("1e", "2g")) {
		cout << "FAIL" << " 1e 2g" << endl;
	}
	if (!b.move("1a", "1b")) {
		cout << "FAIL" << " 1a 1b" << endl;
	}
	if (!b.move("1b", "3b")) {
		cout << "FAIL" << " 1b 3b" << endl;
	}
	if (!b.move("3b", "3a")) {
		cout << "FAIL" << " 3b 3a" << endl;
	}
	if (!b.move("3a", "1a")) {
		cout << "FAIL" << " 3a 1b" << endl;
	}
	if (b.move("1a", "3b")) {
		cout << "FAIL" << " 1a 3b" << endl;
	}
	return 0;
}