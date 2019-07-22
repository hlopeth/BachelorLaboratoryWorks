#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
	Matrix matrix("input.txt");
	matrix.Print();
	cin.get();
	cin.get();
    return 0;
}

