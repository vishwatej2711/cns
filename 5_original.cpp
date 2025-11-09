// A5
// A message is to be transmitted using network resources from one machine to another.
// Calculate and demonstrate the use of a Hash value equivalent to SHA-1.
// Program in C++ using Eclipse.

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <sstream>

uint32_t leftrotate(uint32_t x, unsigned n)
{
    return (x << n) | (x >> (32 - n));
}

std::string sha1(const std::string &message)
{
    // Convert message to bytes
    std::vector<uint8_t> data(message.begin(), message.end());

    // Message length in bits
    uint64_t ml = static_cast<uint64_t>(data.size()) * 8ULL;

    // Append 0x80
    data.push_back(0x80);

    // Append 0x00 until length ≡ 56 (mod 64)
    while ((data.size() % 64) != 56)
    {
        data.push_back(0x00);
    }

    // Append 64-bit big-endian length
    for (int i = 7; i >= 0; --i)
    {
        data.push_back(static_cast<uint8_t>((ml >> (8 * i)) & 0xFF));
    }

    // Initial hash values (h0..h4)
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // Process each 512-bit chunk
    for (size_t offset = 0; offset < data.size(); offset += 64)
    {
        // Prepare message schedule w[0..79]
        uint32_t w[80];
        // first 16 words from the chunk
        for (int t = 0; t < 16; ++t)
        {
            size_t idx = offset + t * 4;
            w[t] = (static_cast<uint32_t>(data[idx]) << 24) |
                   (static_cast<uint32_t>(data[idx + 1]) << 16) |
                   (static_cast<uint32_t>(data[idx + 2]) << 8) |
                   (static_cast<uint32_t>(data[idx + 3]));
        }
        // remaining words
        for (int t = 16; t < 80; ++t)
        {
            w[t] = leftrotate(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
        }

        // Initialize working variables
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        // Main loop
        for (int t = 0; t < 80; ++t)
        {
            uint32_t f, k;
            if (t < 20)
            {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (t < 40)
            {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (t < 60)
            {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else
            {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = leftrotate(a, 5) + f + e + k + w[t];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }

        // Add this chunk's hash to result so far
        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
    }

    // Produce the final digest (20 bytes)
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setfill('0');
    oss << std::setw(8) << (h0);
    oss << std::setw(8) << (h1);
    oss << std::setw(8) << (h2);
    oss << std::setw(8) << (h3);
    oss << std::setw(8) << (h4);

    // The above prints the registers as 8-hex each (32 bits) concatenated,
    // but std::hex on uint32_t will not pad each to exactly 8 digits if the stream
    // interprets them as integers. To ensure each register is exactly 8 hex digits,
    // build from bytes instead:
    std::ostringstream digest_stream;
    digest_stream << std::uppercase << std::hex << std::setfill('0');
    auto append_be = [&](uint32_t v)
    {
        digest_stream << std::setw(2) << ((v >> 24) & 0xFF);
        digest_stream << std::setw(2) << ((v >> 16) & 0xFF);
        digest_stream << std::setw(2) << ((v >> 8) & 0xFF);
        digest_stream << std::setw(2) << (v & 0xFF);
    };
    append_be(h0);
    append_be(h1);
    append_be(h2);
    append_be(h3);
    append_be(h4);

    return digest_stream.str();
}

int main()
{
    std::string message;
    std::cout << "Enter the message to be hashed: ";
    if (!std::getline(std::cin, message))
    {
        message = "";
    }

    std::string h = sha1(message);

    std::cout << std::endl;
    std::cout << "SHA-1 Hash of the message is:" << h << std::endl;
    std::cout << std::endl;
    std::cout << "First 8 characters of the hash are: " << h.substr(0, 8) << std::endl;

    return 0;
}