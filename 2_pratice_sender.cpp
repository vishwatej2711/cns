#include<bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b)
{
    while(b!=0)
    {
        long long temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}

long long modexp(long long base, long long expo, long long mod)
{
    long long result=1;
    base%=mod;
    while(expo > 0)
    {
        if(expo%2!=0)
            result=(result * base)%mod;
        expo/=2;
        base=(base * base)%mod;
    }
    return result;
}



bool isPrime(long long num)
{
    if(num <= 1)
        return false;
    if(num <=3)
        return true;
    if(num % 2 == 0 || num % 3 == 0)
        return false;
        
    for(int i=5;i*i<num;i+=6)
    {
        if(num%i == 0 || num % (i +2) == 0)
            return false;
    }
    return true;
}

int main()
{
    long long p,q;
    cout<<"Enter two prime numbers(p and q) [p > 5 and q > 5]:";
    cin>>p>>q;
    while(!isPrime(p))
    {
        cout<<"p is not a prime number. Enter correct prime number:";
        cin>>p;
    }
    
    while(!isPrime(q))
    {
        cout<<"q is not a prime number. Enter correct prime number:";
        cin>>q;
    }
    
    long long n,phi,e;
    n = p * q;
    phi = (p - 1)*(q - 1);
    cout<<"n: "<<n<<", phi: "<<phi<<endl;
    
    auto startE = chrono::high_resolution_clock::now();
    cout<<"Enter public enponential(e) such that gcd(e,phi)==1 && 1< e < phi: ";
    cin>>e;
    while(gcd(e,phi)!= 1  || 1 > e || e > phi)
    {
        cout<<"Invalid input e, try again:";
        cin>>e;
    }
    
    auto endE = chrono::high_resolution_clock::now();
    chrono::duration<double> keyTime = endE - startE;
    
    cout<<"Public Key(e,n): ("<<e<<","<<n<<")"<<endl;
    cout<<"Time to generate key pairs:"<<keyTime.count()<<" seconds"<<endl;
    
    cin.ignore();
    string msg;
    cout<<"Enter the message:";
    getline(cin, msg);
    
    cout<<"Encrypted Text:";
    
    auto startEnc = chrono::high_resolution_clock::now();
    vector<long long> cipher;

    for (char ch : msg)
    {
        if (isalpha(ch))
        {
            char base = isupper(ch) ? 'A' : 'a';
            long long msgVal = ch - base;
            long long c = modexp(msgVal, e, n);
            cipher.push_back(c);
    
            cout << char((c % 26) + base);
        }
    }

        
    auto endEnc = chrono::high_resolution_clock::now();
    chrono::duration<double> encTime = endEnc - startEnc;
    
    cout<<"\nEncryption time:"<<encTime.count()<<" seconds"<<endl;
    
    
    ofstream fout("cipher.txt");
    fout<<n<<" "<<e<<"\n";
    for(auto c: cipher)
        fout<<c<<" ";
    fout.close();
    
    cout<<"Saved 'cipher.txt' for Receiver program";
    
    return 0;
    
    
    
}
