# BankingSystemC-
This is a basic implementation of a Banking System in C++ in which Data Structures are used.

**Data Structures:**
Customer Structure:

Represents a customer with essential details such as account number, name, PIN, balance, address, contact number, and email.
Manages a queue of transactions.
Transaction Structure:

Represents a transaction with a description (e.g., "Deposit" or "Withdraw") and an amount.
Bank Class:

Manages a list of customers, an unordered map for quick access to customer iterators using account numbers, a binary search tree (BST) for efficient account number searches, and a global transaction history queue.
**Bank Class Methods:**
Customer Management:
add_customer():

Takes user input to create a new customer.
Adds the customer to the list and updates the unordered map for quick access.
Inserts the customer into the binary search tree for efficient account number searches.
display_user(int accnum, int PIN):

Searches for a customer using the account number in the BST.
Displays customer details and transaction history if the PIN matches.
Transaction Operations:
deposit(int accnum, int PIN, double amount):

Searches for a customer using the account number in the BST.
Deposits the specified amount into the customer's balance and records the transaction.
withdraw(int accnum, int PIN, double amount):

Searches for a customer using the account number in the BST.
Withdraws the specified amount from the customer's balance if there are sufficient funds and records the transaction.
**Binary Search Tree (BST) Operations:**
BST Node Insertion:

When adding a new customer, the program inserts the customer into the BST based on their account number for efficient search operations.
BST Node Search (searchTreeNode):

Finds a customer in the BST using their account number.


**Main Function:**
Displays a menu for the user with options to add a customer, display customer details, deposit, withdraw, or exit.
The user interacts with the system by choosing options based on their needs.
The program uses the Bank class methods to perform the specified operations.
Conclusion:
The program provides a basic banking management system with customer information stored in a linked list, efficient retrieval using a hash table, and fast account number searches using a binary search tree. It also supports transaction history and basic deposit/withdraw functionalities.
