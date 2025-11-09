#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function for modular exponentiation: (b^e) % m
long long modexp(long long b, long long e, long long m) {
    long long r = 1;
    b = b % m;
    while (e > 0) {
        if (e % 2 == 1)
            r = (r * b) % m;
        e /= 2;
        b = (b * b) % m;
    }
    return r;
}

int main() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Error: data.txt not found. Run sender first!" << endl;
        return 1;
    }

    long long n, d;
    string line;

    // Read first line: n and d
    getline(file, line);
    stringstream ss(line);
    ss >> n >> d;

    // Read second line: cipher number
    long long c;
    getline(file, line);
    stringstream ss2(line);
    ss2 >> c;

    cout << "n = " << n << ", d = " << d << endl;
    cout << "Received Ciphertext: " << c << endl;
    
    // Calculate key size in bits
    int key_size_bits = 0;
    long long temp = n;
    while (temp > 0) {
        key_size_bits++;
        temp >>= 1;
    }
    cout << "Key size: " << key_size_bits << " bits\n";

    // Start timing for decryption
    auto start_decrypt = high_resolution_clock::now();
    
    long long m = modexp(c, d, n);
    
    auto end_decrypt = high_resolution_clock::now();
    auto duration_decrypt = duration_cast<microseconds>(end_decrypt - start_decrypt);
    
    // Calculate decrypted message size in bits
    int msg_size_bits = 0;
    temp = m;
    while (temp > 0) {
        msg_size_bits++;
        temp >>= 1;
    }
    
    cout << "\nDecrypted Message: " << m << endl;
    cout << "Message size: " << msg_size_bits << " bits\n";
    cout << "Time for decryption: " << duration_decrypt.count() << " microseconds\n";

    return 0;
}
