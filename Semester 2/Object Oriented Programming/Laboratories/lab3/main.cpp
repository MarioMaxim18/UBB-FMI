#include "bank.h"

int main() {
    BankAccount b1("Maxim Mario", 1, 331);
    b1.deposit(100);
    b1.withdraw(50);
    std::cout << b1;
    return 0;
}
