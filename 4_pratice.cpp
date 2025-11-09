#include<bits/stdc++.h>
using namespace std;
int main(){
    int p=7,g=701; //prime number and primitive root
    int a=3,b=6; //private keys
    int A=(int)pow(g,a)%p; //public key of a
    cout<<"Public key of a is "<<A<<endl;
    int B=(int)pow(g,b)%p; //public key of b
    cout<<"Public key of b is "<<B<<endl;


    //without MItM attack
    // int ka=(int)pow(B,a)%p; //secret key for a
    // int kb=(int)pow(A,b)%p; //secret key for b
    // cout<<"Secret key for a is "<<ka<<endl;
    // cout<<"Secret key for b is "<<kb<<endl; 
    // if(ka==kb){
    //     cout<<"Successful key exchange"<<endl;
    //     cout<<"Enter the message to be sent: ";
    //     string msg;
    //     cin>>msg;
    //     cout<<"Message sent: "<<msg<<endl;
    //     for(char &c: msg){
    //         c=c^ka; //simple encryption using XOR with secret key
    //     }
    //     cout<<"Encrypted message: "<<msg<<endl;
    //     //At receiver's end
    //     for(char &c: msg){
    //         c=c^kb; //decryption using XOR with secret key
    //     }
    //     cout<<"Decrypted message: "<<msg<<endl;

    // }
    // else{
    //     cout<<"Key exchange failed"<<endl;
    // }
  
    //with MItM attack
    cout<<"\n---With MItM attack---\n"<<endl;
    int am=5,bm=4; //private keys of MITM
    int Am=(int)pow(g,am)%p; //public key of MITM for a
    int Bm=(int)pow(g,bm)%p; //public key of MITM for b
    //At A's side
    int E1 = (int)pow(A,am)%p; //MITM sends this to A instead of B
    int E2 = (int)pow(B,bm)%p; //MITM sends this to B instead of A

    int kam=(int)pow(E1,a)%p; //secret key for a with MITM
    cout<<"Secret key for a is "<<kam<<endl;
    //At B's side
    int kbm=(int)pow(E2,b)%p; //secret key for b with MITM
    cout<<"Secret key for b is "<<kbm<<endl;



    if(kam==kbm){
        cout<<"Successful key exchange with MITM"<<endl;
    }
    else{
        cout<<"Key exchange failed"<<endl;
    }
    cout<<"Enter the message to be sent: ";
    string msg2;
    cin>>msg2;
    cout<<"Message sent: "<<msg2<<endl;
    //MITM intercepts the message
    for(char &c: msg2){
        c=c^kam; //encryption using XOR with secret key
    }
    cout<<"Encrypted message intercepted by MITM: "<<msg2<<endl;
    //MITM decrypts the message
    for(char &c: msg2){
        c=c^E1; //decryption using XOR with secret key
    }
    cout<<"Decrypted message by MITM: "<<msg2<<endl;
    //MITM re-encrypts the message with b's key
    for(char &c: msg2){
        c=c^E2; //encryption using XOR with secret key
    }
    cout<<"Re-encrypted message sent to B: "<<msg2<<endl;
    //At B's end
    for(char &c: msg2){
        c=c^kbm; //decryption using XOR with secret key
    }

    cout<<"Decrypted message at B's end: "<<msg2<<endl;


}