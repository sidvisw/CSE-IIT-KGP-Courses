// used for IO
#include <string> 
#include <fstream>
#include <iostream>

#include <string.h>
using namespace std;

// why float? think of the expression: 5 / 3 * 3 is it 3 or 5?
struct operandNode {
	float val;
	struct operandNode* next;
};

struct operandStack {
	int size;
	struct operandNode* top;
};

// initialise the operandStack
struct operandStack* createStack() {
	struct operandStack* stack = new struct operandStack;
	stack->size = 0;
	stack->top = NULL;
	return stack;
}

// check if stack is empty
int isEmpty(struct operandStack* stack) {
	if (stack->size == 0)
		return true;
	else return false;
}

// return the top element of stack without deleting
float peek(struct operandStack* stack) {
	return stack->top->val;
}

// returns the top element and deletes from stack
float pop(struct operandStack* stack) {
	float val = stack->top->val;
	struct operandNode* temp = stack->top;
	stack->top = stack->top->next;
	stack->size--;

	// should delete node after popped
	delete temp;
	return val;		

}

// push operand to stack
void push(struct operandStack* stack, float val) {
	struct operandNode* node = new struct operandNode;
	node->val = val;
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

float calc(float val1, float val2, char op) {
	if (op == '/') {
		return val1 / val2;
	} else if (op == '*') {
		return val1 * val2;
	} else if (op == '%') {
		return (int) val1 % (int) (val2);
	} else if (op == '+') {
		return val1 + val2;
	} else {
		return val1 - val2;
	}
}


int evaluate(const char* exp) {
	int i = 0, len = findLength(exp);
	char* token = strtok(strdup(exp), " ");
	struct operandStack* stack = createStack();

	while (token != NULL) {
 		if (isOperand(token)) {
			float value = atoi(token);
			push(stack, value);
		} else {
			float par_1, par_2; 
			if (!isEmpty(stack)) {
				par_1 = pop(stack);
			} else {
				cout << "Invalid string" << endl;
			}
			if (!isEmpty(stack)) {
				par_2 = pop(stack);
			} else {
				cout << "Invalid string" << endl;
			}
			push(stack, calc(par_2, par_1, token[0]));			
		} 
		token = strtok(NULL, " ");
	}	
	return pop(stack);
}

int main() {
	string line;
	ifstream input_file("part_1_output.txt");
	ofstream part_2_output_file("part_2_output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			part_2_output_file << evaluate(line.c_str()) << endl;
		}
		input_file.close();
	}
	else cout<< "Unable to open file"; 
}
