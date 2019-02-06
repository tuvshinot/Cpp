// Section 10
// Challenge - 
// Substitution Cipher

/*
A simple and very old method of sending secret messages is the substitution cipher.
You might have used this cipher with your friends when you were a kid.
Basically, each letter of the alphabet gets replaced by another letter of the alphabet.
For example, every 'a' get replaced with an 'X', and every 'b' gets replaced with a 'Z', etc.

Write a program thats ask a user to enter a secret message.

Encrypt this message using the substitution cipher and display the encrypted message.
Then decryped the encrypted message back to the original message.

You may use the 2 strings below for  your subsitition.
For example, to encrypt you can replace the character at position n in alphabet 
with the character at position n in key.

To decrypt you can replace the character at position n in key
with the character at position n in alphabet.

Have fun! And make the cipher stronger if you wish!
Currently the cipher only substitutes letters - you could easily add digits, puncuation, whitespace and so
forth. Also, currently the cipher always substitues a lowercase letter with an uppercase letter and vice-versa.
This could also be improved.

Remember, the less code you write the less code you have to test!
Reuse existing functionality in libraries and in the std::string class!
*/

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    
    string alphabet {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    string key  {"XZNLWEBGJHQDYVTKFUOMPCIASRxznlwebgjhqdyvtkfuompciasr"};
    string secret_message{};
    string encypted_message{};
    
    cout << "Enter word to encrypt : ";
    getline(cin, secret_message);
    
    for(char c : secret_message) {
        size_t position = alphabet.find(c);
        if(position != string::npos) {
            char new_char {key.at(position)};
            encypted_message += new_char;
        } else {
            encypted_message += c;
        }
    }
    
    cout << "Encrypting message..." << endl;
    cout << "\nEncrypted message : " << encypted_message << endl;
    
    string decrypted_message {};
    for(char c : encypted_message) {
        size_t pos = key.find(c);
        if(pos != string::npos) {
            char new_char = alphabet.at(pos);
            decrypted_message += new_char;
        } else {
            decrypted_message += c;
        }
    }
    
    cout << "Decrypted message..." << endl;
    cout << "Decrypted message: " << decrypted_message << endl;
    
    return 0;
}

