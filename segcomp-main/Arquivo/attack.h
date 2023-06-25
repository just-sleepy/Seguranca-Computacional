#include <bits/stdc++.h>
using namespace std;

#ifndef ATTACK_H  
#define ATTACK_H 

int key_size(vector<string> data);

char get_letter(vector<double> probabilities, string lang);

string get_key(int key_size, string message, string language);

#endif