#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Expense {
    string category;
    double amount;
    string description;
};
double totalIncome = 0.0;
vector<Expense> expenses;
void addIncome();
void addExpense();
void viewExpenses();
void viewSummary();
void saveToFile();
void loadFromFile();
int main() {
    loadFromFile(); 
    int choice;
    do {
        cout << "\n--- Expense Tracker ---\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Expenses\n";
        cout << "4. View Summary\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addIncome();
            break;
        case 2:
            addExpense();
            break;
        case 3:
            viewExpenses();
            break;
        case 4:
            viewSummary();
            break;
        case 5:
            saveToFile();
            cout << "Data saved. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
    return 0;
}
void addIncome() {
    cout << "Enter your income: ";
    cin >> totalIncome;
    cout << "Income added successfully.\n";
}
void addExpense() {
    Expense exp;
    cout << "Enter category (Food, Rent, Entertainment, Misc): ";
    cin >> exp.category;
    cout << "Enter amount: ";
    cin >> exp.amount;
    cout << "Enter description: ";
    cin.ignore();
    getline(cin, exp.description);

    expenses.push_back(exp);
    cout << "Expense added successfully.\n";
}
void viewExpenses() {
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }
    cout << "\n--- Expenses ---\n";
    for (const auto& exp : expenses) {
        cout << "Category: " << exp.category 
             << ", Amount: " << exp.amount 
             << ", Description: " << exp.description << "\n";
    }
}
void viewSummary() {
    double totalExpenses = 0.0;
    for (const auto& exp : expenses) {
        totalExpenses += exp.amount;
    }
    cout << "\n--- Summary ---\n";
    cout << "Total Income: " << totalIncome << "\n";
    cout << "Total Expenses: " << totalExpenses << "\n";
    cout << "Remaining Balance: " << (totalIncome - totalExpenses) << "\n";
}
void saveToFile() {
    ofstream file("expenses.txt");
    if (!file) {
        cout << "Error saving data.\n";
        return;
    }
    file << totalIncome << "\n";
    for (const auto& exp : expenses) {
        file << exp.category << " " << exp.amount << " " << exp.description << "\n";
    }
    file.close();
    cout << "Data saved successfully.\n";
}
void loadFromFile() {
    ifstream file("expenses.txt");
    if (!file) {
        return; 
    }
    file >> totalIncome;
    Expense exp;
    while (file >> exp.category >> exp.amount) {
        file.ignore();
        getline(file, exp.description);
        expenses.push_back(exp);
    }
    file.close();
    cout << "Data loaded successfully.\n";
}