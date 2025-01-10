#include <iostream>
using std::cout, std::cin, std::endl, std::string;

long long combineDigitPairs(long long num) {
    if (num < 0) {
        throw std::invalid_argument("Not positive");
    }
    
    if (num < 10) {
        return num;
    }
    
    //int SIZE = 9223372036854775807;
    long long total = 1;
    int sum = 0;
    int check = 0;
    int check2 = 0;

    while (num > 0) {
        check = num%10;
        num/=10;
        check2 = num%10;
        sum = check * check2;
        total+=sum;  
    }
    return total;
}

int main () {
    cout << combineDigitPairs(1234);
}