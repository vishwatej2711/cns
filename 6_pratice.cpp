#include <iostream>
#include <string>
using namespace std;

// ---------- GCD ----------
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ---------- Modular Inverse ----------
long long modInverse(long long e, long long phi) {
    for (long long i = 1; i < phi; i++) {
        if ((e * i) % phi == 1)
            return i;
    }
    return 0;
}

// ---------- Modular Exponentiation ----------
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}

// ---------- Simple Hash Function ----------
long long simpleHash(const string &msg, long long mod) {
    long long hash = 0;
    for (char c : msg) {
        hash = (hash * 31 + c) % mod;
    }
    return hash;
}

int main() {
    long long p1, q1, e1, p2, q2, e2;
    cout << "=== RSA Secure Communication System ===\n\n";

    // Sender key generation
    cout << "Sender: Enter two prime numbers (p and q): ";
    cin >> p1 >> q1;
    long long n1 = p1 * q1;
    long long phi1 = (p1 - 1) * (q1 - 1);
    cout << "Sender's n = " << n1 << ", phi = " << phi1 << endl;
    cout << "Sender: Enter public exponent e (1 < e < phi, gcd(e, phi)=1): ";
    cin >> e1;
    long long d1 = modInverse(e1, phi1);
    cout << "Sender's Public Key (e, n): (" << e1 << ", " << n1 << ")\n";
    cout << "Sender's Private Key (d, n): (" << d1 << ", " << n1 << ")\n\n";

    // Receiver key generation
    cout << "Receiver: Enter two prime numbers (p and q): ";
    cin >> p2 >> q2;
    long long n2 = p2 * q2;
    long long phi2 = (p2 - 1) * (q2 - 1);
    cout << "Receiver's n = " << n2 << ", phi = " << phi2 << endl;
    cout << "Receiver: Enter public exponent e (1 < e < phi, gcd(e, phi)=1): ";
    cin >> e2;
    long long d2 = modInverse(e2, phi2);
    cout << "Receiver's Public Key (e, n): (" << e2 << ", " << n2 << ")\n";
    cout << "Receiver's Private Key (d, n): (" << d2 << ", " << n2 << ")\n\n";

    cin.ignore();
    string message;
    cout << "Enter message to send: ";
    getline(cin, message);

    // Sender: Hash and sign
    long long hashVal = simpleHash(message, n1);
    cout << "\nHash Value (SHA1 equivalent): " << hashVal << endl;

    long long signature = modExp(hashVal, d1, n1);
    cout << "Digital Signature (Encrypted Hash): " << signature << endl;

    // Encrypt message using Receiver's public key
    cout << "\nEncrypted Message (RSA): ";
    long long cipher[100];
    int len = message.size();
    for (int i = 0; i < len; i++) {
        cipher[i] = modExp((int)message[i], e2, n2);
        cout << cipher[i] << " ";
    }
    cout << endl;

    // Receiver: Decrypt message using private key
    cout << "\nDecrypted Message: ";
    string decrypted = "";
    for (int i = 0; i < len; i++) {
        char ch = (char)modExp(cipher[i], d2, n2);
        decrypted += ch;
    }
    cout << decrypted << endl;

    // Receiver verifies signature
    cout << "\nSenders Hash (Decrypted Signature): ";
    long long decryptedSig = modExp(signature, e1, n1);
    cout << decryptedSig << endl;

    long long receiverHash = simpleHash(decrypted, n1);
    cout << "Receivers Recomputed Hash:" << receiverHash << endl;

    if (decryptedSig == receiverHash)
        cout << "\n Verification Successful: Message is authentic and unaltered.\n";
    else
        cout << "\n Verification Failed: Message altered or sender not authentic.\n";

    return 0;
}
