#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

struct Transaction {
    string description;
    double amount;

    Transaction(const string& desc, double amt) : description(desc), amount(amt) {}
};

struct Customer {
    int account_num;
    string name;
    int PIN;
    double balance;
    string address;
    string contact_num;
    string email;
    queue<Transaction> transactions;

    Customer(int acc_num, const string& nm, int pin, const string& addr, string contact, const string& mail)
            : account_num(acc_num), name(nm), PIN(pin), balance(0), address(addr), contact_num(contact), email(mail) {}

    void addTransaction(const string& desc, double amt) {
        transactions.push(Transaction(desc, amt));
    }

    void deposit(double amount) {
        balance += amount;
        addTransaction("Deposit", amount);
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            addTransaction("Withdraw", amount);
            cout << "Withdraw successful.\n";
        } else {
            cout << "Insufficient balance.\n";
        }
    }

    void displayTransactions() {
        cout << "Transaction History:\n";
        while (!transactions.empty()) {
            auto transaction = transactions.front();
            cout << "Description: " << transaction.description << ", Amount: " << transaction.amount << "\n";
            transactions.pop();
        }
    }
};

class Bank {
private:
    list<Customer> customers;
    unordered_map<int, list<Customer>::iterator> hashTable;
    int lastAccountNum;
    struct TreeNode {
        int account_num;
        list<Customer>::iterator customer_iterator;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int acc_num, list<Customer>::iterator iter) : account_num(acc_num), customer_iterator(iter), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

public:
    Bank() : root(nullptr), lastAccountNum(0) {}

    void add_customer() {
        int account_num = ++lastAccountNum;
        string name;
        int PIN;
        double balance;
        string address;
        string contact_num;
        string email;

        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter PIN code: ";
        cin >> PIN;
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter contact number: ";
        cin.ignore();
        getline(cin, contact_num);
        cout << "Enter email: ";
        cin.ignore();
        getline(cin, email);

        Customer temp(account_num, name, PIN, address, contact_num, email);
        customers.push_back(temp);
        hashTable[account_num] = --customers.end();
        insertTreeNode(account_num, --customers.end());
        cout << "Customer added successfully\n";
        cout << "Account number(please do not forget this): " << account_num << endl;
        cout << "\n________________________________________________________________________________________________\n";
    }

    void display_user(int accnum, int PIN) {
        auto iter = hashTable.find(accnum);
        if (iter != hashTable.end()) {
            auto customer = iter->second;
            if (customer->PIN == PIN) {
                cout << "Name: " << customer->name << endl;
                cout << "Account number: " << customer->account_num << endl;
                cout << "Balance: " << customer->balance << endl;
                cout << "Address: " << customer->address << endl;
                cout << "Contact number: " << customer->contact_num << endl;
                cout << "Email: " << customer->email << endl;
                customer->displayTransactions();
            } else {
                cout << "Invalid PIN.\n";
            }
        } else {
            cout << "Invalid account number.\n";
        }
    }

    void deposit(int accnum, int PIN, double amount) {
        TreeNode* foundNode = searchNode(root, accnum);
        if (foundNode != nullptr && foundNode->customer_iterator->PIN == PIN) {
            auto customer = foundNode->customer_iterator;
            customer->deposit(amount);
        } else {
            cout << "Invalid account number or PIN.\n";
        }
    }

    void withdraw(int accnum, int PIN, double amount) {
        TreeNode* foundNode = searchNode(root, accnum);
        if (foundNode != nullptr && foundNode->customer_iterator->PIN == PIN) {
            auto customer = foundNode->customer_iterator;
            customer->withdraw(amount);
        } else {
            cout << "Invalid account number or PIN.\n";
        }
    }

private:
    void insertTreeNode(int account_num, list<Customer>::iterator iter) {
        root = insertNode(root, account_num, iter);
    }

    TreeNode* insertNode(TreeNode* node, int account_num, list<Customer>::iterator iter) {
        if (node == nullptr) {
            return new TreeNode(account_num, iter);
        }

        if (account_num < node->account_num) {
            node->left = insertNode(node->left, account_num, iter);
        } else if (account_num > node->account_num) {
            node->right = insertNode(node->right, account_num, iter);
        }

        return node;
    }

    TreeNode* searchNode(TreeNode* node, int account_num) {
        if (node == nullptr || node->account_num == account_num) {
            return node;
        }

        if (account_num < node->account_num) {
            return searchNode(node->left, account_num);
        }

        return searchNode(node->right, account_num);
    }
};


int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n=================== BANK MANAGEMENT SYSTEM ===================\n";
        cout << "1. Add Customer\n";
        cout << "2. Display Customer\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.add_customer();
                break;
            case 2: {
                cout << "Enter account number: ";
                int accnum;
                cin >> accnum;
                cout << "Enter PIN: ";
                int PIN;
                cin >> PIN;
                bank.display_user(accnum, PIN);
                break;
            }
            case 3: {
                cout << "Enter account number: ";
                int accnum;
                cin >> accnum;
                cout << "Enter PIN: ";
                int PIN;
                cin >> PIN;
                cout << "Enter deposit amount: ";
                double amount;
                cin >> amount;
                bank.deposit(accnum, PIN, amount);
                break;
            }
            case 5:
                cout << "Exiting the program.\n";
                break;
            case 4:{
                cout << "Enter account number: ";
                int accnum;
                cin >> accnum;
                cout << "Enter PIN: ";
                int PIN;
                cin >> PIN;
                cout << "Enter withdraw amount: ";
                double amount;
                cin >> amount;
                bank.withdraw(accnum, PIN, amount);
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
