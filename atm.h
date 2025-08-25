#ifndef ATM_H
#define ATM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Macros and Constants
#define MAX_CUSTOMERS 5
#define ACTUAL_PIN_DIGITS 4
#define MAX_PIN_STORAGE_LENGTH (ACTUAL_PIN_DIGITS + 1)
#define MAX_NAME_LENGTH 50
#define ACCOUNT_NUMBER_DIGITS 4
#define MAX_ACCOUNTS_ALLOWED_PER_CUSTOMER 5
#define CUSTOMERS_FILE "customers.dat"
#define ACCOUNTS_FILE "accounts.dat"

#define HANDLE_CORRUPTED_FILE_AND_RESET(fp) \
    do { \
        fprintf(stderr, "Error reading file! Creating default data!\\n"); \
        if (fp) fclose(fp); \
        populate_default_data(); \
        return; \
    } while(0)

#define MACRO_TO_STRING_HELPER(x) #x
#define MACRO_TO_STRING(x) MACRO_TO_STRING_HELPER(x)

// Forward declaration
struct customer;

// Structures
typedef struct account {
    int account_number;
    double balance;
    struct customer *owner;
    struct account *next;
} Account;

typedef struct customer {
    char pin[MAX_PIN_STORAGE_LENGTH];
    char name[MAX_NAME_LENGTH];
    Account *accounts_head;
    Account *accounts_last;
    int num_accounts;
    bool is_active;
} Customer;

// Global Variables
extern Customer customers[MAX_CUSTOMERS];
extern Customer *current_customer;
extern Account *current_account;

// Function Prototypes

// system.c
void initialize_system();
void populate_default_data();
void cleanup_system();
void save_data_to_files();
void load_data_from_files();

// ui.c
bool login_screen();
void main_menu();
void admin_menu();
bool admin_switch_to_account();
void display_all_customers_accounts();
void clear_screen();

// customer.c
bool is_valid_pin_format(const char *pin_str);
bool is_valid_name_format(const char *name_str);
bool change_pin_wrapper(Customer *customer_ptr);

// account.c
Account* create_account_node(int account_number, double initial_balance, Customer *owner_customer);
void add_account_to_customer(Customer *customer_ptr, Account *new_account_node);
bool remove_account_from_customer(Customer *customer_ptr, int account_number_to_delete);
Account* find_account_by_number(const Customer *customer_ptr, int account_number_to_find);
Account* find_account_globally(int account_number, Customer** found_customer_ptr);
void display_customer_accounts(const Customer *customer_ptr);
int generate_unique_account_number();
bool create_new_account_wrapper(Customer *customer);
bool delete_account_wrapper(Customer *customer_ptr);
bool switch_account_wrapper(Customer *customer_ptr);
void display_balance(const Account *account);
bool withdraw_money_wrapper(Account *account);
bool deposit_money_wrapper(Account *account);
void free_customer_accounts(Customer *customer_ptr);

// utils.c
bool get_double_input(double *value, const char *prompt);
bool get_int_input(int *value, const char *prompt);
void clear_input_buffer();

#endif // ATM_H