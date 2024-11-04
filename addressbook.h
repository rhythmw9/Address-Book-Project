#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

//define a structure called contact to hold info about person
typedef struct contact Contact;

//function to add a contact
void addContact(Contact ** head, int position, char * contactInfo);

//function to delete a contact
void deleteContact(Contact ** head, int position);

//function to print the whole contents of a contact
void getContact(Contact ** head, int position);

//function to get a specific member of a contact
void getField(Contact ** head, int position, char *field);

//function to get number of contacts in the list
int getNumContacts(Contact ** head);

//function to load a contact from a file
void loadContact(Contact ** head, char * fileName);

//function to save a contact to a file
void saveContact(Contact *head, char *fileName);

//function to edit a contact
void editContact(Contact *head, int index, char *fieldName, char *newValue);

//function to sort contacts
void sortContacts(Contact **head);

Contact* sortedMerge(Contact* a, Contact* b);

Contact* getMiddle(Contact* head);


#endif
