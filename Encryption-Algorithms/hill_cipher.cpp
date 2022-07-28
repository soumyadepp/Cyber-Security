#include <bits/stdc++.h>
using namespace std;

vector<vector<int>>matrix_multiplication_mod26(vector<vector<int>>mat1,vector<vector<int>>mat2){
    vector<vector<int>>ans(mat1.size(),vector<int>(mat2[0].size(),0));
    for(int i = 0 ; i < mat1.size(); i++){
        for(int j = 0 ; j < mat2[0].size(); j++){
            for(int k = 0 ; k < mat1[0].size(); k++){
                ans[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    for(auto &i : ans){
        for(auto &j : i){
            j = j % 26;
        }
    }
    return ans;
}

string hill_cipher(string plain_text,vector<vector<int>>key){
    int n = key.size();
    string temp = "";
    temp.push_back(plain_text[0]);
    vector<string>parts;
    int i = 1;
    while(i < plain_text.size()){
        if(temp.size() == key.size()){
            parts.push_back(temp);
            temp = "";
        }
        else if(temp.back() == plain_text[i]){
            temp += "x";
        }
        else{
            temp += plain_text[i++];
        }
    }
    if(temp.size()){
        while(temp.size() < key.size()){
            temp += "x";
        }
        parts.push_back(temp);
    }
    vector<vector<int>>multipliers;
    for(auto i : parts){
        vector<int>temp;
        for(auto ch : i){
            temp.push_back(ch - 'a');
        }
        multipliers.push_back(temp);
    }
    vector<vector<int>>encrypted_parts = matrix_multiplication_mod26(multipliers,key);
    string ans = "";
    cout << "Encrypt\n";
    for(auto i : encrypted_parts){
        for(auto j : i){
            ans.push_back(j + 'a');
        }
    }
    return ans;
}

int main(){
    string plain_text = "soumyadeep";
    vector<vector<int>>key = {{1,2,0},{3,11,4},{4,13,1}};
    string cipher_text = hill_cipher(plain_text,key);
    cout << "cipher text : " << cipher_text << endl;

    return 0;
}
