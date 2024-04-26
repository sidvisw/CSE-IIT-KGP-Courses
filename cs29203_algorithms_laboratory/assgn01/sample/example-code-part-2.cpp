#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int evaluate(const char* rp_exp) {
	cout << rp_exp << endl;
	return 0;
}

int main() {
	string line;
	ifstream input_file("part_1_output.txt");
	ofstream part_2_output_file("part_2_output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			// Second part: Implement evaluate function and associated linked list impl. of stack
			part_2_output_file << evaluate(line.c_str()) << endl;
		}
		input_file.close();
	}
	else cout << "Unable to open file"; 
	part_2_output_file.close();
	return 0;
}

