// Section 11
// Function Overloading
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void print(int);
void print(double);
void print(string);
void print(string, string);
void print(vector<string>);

int find_area(int);
double find_area(double,double);


void print(int num) {
    cout << "Printing int: " << num << endl;
}

void print(double num) {
    cout << "Printing double: " << num << endl;
}

void print(string s) {
    cout << "Printing string: " << s << endl;
}

void print(string s, string t) {
    cout << "Printing 2 strings: " << s << " and " << t << endl;
}

void print(vector<string> v) {
    cout << "Printing vector of strings: " ;
    for (auto s: v )
        cout << s + " ";
    cout << endl;
}

int main() {
    print(100);    // int
    print('A');     //  character is always promoted to int should print 65 ASCII ('A')
    
    print(123.5);   // double
    print(123.3F);  // Float is promoted to double
    
    print("C-style string");  // C-style string is converted to a C++ string
    
    string s {"C++ string"};    
    print(s);       // C++ string
    
    print("C-style string", s); // First argument is converted to a C++ string
    
    vector<string> three_stooges {"Larry", "Moe", "Curly"};
    print(three_stooges);
    
    cout << endl;
    
    
    
    // radius exercise function call
    int square_area = find_area(2);
    double rectangle_area = find_area(4.5,2.3);
    
    return 0;
}



int find_area(int side_length) {
    return pow(side_length,2); //return side_length*side_length will also work
}

double find_area(double length, double width) {
    return length*width;
}