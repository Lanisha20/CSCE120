#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	// TODO(student): print prompt for input
	cout << "Enter numbers 10 <= a <= b < 10000: ";
	// TODO(student): read the numbers from standard input
	int a;
	int b;
	cin >> a >> b;
	// TODO(student): validate input (and reprompt on invalid input)
	while (is_valid_range(a,b) != true) {
		cout << "Invalid Input" << endl;
		cout << "Enter numbers 10 <= a <= b < 10000: ";
		cin >> a >> b;
	}
	// TODO(student): compute and display solution
	count_valid_mv_numbers(a,b);
	return 0;
}