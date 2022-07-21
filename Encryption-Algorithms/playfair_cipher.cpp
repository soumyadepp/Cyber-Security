#include <bits/stdc++.h>
using namespace std;

//consider i and j as degrams
//assumption : both degrams dont occur in the same string simultaneously and key has no spaces
unordered_map<char,pair<int,int>>char_to_indices;
char playfair_matrix[5][5];


string get_cipher_string(char a,char b){
    pair<int,int>pos_of_a = char_to_indices[a];
    pair<int,int>pos_of_b = char_to_indices[b];
    string res = "";
    char f_char,s_char;
    //if the characters are in same row
    if(pos_of_a.first == pos_of_b.first){
        f_char = playfair_matrix[pos_of_a.first][(pos_of_a.second + 1)%5];
        s_char = playfair_matrix[pos_of_b.first][(pos_of_b.second + 1)%5];
    }
    //if the characters are in same column
    else if(pos_of_a.second == pos_of_b.second){
        f_char = playfair_matrix[(pos_of_a.first + 1)%5][pos_of_a.second];
        s_char = playfair_matrix[(pos_of_b.first + 1)%5][pos_of_b.second];
    }
    //if the characters are not in same row or column
    else{
        f_char = playfair_matrix[pos_of_a.first][pos_of_b.second];
        s_char = playfair_matrix[pos_of_b.first][pos_of_a.second];
    }
    res.push_back(f_char);
    res.push_back(s_char);
    return res;
}

vector<string>divide_into_pairs(string plain_text){
    int count = 0;
    vector<string>res;
    string temp = "";
    bool store[256] = {0};
    for(int i = 0 ; i < plain_text.size(); i++){
        if(temp.size() == 2){
            if(temp[1] == temp[0]){
                temp.pop_back();
                res.push_back(temp + "x");
                temp = temp[0];
            }
            else{
                res.push_back(temp);
                temp = "";
            }
        }
        temp += plain_text[i];
    }
    if(temp.size() == 2){
        res.push_back(temp);
    }
    else if(temp.size() == 1){
        res.push_back(temp + "x");
    }
    return res;
}

string playfair_cipher(string plain_text,string key){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            playfair_matrix[i][j] = '-';
        }
    }
    int idx = 0 , i = 0 , j = 0;
    bool store[26] = {false};
    //fill the key in the matrix
    for(i = 0 ; i < 5 && idx < key.size(); i++){
        for(j = 0 ; j < 5 && idx < key.size(); j++){
            if(!store[key[idx]] && (key[idx] == 'i' || key[idx] == 'j')){
                char_to_indices['i'] = char_to_indices['j'] = make_pair(i,j);
                playfair_matrix[i][j] = key[idx];
                store['i' - 'a'] = true;
                store['j' - 'a'] = true;
            }
            else if(!store[key[idx] - 'a']){
                char_to_indices[key[idx]] = make_pair(i,j);
                playfair_matrix[i][j] = key[idx];
                store[key[idx] - 'a'] = true;
            }
            idx++;
        }
    }
    //fill remaining characters
    char ch = 'a';
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            if(playfair_matrix[i][j] == '-'){
                while(store[ch - 'a']){
                    ch++;
                }
                if(ch == 'i' || ch == 'j'){
                    char_to_indices['i'] = make_pair(i,j);
                    char_to_indices['j'] = make_pair(i,j);
                    store['i' - 'a'] = true;
                    store['j' - 'a'] = true;
                    playfair_matrix[i][j] = ch;
                }
                else{
                    char_to_indices[ch] = make_pair(i,j);
                    store[ch - 'a'] = true;
                    playfair_matrix[i][j] = ch;
                }
            }
        }
    }
    vector<string>pairs = divide_into_pairs(plain_text);
    string res = "";
    for(auto i : pairs){
        string req_string = get_cipher_string(i[0],i[1]);
        res += req_string;
    }
    return res;
}

int main(){
    string res = playfair_cipher("cheese","monarchy");
    cout << "PLAYFAIR MATRIX" << endl;
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            cout << playfair_matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "CIPHER TEXT :" << endl;
    cout << res << endl;
    return 0;
}
