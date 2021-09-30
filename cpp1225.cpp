#include<iostream>
#include <sstream>
#include <string.h>

using namespace std;


int main()
{
	string A, B;

	cin >> A >> B;

	int lenA = A.size();
	int lenB = B.size();

	unsigned int total = 0;

	for (int i = 0; i < lenA; i++) {
		for (int j = 0; j < lenB; j++) {
			total = total + (A[i] - '0') * (B[j] - '0');
		}
	}

	cout << total;
}
