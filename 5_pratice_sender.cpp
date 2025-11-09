#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <fstream>
using namespace std;

string simple_hash(const string &s) {
    uint32_t h = 5381;
    for (unsigned char c : s)
        h = ((h << 5) + h) + c; // h = h * 33 + c

    stringstream ss;
    ss << hex << nouppercase << setw(8) << setfill('0') << (h & 0xFFFFFFFF);
    return ss.str();
}

int main() {
    cout << "=== SENDER SIDE ===\n";
    cout << "Enter message to send: ";
    string message;
    getline(cin, message);

    string digest = simple_hash(message);

    cout << "\n[SENDER] Message: " << message << endl;
    cout << "[SENDER] Computed Hash: " << digest << endl;

    // Save to file (simulate network transmission)
    ofstream out("network_data.txt");
    out << message << "\n" << digest;
    out.close();

    cout << "\nMessage and hash written to network_data.txt (simulated network).\n";
    return 0;
}
