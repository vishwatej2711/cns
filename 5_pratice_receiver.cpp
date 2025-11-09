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
        h = ((h << 5) + h) + c;

    stringstream ss;
    ss << hex << nouppercase << setw(8) << setfill('0') << (h & 0xFFFFFFFF);
    return ss.str();
}

int main() {
    cout << "=== RECEIVER SIDE ===\n";

    // Read message and hash from file
    ifstream in("network_data.txt");
    if (!in) {
        cerr << "Error: No data file found.\n";
        return 1;
    }

    string message, sent_hash;
    getline(in, message);
    getline(in, sent_hash);
    in.close();

    cout << "[RECEIVER] Received Message: " << message << endl;
    cout << "[RECEIVER] Received Hash: " << sent_hash << endl;

    // Compute own hash
    string my_hash = simple_hash(message);
    cout << "[RECEIVER] Recomputed Hash: " << my_hash << endl;

    if (my_hash == sent_hash)
        cout << "\n✅ Integrity Verified: Message not tampered.\n";
    else
        cout << "\n❌ Integrity Failed: Tampering detected!\n";

    return 0;
}
