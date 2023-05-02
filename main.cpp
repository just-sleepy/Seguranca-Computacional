#include <bits/stdc++.h>
#include "treats.h"
#include "attack.h"
using namespace std;
 
#define pb push_back
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"
#define YLW "\e[93m"

void cifrador(string key, string message){
    key = equal_key(message, key);
    // cifra de acordo com a tabela de vigenere
    string msg = "";
    for(int i=0; i<key.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') msg += message[i];
        else msg += (((message[i]-'a') + key[i]-'a') % 26) + 'a';
    }
    cout << GRN << msg << NC << endl;
}

void decifrador(string key, string message){
    key = equal_key(message, key);
    // decifra de acordo com a tabela de vigenere
    string msg = "";
    for(int i=0; i<message.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') msg += message[i];
        else msg += ((((message[i]-'a')-(key[i]-'a')) + 26) % 26) + 'a';
    }
    cout << GRN << msg << NC << endl;
}

int32_t main(){
    vector<string> dados = get_input("message.txt");
    
    int op = 0;
    while(op != 1 and op != 2){
        cout << YLW << "Digite a opcao desejada:" << NC << endl;
        cout << YLW << "1) Cifrador" << NC <<endl;
        cout << YLW << "2) Decifrador" << NC <<endl;
        cin >> op;
        if(op != 1 and op != 2){cout << RED << "Opcao invalida!" << NC << endl;}
    }
    if(op == 1){
        cout << YLW << "Digite uma chave para cifrar a mensagem, seguindo a Cifra de Vigenere: " << NC << endl;
        string key; cin >> key;
        cout<< YLW << "Mensagem cifrada:"<< NC <<endl;
        cifrador(key, concat(dados));
    } else if(op == 2){
        cout<< YLW << "Selecione uma língua: (en/pt)" << NC <<endl;
        string lang; cin>>lang;
        while(treat_string(lang) != "en" and treat_string(lang)!="pt"){
            cout<< RED << "Opção inválida." << NC << endl;
            cout<< YLW << "Selecione uma língua: (en/pt)"<< NC <<endl;
            cin>>lang;
        }
        lang = treat_string(lang);
        op = 0;
        while(op != 1 and op != 2){
            cout << YLW << "Digite a opcao desejada:" << NC << endl;
            cout << YLW << "1) Decifrar com chave" << NC << endl;
            cout << YLW << "2) Decifrar sem chave" << NC << endl;
            cin >> op;
            if(op != 1 and op != 2){cout << RED << "Opcao invalida!" << NC << endl;}
        }
        if(op == 1){
            cout << YLW << "Digite uma senha para decifrar a mensagem, seguindo a Cifra de Vigenere: " << NC << endl;
            string key; cin >> key;
            cout<< YLW << "Mensagem decifrada:" << NC <<endl;
            decifrador(key, concat(dados));
        }else if(op == 2){
            int lenght_key = key_size(dados);
            if(lenght_key == 0){
                cout<< RED << "O tamanho da amostra é muito pequeno." << NC <<endl;
                return 0;
            }
            cout<< YLW << "Tamanho da chave: "<< GRN << lenght_key<< NC <<endl;
            string key = get_key(lenght_key, clean_text(dados), lang);
            cout<<YLW<<"Chave estimada: "<< GRN <<key<<NC<<endl;
            cout<< YLW << "Mensagem decifrada:"<< NC <<endl;
            decifrador(key, concat(dados));
        }
    }

    return 0;
}
