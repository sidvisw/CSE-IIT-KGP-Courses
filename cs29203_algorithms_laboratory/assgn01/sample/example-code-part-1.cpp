#include <string>
#include <fstream>
#include <iostream>
using namespace std;


char* convert(const char *exp) {
	cout << exp << endl;
	return 0;
}

int main() {
	string line;
	ifstream input_file("input.txt");
	ofstream part_1_output_file("part_1_output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			// First part: Implement convert function and associated linked list impl. of stack 
			char* rp_exp = convert(line.c_str());
			part_1_output_file << rp_exp << endl;
		}
		input_file.close();
	}
	else cout << "Unable to open file"; 
	part_1_output_file.close();
	return 0;
}

