#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define endl "\n"
#define all(x) x.begin(), x.end()
#define pb push_back

vector<vector<int>> vigenere(26);

void cifrador(string key, string message){
    // colocando a senha do mesmo tamanho da messagem
    string aux = key;
    while(key.size() < message.size()){
        key += aux;
    }
    while(key.size() > message.size()){
        key = key.substr(0, key.size()-1);
    }

    // cifra de acordo com a tabela de vigenere
    string msg = "";
    for(int i=0; i<key.size(); i++){
        msg += vigenere[key[i] - 'a'][message[i] - 'a'] + 'a';
    }
    cout << "Mensagem cifrada: " << endl << msg << endl;
}

void decifrador(string key, string message){
    
}

int32_t main(){

    // criando a cifra de vigenere
    int cnt = 0;
    for(int i=0; i<26; i++){
        for(int j=cnt; j<26; j++){
            vigenere[i].pb(j);
        }
        for(int j=0; j<cnt; j++){
            vigenere[i].pb(j);
        }
        cnt++;
    }
    
    int op = 0;
    while(op != 1 and op != 2){
        cout << "Digite a opcao desejada:" << endl;
        cout << "1) Cifrador" << endl;
        cout << "2) Decifrador" << endl;
        cin >> op;
        if(op != 1 and op != 2){cout << "Opcao invalida!" << endl;}
    }
    if(op == 1){
        cout << "Digite uma mensagem para ser cifrada: " << endl;
        string message; cin >> message;
        cout << "Digite uma senha para cifrar a mensagem, seguindo a Cifra de Vigenere: " << endl;
        string key; cin >> key;
        cifrador(key, message);
    } else if(op == 2){
        cout << "Digite uma mensagem para ser decifrada: " << endl;
        string message; cin >> message;
        cout << "Digite uma senha para decifrar a mensagem, seguindo a Cifra de Vigenere: " << endl;
        string key; cin >> key;
        decifrador(key, message);
    }

    return 0;
}