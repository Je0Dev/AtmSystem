ATM System Simulation in C
This project is a console-based application that simulates the basic functionalities of an Automated Teller Machine (ATM). It is written entirely in C and contained within a single source file. The system manages customer data, supports multiple bank accounts per customer, and persists all information to local data files.

🌟 Features
Customer Authentication: Secure login for customers using an account number and a 4-digit PIN.

Core Banking Operations:

Check account balance.

Withdraw funds, with checks for sufficient balance.

Deposit funds.

Account Management:

Customers can create new bank accounts.

Customers can delete existing accounts (as long as it's not their only one).

Support for switching between multiple accounts.

PIN Management: Ability for users to change their PIN after verifying their old one.

Data Persistence: All customer and account data is saved to customers.dat and accounts.dat upon exiting the program and loaded back upon startup.

Administrator Mode: A special login for an administrator to view a list of all customers and their associated accounts.

🚀 How to Compile and Run
This project is self-contained in a single C file and has no external dependencies, making it easy to compile.

1. Compilation
You will need a C compiler like gcc. Open your terminal or command prompt, navigate to the directory containing the source file, and run the following command:

Bash

# Assuming you have renamed the file to atm.c
gcc main.c system.c ui.c customer.c account.c utils.c -o main.exe 
2. Running the Program
Once compiled, you can run the application with this command:

Bash

./main.exe
(On Windows, you can just type main.exe)

📋 How to Use
Customer Login
When prompted, enter any of your bank account numbers.

Enter your 4-digit PIN associated with that account.

Upon successful login, you will be presented with the main menu to perform transactions.

Administrator Login
The program has a hardcoded administrator account for viewing all system data.

At the login screen, enter the account number: 1

When asked for the administrator password, enter: ece23044Project3

When asked for the administrator PIN, enter: 1111

You will then access the administrator menu.
