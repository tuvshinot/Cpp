#include <stdio.h>
#include <iostream >
#include <string>
#include <algorithm>

using namespace std;


string return_pop_back(string letters) {
	letters.pop_back();
	return letters;
}

string setPreviousValueReversed(string letters) {
	if (letters.length() == 1) {
		letters = "";
	}
	else {
		letters = return_pop_back(letters);
		reverse(letters.begin(), letters.end());
	}
	return letters;
}

int main()
{
	string letters{};
	cout << "Insert Letters to Build Pyramid : ";
	getline(cin, letters);

	int row_count = letters.length();
	int space_count{ row_count - 1 };
	string building{ letters[0] };

	for (int i = 0; i < row_count; i++) {
		string space(space_count, '-');
		string previous = setPreviousValueReversed(building);
		cout << space + building + previous << endl;
		building += letters[i + 1];
		space_count--;
	}
	return 0;
}