#include<bits/stdc++.h>
#include <cctype>
using namespace std;
string Ceaser(string text,int s){
    string result="";
    for(int i=0 ; i<text.length();i++)
    {   char ch;
        if(isupper(text[i])){
            ch = ((text[i]+s)%26)+'A';
        }
        else
        {
            ch =  ((text[i]+s)%26)+'a';
        }
        result = result+ch;
    }
    return result;
}
string vegenere(string text,string key)
{   
    string result="";
    int j=0;
    for(int i=0 ; i<text.length(); i++)
    {   text[i]= toupper(text[i]);
         key[j]=toupper(key[j]);

        char ch;
        ch=(text[i]+key[j])%26+'A';
        result = result+ch;
        j=(j+1)%key.length();
    }
    return result;
}
 
string monoalphabetic(string text,string key){
    string result="";
    for(int i=0 ; i<text.length(); i++)
    {   
        char ch = key[text[i]-'a'];
        result = result+ch;
    }
    return result;
}
string verman(string text,string key){
    string result="";
    int j=0;
    for(int i=0 ; i<text.length();i++)
    {
        char ch = text[i]^key[j];
        result = result+ch;
        j=(j+1)%key.length();
    }
}
string encryptRailFence(string text, int key) {
    vector<string> rail(key);
    int dir = 1, row = 0;

    for (char c : text) {
        rail[row] += c;
        if (row == 0)
            dir = 1;
        else if (row == key - 1)
            dir = -1;
        row += dir;
    }

    string result;
    for (string r : rail)
        result += r;
    return result;
}


int main(){
    int n;
    // cout<<"Enter the option number: ";
    // cin>>n;

    string enc=monoalphabetic("vishwatej","qwertyuiopasdfghjklzxcvbnm");
    cout<<enc<<endl;
   
    return 0;
      
}
