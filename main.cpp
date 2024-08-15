#include <iostream>
#include <string>
#include <algorithm>

std::string addition(std::string x, std::string y, std::string base) {
    int lenx = x.length();
    int leny = y.length();
    int b = std::stoi(base);
    int len = std::max(lenx, leny);
    int carry = 0;
    std::string result;

    for (int i = 0; i < len; i++) {
        int digitx, digity;
        if (i < lenx) {
            digitx = x[lenx - i - 1] - '0';
        }
        else {
            digitx = 0;
        }
        if (i < leny) {
            digity = y[leny - i - 1] - '0';
        }
        else {
            digity = 0;
        }
        int sum_digits = digitx + digity + carry;
        carry = sum_digits / b;
        sum_digits = sum_digits % b;
        result = std::to_string(sum_digits) + result;
    }

    if (carry > 0) {
        result = std::to_string(carry) + result;
    }
    return result;
}

// only for case where x > y
// this is necessary for Karasuba final step to combine all results
std::string subtraction(std::string x, std::string y, std::string base) {
    int lenx = x.length();
    int leny = y.length();
    int b = std::stoi(base);
    int borrow = 0;
    std::string result;

    for (int i = 0; i < lenx; i++) {
        int digitx, digity;
        digitx = x[lenx - i - 1] - '0'; 
        
        if (i < leny) {
            digity = y[leny - i - 1] - '0';
        }
        else {
            digity = 0;
        }
        int substract = digitx - digity - borrow;
        if (substract >= 0) {
            borrow = 0;
        }
        else {
            substract = substract + b;
            borrow = 1;
        }
        result = result + std::to_string(substract);
    }
    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string KaratsubaMultiplication(std::string x, std::string y, std::string base) {
    std::string result;
    int lenx = x.length();
    int leny = y.length();
    int len = std::max(lenx, leny);
    int k = len / 2;
    
    //std::cout << "Initial x: " << x << ", y: " << y << std::endl;

    // Padding with leading zeros
    if (lenx < len) {
        x = std::string(len - lenx, '0') + x;
    }
    if (leny < len) {
        y = std::string(len - leny, '0') + y;
    }

    lenx = x.length();
    leny = y.length();
    // Base case for recursion
    if (lenx == 1 || leny == 1) {
        std::string product = "0";
        for (int i = 0; i < std::stoi(x); i++) {
            product = addition(product, y, base);
        }
        //std::cout << "Base case multiplication: " << x << " * " << y << " = " << product << std::endl;
        return product;
    }

    //std::cout << "After padding x: " << x << ", y: " << y << std::endl;

    // Splitting the numbers
    std::string x1 = x.substr(0, len - k);
    std::string x0 = x.substr(len - k);
    std::string y1 = y.substr(0, len - k);
    std::string y0 = y.substr(len - k);

    // std::cout << "Split x1: " << x1 << ", x0: " << x0 << std::endl;
    // std::cout << "Split y1: " << y1 << ", y0: " << y0 << std::endl;

    // Recursive multiplications
    std::string p0 = KaratsubaMultiplication(x0, y0, base);
    std::string p2 = KaratsubaMultiplication(x1, y1, base);
    std::string p1 = KaratsubaMultiplication(addition(x0, x1, base), addition(y0, y1, base), base);

    //std::cout << "p0: " << p0 << ", p1: " << p1 << ", p2: " << p2 << std::endl;

    // Combining the results
    std::string result1 = p2 + std::string(2 * k, '0');
    std::string result2 = subtraction(p1, addition(p2, p0, base), base) + std::string(k, '0');
    
    // std::cout << "Result1 (p2 shifted): " << result1 << std::endl;
    // std::cout << "Result2 (p1 - p2 - p0 shifted): " << result2 << std::endl;

    result = addition(addition(result1, result2, base), p0, base);

    //std::cout << "Final result: " << result << std::endl;
    return result;
}

int main() {
    std::string x, y, base;
    std::cin >> x >> y >> base;
    std::string multiplied_result = KaratsubaMultiplication(x, y, base);
    int index = 0;
    int result_len = multiplied_result.length();
    for (int i = 0; i < result_len; i++) {
        if (multiplied_result[i] == '0') {
            index++;
        }
    }
    multiplied_result = multiplied_result.substr(index - 1);

    std::cout << addition(x, y, base) << " " << multiplied_result << " " << "0" << std::endl; 
    return 0;
}