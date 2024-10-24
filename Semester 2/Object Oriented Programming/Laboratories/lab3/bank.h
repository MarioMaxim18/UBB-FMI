#include <iostream>
#include <cmath>

class BankAccount {
private:
    std::string accountHolderName;
    int accountNumber;
    int accountBalance;

public:
    // Constructor
    BankAccount(std::string name, int number, int balance): accountHolderName(name), accountNumber(number), accountBalance(balance) {}

    // Getters
    std::string getAccountHolderName() const { return accountHolderName; }
    int getAccountNumber() const { return accountNumber; }
    int getBalance() const { return accountBalance; }

    // Setters
    void setAccountHolderName(std::string name);
    void setAccountNumber(int number);
    void setBalance(double newBalance);

    // Methods for depositing and withdrawing funds
    void deposit(double amount) { accountBalance += amount; }
    void withdraw(double amount) { accountBalance -= amount; }

    // Overload the stream insertion operator to display account details
    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
        os << "Account Holder Name: " << account.getAccountHolderName() << "\n";
        os << "Account Number: " << account.getAccountNumber() << "\n";
        os << "Balance: " << account.getBalance() << "\n";
        return os;
    }
};