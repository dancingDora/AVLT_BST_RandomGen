//
// Created by 陆逸凡 on 2023/2/22.
//
#include <iostream>
#include <time.h>
#include <unordered_set>
#include <fstream>
using namespace std;

unordered_set<int> table;
unordered_set<int> del;

int genRandomInt() {
    return rand() % RAND_MAX;
}
int genRandomDel(int n) {
    return rand() % n;
}
int main() {
    ifstream fin("dataGen1");
    ofstream fout("test1.txt");
    std::srand(time(0));
    int n;
    fin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        int tmp = genRandomInt();
        while (table.find(tmp) != table.end())
            tmp = genRandomInt();
        table.insert(tmp);
        a[i] = tmp;
    }

    fout << 'i' << endl;

    for (auto it: table) {
        fout << it << endl;
    }

    fout << 'r' << endl;

    for(int i = 0; i < n/10; ++i) {
        int tmp = genRandomDel(n);
        while(del.find(tmp) != del.end())
            tmp = genRandomDel(n);
        del.insert(tmp);
        fout << a[tmp] << endl;
    }
//the second time
    fout << 'i' << endl;

    for (auto it: table) {
        fout << it << endl;
    }

    fout << 'r' << endl;

    for(int i = 0; i < n/10; ++i) {
        int tmp = genRandomDel(n);
        while(del.find(tmp) != del.end())
            tmp = genRandomDel(n);
        del.insert(tmp);
        fout << a[tmp] << endl;
    }


}