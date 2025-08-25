🏧 ATM System Simulation in C
Welcome to the ATM System Simulation, a comprehensive console-based application built entirely in C. 
This project simulates the core functionalities of an Automated Teller Machine, managing customer data, multiple accounts, and ensuring all information is saved and loaded from local files.

✨ Key Features
🔐 Secure Customer Authentication: Robust login system requiring a unique account number and a 4-digit PIN.

🏦 Core Banking Operations:

💰 Check Balance: Instantly view your current account balance.

💸 Withdraw Funds: Withdraw cash with built-in checks for sufficient funds.

📥 Deposit Funds: Easily deposit money into your account.

👥 Advanced Account Management:

➕ Create New Accounts: Customers can open new bank accounts on the fly.

➖ Delete Accounts: Remove old accounts (as long as it's not the only one).

↔️ Switch Accounts: Seamlessly switch between multiple accounts.

🛡️ PIN Management: Change your PIN securely after verifying your current one.

💾 Data Persistence: All customer and account data is automatically saved to customers.dat and accounts.dat when you exit and reloaded on the next launch.

🕵️ Administrator Mode: A special login for an administrator to view a complete list of all customers and their associated accounts.

🚀 Getting Started
This project is built to be simple and has no external dependencies. Here’s how you can get it up and running.

1. Compilation
You will need a C compiler like gcc. Open your terminal, navigate to the project directory, and run the following command to compile all the source files:

Bash

gcc main.c system.c ui.c customer.c account.c utils.c -o atm.exe
2. Running the Program
Once compiled, you can launch the application with this simple command:

Bash

./atm.exe
(On Windows, you can just type atm.exe)

📋 How to Use
Customer Login
When prompted, enter any of your bank account numbers.

Enter your 4-digit PIN associated with that account.

You're in! You will be directed to the main menu to perform transactions.

Administrator Login
The system includes a hardcoded administrator account for system-wide oversight.

At the login screen, enter the account number: 1

Enter the administrator password: ece23044Project3

Enter the administrator PIN: 1111

You will now have access to the administrator menu.
