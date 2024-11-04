#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addressbook.h"


int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	Contact * head;
	head = NULL;

	char buffer[BUFSIZ];

	printf("Ready\n");

	int index = 0;
	char tempChar;
	do{ fgets(buffer, BUFSIZ, stdin);

		tempChar = buffer[0];

		switch(tempChar){
		case 'a':
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			fgets(buffer, BUFSIZ, stdin);
			addContact(&head, index, buffer);
		    break;
		case 'd':
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			deleteContact(&head, index);
			break;
		case 'g':
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			getContact(&head, index);
			break;
		case 'f':
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			fgets(buffer, BUFSIZ, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			getField(&head, index, buffer);
			break;
		case 'n':
			printf("%d\n",getNumContacts(&head));
			break;
		case 'l':
			fgets(buffer, BUFSIZ, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			loadContact(&head, buffer);
			break;
		case 's':
			fgets(buffer, BUFSIZ, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			saveContact(head, buffer);
			break;
		case 'e':
			index = atoi(fgets(buffer, BUFSIZ, stdin));

			fgets(buffer, BUFSIZ, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			char* field = strdup(buffer);

			fgets(buffer, BUFSIZ, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			char *value = strdup(buffer);

			editContact(head, index, field, value);
			free(field);
			free(value);
			break;
		case 'o':
			sortContacts(&head);
			break;
	    }
	} while(tempChar != 'q');
	printf("Complete\n");

	return EXIT_SUCCESS;
}
