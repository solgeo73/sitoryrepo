#include <iostream>
#include <string>

using namespace std;

class BankAccount {
protected:
    string accountNumber;
    string ownerName;
    double balance;

public:
    BankAccount(string accNum, string name, double initialBalance = 0.0)
        : accountNumber(accNum), ownerName(name), balance(initialBalance) {
        if (initialBalance < 0) {
            balance = 0.0;
            cout << "Предупреждение: начальный баланс не может быть отрицательным." << endl;
        }
    }

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Пополнено: " << amount << " руб." << endl;
        }
        else {
            cout << "Ошибка: сумма пополнения должна быть положительной." << endl;
        }
    }

    virtual bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Снято: " << amount << " руб." << endl;
            return true;
        }
        else if (amount > balance) {
            cout << "Ошибка: недостаточно средств на счете." << endl;
            return false;
        }
        else {
            cout << "Ошибка: сумма снятия должна быть положительной." << endl;
            return false;
        }
    }

    virtual void displayInfo() const {
        cout << "Информация о счете:" << endl;
        cout << "  Номер счета: " << accountNumber << endl;
        cout << "  Владелец: " << ownerName << endl;
        cout << "  Баланс: " << balance << " руб." << endl;
    }

    string getAccountNumber() const { return accountNumber; }
    string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string name, double initialBalance = 0.0, double rate = 1.5)
        : BankAccount(accNum, name, initialBalance), interestRate(rate) {
        if (rate < 0) {
            interestRate = 0.0;
            cout << "Предупреждение: процентная ставка не может быть отрицательной." << endl;
        }
    }

    void applyInterest() {
        double interest = balance * (interestRate / 100.0);
        balance += interest;
        cout << "Начислены проценты: " << interest << " руб. (ставка: " << interestRate << "%)" << endl;
    }

    void displayInfo() const override {
        BankAccount::displayInfo();
        cout << "  Тип счета: Сберегательный" << endl;
        cout << "  Процентная ставка: " << interestRate << "%" << endl;
    }

    double getInterestRate() const { return interestRate; }

    void setInterestRate(double rate) {
        if (rate >= 0) {
            interestRate = rate;
            cout << "Процентная ставка изменена на: " << rate << "%" << endl;
        }
        else {
            cout << "Ошибка: процентная ставка не может быть отрицательной." << endl;
        }
    }
};

int main() {

    cout << "Создание обычного банковского счета:" << endl;
    BankAccount regularAccount("37638792387327834787", "Иван Иванов", 4000.0);
    regularAccount.displayInfo();
    cout << endl;

    cout << "Операции с обычным счетом:" << endl;
    regularAccount.deposit(2000.0);
    regularAccount.withdraw(1500.0);
    regularAccount.withdraw(6000.0);
    regularAccount.displayInfo();
    cout << endl;

    cout << "Создание сберегательного счета:" << endl;
    SavingsAccount savingsAccount("67234763267326532674", "Пётр Петровов", 11000.0, 2.5);
    savingsAccount.displayInfo();
    cout << endl;

    cout << "Операции со сберегательным счетом:" << endl;
    savingsAccount.deposit(6000.0);
    savingsAccount.withdraw(2500.0);

    cout << "\nНачисление процентов на сберегательный счет:" << endl;
    savingsAccount.applyInterest();
    savingsAccount.displayInfo();

    return 0;
}
