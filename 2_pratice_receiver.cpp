#include<bits/stdc++.h>

using namespace std;


long long modInv(long long e, long long phi)
{
    for(int i=1;i<phi;i++)
    {
        if((e * i)%phi == 1 )
            return i;
    }
    return -1;
}

long long modexp(long long base, long long expo, long long mod)
{
    long long result = 1;
    base%=mod;
    while(expo > 0)
    {
        if(expo%2 != 0)
            result= (result * base)%mod;
        expo/=2;
        base=(base * base)%mod;
    }
    return result;
}


int main()
{
    ifstream fin("cipher.txt");
    if(!fin)
    {
        cout<<"Error: 'cipher.txt not found";
        return 0;
    }
    
    long long n,e;
    fin>>n>>e;
    vector<long long > cipher;
    long long temp;
    while (fin >> temp)
    {
        cipher.push_back(temp);
    }
    fin.close();
    
    cout<<"Received Public Keys:(n,e)=>("<<n<<","<<e<<")"<<endl;
    cout<<"Cipher:";
    for(auto c: cipher)
        cout<<c<<" ";
    
    long long p,q;
    cout<<"\n Enter the same prime numbers that were entered by sender:";
    cin>>p>>q;
    
    long long phi;
    if(p * q != n)
    {    cout<<"Error: You did not entered correct prime numbers";
        return 0;
    }    
    phi = (p - 1)*(q - 1);
    
    auto startD = chrono::high_resolution_clock::now();
    long long d = modInv(e,phi);
    auto endD = chrono::high_resolution_clock::now();
    chrono::duration<double> privTime = endD - startD;
    
    if(d == -1)
    {
        cout<<"Error: Modular inverse doees not exusts (e, phi )not coprime"<<endl;
        return 0;
    }
    
    auto startDec = chrono::high_resolution_clock::now();
    string message="";
    for(auto c:cipher)
    {
        long long m = modexp(c,d,n);
        message+=char(m + 'A');
    }
    auto endDec = chrono::high_resolution_clock::now();
    chrono::duration<double> decTime = endDec - startDec;
    cout<<"Decrypted text:"<<message<<endl;
    cout<<"Decryption time: "<<decTime.count()<<" seconds"<<endl;
}
