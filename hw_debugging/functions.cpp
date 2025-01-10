#include <climits>
#include <stdexcept>

bool SumIsEven(int a, int b) {
  if((a+b)%2) {
    return false;
  }
  else {
    return true;
  }
}

int Largest(int a, int b, int c) {
  int d = a;
  if (a > d) {
    d = a;
  } 
  if (b > d) {
    d = b;
  } 
  if (c > d) {
    d = c;
  }
  return d;
}

unsigned int BoxesNeeded(int apples) {
  int a = apples;
  if (a > 0) {
    if (a < 20) {
      return 1;
    }
    if (a % 20 == 0) {
      return (a/20);
    }
    else {
      return (a/20 + 1);
    }
  }
  return 0;
}

bool SmarterSection(float A_correct, float A_total, float B_correct, float B_total) {
  //int sectA = 100 * (A_correct/A_total);
  if ((A_correct > A_total || B_correct > B_total) || (A_correct < 0 || B_correct < 0)) {
    throw std::invalid_argument("Cannot have more correct than were asked. Please input valid numbers.");
  }
  float sectA = 100 * float(A_correct/A_total);
  float sectB = 100 * float(B_correct/B_total);
  //int sectB = 100 * (B_correct/B_total);
  if (sectA > sectB) {
    return true;
  }
  else {
    return false;
  }
}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas < 0) {
    return false;
  }
  if (pizzas >= 10 && pizzas <= 20) {
    return true;
  }
  if (is_weekend && pizzas >= 10) {
    return true;
  }
  else {
    return false;
  }
  return false;
}

long long SumBetween(long long low, long long high) {
  //int value = 0;
  if (high == low) {
    return high;
  }
  if (high < low) {
    throw std::invalid_argument("Input out of order, input low first then high.");
  }
  //if (high = low) {
  //   return low;
  //}
  if(high  > 0 && low < 0){
    if(low == LLONG_MIN && high == LLONG_MAX){
      return low;
    }
  }
  if (high-low > 1000000) {
    throw std::overflow_error("Overflows minimum or maximum value. ");
  }
  long long count = high - low + 1;
  if (low > 0 && high > LLONG_MAX - low) {
        throw std::overflow_error("Summation causes overflow.");
  }
  if (low < LLONG_MIN || high > LLONG_MAX) {
    throw std::overflow_error("Overflows minimum or maximum value. ");
  }
  long long sum = count * (low + high) / 2;
  return sum;
  /*if (value < LLONG_MAX && value > LLONG_MIN) {
    return value;
  }*/
  //return value;
  //throw std::overflow_error("Overflows minimum or maximum value. ");
}

long long Product(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    if ((a > 0 && b > 0)) {
        if (LLONG_MAX / b < a) {
          throw std::overflow_error("Overflows minimum or maximum value.");
        }
    } 
    if ((a < 0 && b < 0)) {
      if (LLONG_MAX / b > a) {
        throw std::overflow_error("Overflows minimum or maximum value.");
      }
    }
    if ((a > 0 && b < 0)) {
        if (LLONG_MIN / b < a) {
            throw std::overflow_error("Overflows minimum or maximum value.");
        }
    }
    if (a < 0 && b > 0) {
      if (LLONG_MIN / b > a) {
        throw std::overflow_error("Overflows minimum or maximum value.");
      }
    }
    return a * b;


  /*if ((a > LLONG_MAX || a < LLONG_MIN) || (b > LLONG_MAX || b < LLONG_MIN))
  {
    throw std::overflow_error("Overflows minimum or maximum value. ");
  }*/
  //return a * b;
}