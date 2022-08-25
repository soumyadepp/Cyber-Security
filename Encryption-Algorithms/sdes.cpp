#include <bits/stdc++.h>
using namespace std;

string permute(string s,vector<int>order){
    string res = "";
    for(auto i : order){
        res.push_back(s[i - 1]);
    }
    return res;
}

string xorString(string s1,string s2){
    string res = "";
    for(int i = 0 ; i < s1.size(); i++){
        res += s1[i] != s2[i] ? "1" : "0";
    }
    return res;
}

class KeyGenerator{
    vector<int>p10,p8;
    string keyString;
    public:
    void setKeyString(string keyString){
        this -> keyString = keyString;
    }
    void setP10(vector<int>p10){
        this -> p10 = p10;
    }
    void setP8(vector<int>p8){
        this -> p8 = p8;
    }
    pair<string,string> generate(){
        string firstHalf = keyString.substr(0,5);
        string secondHalf = keyString.substr(5);
        string ls1 = firstHalf.substr(1);
        ls1.push_back(firstHalf[0]);
        string ls2 = secondHalf.substr(1);
        ls2.push_back(secondHalf[0]);
        string k1 = permute(ls1 + ls2,p8);
        ls1 = ls1.substr(3) + ls1.substr(0,3);
        ls2 = ls2.substr(3) + ls2.substr(0,3);
        string k2 = permute(ls1 + ls2,p8);
        return make_pair(k1,k2);
    }
};

class SDESAlgorithm{
    vector<int>p10,p8,p4,ip,ip_inv,ep;
    vector<vector<int>>s0,s1;
    string messageString;
    KeyGenerator keygen;
    pair<string,string>keys;
    unordered_map<string,int>num_map;
    unordered_map<int,string>bin_map;
    public:
    SDESAlgorithm(string plainText,string keyString){
        if(plainText.size() != 8){
            cout << "Invalid plain text size" << endl;
            exit(-1);
        }
        if(keyString.size() != 10){
            cout << "Invalid key size" << endl;
            exit(-1);
        }
        this -> messageString = plainText;
        keygen.setKeyString(keyString);
        keygen.setP10(p10);
        keygen.setP8(p8);
        this -> keys = keygen.generate();
        num_map["00"] = 0; bin_map[0] = "00";
        num_map["01"] = 1; bin_map[1] = "01";
        num_map["10"] = 2; bin_map[2] = "10";
        num_map["11"] = 3; bin_map[3] = "11";
    }
    void setP10(vector<int>p10){
        this -> p10 = p10;
    }
    void setP8(vector<int>p8){
        this -> p8 = p8;
    }
    void setP4(vector<int>p4){
        this -> p4 = p4;
    }
    void setIp(vector<int>ip){
        this -> ip = ip;
    }
    void setIpInverse(vector<int>ip_inv){
        this -> ip_inv = ip_inv;
    }
    void setEp(vector<int>ep){
        this -> ep = ep;
    }
    void setS0S1(vector<vector<int>>s0,vector<vector<int>>s1){
        this -> s0 = s0;
        this -> s1 = s1;
    }
    string expand(string pt){
        if(ep.size() != 8){
            cout << "Invalid EP" << endl;
            exit(-1);
        }
        string res = permute(pt,ep);
        return res;
    }
    string compress(string expanded){
        if(s0.size() != 4 || s1.size() != 4){
            cout << "Invalid s0 or s1" << endl;
            exit(-1);
        }
        string firstHalf = expanded.substr(0,4);
        string secondHalf = expanded.substr(4);
        string idx1 = "",idx2 = "";
        idx1.push_back(firstHalf[0]);idx1.push_back(firstHalf[3]);
        idx2.push_back(firstHalf[1]); idx2.push_back(firstHalf[2]);
        int i = num_map[idx1] , j = num_map[idx2];
        firstHalf = bin_map[s0[i][j]];
        idx1 = "",idx2 = "";
        idx1.push_back(secondHalf[0]);idx1.push_back(secondHalf[3]);
        idx2.push_back(secondHalf[1]);idx2.push_back(secondHalf[2]);
        i = num_map[idx1] , j = num_map[idx2];
        secondHalf = bin_map[s1[i][j]];
        string res = firstHalf + secondHalf;
        res = permute(res,p4);
        return res;
    }
    string encrypt(){
        if(ip.size() != 8) {
            cout << "Invalid IP" << endl;
            exit(-1);
        }
        string ipString = permute(messageString,ip);
        string firstHalf = ipString.substr(0,4);
        string secondHalf = ipString.substr(4);
        string k1 = keys.first , k2 = keys.second;
        string res1 = expand(secondHalf);
        res1 = compress(res1);
        firstHalf = xorString(firstHalf,res1);
        swap(firstHalf,secondHalf);
        string res2 = expand(secondHalf);
        res2 = compress(res2);
        firstHalf = xorString(firstHalf,res2);
        string k = firstHalf + secondHalf;
        
        if(ip_inv.size() != 8){
            cout << "Invalid IP Inverse"<<endl;
            exit(-1);
        }
        return permute(k,ip_inv);
    }
};

int main(){
    string plain_text = "11010011" , keyString = "1001110101";
    vector<int>p10 = {3,5,2,7,4,10,1,9,8,6};
    vector<int>p8 = {6,3,7,4,8,5,10,9};
    vector<int>p4 = {2,4,3,1};
    vector<int>ip = {2,6,3,1,4,8,5,7};
    vector<int>ip_inv = {4,1,3,5,7,2,8,6};
    vector<int>ep = {4,1,2,3,2,3,4,1};
    vector<vector<int>>s0 = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
    vector<vector<int>>s1 = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
    SDESAlgorithm solve(plain_text,keyString);
    solve.setP10(p10);
    solve.setP8(p8);
    solve.setP4(p4);
    solve.setIp(ip);
    solve.setIpInverse(ip_inv);
    solve.setEp(ep);
    solve.setS0S1(s0,s1);
    string cipher_text = solve.encrypt();
    cout << "Cipher Text : " << cipher_text << endl;
    return 0;
}
