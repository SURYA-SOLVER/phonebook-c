#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define PHONE_LEN 20
#define DB_FILE "contacts.bin"

typedef struct {
    char name[MAX_LEN];
    char phone[PHONE_LEN];
    char email[MAX_LEN];
} Contact;

// Cleaner architecture: Functions open/close files internally or handle errors gracefully
void addContact(void);
void editContact(void);
void deleteContact(void);
void listContacts(void);
void getStringInput(char *buffer, int maxLength);
void clearInputBuffer(void);

int main(int argc, char const *argv[]) {
    int choice;

    // Ensure the data file exists or can be created right at launch
    FILE *fp = fopen(DB_FILE, "ab");
    if (fp == NULL) {
        perror("Initial database creation failed");
        exit(1);
    }
    fclose(fp);

    while (1) {
        printf("\n=============================\n");
        printf("   PHONE BOOK APPLICATION    \n");
        printf("=============================\n");
        printf("1. Add Contact\n");
        printf("2. Edit Contact\n");
        printf("3. Delete Contact\n");
        printf("4. List Contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Error: Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); // Consume the newline left by scanf

        switch (choice) {
            case 1: addContact(); break;
            case 2: editContact(); break;
            case 3: deleteContact(); break;
            case 4: listContacts(); break;
            case 5:
                printf("Exiting Phone Book Application. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid Choice. Please try again.\n");
                break;
        }
    }
    return 0;
}

// Helper function to safely read strings with spaces and trim newlines
void getStringInput(char *buffer, int maxLength) {
    if (fgets(buffer, maxLength, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; // Remove newline
        }
    }
}

// Helper to flush remaining junk out of stdin
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

void addContact(void) {
    FILE *fp = fopen(DB_FILE, "ab"); // Append binary mode
    if (fp == NULL) {
        perror("Error opening database");
        return;
    }

    Contact c;
    printf("\n--- Add New Contact ---\n");
    printf("Enter Name : ");  getStringInput(c.name, MAX_LEN);
    printf("Enter Phone: ");  getStringInput(c.phone, PHONE_LEN);
    printf("Enter Email: ");  getStringInput(c.email, MAX_LEN);

    fwrite(&c, sizeof(Contact), 1, fp);
    fclose(fp);
    printf("Contact Added Successfully!\n");
}

void editContact(void) {
    FILE *fp = fopen(DB_FILE, "rb+"); // Read/Write binary mode
    if (fp == NULL) {
        perror("Error opening database");
        return;
    }

    Contact c;
    char searchName[MAX_LEN];
    int found = 0;

    printf("\nEnter name of the contact to edit: ");
    getStringInput(searchName, MAX_LEN);

    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.name, searchName) == 0) { // Case-insensitive match!
            found = 1;
            printf("\nContact Found! Enter New Details:\n");
            printf("Enter New Name [%s]: ", c.name);   getStringInput(c.name, MAX_LEN);
            printf("Enter New Phone [%s]: ", c.phone); getStringInput(c.phone, PHONE_LEN);
            printf("Enter New Email [%s]: ", c.email); getStringInput(c.email, MAX_LEN);

            // Back up the file pointer by exactly 1 struct size to overwrite it
            fseek(fp, -((long)sizeof(Contact)), SEEK_CUR);
            fwrite(&c, sizeof(Contact), 1, fp);
            printf("Contact Updated Successfully!\n");
            break; 
        }
    }
    
    if (!found) printf("Contact '%s' not found.\n", searchName);
    fclose(fp);
}

void deleteContact(void) {
    FILE *fp = fopen(DB_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening database");
        return;
    }

    char searchName[MAX_LEN];
    printf("\nEnter name of the contact to delete: ");
    getStringInput(searchName, MAX_LEN);

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        perror("Error creating temporary storage");
        fclose(fp);
        return;
    }

    Contact c;
    int found = 0;

    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.name, searchName) == 0) {
            found = 1; // Skip writing this to the temp file
        } else {
            fwrite(&c, sizeof(Contact), 1, temp);
        }
    }
    
    fclose(fp);
    fclose(temp);

    if (found) {
        remove(DB_FILE);
        rename("temp.bin", DB_FILE);
        printf("Contact deleted successfully.\n");
    } else {
        remove("temp.bin"); // Clean up temporary file
        printf("Contact '%s' not found.\n", searchName);
    }
}

void listContacts(void) {
    FILE *fp = fopen(DB_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening database");
        return;
    }

    Contact c;
    int count = 0;

    printf("\n==================================================================\n");
    printf("%-25s | %-15s | %-25s\n", "NAME", "PHONE", "EMAIL");
    printf("==================================================================\n");

    while (fread(&c, sizeof(Contact), 1, fp)) {
        printf("%-25s | %-15s | %-25s\n", c.name, c.phone, c.email);
        count++;
    }
    
    if (count == 0) {
        printf("No contacts found in the phone book.\n");
    } else {
        printf("------------------------------------------------------------------\n");
        printf("Total Contacts: %d\n", count);
    }
    fclose(fp);
}
