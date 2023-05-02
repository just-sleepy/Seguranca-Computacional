#include <bits/stdc++.h>
using namespace std;

#include "treats.h"

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"
#define YLW "\e[93m"

int key_size(vector<string> data){
    int count=0;
    string text = clean_text(data);
    
    map<string, set<int>> trigramas;
    for(int i=0; i<text.size()-2; i++){
        string tri_a = text.substr(i, 3);
        for(int j=i+1; j<text.size()-2; j++){
            string tri_b = text.substr(j, 3);
            if(tri_a == tri_b){
                trigramas[tri_a].insert(j-i);
            }
        }
    }

    map<int, int> divs;
    for(auto trig: trigramas){
        set<int> distances = trig.second;
        for(auto d: distances){
            for(int i=2; i<=20; i++){
                if(d%i == 0){
                    divs[i]++;
                }
            }
        }
    }
    vector<pair<int,int>> greaters;
    int maior = 0;
    int save = 0;
    for(auto it: divs){
        greaters.push_back(it);
    }
    auto ordena = [&] (pair<int,int> a, pair<int,int> b) {
        return tie(a.second, a.first) > tie(b.second, b.first);
    };
    sort(greaters.begin(), greaters.end(), ordena);

    if(greaters.empty()){
        return 0;
    }
    cout<< YLW << "Possíveis tamanhos de chaves"<< NC <<endl;
    for(auto it: greaters){
        cout<< CYN << "Tamanho = "<<it.first<<" Ocorrências = "<<it.second << NC <<endl;
    }
    
    int key_size = greaters[0].first;
    cout<<YLW<<"O tamanho escolhido foi: "<< GRN <<greaters[0].first<<NC<<endl;
    if(key_size <= 3) cout<<RED<<"O tamanho da chave é considerado pequeno, recomendamos que escolha outro tamanho."<<NC<<endl;
    char opt;
    cout<< YLW << "Você deseja escolher o seu próprio tamanho de chave? (s/n)" << NC <<endl;
    cin>>opt;
    while(tolower(opt) != 's' and tolower(opt) != 'n'){
        cout<< RED << "Opção inválida." << NC << endl;
        cout<< YLW << "Você deseja escolher o seu próprio tamanho de chave? (s/n)" << NC <<endl;
        cin>>opt;
    }
    if(opt == 's'){
        cout<< YLW << "Escolha um tamanho entre 2 e 20" << NC <<endl;
        int tamanho; cin>>tamanho;
        while(tamanho < 2 or tamanho >20){
            cout<< RED << "Opção inválida." << NC << endl;
            cout<< YLW << "Escolha um tamanho entre 2 e 20" << NC <<endl;
            cin>>tamanho;
        }
        key_size = tamanho;
    }

    return key_size;
}

char get_letter(vector<double> probabilities, string lang){
    vector<double> en = {0.08167,0.01492,0.02782,0.04253,0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153,0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.0097, 0.02360, 0.00150, 0.01974, 0.00074};
    vector<double> pt = {0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0128, 0.0618, 0.0040, 0.0002, 0.0278, 0.0474, 0.0505,0.1073, 0.0252, 0.0120, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167, 0.0001, 0.0021, 0.0001, 0.0047};

    vector<double> prob = (lang == "en" ? en : pt);

    double menor = 0x3f3f3f3f;
    char c;
    // shiftando e pegando a menor diferenca
    for(int i=0; i<26; i++){
        double diff = 0;
        for(int j=0; j<26; j++){
            diff += abs(probabilities[(i+j)%26] - prob[j]);
        }
        if(diff < menor){
            menor = diff;
            c = i + 'a';
        }
    }
    return c;
}

string get_key(int key_size, string message, string language){
    string key = "";
    for(int i=0; i<key_size; i++){
        int total = 0;
        vector<int> freq(26);
        for(int j=i; j<message.size(); j+= key_size){
            freq[message[j]-'a']++;
            total++;
        }
        vector<double> probabilities;
        for(int c=0; c<26; c++){
            double x = (freq[c]/(double)total);
            probabilities.push_back(x);
        }
        key += get_letter(probabilities, language);
    }
    return key;
}


