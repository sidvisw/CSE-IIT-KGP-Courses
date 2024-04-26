// used for IO
#include <string>
#include <fstream>
#include <iostream>

#include <string.h>
using namespace std;

struct operatorNode {
	char data;
	struct operatorNode* next;
};

struct operatorStack {
	int size;
	struct operatorNode* top;
};

// initialise the operatorStack
struct operatorStack* createStack() {
	struct operatorStack* stack = new struct operatorStack;
	stack->size = 0;
	stack->top = NULL;
	return stack;
}

// check if stack is empty
bool isEmpty(struct operatorStack* stack) {
	if (stack->size == 0)
		return true;
	else return false;
}

// return the top element of stack without deleting
char peek(struct operatorStack* stack) {
	return stack->top->data;
}

// returns the top element and deletes from stack
char pop(struct operatorStack* stack) {
	char data = stack->top->data;
	struct operatorNode* temp = stack->top;
	stack->top = stack->top->next;
	stack->size--;

	// should delete node after popped
	delete temp;
	return data;		
}

// push operator to stack
void push(struct operatorStack* stack, char data) {
	struct operatorNode* node = new struct operatorNode;
	node->data = data;
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

int operatorScore(char op) {
	if (op == '(' || op == ')')
		return 3;
	else if (op == '*' || op == '/' || op == '%')
		return 2;
	else return 1;
}

/*
	= 0: same precedence
	> 0: op1 has higher precedence 
	< 0: op2 has higher precedence
*/
int precedence(char op1, char op2) {
	return operatorScore(op1) - operatorScore(op2);
}

int findLength(const char* ch) {
	int i = 0;
	while (ch[i] != '\0')
		i++;
	return i;
}

bool isOperand(char* ch) {
	if (findLength(ch) > 1) {
		return true;
	}
	else if (ch[0] >= '0' && ch[0] <= '9') {
		return true;
	}
	else return false;
}

char* convert(const char *exp) {
	int i = 0, j = 0, len = findLength(exp);
	struct operatorStack* stack = createStack();
	char* rp_exp = (char *) malloc(sizeof(char)*len);

	char* token = strtok(strdup(exp), " ");
	while(token != NULL) {

		if (isOperand(token)) {
			int l = 0;
			while (token[l] != '\0') {
				rp_exp[j++] = token[l++];			
			}
		} else {
			if (token[0] == '(') {
				push(stack, token[0]);
			} else if (token[0] == ')') {
				while (!isEmpty(stack) && peek(stack) != '(') {
					rp_exp[j++] = ' ';
					rp_exp[j++] = pop(stack);
				}
				pop(stack);
			} else {
				rp_exp[j++] = ' ';
				while (!isEmpty(stack) && precedence(token[0], peek(stack)) <= 0 && peek(stack) != '(') {
					rp_exp[j++] = pop(stack);
					rp_exp[j++] = ' ';
				}
				push(stack, token[0]);
			}
		} 
		token = strtok(NULL, " ");
	}

	while (!isEmpty(stack)) {
		rp_exp[j++] = ' ';
		rp_exp[j++] = pop(stack);
	}
	rp_exp[j] = '\0';
	return rp_exp;
}

int main() {
	string line;
	ifstream input_file("input.txt");
	ofstream part_1_output_file("part_1_output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			char* rp_exp = convert(line.c_str());
			part_1_output_file << rp_exp << endl;
		}
		input_file.close();
	}
	else cout<< "Unable to open file"; 
}
