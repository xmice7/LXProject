#define _CRT_SECURE_NO_WARNINGS
#include "price.h"
#include <cstdio>
#include <iostream>

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
    FILE* file = fopen(my_file, "r");
    if (file == NULL) {
        cout << "File opening error!" << endl;
        return;
    }

    Price total = {0, 0};
    Price item;
    int quantity;
    char name[50];

    while (true) {
    int result = fscanf(file, "%49s %d %hd %d", name, &item.hryvnia, &item.kop, &quantity);
    if (result == EOF) break;

    if (result != 4) {
        cout << "Input format error!" << endl;
        fclose(file);
        return;
    }

    int extra;
    while ((extra = fgetc(file)) != EOF) {
        if (extra == '\n') break;
        if (extra != ' ' && extra != '\t' && extra != '\r') {
            cout << "Input format error!" << endl;
            continue;
        }
    }

    if (item.hryvnia < 0 || item.kop < 0 || quantity < 0) {
        cout << "Negative values aren't allowed!" << endl;
        fclose(file);
        return;
    }
    if (item.kop > 99) {
        cout << "Kop error!" << endl;
        fclose(file);
        return;
    }

    multiply(item, quantity);
    add(total, item);
}
    fclose(file);
    
    cout << "Before rounding: "; print(total); cout << endl;

    round(total);
    cout << "Before payment: "; print(total);
    cout << endl;
}
