
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

long long gcd(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long modinv(long long e, long long phi) {
    for (long long i = 1; i < phi; ++i) {
        if ((e * i) % phi == 1)
            return i;
    }
    return -1; 
}

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

bool is_prime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0) return false;
    for (long long i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    long long p, q;

    while (true) {
        cout << "Enter prime number p: ";
        cin >> p;
        cout << "Enter prime number q: ";
        cin >> q;
        if (is_prime(p) && is_prime(q)) break;
        cout << "Both p and q must be prime numbers! Try again.\n\n";
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    cout << "\nn = " << n << ", phi = " << phi << "\n";
    
    // Calculate key size in bits
    int key_size_bits = 0;
    long long temp = n;
    while (temp > 0) {
        key_size_bits++;
        temp >>= 1;
    }
    cout << "Key size: " << key_size_bits << " bits\n";

    long long e;
    while (true) {
        cout << "Enter e : ";
        cin >> e;
        if (gcd(e, phi) == 1) break;
        cout << "Invalid e! Try again.\n";
    }

    // Start timing for key generation
    auto start_keygen = high_resolution_clock::now();
    
    long long d = modinv(e, phi);
    if (d == -1) {
        cerr << "Could not find modular inverse for e. Exiting.\n";
        return 1;
    }
    
    auto end_keygen = high_resolution_clock::now();
    auto duration_keygen = duration_cast<microseconds>(end_keygen - start_keygen);
    
    cout << "\nPrivate key (d) = " << d << "\n";
    cout << "Time for key generation: " << duration_keygen.count() << " microseconds\n";

    long long m;
    cout << "\nEnter the number to encrypt: ";
    cin >> m;
    
    // Calculate message size in bits
    int msg_size_bits = 0;
    temp = m;
    while (temp > 0) {
        msg_size_bits++;
        temp >>= 1;
    }
    cout << "Message size: " << msg_size_bits << " bits\n";

    // Start timing for encryption
    auto start_encrypt = high_resolution_clock::now();
    
    long long c = modexp(m, e, n);
    
    auto end_encrypt = high_resolution_clock::now();
    auto duration_encrypt = duration_cast<microseconds>(end_encrypt - start_encrypt);
    
    cout << "\nCiphertext = " << c << "\n";
    cout << "Time for encryption: " << duration_encrypt.count() << " microseconds\n";

    ofstream fout("data.txt");
    if (!fout.is_open()) {
        cerr << "Error: could not open data.txt for writing.\n";
        return 1;
    }
    fout << n << " " << d << "\n" << c << "\n";
    fout.close();

    cout << "\n[+] Ciphertext and keys saved to data.txt successfully!\n";
    return 0;
}
