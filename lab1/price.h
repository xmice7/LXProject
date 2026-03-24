#ifndef PRICE_H
#define PRICE_H

#include <cstdio>

struct Price {
    int hryvnia;
    short int kop;
};

void add(Price& total, const Price& item);
void multiply(Price& item, int quantity);
void round(Price& cina);
void print(const Price& cina);
void Total(const char* my_file);

#endif 