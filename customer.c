#include "atm.h"

bool is_valid_pin_format(const char *pin_str) {
    if (pin_str == NULL) return false;
    int len = strlen(pin_str);
    if (len != ACTUAL_PIN_DIGITS) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit(pin_str[i])) {
            return false;
        }
    }
    return true;
}

bool is_valid_name_format(const char *name_str) {
    if (name_str == NULL || strlen(name_str) == 0 || strlen(name_str) >= MAX_NAME_LENGTH) {
        return false;
    }
    for (int i = 0; name_str[i] != '\0'; i++) {
        if (!(isalpha(name_str[i]) || isspace(name_str[i]))) {
            return false;
        }
    }
    return true;
}

bool change_pin_wrapper(Customer *customer_ptr) {
    if (!customer_ptr) return false;

    char old_pin[MAX_PIN_STORAGE_LENGTH];
    char new_pin1[MAX_PIN_STORAGE_LENGTH];
    char new_pin2[MAX_PIN_STORAGE_LENGTH];

    printf("Enter your current PIN: ");
    scanf("%s", old_pin);
    clear_input_buffer();

    if (strcmp(old_pin, customer_ptr->pin) != 0) {
        printf("Incorrect PIN.\\n");
        return false;
    }

    printf("Enter new PIN: ");
    scanf("%s", new_pin1);
    clear_input_buffer();

    if (!is_valid_pin_format(new_pin1)) {
        printf("Invalid PIN format. PIN must be %d digits.\\n", ACTUAL_PIN_DIGITS);
        return false;
    }

    printf("Confirm new PIN: ");
    scanf("%s", new_pin2);
    clear_input_buffer();

    if (strcmp(new_pin1, new_pin2) == 0) {
        strcpy(customer_ptr->pin, new_pin1);
        printf("PIN changed successfully.\\n");
        return true;
    } else {
        printf("PINs do not match.\\n");
        return false;
    }
}