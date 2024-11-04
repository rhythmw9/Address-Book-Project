# Address Book Project

A command-line address book application written in C. This project enables users to manage a list of contacts by adding, editing, deleting, and retrieving contact information. The program also supports saving and loading contacts to and from a file, making data persistent across sessions.

## Features
- **Add, Delete, and Edit Contacts**: Users can add new contacts, delete existing ones, and edit contact details.
- **Retrieve Specific Contact Information**: Allows retrieval of all details for a contact or a specific field (e.g., last name or email).
- **Sort Contacts**: Sorts contacts alphabetically by last name and other criteria.
- **File I/O Support**: Save contacts to a file and load them from a file to retain information between program sessions.
- **Dynamic Memory Management**: Manages memory efficiently using linked lists, with dynamic allocation for each contact.

## Project Structure
- **main.c**: Contains the main function and command handling for the application.
- **addressbook.c**: Implements core functions for contact management, including adding, deleting, editing, and saving/loading contacts.
- **addressbook.h**: Defines the `Contact` struct and function prototypes.

## Usage Instructions
After compiling the program (instructions below), you can use the following commands in the application:

1. **Add a Contact**
   - Command: `a`
   - Input: Position (integer), followed by contact info in `LastName,FirstName,Email,PhoneNumber` format.
   - Example:
     ```
     a
     0
     Doe,John,john@example.com,123-456-7890
     ```

2. **Delete a Contact**
   - Command: `d`
   - Input: Position (integer) of the contact to delete.
   - Example:
     ```
     d
     0
     ```

3. **Get All Contact Details**
   - Command: `g`
   - Input: Position (integer) of the contact.
   - Example:
     ```
     g
     0
     ```

4. **Get a Specific Contact Field**
   - Command: `f`
   - Input: Position (integer) of the contact, then the field name (`lastName`, `firstName`, `email`, or `phoneNumber`).
   - Example:
     ```
     f
     0
     email
     ```

5. **Get Number of Contacts**
   - Command: `n`
   - Example:
     ```
     n
     ```

6. **Load Contacts from a File**
   - Command: `l`
   - Input: File name (e.g., `contacts.txt`).
   - Example:
     ```
     l
     contacts.txt
     ```

7. **Save Contacts to a File**
   - Command: `s`
   - Input: File name.
   - Example:
     ```
     s
     contacts.txt
     ```

8. **Edit a Contact**
   - Command: `e`
   - Input: Position (integer), field name to edit, and new value.
   - Example:
     ```
     e
     0
     lastName
     Smith
     ```

9. **Sort Contacts**
   - Command: `o`
   - Example:
     ```
     o
     ```

10. **Quit the Program**
    - Command: `q`
    - Example:
      ```
      q
      ```


