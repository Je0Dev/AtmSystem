#include "atm.h"


bool get_double_input(double *value, const char *prompt) {
    printf("%s", prompt);
    if (scanf("%lf", value) == 1) {
        clear_input_buffer();
        return true;
    }
    clear_input_buffer();
    return false;
}

bool get_int_input(int *value, const char *prompt) {
    printf("%s", prompt);
    if (scanf("%d", value) == 1) {
        clear_input_buffer();
        return true;
    }
    clear_input_buffer();
    return false;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}