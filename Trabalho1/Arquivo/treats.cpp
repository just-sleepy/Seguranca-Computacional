#include <bits/stdc++.h>
using namespace std;

// colocando a senha do mesmo tamanho da messagem
string equal_key(string message, string key){
    string aux = "";
    int j = 0;
    for(int i=0; i<message.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') aux += message[i];
        else{
            aux += key[j];
            j++;
            j %= key.size();
        }
    }
    return aux;
}

string treat_string(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

vector<string> get_input(string string_file){
    vector<string> data;
    ifstream file;
    file.open(string_file, ios::in);
    if (file.is_open()){
        string line;
        string space = " ";
        while(getline(file, line)){
            size_t pos = 0;
            while ((pos = line.find(space)) != string::npos) {
                data.push_back(treat_string(line.substr(0, pos)));
                line.erase(0, pos + space.length());
            }
            data.push_back(treat_string(line));
        }
        file.close();
    }
    return data;
}

string concat(vector<string> vs){
    string aux = "";
    for(int i=0; i<vs.size(); i++){
        aux += vs[i];
        if(i != vs.size()-1) aux += " ";
    }
    return aux;
}

string clean_text(vector<string> vs){
    string aux = "";
    for(int i=0; i<vs.size(); i++){
        for(auto c : vs[i]){
            if(c < 'a' or c >'z') continue;
            aux += c;
        }
    }
    return aux;
}