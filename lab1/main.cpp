// main.cpp – головний файл програми
// Лаб. 1. Знов структури. Файли.
// ООП (С++) – ЛНУ
//
// Вхід:  input.txt  (рядки: ціна_грн  ціна_коп  кількість)
// Вихід: загальна сума чеку та сума до оплати після заокруглення

#include <stdio.h>
#include "Price.h"

int main() {

    // -------------------------------------------------------
    // Відкриття файлу
    // -------------------------------------------------------
    // У MS Visual Studio (MSVC) рекомендується безпечна версія:
    //   FILE* pFile = nullptr;
    //   errno_t err = fopen_s(&pFile, "input.txt", "r");
    //   if (err != 0 || pFile == nullptr) { ... }
    //
    // Стандартна (C/C++, сумісна з GCC):
    FILE* pFile = fopen("input.txt", "r");

    if (pFile == nullptr) {
        printf("Помилка: не вдалося відкрити файл input.txt\n");
        return 1;
    }

    // -------------------------------------------------------
    // Зчитування даних та обчислення суми
    // -------------------------------------------------------
    Price total;
    total.grn = 0;
    total.kop = 0;

    int priceGrn;
    int priceKop;
    int qty;

    int lineNum = 0;

    printf("=== Деталі чеку ===\n");

    // Читаємо файл: кожний рядок містить 3 числа (грн коп кількість)
    // У MSVC можна використати безпечну версію:
    //   while (fscanf_s(pFile, "%d %d %d", &priceGrn, &priceKop, &qty) == 3)
    while (fscanf(pFile, "%d %d %d", &priceGrn, &priceKop, &qty) == 3) {
        lineNum++;

        Price item;
        item.grn = priceGrn;
        item.kop = (short)priceKop;

        Price lineTotal = item.multiply(qty);

        printf("Позиція %d: ", lineNum);
        item.print();
        printf(" x %d шт = ", qty);
        lineTotal.print();
        printf("\n");

        total = total.add(lineTotal);
    }

    fclose(pFile);

    if (lineNum == 0) {
        printf("Файл порожній або має неправильний формат.\n");
        return 1;
    }

    // -------------------------------------------------------
    // Виведення результату
    // -------------------------------------------------------
    printf("\n=== Підсумок ===\n");

    printf("Загальна сума:    ");
    total.print();
    printf("\n");

    Price rounded = total.round();
    printf("Сума до оплати:   ");
    rounded.print();
    printf("\n");

    return 0;
}
