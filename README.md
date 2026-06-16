# Phone Book Application

A simple command-line Phone Book application written in C for managing contact information.

## Features

✨ **Core Functionality:**
- **Add Contact** - Add new contacts with name, phone number, and email
- **Edit Contact** - Update existing contact information
- **Delete Contact** - Remove contacts from the phone book
- **List Contacts** - Display all contacts in a formatted table
- **Persistent Storage** - All data is saved to a binary file (`contacts.bin`)

## Technical Highlights

- **Binary File Storage** - Efficient data persistence using binary files
- **Struct-Based Design** - Contact structure for organized data management
- **Input Validation** - Safe string input handling with buffer overflow protection
- **Case-Insensitive Search** - Find contacts regardless of name case
- **Clean Architecture** - Modular function design with proper error handling

## Project Information

- **Course:** C Language - First Year, First Semester
- **Language:** C
- **File Size Limit:** 100 characters for name/email, 20 for phone
- **Database File:** `contacts.bin`

## How to Compile and Run

### Using GCC:
```bash
gcc -o phonebook phonebook.c
./phonebook
```

### Using Makefile:
```bash
make
make run
```

## Usage

1. Run the program
2. Choose from the menu:
   - `1` - Add a new contact
   - `2` - Edit an existing contact
   - `3` - Delete a contact
   - `4` - List all contacts
   - `5` - Exit the application

## Example Session

```
=============================
   PHONE BOOK APPLICATION    
=============================
1. Add Contact
2. Edit Contact
3. Delete Contact
4. List Contacts
5. Exit
Enter your choice (1-5): 1

--- Add New Contact ---
Enter Name : John Doe
Enter Phone: 9876543210
Enter Email: john@example.com
Contact Added Successfully!
```

## Data Structure

```c
typedef struct {
    char name[100];     // Contact name
    char phone[20];     // Phone number
    char email[100];    // Email address
} Contact;
```

## Notes

- The application automatically creates the `contacts.bin` file on first run
- All searches are case-insensitive for better usability
- The program validates user input to prevent common errors
- Binary file format ensures efficient storage

## Author

Created as a course project for C Language (First Year, First Semester)

---

**Happy coding!** 📞
