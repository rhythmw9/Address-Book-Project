#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addressbook.h"
#define MAXLENGTH 100

struct contact{
	char * lastName;
	char * firstName;
	char * email;
	char * phoneNum;
	Contact * pNextContact;
};

void addContact(Contact ** head, int position, char * contactInfo){
	char *lastName = strtok(contactInfo, ",");
	char *firstName = strtok(NULL, ",");
	char *email = strtok(NULL, ",");
	char *phoneNum = strtok(NULL, ",");

	Contact * newContact = (Contact*)malloc(sizeof(Contact));
	phoneNum[strcspn(phoneNum, "\n")] = 0;  // Remove newline character

	newContact -> lastName = strdup(lastName);
	newContact -> firstName = strdup(firstName);
	newContact -> email = strdup(email);
	newContact -> phoneNum = strdup(phoneNum);


	if(*head == NULL || position == 0){
		newContact -> pNextContact = *head;
		*head = newContact;
	} else {
        Contact *current = *head;
        for (int i = 0; i < position - 1; i++) {

            if (current->pNextContact == NULL) break;
            current = current->pNextContact;
        }
        newContact->pNextContact = current->pNextContact;
        current->pNextContact = newContact;
    }
}

void deleteContact(Contact ** head, int position){
	if(*head == NULL){
		return;
	}
	Contact * temp = *head;
	if(position == 0){
		*head = temp-> pNextContact;
		free(temp);
		return;
	}
	for(int i = 0; temp != NULL && i < position - 1; i++){
		temp = temp -> pNextContact;
	}
	if(temp == NULL || temp -> pNextContact == NULL){
		return;
	}
	Contact * deleteContact = temp -> pNextContact;
	temp -> pNextContact = deleteContact -> pNextContact;
	free(deleteContact);
}

void getContact(Contact ** head, int position){
	Contact * temp = *head;
	for(int i = 0; temp != NULL && i < position; i++){
		temp = temp -> pNextContact;
	}
	if(temp == NULL){
		return;
	}
	printf("%s,%s,%s,%s\n", temp->lastName, temp->firstName, temp->email, temp->phoneNum);
}

void getField(Contact ** head, int position, char *field){
	Contact * current = *head;
	int count = 0;
	while(current != NULL){
		if(count == position){
			if(strcmp(field, "lastName") == 0){
				printf("%s\n", current->lastName);
			} else if(strcmp(field, "firstName") == 0){
				printf("%s\n", current->firstName);
			} else if(strcmp(field, "email") == 0){
				printf("%s\n", current->email);
			} else if(strcmp(field, "phoneNumber") == 0){
				printf("%s\n", current->phoneNum);
			} else{
				return;
			}
			return;
		}
		count++;
		current = current -> pNextContact;
	}
}

int getNumContacts(Contact ** head){
	int count = 0;
	Contact * current = *head;
	while(current != NULL){
		count++;
		current = current ->pNextContact;
	}
	return count;
}

void loadContact(Contact ** head, char * fileName){
	char buffer[BUFSIZ];
	FILE * fp = fopen(fileName, "r");
	if(fp == NULL){
		return;  // return if file cannot be opened
	}
	char lineofFile[MAXLENGTH * 4];

	// Skip the header line
	fgets(buffer, BUFSIZ, fp);

	while(fgets(lineofFile, sizeof(lineofFile), fp) != NULL){
		char *lastName = strtok(lineofFile, ",");
		char *firstName = strtok(NULL, ",");
		char *email = strtok(NULL, ",");
		char *phoneNum = strtok(NULL, ",");

		if(phoneNum != NULL){
	            phoneNum[strcspn(phoneNum, "\n")] = 0;  // Remove newline character
	        }

		Contact *newContact = malloc(sizeof(Contact));
		newContact -> lastName = strdup(lastName);
		newContact -> firstName = strdup(firstName);
		newContact -> email = strdup(email);
		newContact -> phoneNum = strdup(phoneNum);
		newContact ->pNextContact = NULL;


		if(*head==NULL){
			*head = newContact;
		} else{
			Contact *temp = *head;
			while(temp ->pNextContact != NULL){
				temp = temp ->pNextContact;
			}
			temp ->pNextContact = newContact;
		}
	}
	fclose(fp);
}

void saveContact(Contact *head, char *fileName){
	FILE * fp = fopen(fileName, "w");

	fprintf(fp, "lastName,firstName,email,phoneNumber\n");

	for(Contact *current = head; current != NULL; current = current ->pNextContact){
		fprintf(fp, "%s,%s,%s,%s\n", current ->lastName, current ->firstName, current ->email, current ->phoneNum);
	}
	fclose(fp);
}

void editContact(Contact *head, int index, char *fieldName, char *newValue){
    Contact *current = head;
    while(current && index > 0){
    	current = current->pNextContact;
    	index--;
    }

    if(current != NULL){  // If contact with given index was found
        if(strcmp(fieldName, "lastName") == 0){
            free(current ->lastName);
            current ->lastName = strdup(newValue);
        } else if(strcmp(fieldName, "firstName") == 0){
            free(current ->firstName);
            current ->firstName = strdup(newValue);
        } else if(strcmp(fieldName, "email") == 0){
            free(current ->email);
            current ->email = strdup(newValue);
        } else if(strcmp(fieldName, "phoneNumber") == 0){
            free(current ->phoneNum);
            current ->phoneNum = strdup(newValue);
        } else{
           return;
        }
    }
}

Contact* getMiddle(Contact* head) {
    if (head == NULL)
        return head;

    Contact* slow = head, *fast = head;

    while (fast->pNextContact && fast->pNextContact->pNextContact) {
        slow = slow->pNextContact;
        fast = fast->pNextContact->pNextContact;
    }

    return slow;
}

Contact* sortedMerge(Contact* a, Contact* b) {
    Contact* result = NULL;

    // Base cases
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // Compare fields and decide which to put in sorted list
    if (strcmp(a->lastName, b->lastName) < 0
        || (strcmp(a->lastName, b->lastName) == 0 && strcmp(a->firstName, b->firstName) < 0)
        || (strcmp(a->lastName, b->lastName) == 0 && strcmp(a->firstName, b->firstName) == 0 && strcmp(a->email, b->email) < 0)
        || (strcmp(a->lastName, b->lastName) == 0 && strcmp(a->firstName, b->firstName) == 0 && strcmp(a->email, b->email) == 0 && strcmp(a->phoneNum, b->phoneNum) < 0)) {
        result = a;
        result->pNextContact = sortedMerge(a->pNextContact, b);
    } else {
        result = b;
        result->pNextContact = sortedMerge(a, b->pNextContact);
    }

    return result;
}

void sortContacts(Contact** head) {
    Contact* current = *head;
    Contact* a, * b;

    // Base case
    if ((current == NULL) || (current->pNextContact == NULL)) {
        return;
    }

    // Split head into 'a' and 'b' sublists
    Contact* middle = getMiddle(current);
    b = middle->pNextContact;
    middle->pNextContact = NULL;
    a = current;

    // Recursively sort the sublists
    sortContacts(&a);
    sortContacts(&b);

    // Answer = merge the two sorted lists together
    *head = sortedMerge(a, b);
}
