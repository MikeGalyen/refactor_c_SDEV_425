#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 15


// Function prototypes
void fillPassword(size_t , char[]);
void showResults(char);
// should have void listed
void showMenu(void);
void getUsernameAndCheck(char *var);
void checkForPassword(void);

// Define a variable to hold a password
// and the copy
char password[MAX];
char cpassword[MAX];
char buf[MAX];
char *buff_p = buf;
FILE *sec_file;


int main(void)
{
    // Welcome the User
    printf("Welcome to the C Array Program!\n");

    // Variables
    char cont = 'y'; // To continue with loop
    int cVar = 0; // process variable

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

    // Call the Copy routine
    fillPassword(sizeof(password),password);
    
    // Display variable values
    printf("password is %s\n", password);
    printf("cVar is %d\n", cVar);

    // Copy password
    memcpy(cpassword, password,sizeof(password));
    
    // call to get username ///////////////////////////////////////////////////
    getUsernameAndCheck(buff_p);
    // tesst//////////////////////////////////////////////////////
    printf("testing %s", buf);
    
    // Pause before exiting
    char confirm;
    printf("Confirm your exit by pressing return!\n");
    confirm = getchar();
    while (getchar() != '\n') {
        confirm = getchar();
    }
    return 0;
}

void getUsernameAndCheck(char *var) {
    printf("Enter your username of 15 or less characters");
    char val = '0';
    fgets(var, MAX, stdin);
    while (val == '0') {
        printf("Please enter username");
        fgets(var, MAX, stdin);
        if (strlen(var) > 15 || strlen(var) < 1) {
            printf("Not a valid length username");
            continue;
        }
        else {
            printf("Your username is %s \n", var);
            val = '1';
        }
    }
    sec_file = fopen("shared_secrets.txt", "r");
}

// open password file and get password associated with username
void checkForPassword(void) { ///////////////////////DCL20-C. Explicitly specify void when a function accepts no arguments
    // File pointer
    
    
    
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
