#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Diary Entry
typedef struct DiaryEntry {
    char date[15];    // Date in format YYYY-MM-DD
    char time[10];    // Time in format HH:MM
    char note[500];   // The content of the diary entry
    struct DiaryEntry *next;  // Pointer to the next entry in the list
} DiaryEntry;

// Function to add a new entry to the diary
void addEntry(DiaryEntry **head) {
    DiaryEntry *newEntry = (DiaryEntry *)malloc(sizeof(DiaryEntry));
    
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", newEntry->date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", newEntry->time);
    getchar();  // To consume the newline character left by scanf
    printf("Enter your diary note: ");
    fgets(newEntry->note, sizeof(newEntry->note), stdin);
    
    newEntry->next = NULL;
    
    // Insert the new entry at the end of the list
    if (*head == NULL) {
        *head = newEntry;
    } else {
        DiaryEntry *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newEntry;
    }
    printf("Diary entry added successfully!\n");
}

// Function to display all entries in the diary
void viewEntries(DiaryEntry *head) {
    if (head == NULL) {
        printf("No diary entries found!\n");
        return;
    }

    DiaryEntry *temp = head;
    while (temp != NULL) {
        printf("\nDate: %s\n", temp->date);
        printf("Time: %s\n", temp->time);
        printf("Note: %s\n", temp->note);
        temp = temp->next;
    }
}

// Function to edit an entry based on date
void editEntry(DiaryEntry *head, char *date) {
    DiaryEntry *temp = head;
    int found = 0;
    
    while (temp != NULL) {
        if (strcmp(temp->date, date) == 0) {
            found = 1;
            printf("Editing entry for %s:\n", date);
            printf("Enter new Time (HH:MM): ");
            scanf("%s", temp->time);
            getchar();  // To consume newline
            printf("Enter new diary note: ");
            fgets(temp->note, sizeof(temp->note), stdin);
            printf("Diary entry updated successfully!\n");
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No entry found for the given date.\n");
    }
}

// Function to delete an entry based on date
void deleteEntry(DiaryEntry **head, char *date) {
    if (*head == NULL) {
        printf("Diary is empty.\n");
        return;
    }

    DiaryEntry *temp = *head, *prev = NULL;
    if (strcmp(temp->date, date) == 0) {
        *head = temp->next;  // Move head to the next entry
        free(temp);  // Free the memory of the deleted entry
        printf("Diary entry for %s deleted successfully!\n", date);
        return;
    }

    while (temp != NULL && strcmp(temp->date, date) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("No entry found for the given date.\n");
        return;
    }

    prev->next = temp->next;  // Unlink the node from the list
    free(temp);  // Free the memory of the deleted entry
    printf("Diary entry for %s deleted successfully!\n", date);
}

// Main function to interact with the user
int main() {
    DiaryEntry *head = NULL;
    int choice;
    char date[15];

    while (1) {
        printf("\nDigital Diary Menu:\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Edit Entry\n");
        printf("4. Delete Entry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume newline after scanf

        switch (choice) {
            case 1:
                addEntry(&head);
                break;
            case 2:
                viewEntries(head);
                break;
            case 3:
                printf("Enter the date of the entry to edit (YYYY-MM-DD): ");
                scanf("%s", date);
                editEntry(head, date);
                break;
            case 4:
                printf("Enter the date of the entry to delete (YYYY-MM-DD): ");
                scanf("%s", date);
                deleteEntry(&head, date);
                break;
            case 5:
                printf("Exiting Digital Diary...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
