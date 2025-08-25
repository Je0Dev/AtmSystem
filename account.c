#include "atm.h"

Account* create_account_node(int account_number, double initial_balance, Customer *owner_customer) {
    Account* new_account = (Account*)malloc(sizeof(Account));
    if (new_account) {
        new_account->account_number = account_number;
        new_account->balance = initial_balance;
        new_account->owner = owner_customer;
        new_account->next = NULL;
    }
    return new_account;
}

void add_account_to_customer(Customer *customer_ptr, Account *new_account_node) {
    if (!customer_ptr || !new_account_node) return;

    if (customer_ptr->accounts_head == NULL) {
        customer_ptr->accounts_head = new_account_node;
        customer_ptr->accounts_last = new_account_node;
    } else {
        customer_ptr->accounts_last->next = new_account_node;
        customer_ptr->accounts_last = new_account_node;
    }
    customer_ptr->num_accounts++;
}

bool remove_account_from_customer(Customer *customer_ptr, int account_number_to_delete) {
    if (!customer_ptr || !customer_ptr->accounts_head) return false;

    Account *current = customer_ptr->accounts_head;
    Account *prev = NULL;

    while (current != NULL && current->account_number != account_number_to_delete) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return false; // Not found

    if (prev == NULL) { // Head is the one to be deleted
        customer_ptr->accounts_head = current->next;
    } else {
        prev->next = current->next;
    }

    if (current == customer_ptr->accounts_last) {
        customer_ptr->accounts_last = prev;
    }

    free(current);
    customer_ptr->num_accounts--;
    return true;
}

Account* find_account_by_number(const Customer *customer_ptr, int account_number_to_find) {
    if (!customer_ptr) return NULL;
    Account* current = customer_ptr->accounts_head;
    while (current != NULL) {
        if (current->account_number == account_number_to_find) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Account* find_account_globally(int account_number, Customer** found_customer_ptr) {
    if (found_customer_ptr) {
        *found_customer_ptr = NULL;
    }
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customers[i].is_active) {
            Account* acc = find_account_by_number(&customers[i], account_number);
            if (acc) {
                if (found_customer_ptr) {
                    *found_customer_ptr = &customers[i];
                }
                return acc;
            }
        }
    }
    return NULL;
}

void display_customer_accounts(const Customer *customer_ptr) {
    if (customer_ptr) {
        Account *acc = customer_ptr->accounts_head;
        while (acc) {
            printf("  Account Number: %d, Balance: %.2f\\n", acc->account_number, acc->balance);
            acc = acc->next;
        }
    }
}

int generate_unique_account_number() {
    int new_acc_num;
    do {
        new_acc_num = 1000 + rand() % 9000;
    } while (find_account_globally(new_acc_num, NULL) != NULL);
    return new_acc_num;
}

bool create_new_account_wrapper(Customer *customer) {
    if (customer->num_accounts >= MAX_ACCOUNTS_ALLOWED_PER_CUSTOMER) {
        printf("Maximum number of accounts reached.\\n");
        return false;
    }

    Account *new_account = create_account_node(generate_unique_account_number(), 0.0, customer);
    if (new_account) {
        add_account_to_customer(customer, new_account);
        printf("New account created successfully with account number: %d\\n", new_account->account_number);
        return true;
    }
    return false;
}

bool delete_account_wrapper(Customer *customer_ptr) {
    if (customer_ptr->num_accounts <= 1) {
        printf("You cannot delete your only account.\\n");
        return false;
    }

    int account_to_delete;
    if (!get_int_input(&account_to_delete, "Enter account number to delete: ")) {
        printf("Invalid input for account number.\\n");
        return false;
    }

    if (remove_account_from_customer(customer_ptr, account_to_delete)) {
        printf("Account deleted successfully.\\n");
        // If the deleted account was the current one, switch to another
        if (current_account->account_number == account_to_delete) {
            current_account = customer_ptr->accounts_head;
        }
        return true;
    } else {
        printf("Account not found or could not be deleted.\\n");
        return false;
    }
}

bool switch_account_wrapper(Customer *customer_ptr) {
    int target_account_number;
    if (!get_int_input(&target_account_number, "Enter account number to switch to: ")) {
        printf("Invalid input for account number.\\n");
        return false;
    }

    Account *target_account = find_account_by_number(customer_ptr, target_account_number);
    if (target_account) {
        current_account = target_account;
        printf("Switched to account %d.\\n", target_account->account_number);
        return true;
    } else {
        printf("Account not found.\\n");
        return false;
    }
}

void display_balance(const Account *account) {
    if (account) {
        printf("Current balance for account %d: %.2f\\n", account->account_number, account->balance);
    }
}

bool withdraw_money_wrapper(Account *account) {
    double amount;
    if (get_double_input(&amount, "Enter amount to withdraw: ")) {
        if (amount > 0 && amount <= account->balance) {
            account->balance -= amount;
            printf("Withdrawal successful. New balance: %.2f\\n", account->balance);
            return true;
        } else {
            printf("Invalid amount or insufficient funds.\\n");
            return false;
        }
    }
    return false;
}

bool deposit_money_wrapper(Account *account) {
    double amount;
    if (get_double_input(&amount, "Enter amount to deposit: ")) {
        if (amount > 0) {
            account->balance += amount;
            printf("Deposit successful. New balance: %.2f\\n", account->balance);
            return true;
        } else {
            printf("Invalid amount.\\n");
            return false;
        }
    }
    return false;
}

void free_customer_accounts(Customer *customer_ptr) {
    Account *current = customer_ptr->accounts_head;
    while (current != NULL) {
        Account *temp = current;
        current = current->next;
        free(temp);
    }
    customer_ptr->accounts_head = NULL;
    customer_ptr->accounts_last = NULL;
}