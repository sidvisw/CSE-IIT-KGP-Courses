#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
	string line;
	ifstream input_file("input.txt");
	ofstream output_file("output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			output_file << line << endl;
		}
		input_file.close();
	}
	else cout << "Unable to open file" << endl; 
	output_file.close();
	return 0;
}