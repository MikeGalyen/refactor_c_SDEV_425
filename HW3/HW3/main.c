#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 20 // Limit for buffers
#define T_SIZE = 100 // Limit for time buffer


// Function prototypes
void showResults(char);
void showMenu(void);
int getUsernameAndCheck(char* un);
int getPasswordAndCheck(char* up);
void clearScreen(void);
void printTime(void);
char * returnTime(void);
void auditLog(char* message);

// Global variables
char username[MAX];
char userpassword[MAX];
char *timeStamp = " ";
char *secrets_file = "/Users/michaelgalyen/Documents/SDEV_425/HW3/shared_secrets.txt";
char *audit_log_file = "/Users/michaelgalyen/Documents/SDEV_425/HW3/audit_file.txt";
FILE *sec_file;
FILE *audit_file;


// Main routine
int main(void) {
    // Print time for user
    printTime();
    
    // Welcome the User
    printf("Welcome to the C Array Program!\n");

    // Variables
    char *messageUserName = " Failed username attempt \n"; // Message to use for logging
    char *messagePassword = " Failed password attempt \n"; // Message to use for logging
    char *messageLogin = " Successful login \n"; // Message to use for logging
    char *messageLogout = " User Logged out \n"; // Message to use for logging
    char cont = 'y'; // To continue with loop
    int checkUserName = 2; // Int to control login loop
    int checkUserPassword = 2; // Int to control login loop
    
    // While loop to control user login will only exit with a successful login
    while (checkUserName != 0 || checkUserPassword != 0) {
        // call to get username
        checkUserName = getUsernameAndCheck(username);
        // Check for file not being found
        if (checkUserName != 0) {
            // Log file not found
            auditLog(messageUserName);
        }
        // call to get password
        checkUserPassword = getPasswordAndCheck(userpassword);
        // Check for file not found
        if (checkUserPassword != 0) {
            // log file not found
            auditLog(messagePassword);
        }
    }
    // Log successful login
    auditLog(messageLogin);
    // Call clearScreen() to clear screen by adding a ton \n characters
    clearScreen();
    // Display menu and Get Selection
    
    // While loop to display sparts seasons menu upon successful login
    while (1) {
        // Eat lingering \n from previous interaction
        if (cont == '\n') {
            // Get the user selection
            cont = getchar();
            // Display the menu response
            showResults(cont);
        }
        // Check if user has entered the quit character
        if (cont == 'e' || cont == 'E') {
            break;
        }
        // Diaply the Menu
        showMenu();
        
        // Get the user selection
        cont = getchar();
        
        // Display the menu response
        showResults(cont);
    }
    
    char confirm; // variable to hold user reponse that quits application
    printf("Confirm your exit by pressing return!\n");
    // Eat previously hanging \n
    confirm = getchar();
    // whle loop to wait for user to press enter
    while (getchar() != '\n') {
        // Get user response
        confirm = getchar();
    }
    // Log user logout
    auditLog(messageLogout);
    // Free memory on program exit
    free(username);
    free(userpassword);
    free(timeStamp);
    free(secrets_file);
    free(audit_log_file);
    free(sec_file);
    free(audit_file);
    // Return 0 for successful
    return 0;
}

// Function takes array as argument and returns a char
// open password file and get password associated with username
int getUsernameAndCheck(char* un) {
    // Variables
    char *message = "File not found when retrieving shared_secrets.txt \n"; // Message for audit logging
    char buf[MAX]; // buffer to hold user input
    char *buff_p = buf; // Pointr to buffer
    char replace[] = "\n"; // array used to add \0 to string
    int result = 2; // Int to return
    char val = '0'; // Char used to control while loop
    // While loop to get user input
    while (val == '0') {
        // Print message
        printf("Please enter username\n");
        // Get user input
        fgets(buff_p, MAX, stdin);
        if (strlen(buff_p) > MAX || strlen(buff_p) < 1 || sizeof(buff_p) > 15) {
            // Print if input invalid
            printf("Try again");
            continue;
        }
        // input is valid
        else {
            // Find index of \n
            unsigned long long size = strcspn(buff_p, replace);
            // replace \n with string terminator
            buff_p[size] = '\0';
            // Break out of while loop
            val = '1';
        }
    }
    // Open file to read usernames
    sec_file = fopen(secrets_file, "r");
    // Check if file didn't exist
    if (sec_file < 0) {
        // Log file didn't exist
        auditLog(message);
    }
    // File existed so parse lines for matching username
    else {
        // Create buffer to hold lines from file
        char lineBuffer[100];
        // While loop loops until username is found or end of file character is found
        while ((fgets(lineBuffer, sizeof(lineBuffer), sec_file)) && (* lineBuffer != EOF || (!feof(stdin) && !ferror(stdin)))) {
            // Split line on whitespace
            char* original_username = strtok(lineBuffer, " ");
            // Check the token created by splitting against the user input
            result = strcmp(buff_p, original_username);
        }
        // Close file
        fclose(sec_file);
    }
    // Once there's a match, copy username out to global array
    if (result == 0) {
        for (int i = 0; i <= sizeof(buff_p); i++) {
            un[i] = buff_p[i];
        }
        // Return int
        return result;
    }
    // Return int
    return 1;
} // End of getUsernameAndCheck()

// Function takes array as argument and returns a char
// open password file and get password associated with username
int getPasswordAndCheck(char* up) {
    // Variables
    char *message = "File not found when retrieving shared_secrets.txt \n"; // Message for audit log
    char buf[MAX]; // buffer to hold user input
    char *buff_p = buf; // Pointer to buffer
    char replace[] = "\n"; // Char to replace
    int result = 2; // Int to return
    char val = '0'; // Int to control while loop
    // While loop to get user input
    while (val == '0') {
        // Print message
        printf("Please enter password\n");
        // Eat previous dangling \n
        fgets(buff_p, MAX, stdin);
        // Check user input
        if (strlen(buff_p) > MAX || strlen(buff_p) < 1 || sizeof(buff_p) > 15) {
            printf("Try again");
            continue;
        }
        // If user input is valid
        else {
            // Find index of \n
            unsigned long long size = strcspn(buff_p, replace);
            // replace \n
            buff_p[size] = '\0';
            // Break out of loop
            val = '1';
        }
    }
    // Open file for credentials
    sec_file = fopen(secrets_file, "r");
    // If file doesn't exist
    if (sec_file < 0) {
        // Log file not found
        auditLog(message);
    }
    // Parse through file looking for a matching username and
    else {
        // buffer to hold lines as they're parsed through
        char lineBuffer[100];
        // While loop to loop through lines in the file
        while ((fgets(lineBuffer, sizeof(lineBuffer), sec_file)) && (* lineBuffer != EOF || (!feof(stdin) && !ferror(stdin)))) {
            // Split line on white space
            char* original_password = strtok(lineBuffer, " ");
            // Move to the next token
            original_password = strtok(NULL, " ");
            // Compare user input with string token
            result = strcmp(buff_p, original_password);
        }
        // Close file
        fclose(sec_file);
    }
    // If there's a match, copy string token out to global array
    if (result == 0) {
        for (int i = 0; i <= sizeof(buff_p); i++) {
            up[i] = buff_p[i];
        }
        // In case of a matching string, return 0
        return result;
    }
    // In case of no match, return 1
    return 1;
    
    
    
}

// Function takes one char as argument and returns nothing
// Function prints message based on user input
void showResults(char value) {
    switch (value){
    case 'F':
    case 'f':
        printf("Welcome to the Football season!\n");
        break;
    case 'S':
    case 's':
        printf("Welcome to the Soccer season!\n");
        break;
    case 'B':
    case 'b':
        printf("Welcome to the Baseball season!\n");
        break;
    case 'E':
    case 'e':
        printf("Exiting the Menu system!\n");
        break;
    case '\n':
        break;
    default:
        printf("Please enter a valid selection\n");
    }
    
}

// Function takes no arguments and returns nothing
// Function prints menu
void showMenu(void) {
    printf("Enter a selection from the following menu.\n");
    printf("B. Baseball season.\n");
    printf("F. Football season.\n");
    printf("S. Soccer season.\n");
    printf("E. Exit the system.\n");
}
// Function effectively obscures the user data by printing many new lines
// Function takes no arguments and returns nothing
void clearScreen(void) {
    int n;
    for (n = 0; n < 20; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
    }
// Function takes no arguments, prints time to terminal, and return nothing
void printTime(void) {
    // Get epoch time
    time_t t ;
    // Create pointer to time structure
    struct tm *tmp;
    // Create array
    char MY_TIME[sizeof(t) + 10];
    // Return time object
    time( &t );
    // Fill tm structure
    tmp = localtime(&t);
    // Format time
    strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d %H:%M", tmp);
    // Thie function prints the time and returns nothing
    printf("%s\n", MY_TIME );
}
// Function takes no arguments and returns the current time as a string
char * returnTime(void) {
    // Get epoch time
    time_t t ;
    // Pointer to time structure
    struct tm *tmp;
    // Create array
    char MY_TIME[sizeof(t) + 10];
    // Return time object
    time( &t );
    // Fill tm structure
    tmp = localtime(&t);
    // Format time
    strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d %H:%M", tmp);
    // Allocate memory for time string
    char *t_str = malloc(sizeof(t) + 1);
    // Fill time string
    for (int i = 0; i <= sizeof(MY_TIME); i++) {
        if (i == sizeof(MY_TIME) + 1) {
            t_str[i] = '\0';
        }
        else {
            t_str[i] = MY_TIME[i];
        }
    }
    // Return time string
    return t_str;
}
// Function takes one argument and retuns nothing
void auditLog(char* message) {
    // Create timestamp
    for (int i = 0; i < sizeof(returnTime()); i++) {
        timeStamp = returnTime();
    }
    // Open file
    audit_file = fopen(audit_log_file, "a");
    // Write timestamp to file
    fputs(timeStamp, audit_file);
    // Write argument message
    fputs(message, audit_file);
    // Close file
    fclose(audit_file);
}
