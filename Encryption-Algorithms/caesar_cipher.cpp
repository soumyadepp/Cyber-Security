#include <bits/stdc++.h>

using namespace std;

unordered_map<char,int>mp;

void init(){
    int i = 1;
    for(char ch = 'a'; ch <= 'z'; ch++,i++){
        mp[ch] = i;
    }
    i = 1;
    for(char ch = 'A' ; ch <= 'Z' ; ch++,i++){
        mp[ch] = i;
    }
}

string caesar_cipher(string plain_text,int k){
    string ans = "";
    int i = 1;
    for(auto i : plain_text){
        if(i != ' '){
            ans += islower(i) ? ((mp[i] + k - 1)%26 + 'a') : ((mp[i] + k - 1)%26 + 'A');
        }
        else{
            ans += " ";
        }
    }
    return ans;
}

string decrypt(string cipher_text,int k){
    string plain_text_from_decrypt = "";
    for(auto i : cipher_text){
        if(i != ' '){
            if(mp[i] - k - 1 >= 0)
            plain_text_from_decrypt += islower(i) ? mp[i] - 1 - k + 'a' : mp[i] - 1 - k + 'A';
            else{
                plain_text_from_decrypt += islower(i) ? 'z' + mp[i] - k  : 'Z' + mp[i] - k ;
            }
        }
        else{
            plain_text_from_decrypt += " ";
        }
    }
    return plain_text_from_decrypt;
}

int brute_force_key_find(string cipher_text,string plain_text){
    // O(26 * N)
    for(int i = 1 ; i <= 26 ; i++){
        string check = decrypt(cipher_text,i);
        if(check == plain_text) return i;
    }
    return -1;
}

int main(){
    //initialize the map
    init();
    //running test cases
    for(int i = 1 ; i <= 26 ; i++){
        cout << "TEST CASE : " << i  << endl;
        cout << "-----------------------------\n";
        string plain_text = "I am Soumyadeep";
        string cipher_text = caesar_cipher(plain_text,i);
        //ask for key
        int key = brute_force_key_find(cipher_text,plain_text);
        //use the key to decrypt
        if(key != -1){
            string plain_text_from_decrypt = decrypt(cipher_text,key);
            if(plain_text_from_decrypt != plain_text){
                cout << "TEST CASE FAILED at key = " << i << endl; 
                exit(-1);
            }
            cout << "Plain text : " << plain_text << endl;
            cout << "Cipher text :" << cipher_text << endl;
            cout << "Decrypted text : " << plain_text_from_decrypt << endl;
            cout << "Key used to decrypt was " << key << endl;
            cout << endl;
        }
        else{
            cout << "This text was not encrypted by caesar cipher" << endl;
        }
    }
    return 0;
}
