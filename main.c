#include "atm.h"

int main() {
    printf("\\n\\n--Welcome to the ATM System--\\n\\n");
    initialize_system();
    printf("The system has been initialized.\\n");

    load_data_from_files();
    printf("Loading/creating initial data is complete.\\n");

    char continue_program_char;
    bool continue_main_loop = true;

    do {
        clear_screen();
        if (login_screen()) {
            main_menu();
        } else {
            printf("\\nLogin failed!\\n");
        }

        printf("\\nWould you like to perform another transaction or try to log in again? (y/n): ");
        if (scanf(" %c", &continue_program_char) != 1) {
            clear_input_buffer();
            fprintf(stderr, "You have entered an invalid option! The program is terminating!\\n");
            continue_main_loop = false;
        }
        clear_input_buffer();

        if (toupper(continue_program_char) != 'Y') {
            continue_main_loop = false;
        }

    } while (continue_main_loop);

    printf("\\nSaving data...\\n");
    save_data_to_files();
    printf("\\nClearing memory...\\n");
    cleanup_system();
    printf("Data saved and memory cleared successfully!\\n");
    printf("\\nThank you for using our ATM system! We hope to see you again soon!\\n");

    return EXIT_SUCCESS;
}