#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20


// Function prototypes
void fillPassword(size_t , char[]);
void showResults(char);
// should have void listed
void showMenu(void);
int getUsernameAndCheck(char* un);
int checkForPassword(char* up);
void ClearScreen(void);

// Define a variable to hold a password
// and the copy
char password[MAX];
char cpassword[MAX];
char username[MAX];
char userpassword[MAX];
FILE *sec_file;
FILE *audit_file;


int main(void)
{
    // Welcome the User
    printf("Welcome to the C Array Program!\n");

    // Variables
    char cont = 'y'; // To continue with loop
    int cVar = 0; // process variable

    // Call the Copy routine
//    fillPassword(sizeof(password),password);
//
//    // Display variable values
//    printf("password is %s\n", password);
//    printf("cVar is %d\n", cVar);
//
//    // Copy password
//    memcpy(cpassword, password,sizeof(password));
    int checkUserName = 2;
    int checkUserPassword = 2;
    
    // call to get username ///////////////////////////////////////////////////
    checkUserName = getUsernameAndCheck(username);
    //printf("testing %zu \n", sizeof(temp_buf));
    if (checkUserName == 0) {
        printf("yes\n");///////////////////////////////////////////////////////////////////////////////
        printf("This is what we'e looking for %s\n", username);
        checkUserPassword = checkForPassword(userpassword);
        if (checkUserPassword == 0) {
            // Create new lines to obscure username and password
            ClearScreen();
            // Display menu and Get Selection
            while (1) {
                
                if (cont == '\n') {
                    // Get the user selection
                    cont = getchar();
                    
                    // Display the menu response
                    showResults(cont);

                }
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
        }
        else {
            printf("password bad");
        }
    }
    else {
        printf("Try again");
    }
    char confirm;
    printf("Confirm your exit by pressing return!\n");
    confirm = getchar(); //this line was causing yout o have ot hit return twice
    while (getchar() != '\n') {
        confirm = getchar();
    }
    return 0;
}

int getUsernameAndCheck(char* un) {
    char buf[MAX];
    char *buff_p = buf;
    char replace[] = "\n";
    int result = 2;
    char val = '0';
    //fgets(buff_p, MAX, stdin);
    while (val == '0') {
        printf("Please enter username\n");
        fgets(buff_p, MAX, stdin);
        if (strlen(buff_p) > MAX || strlen(buff_p) < 1) {
            printf("Try again");
            continue;
        }
        else {
            unsigned long long size = strcspn(buff_p, replace);
            buff_p[size] = '\0';
            printf("%s\n", buff_p);
            val = '1';
        }
    }
    sec_file = fopen("/Users/michaelgalyen/Documents/SDEV_425/HW3/shared_secrets.txt", "r");
    if (sec_file < 0) {
        audit_file = fopen("/Users/michaelgalyen/Documents/SDEV_425/HW3/audit_file.txt", "a");
        fputs("File not found when retrieving shared_secrets.txt ", audit_file);
    }
    else {
        char lineBuffer[100];
        while (fgets(lineBuffer, sizeof(lineBuffer), sec_file)) {
            puts(lineBuffer);
            char* original_username = strtok(lineBuffer, " ");
            //printf("The size of your name is %zu\n", sizeof(original_username));
            result = strcmp(buff_p, original_username);
            printf("%s and %s\n", buff_p, original_username);
            printf("The result is %d\n", result);
        }
        
        
    }
    if (result == 0) {
        for (int i = 0; i <= sizeof(buff_p); i++) {
            un[i] = buff_p[i];
        }
        return result;
    }
    return 1;
} // End of getUsernameAndCheck()

// open password file and get password associated with username
int checkForPassword(char * up) { ///////////////////////DCL20-C. Explicitly specify void when a function accepts no arguments
    char buf[MAX];
    char *buff_p = buf;
    char replace[] = "\n";
    int result = 2;
    char val = '0';
    //fgets(buff_p, MAX, stdin);
    while (val == '0') {
        printf("Please enter password\n");
        fgets(buff_p, MAX, stdin);
        if (strlen(buff_p) > MAX || strlen(buff_p) < 1) {
            printf("Try again");
            continue;
        }
        else {
            unsigned long long size = strcspn(buff_p, replace);
            buff_p[size] = '\0';
            printf("%s\n", buff_p);
            val = '1';
        }
    }
    sec_file = fopen("/Users/michaelgalyen/Documents/SDEV_425/HW3/shared_secrets.txt", "r");
    if (sec_file < 0) {
        audit_file = fopen("/Users/michaelgalyen/Documents/SDEV_425/HW3/audit_file.txt", "a");
        fputs("File not found when retrieving shared_secrets.txt ", audit_file);
    }
    else {
        char lineBuffer[100];
        while (fgets(lineBuffer, sizeof(lineBuffer), sec_file)) {
            puts(lineBuffer);
            char* original_password = strtok(lineBuffer, " ");
            printf("1 %s\n", original_password);
            original_password = strtok(NULL, " ");
            printf("2 %s\n", original_password);
            result = strcmp(buff_p, original_password);
            printf("%s and %s\n", buff_p, original_password);
            printf("The result is %d\n", result);
        }
        
        
    }
    if (result == 0) {
        for (int i = 0; i <= sizeof(buff_p); i++) {
            up[i] = buff_p[i];
        }
        return result;
    }
    return 1;
    
    
    
}

// Make a String of '1's
void fillPassword(size_t n, char dest[]) {
    // Should be n-1
     for (size_t j = 0; j < n; j++) {
        dest[j] = '1';
    }
    // Add null terminator for string
    dest[n] = '\0';
}

/* Display the Results*/
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

/* Display the Menu*/
void showMenu(void) {
    printf("Enter a selection from the following menu.\n");
    printf("B. Baseball season.\n");
    printf("F. Football season.\n");
    printf("S. Soccer season.\n");
    printf("E. Exit the system.\n");
}

void ClearScreen(void) {
    int n;
    for (n = 0; n < 20; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
    }
