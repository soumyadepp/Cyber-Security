#include <bits/stdc++.h>
using namespace std;

//consider only lowercase alphabets and spaces
string monoalphabetic_cipher(string plain_text,string KEY){
    string res = "";
    int store[256];
    int idx = 0;
    for(int i = 0 ; i < min(26,(int)KEY.size()); i++){
        store[idx++] = KEY[i] - 'a'; 
    }
    cout << "done =>" << endl;
    for(auto i : plain_text){
        res += i == ' ' ? ' ': store[i - 'a'] + 'a';
    }
    return res;
}


int main(){
    string plain_text = "my name is soumyadeep ghosh";
    string key = "thequickbrownfoxjumpsoverlazydog";
    string cipher_text = monoalphabetic_cipher(plain_text,key);

    cout << cipher_text;

    return 0;
}
