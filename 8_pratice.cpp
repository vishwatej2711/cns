#include <iostream>
#include <fstream>
using namespace std;

// Encrypt the image using Caesar Cipher
void encryptImage(const string &inputFile, const string &outputFile, int key) {
    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);
    if (!fin || !fout) {
        cout << "Error opening file!" << endl;
        return;
    }

    char ch;
    while (fin.get(ch)) {
        // Shift byte by key (mod 256 for wrap-around)
        unsigned char encrypted = (unsigned char)(ch + key) % 256;
        fout.put(encrypted);
    }

    fin.close();
    fout.close();
    cout << "Image encrypted successfully → " << outputFile << endl;
}

// Decrypt the image using Caesar Cipher
void decryptImage(const string &inputFile, const string &outputFile, int key) {
    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);
    if (!fin || !fout) {
        cout << "Error opening file!" << endl;
        return;
    }

    char ch;
    while (fin.get(ch)) {
        // Reverse shift
        unsigned char decrypted = (unsigned char)((ch - key + 256) % 256);
        fout.put(decrypted);
    }

    fin.close();
    fout.close();
    cout << "Image decrypted successfully → " << outputFile << endl;
}

int main() {
    string inputFile, encryptedFile, decryptedFile;
    int key;

    cout << "Enter input image filename (e.g., image.jpg): ";
    cin >> inputFile;
    cout << "Enter encrypted output filename (e.g., encrypted.img): ";
    cin >> encryptedFile;
    cout << "Enter decrypted output filename (e.g., decrypted.jpg): ";
    cin >> decryptedFile;
    cout << "Enter numeric key (1–255): ";
    cin >> key;

    encryptImage(inputFile, encryptedFile, key);
    decryptImage(encryptedFile, decryptedFile, key);

    return 0;
}
