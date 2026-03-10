#include "Price.h"
#include <stdio.h>

// Додавання двох цін
Price Price::add(Price other) const {
    Price result;
    int totalKop = (int)kop + (int)other.kop;
    result.grn = grn + other.grn + totalKop / 100;
    result.kop = (short)(totalKop % 100);
    return result;
}

// Множення ціни на позитивне ціле число
Price Price::multiply(int n) const {
    Price result;
    int totalKop = (int)kop * n;
    result.grn = grn * n + totalKop / 100;
    result.kop = (short)(totalKop % 100);
    return result;
}

// Заокруглення копійок до найближчих 10 копійок
// Правило: остача від ділення на 10
//   1..4  -> округлити вниз (відняти остачу)
//   5..9  -> округлити вгору (додати 10 - остача)
Price Price::round() const {
    Price result;
    result.grn = grn;
    result.kop = kop;

    int ones = (int)kop % 10;  // цифра одиниць копійок

    if (ones >= 1 && ones <= 4) {
        // Округлюємо вниз
        result.kop = (short)(kop - ones);
    } else if (ones >= 5 && ones <= 9) {
        // Округлюємо вгору
        int newKop = (int)kop + (10 - ones);
        result.grn = grn + newKop / 100;
        result.kop = (short)(newKop % 100);
    }
    // ones == 0: вже кратне 10, нічого не змінюємо

    return result;
}

// Виведення ціни у форматі "X грн Y коп"
void Price::print() const {
    printf("%d грн %02d коп", grn, (int)kop);
}
