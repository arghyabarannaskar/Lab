#include<iostream>
using namespace std;

int main(){

    int x = 10;
    int y = 5;

    auto mixed_capture = [=, &y]() {
        // x is captured by value, y is captured by reference
        std::cout << "x: " << x << ", y: " << y << std::endl;
        y++;  // Can modify y
        x++;  // This would cause an error because x is captured by value
    };

    mixed_capture();
    std::cout << "y: " << y << std::endl;  // y will be 6


    return 0;
}