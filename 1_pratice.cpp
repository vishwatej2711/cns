#include<iostream>
#include<string>
#include<vector>
using namespace std;

string ceaser(string s, int shift) {
    string ans= "";
    for(int i=0;i<s.length();i++) {
        char ch = s[i];
        if(isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ans += char((ch - base + shift) % 26 + base);
        } else {
            ans += ch;
        }
    }
    return ans;
}

string deceaser(string s, int shift) {
    string ans= "";
    for(int i=0;i<s.length();i++) {
        char ch = s[i];
        if(isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ans += char((ch - base - shift + 26) % 26 + base);
        } else {
            ans += ch;
        }
    }
    return ans;
}


string monoalpha(string s, string key) {
    string ans= "";
    for(int i=0;i<s.length();i++) {
        char ch = s[i];
        if(isalpha(ch)) {
            int index = toupper(ch) - 'A';
            ans += key[index];
        }  else  {
            ans += ch;
        }
    }
    return ans;
}

string demonoalpha(string s, string key) {
    string ans= "";
    for(int i=0;i<s.length();i++) {
        char ch = s[i];
        if(isalpha(ch)) {
            ch = toupper(ch);
            int index = key.find(ch);
            ans += char(index + 'A');
        }  else  {
            ans += ch;
        }
    }
    return ans;
}


string polyalpha(string s, string key) {
    string ans= "";
    for(int i=0;i<s.length();i++)
    {
        char c = toupper(s[i]);
        char k = toupper(key[i % key.size()]);
        if(isalpha(c)){
            ans += char(((c - 'A') + (k - 'A'))% 26 + 'A' );
        } else {
            ans += c;
        }
    }
    return ans;
}

string depolyalpha(string s, string key) {
    string ans= "";
    for(int i=0;i<s.length();i++)
    {
        char c = toupper(s[i]);
        char k = toupper(key[i % key.size()]);
        if(isalpha(c)){
            ans += char(((c - 'A') - (k - 'A') + 26)% 26 + 'A' );
        } else {
            ans += c;
        }
    }
    return ans;
}


string railfence(string text, int key) {
    vector<string> rail(key);
    int row = 0, dir = 1;

    for (char c : text) {
        rail[row] += c;
        if (row == 0) dir = 1;
        else if (row == key - 1) dir = -1;
        row += dir;
    }

    string result = "";
    for (string r : rail) result += r;
    return result;
}

string derailfence(string cipher, int key) {
    vector<string> rail(key);
    vector<int> railLen(key, 0);
    int row = 0, dir = 1;

    for (char c : cipher) {
        railLen[row]++;
        if (row == 0) dir = 1;
        else if (row == key - 1) dir = -1;
        row += dir;
    }

    int index = 0;
    for (int i = 0; i < key; i++) {
        rail[i] = cipher.substr(index, railLen[i]);
        index += railLen[i];
    }

    string result = "";
    row = 0; dir = 1;
    vector<int> railIndex(key, 0);

    for (int i = 0; i < cipher.size(); i++) {
        result += rail[row][railIndex[row]++];
        if (row == 0) dir = 1;
        else if (row == key - 1) dir = -1;
        row += dir;
    }

    return result;
}


string vernam(string text, string key) {
    string result = "";
    int keyIndex = 0;

    for (int i = 0; i < text.size(); i++) {
        char c = toupper(text[i]);
        if (!isalpha(c)) {
            result += c;
            continue;
        }

        char k = toupper(key[keyIndex % key.size()]);
        // char encrypted = char((((c - 'A') ^ (k - 'A')) % 26) + 'A');
        // this is also one method using XOR but it is difficult to decrypt as xor operation is not reversible in mod 26
        int enc = ( (c - 'A') + (k - 'A') ) % 26;
        result += char(enc + 'A');
        keyIndex++;
    }
    return result;
}


string devernam(string text, string key) {
    string result = "";
    int keyIndex = 0;

    for (int i = 0; i < text.size(); i++) {
        char c = toupper(text[i]);
        if (!isalpha(c)) {
            result += c;
            continue;
        }

        char k = toupper(key[keyIndex % key.size()]);
        int dec = ( (c - 'A') - (k - 'A') + 26 ) % 26;
        result += char(dec + 'A');
        keyIndex++;
    }
    return result;
}
string eonetimepad(string text, string key) {
    string cipher = "";
    for (int i = 0; i < text.size(); i++)
        cipher += text[i] ^ key[i];   // XOR for encryption
    return cipher;
}

string donetimepad(string cipher, string key) {
    string text = "";
    for (int i = 0; i < cipher.size(); i++)
        text += cipher[i] ^ key[i];   // XOR again for decryption
    return text;
}


int main()
{
    int num;
    int flag = 1;
    do{
        cout<<"Encryption Algorithms: "<<endl;
        cout<<"1.Caesar Cipher \n 2.Monoalphabetic Cipher \n 3.Polyalphabetic Cipher \n 4.Rail Fence Cipher \n 5.Vernam Cipher  "<<endl;
        cout<<"<---Select one of the following Encryption Algorithm with which you want to encrypt your string(1-5)--->";
        cin>>num;
        cin.ignore();
        string s, Key, encrypted, decrypted;
        int shift;

        cout<<"Enter a string to encrypt: ";
        getline(cin, s); 
        if(num == 1 || num == 4){
            if(num == 4)
                cout<<"NOTE: While entering shift for Rail Fence cipher please enter integer value only"<<endl; 
            if(num == 1)
                cout<<"NOTE: While entering shift for Caesar cipher please enter integer value only"<<endl;
                
            cout<<"Enter shift value: ";
            cin>>shift;
        }
        else
        {
            if(num == 2)
                cout<<"NOTE: While entering Key for Monoalphabetic cipher please enter 26 character string in any order"<<endl;
            if(num == 3)
                cout<<"NOTE: While entering Key for Polyalphabetic cipher please enter a string of any length"<<endl;
            if(num == 5)
                cout<<"NOTE: While entering Key for Vernam cipher please enter a string of any length"<<endl;   
            
            cout<<"Enter Key: ";
            cin>>Key;
        }
        cout<<"Original string: \n " << s << endl;
        switch(num)
        {
            case 1:
                cout<<"You have selected Caesar Cipher"<<endl;
                encrypted =ceaser(s, shift);
                break;
            
            case 2:
                cout<<"You have selected Monoalphabetic Cipher"<<endl;
                encrypted = monoalpha(s, Key);
                break;
            
            case 3:
                cout<<"You have selected Polyalphabetic Cipher"<<endl;
                encrypted = polyalpha(s, Key);
                break;
            
            case 4: 
                cout<<"You have selected Rail Fence Cipher"<<endl;
                encrypted = railfence(s, shift);
                break;
            
            case 5:
                cout<<"You have selected Vernam Cipher "<<endl;
                encrypted = vernam(s, Key);
                break;    

            default:
                cout<<"Invalid Option"<<endl;
                break;
        }
        cout<<"--------------------------------------------"<<endl;
        cout<<"Encrypted string: "<< encrypted << endl;
        cout<<"--------------------------------------------"<<endl;

        switch(num)
        {
            case 1:
                cout<<"Decryption using Caesar Cipher"<<endl;
                decrypted =deceaser(encrypted, shift);
                break;
            
            case 2:
                cout<<"Decryption using Monoalphabetic Cipher"<<endl;
                decrypted = demonoalpha(encrypted, Key);
                break;
            
            case 3:
                cout<<"Decryption using Polyalphabetic Cipher"<<endl;
                decrypted = depolyalpha(encrypted, Key);
                break;
            
            case 4: 
                cout<<"Decryption using Rail Fence Cipher"<<endl;
                decrypted = derailfence(encrypted, shift);
                break;
            
            case 5:
                cout<<"Decryption using Vernam Cipher"<<endl;
                decrypted = devernam(encrypted, Key);
                break; 
            
            default:
                cout<<"Invalid Option"<<endl;
                break;    
                
        }

        cout<<"--------------------------------------------"<<endl;
        cout<<"Decrypted string: "<< decrypted << endl;    
        cout<<"--------------------------------------------"<<endl;

        cout<<"Do you want to continue? (1 for Yes / 0 for No): ";
        cin>>flag;
    
    } while(flag);

    return 0;
}

