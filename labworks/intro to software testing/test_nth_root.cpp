#include <iostream>
#include <cmath>
#include "./nth_root.h"
#include  "test_helpers.h"



int main() {
    bool pass = true;

    {   // MINIMUM REQUIREMENT (for this lab)
        // Testing nth_root with various values
        nth_root(2, 1);

        // Exception testing without using std::domain_error
        try {
            nth_root(-6, 0);
            std::cout << "[FAIL] expected nth_root(-6, 0) to throw an exception, but nothing thrown" << std::endl;
            pass = false;
        } catch (...) {
            std::cout << "[PASS] nth_root(-6, 0) threw an exception as expected" << std::endl;
        }

        try {
            nth_root(0, 1);
            std::cout << "[FAIL] expected nth_root(0, 1) to throw an exception, but nothing thrown" << std::endl;
            pass = false;
        } catch (...) {
            std::cout << "[PASS] nth_root(0, 1) threw an exception as expected" << std::endl;
        }

        try {
            nth_root(4, -2);
            std::cout << "[FAIL] expected nth_root(4, -2) to throw an exception, but nothing thrown" << std::endl;
            pass = false;
        } catch (...) {
            std::cout << "[PASS] nth_root(4, -2) threw an exception as expected" << std::endl;
        }

        nth_root(3, -3);
        nth_root(-1, 6);
        nth_root(-9, -6);
        nth_root(1, 10);
        nth_root(-3, 21);
        nth_root(6, 1.0 / 10);
        nth_root(6, 7.0 / 8);
    }


    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
