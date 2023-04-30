#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define endl "\n"
#define all(x) x.begin(), x.end()
#define pb push_back

vector<vector<int>> vigenere(26);

string treat_string(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// ABCD
map<string, vector<int>> trigramas;

string concat(vector<string> vs){
    string aux = "";
    for(int i=0; i<vs.size(); i++){
        aux += vs[i];
        if(i != vs.size()-1) aux += " ";
    }
    return aux;
}

void add_trigram(vector<string> data){
    int count=0;

    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            if(j>=data[i].size()-2) continue;
            string s = data[i].substr(j, 3);
            bool flag = false;
            for(int k=0; k<s.size(); k++) if(s[k]<'a' or s[k]>'z') flag = true;
            if(flag or s.size()!=3) continue;
            trigramas[s].pb(count+j);
        }
        count += data[i].size()+1;
    }

    map<int, int> divs;
    map<int, bool> visited;
    for(auto trig: trigramas){
        vector<int> idx = trig.second;
        for(int i=0; i<idx.size(); i++){
            // primeira trigrama
            for(int j=i+1; j<idx.size(); j++){
                // outra trigrama
                int dist = abs(idx[i] - idx[j]);
                if(visited[dist]) continue;
                visited[dist];
                // Get divisors
                for(int i=2; i*i<= dist; i++){
                    if(dist%i==0){
                        divs[i]++;
                        int other = dist/i;
                        if(other != i) divs[other]++;
                    }
                }
                divs[dist]++;
            }
        }
    }
    int maior = 0;
    int save = 0;
    cout<<"FREQUENCIA "<<endl;
    for(auto it: divs){
        cout<<it.first<<" "<<it.second<<endl;
        if(it.second >= maior){
            maior = it.second;
            save = it.first;
        }
    }

    cout<<"TAMANHO QUE MAIS APARECE = "<<save<<endl;

    for(auto it: trigramas){
        cout<<it.first<<" ";
        for(int i=0; i<it.second.size(); i++){
            cout<<it.second[i]<<" ";
        }
        cout<<endl;
    }
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

void cifrador(string key, string message){
    key = equal_key(message, key);

    // cifra de acordo com a tabela de vigenere
    string msg = "";
    for(int i=0; i<key.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') msg += message[i];
        else msg += vigenere[key[i] - 'a'][message[i] - 'a'] + 'a';
    }
    cout << msg << endl;
}

void decifrador(string key, string message){
    key = equal_key(message, key);

    // decifra de acordo com a tabela de vigenere
    string msg = "";
    for(int i=0; i<message.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') msg += message[i];
        else msg += ((((message[i]-'a')-(key[i]-'a')) + 26)%26) + 'a';
    }
    cout << msg << endl;
}

int32_t main(){
    vector<string> dados = get_input("mensagem.txt");
    add_trigram(dados);
    //return 0;

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
        cout << "Digite uma chave para cifrar a mensagem, seguindo a Cifra de Vigenere: " << endl;
        string key; cin >> key;
        cout<<"Mensagem cifrada:"<<endl;
        cifrador(key, concat(dados));
    } else if(op == 2){
        op = 0;
        while(op != 1 and op != 2){
            cout << "Digite a opcao desejada:" << endl;
            cout << "1) Decifrar com chave" << endl;
            cout << "2) Decifrar sem chave" << endl;
            cin >> op;
            if(op != 1 and op != 2){cout << "Opcao invalida!" << endl;}
        }
        if(op == 1){
            cout << "Digite uma senha para decifrar a mensagem, seguindo a Cifra de Vigenere: " << endl;
            string key; cin >> key;
            cout<<"Mensagem decifrada:"<<endl;
            decifrador(key, concat(dados));
        }else{
            
            string key;
            cout<<"Mensagem decifrada:"<<endl;
            for(auto message: dados){
                decifrador(key, message);
            }
        }
    }

    return 0;
}
