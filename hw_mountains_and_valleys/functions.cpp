#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	return (10<=a && a<=b && b<10000);
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	int v1 = 0; int v2 = 0; int v3 = 0; int v4 = 0; int v5 = 0;
	int v6 = 0; int v7 = 0; int v8 = 0; int v9 = 0; int v10 = 0;
	if (number >= 1000000000) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		number= number/10;
		v4 = number % 10;
		number= number/10;
		v5 = number % 10;
		number= number/10;
		v6 = number % 10;
		number= number/10;
		v7 = number % 10;
		number= number/10;
		v8 = number % 10;
		number= number/10;
		v9 = number % 10;
		number= number/10;
		v10 = number % 10;
		if (v10 < v9 && v9 > v8 && v8 < v7 && v7 > v6 && v6 < v5 && v5 > v4 && v4 < v3 && v3 > v2 && v2 < v1) {
			return 'M';
		}
		else if (v10 > v9 && v9 < v8 && v8 > v7 && v6 < v5 && v5 > v4 && v4 < v3 && v3 > v2 && v2 < v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 100000000) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		number= number/10;
		v4 = number % 10;
		number= number/10;
		v5 = number % 10;
		number= number/10;
		v6 = number % 10;
		number= number/10;
		v7 = number % 10;
		number= number/10;
		v8 = number % 10;
		number= number/10;
		v9 = number % 10;
		if (v9 < v8 && v8 > v7 && v7 < v6 && v6 > v5 && v5 < v4 && v4 > v3 && v3 < v2 && v2 > v1) {
			return 'M';
		}
		else if (v9 > v8 && v8 < v7 && v7 > v6 && v6 < v5 && v5 > v4 && v4 < v3 && v3 > v2 && v2 < v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 10000000) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		number= number/10;
		v4 = number % 10;
		number= number/10;
		v5 = number % 10;
		number= number/10;
		v6 = number % 10;
		number= number/10;
		v7 = number % 10;
		number= number/10;
		v8 = number % 10;
		if (v8 < v7 && v7 > v6 && v6 < v5 && v5 > v4 && v4 < v3 && v3 > v2 && v2 < v1) {
			return 'M';
		}
		else if (v8 > v7 && v7 < v6 && v6 > v5 && v5 < v4 && v4 > v3 && v3 < v2 && v2 > v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 1000000) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		number= number/10;
		v4 = number % 10;
		number= number/10;
		v5 = number % 10;
		number= number/10;
		v6 = number % 10;
		number= number/10;
		v7 = number % 10;
		if (v7 < v6 && v6 > v5 && v5 < v4 && v4 > v3 && v3 < v2 && v2 > v1) {
			return 'M';
		}
		else if (v7 > v6 && v6 < v5 && v5 > v4 && v4 < v3 && v3 > v2 && v2 < v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 100000) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		number= number/10;
		v4 = number % 10;
		number= number/10;
		v5 = number % 10;
		number= number/10;
		v6 = number % 10;
		if (v6 < v5 && v5 > v4 && v4 < v3 && v3 > v2 && v2 < v1) {
			return 'M';
		}
		else if (v6 > v5 && v5 < v4 && v4 > v3 && v3 < v2 && v2 > v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 10000) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		number= number/10;
		v4 = number % 10;
		number= number/10;
		v5 = number % 10;
		if (v5 < v4 && v4 > v3 && v3 < v2 && v2 > v1) {
			return 'M';
		}
		else if (v5 > v4 && v4 < v3 && v3 > v2 && v2 < v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 1000) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		number= number/10;
		v4 = number % 10;
		if (v4 < v3 && v3 > v2 && v2 < v1) {
			return 'M';
		}
		else if (v4 > v3 && v3 < v2 && v2 > v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 100) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		number= number/10;
		v3 = number % 10;
		if (v3 < v2 && v2 > v1) {
			return 'M';
		}
		else if (v3 > v2 && v2 < v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	else if (number >= 10) {
		v1 = number % 10;
		number= number/10;
		v2 = number % 10;
		if (v2 < v1) {
			return 'M';
		}
		else if (v2 > v1) {
			return 'V';
		}
		else { 
			return 'N'; 
		}
	}
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	return 'N';
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int m = 0; int v = 0;
	for (int x = a; x <= b; ++x) {
		if(classify_mv_range_type(x) == 'M') {
			m++;
		}
		if(classify_mv_range_type(x) == 'V') {
			v++;
		}
	}
	cout << "There are " << m << " mountain ranges and " << v << " valley ranges between " << a << " and " << b << "." << endl;
}