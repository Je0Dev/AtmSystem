#include "atm.h"

// Define global variables
Customer customers[MAX_CUSTOMERS];
Customer *current_customer = NULL;
Account *current_account = NULL;

void initialize_system() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        customers[i].is_active = false;
        customers[i].accounts_head = NULL;
        customers[i].accounts_last = NULL;
        customers[i].num_accounts = 0;
        strcpy(customers[i].name, "");
        strcpy(customers[i].pin, "");
    }
    current_customer = NULL;
    current_account = NULL;
}

void populate_default_data() {
    printf("\\nCreating default customer and account data...\\n");
    strcpy(customers[0].name, "Giannis Papadogiannis");
    strcpy(customers[0].pin, "1235");
    customers[0].is_active = true;
    customers[0].num_accounts = 0;

    strcpy(customers[1].name, "Eirini Famfarotou");
    strcpy(customers[1].pin, "5228");
    customers[1].is_active = true;
    customers[1].num_accounts = 0;

    strcpy(customers[2].name, "Nikos Kostakis");
    strcpy(customers[2].pin, "1661");
    customers[2].is_active = true;
    customers[2].num_accounts = 0;

    strcpy(customers[3].name, "Eleni Michailidou");
    strcpy(customers[3].pin, "9229");
    customers[3].is_active = true;
    customers[3].num_accounts = 0;

    strcpy(customers[4].name, "Kostas Antoniou");
    strcpy(customers[4].pin, "3333");
    customers[4].is_active = true;
    customers[4].num_accounts = 0;

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customers[i].is_active) {
            Account *initial_account = create_account_node(
                generate_unique_account_number(),
                1000.0 + (i * 250),
                &customers[i]
            );
            if (initial_account) {
                add_account_to_customer(&customers[i], initial_account);
            } else {
                fprintf(stderr, "Failed to create initial account for %s.\\n", customers[i].name);
            }
        }
    }
    printf("Default data creation is complete!\\n");
}

void cleanup_system() {
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        free_customer_accounts(&customers[i]);
        customers[i].is_active = false;
        customers[i].num_accounts = 0;
        strcpy(customers[i].name, "");
        strcpy(customers[i].pin, "");
    }
    current_customer = NULL;
    current_account = NULL;
}

void save_data_to_files() {
    FILE *fp_customers = fopen(CUSTOMERS_FILE, "wb");
    if (!fp_customers) {
        perror("Error opening customers file for writing");
        return;
    }

    FILE *fp_accounts = fopen(ACCOUNTS_FILE, "wb");
    if (!fp_accounts) {
        perror("Error opening accounts file for writing");
        fclose(fp_customers);
        return;
    }

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customers[i].is_active) {
            // Save customer data
            fprintf(fp_customers, "%d,%s,%s\\n", i, customers[i].name, customers[i].pin);

            // Save account data
            Account *current_acc = customers[i].accounts_head;
            while (current_acc) {
                fprintf(fp_accounts, "%d,%d,%.2f\\n", current_acc->account_number, i, current_acc->balance);
                current_acc = current_acc->next;
            }
        }
    }

    fclose(fp_customers);
    fclose(fp_accounts);
}

void load_data_from_files() {
    FILE *fp_customers_file = fopen(CUSTOMERS_FILE, "rb");
    int loaded_customers_count = 0;

    if (!fp_customers_file) {
        printf("Customer data file not found. Creating default data.\\n");
        populate_default_data();
        return;
    }

    // Clear existing data before loading
    cleanup_system();
    initialize_system();

    int cust_idx_from_file;
    char name_from_file[MAX_NAME_LENGTH];
    char pin_from_file[MAX_PIN_STORAGE_LENGTH];

    while (fscanf(fp_customers_file, "%d,%[^,],%s\\n", &cust_idx_from_file, name_from_file, pin_from_file) == 3) {
        if (cust_idx_from_file >= 0 && cust_idx_from_file < MAX_CUSTOMERS) {
            if (!customers[cust_idx_from_file].is_active) {
                strcpy(customers[cust_idx_from_file].name, name_from_file);
                strcpy(customers[cust_idx_from_file].pin, pin_from_file);
                customers[cust_idx_from_file].is_active = true;
                loaded_customers_count++;
            }
        }
    }
    fclose(fp_customers_file);

    FILE *fp_accounts_file = fopen(ACCOUNTS_FILE, "rb");
    int loaded_accounts_count = 0;

    if (fp_accounts_file) {
        int acc_num_from_file, cust_idx_from_file_acc;
        double balance_from_file;
        int invalid_accounts_count = 0;

        while (fscanf(fp_accounts_file, "%d,%d,%lf\\n", &acc_num_from_file, &cust_idx_from_file_acc, &balance_from_file) == 3) {
            if (cust_idx_from_file_acc >= 0 && cust_idx_from_file_acc < MAX_CUSTOMERS && customers[cust_idx_from_file_acc].is_active) {
                if (find_account_globally(acc_num_from_file, NULL) == NULL) {
                    Account *new_acc = create_account_node(acc_num_from_file, balance_from_file, &customers[cust_idx_from_file_acc]);
                    if (new_acc) {
                        add_account_to_customer(&customers[cust_idx_from_file_acc], new_acc);
                        loaded_accounts_count++;
                    }
                }
            } else {
                invalid_accounts_count++;
            }
        }
        fclose(fp_accounts_file);

        if (invalid_accounts_count > 0) {
            printf("Warning: %d accounts were ignored due to invalid data.\\n", invalid_accounts_count);
        }
    }

    printf("Data loading complete!\\n");
    printf("Loaded:\\n");
    printf("- %d active customers\\n", loaded_customers_count);
    printf("- %d accounts\\n", loaded_accounts_count);
}