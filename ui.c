#include "atm.h"

// Global admin variables
Customer admin_customer;
Account admin_account;

bool login_screen() {
    int input_account_number_int;
    char input_pin_str[MAX_PIN_STORAGE_LENGTH];

    printf("\\n--- LOGIN SCREEN ---\\n");

    if (!get_int_input(&input_account_number_int, "Enter your account number: ")) {
        printf("Invalid account number!. It must be an integer!\\n");
        return false;
    }

    if (input_account_number_int == 1) {
        char admin_password[50];
        char admin_pin[MAX_PIN_STORAGE_LENGTH];
        printf("Enter the ATM administrator password: ");
        #define ADMIN_PASSWORD_MAXLEN 49
        if (scanf("%" MACRO_TO_STRING(ADMIN_PASSWORD_MAXLEN) "s", admin_password) != 1) {
            clear_input_buffer();
            printf("Error reading administrator password!\\n");
            return false;
        }
        #undef ADMIN_PASSWORD_MAXLEN
        clear_input_buffer();

        if (strcmp(admin_password, "ece23044Project3") == 0) {
            printf("Administrator password confirmed!\\n");
            printf("Enter administrator PIN (%d digits): ", ACTUAL_PIN_DIGITS);
            if (scanf("%" MACRO_TO_STRING(ACTUAL_PIN_DIGITS) "s", admin_pin) != 1) {
                clear_input_buffer();
                printf("Error reading administrator PIN!\\n");
                return false;
            }
            clear_input_buffer();

            if (is_valid_pin_format(admin_pin) && strcmp(admin_pin, "1111") == 0) {
                printf("\\nSuccessful login as administrator! Welcome!\\n");
                strcpy(admin_customer.name, "Administrator");
                strcpy(admin_customer.pin, "1111");
                admin_customer.accounts_head = &admin_account;
                admin_customer.accounts_last = &admin_account;
                admin_customer.num_accounts = 1;
                admin_customer.is_active = true;

                admin_account.account_number = 1;
                admin_account.balance = 1000.0;
                admin_account.owner = &admin_customer;

                current_customer = &admin_customer;
                current_account = &admin_account;
                admin_menu();
                return true;
            } else {
                printf("Wrong administrator PIN!\\n");
                return false;
            }
        } else {
            printf("Wrong administrator password!\\n");
            return false;
        }
    }

    Customer *found_customer = NULL;
    Account *found_account = find_account_globally(input_account_number_int, &found_customer);

    if (found_account && found_customer) {
        for (int attempts = 3; attempts > 0; --attempts) {
            printf("Enter your PIN (%d digits): ", ACTUAL_PIN_DIGITS);
            if (scanf("%" MACRO_TO_STRING(ACTUAL_PIN_DIGITS) "s", input_pin_str) != 1) {
                clear_input_buffer();
                printf("Error reading PIN!\\n");
                return false;
            }
            clear_input_buffer();

            if (strcmp(input_pin_str, found_customer->pin) == 0) {
                current_customer = found_customer;
                current_account = found_account;
                printf("\\nWelcome, %s!\\n", current_customer->name);
                return true;
            } else {
                printf("Wrong PIN! You have %d attempts left.\\n", attempts - 1);
            }
        }
    } else {
        printf("Account not found!\\n");
    }

    return false;
}

void main_menu() {
    int choice;
    do {
        printf("\\n--- Main Menu ---\\n");
        printf("1. Display Balance\\n");
        printf("2. Withdraw Money\\n");
        printf("3. Deposit Money\\n");
        printf("4. Change PIN\\n");
        printf("5. Create New Account\\n");
        printf("6. Delete Account\\n");
        printf("7. Switch Account\\n");
        printf("8. Logout\\n");
        printf("Your choice: ");

        if (!get_int_input(&choice, "")) {
            printf("Invalid input! Please enter a number.\\n");
            continue;
        }

        switch (choice) {
            case 1: display_balance(current_account); break;
            case 2: withdraw_money_wrapper(current_account); break;
            case 3: deposit_money_wrapper(current_account); break;
            case 4: change_pin_wrapper(current_customer); break;
            case 5: create_new_account_wrapper(current_customer); break;
            case 6: delete_account_wrapper(current_customer); break;
            case 7: switch_account_wrapper(current_customer); break;
            case 8: printf("Logging out...\\n"); return;
            default: printf("Invalid choice. Please try again.\\n");
        }
    } while (choice != 8);
}


void admin_menu() {
    int choice;
    do {
        printf("\\n--- Admin Menu ---\\n");
        printf("1. Display All Customers and Accounts\\n");
        printf("2. Switch to a Specific Account\\n");
        printf("3. Logout\\n");
        printf("Your choice: ");

        if (!get_int_input(&choice, "")) {
            printf("Invalid input! Please enter a number.\\n");
            continue;
        }

        switch (choice) {
            case 1: display_all_customers_accounts(); break;
            case 2: admin_switch_to_account(); break;
            case 3: printf("Logging out...\\n"); return;
            default: printf("Invalid choice. Please try again.\\n");
        }
    } while (choice != 3);
}

bool admin_switch_to_account() {
    int target_account_number;
    if (!get_int_input(&target_account_number, "Enter account number to switch to: ")) {
        printf("Invalid input for account number.\\n");
        return false;
    }

    Customer *target_customer = NULL;
    Account *target_account = find_account_globally(target_account_number, &target_customer);

    if (target_account && target_customer) {
        current_customer = target_customer;
        current_account = target_account;
        printf("Successfully switched to account %d, owned by %s.\\n", target_account->account_number, target_customer->name);
        main_menu(); // Enter the main menu for the switched account
        return true;
    } else {
        printf("Account not found.\\n");
        return false;
    }
}

void display_all_customers_accounts() {
    printf("\\n--- All Customers and Accounts ---\\n");
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customers[i].is_active) {
            printf("Customer: %s (PIN: %s)\\n", customers[i].name, customers[i].pin);
            display_customer_accounts(&customers[i]);
            printf("--------------------\\n");
        }
    }
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}