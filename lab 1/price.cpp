#define _CRT_SECURE_NO_WARNINGS
#include "price.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void add(Price& total, const Price& item) {
    total.hryvnia += item.hryvnia;
    total.kop += item.kop;
    total.hryvnia += total.kop / 100;
    total.kop %= 100;
}

void multiply(Price& item, int quantity) {
    item.hryvnia *= quantity;
    item.kop *= quantity;
    item.hryvnia += item.kop / 100;
    item.kop %= 100;
}

void round(Price& cina) {
    int ostatok = cina.kop % 10;

    if (ostatok < 5)
        cina.kop -= ostatok;
    else
        cina.kop += (10 - ostatok);
    
    cina.hryvnia += cina.kop / 100;
    cina.kop %= 100;
}


void print(const Price& cina) {
    printf("%d hrn %hd kop", cina.hryvnia, cina.kop);
}

void Total(const char* my_file) {
    ifstream file(my_file);
    if (!file) {
        cout << "File opening error!" << endl;
        return;
    }

    Price total = {0, 0};
    string line;
    int line_no = 0;

    while (getline(file, line)) {
        ++line_no;

        if (line.find_first_not_of(" \t\r") == string::npos)
            continue;

        istringstream in(line);
        string name;
        Price item = {0, 0};
        int quantity = 0;

        if (!(in >> name >> item.hryvnia >> item.kop >> quantity)) {
            cout << "Input format error at line " << line_no << "!" << endl;
            return;
        }

        string extra;
        if (in >> extra) {
            cout << "Input format error at line " << line_no << "!" << endl;
            return;
        }

        if (item.hryvnia < 0 || item.kop < 0 || quantity < 0) {
            cout << "Negative values aren't allowed at line " << line_no << "!" << endl;
            return;
        }

        if (item.kop > 99) {
            cout << "Kopiyki error at line " << line_no << " in input.txt!" << endl;
        }

        multiply(item, quantity);
        add(total, item);
    }
    
    cout << "Before rounding: "; print(total); cout << endl;

    round(total);
    cout << "Before payment: "; print(total);
    cout << endl;
}
