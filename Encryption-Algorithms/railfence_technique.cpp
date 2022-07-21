//railfence technique
#include <bits/stdc++.h>
using namespace std;

string railfence_technique_encrypt(string plain_text){
    int n = plain_text.size();
    string even = "", odd = "";
    for(int i = 0 ; i < n; i++){
        if(i & 1) odd += plain_text[i];
        else even += plain_text[i];
    }
    return even + odd;
}

int main(){
    string plain_text = "soumyadeep";
    string cipher_text = railfence_technique_encrypt(plain_text);
    cout << "CIPHER_TEXT : " << endl;
    cout << cipher_text << endl;

    return 0;
}
