//
// Created by 陆逸凡 on 2023/2/22.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_set>

using namespace std;

unordered_set<int> table;

int genRandomInt(){
    return rand() * rand() % RAND_MAX;
}

int main(){
    std::srand(time(0));
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i){
        int tmp = genRandomInt();
        while(table.find(tmp) != table.end()){
            tmp = genRandomInt();
        }
        table.insert(tmp);
    }
    for(auto it : table) {
        cout << it << endl;
    }
}