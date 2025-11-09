#include<bits/stdc++.h>
using namespace std;
string encrypt(string msg, int key) {
    string encrypted = "";
    for (char c : msg) {
        encrypted += (c ^ key)+key; // Simple XOR encryption
    }
    return encrypted;
}
string decrypt(string msg, int key) {
    string decrypted = "";
    for (char c : msg) {
        decrypted += (c - key)^key; // Simple XOR decryption
    }
    return decrypted;
}
main(){
    string message = "HELLO";
    int key = 129; // Example key for XOR
    string encrypted_msg = encrypt(message, key);
    cout << "Encrypted Message: " << encrypted_msg << endl;
    string decrypted_msg = decrypt(encrypted_msg, key);
    cout << "Decrypted Message: " << decrypted_msg << endl;
    
}