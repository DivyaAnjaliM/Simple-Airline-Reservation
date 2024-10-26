#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for airline reservation
struct Reservation {
    char passportNumber[20];
    char name[50];
    int seatNumber;
    char email[50];
    struct Reservation* next;
};

// Declare pointers to the structure
struct Reservation* first = NULL;
struct Reservation* current = NULL;
struct Reservation* dummy = NULL;

// Function prototypes
void reserveSeat();
void cancelReservation();
void displayReservations();
void saveToFile();
void getDetails(char* passportNumber, char* name, char* email);

// Main function
int main() {
    int choice;
    int num = 1;

    do {
        printf("\n--- Airline Reservation System ---\n");
        printf("1. Reserve a Seat\n");
        printf("2. Cancel Reservation\n");
        printf("3. Display Reservations\n");
        printf("4. Save Reservations to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                reserveSeat(&num);
                break;
            case 2:
                cancelReservation();
                break;
            case 3:
                displayReservations();
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to reserve a seat
void reserveSeat(int* num) {
    if (*num > 100) { // assuming there are only 100 seats available
        printf("All seats are full.\n");
        return;
    }

    struct Reservation* newReservation = (struct Reservation*)malloc(sizeof(struct Reservation));
    if (newReservation == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    getDetails(newReservation->passportNumber, newReservation->name, newReservation->email);
    newReservation->seatNumber = (*num)++;
    newReservation->next = NULL;

    if (first == NULL) {
        first = newReservation;
        current = newReservation;
    } else {
        current->next = newReservation;
        current = newReservation;
    }

    printf("Seat reserved successfully. Seat Number: %d\n", newReservation->seatNumber);
}

// Function to cancel a reservation
void cancelReservation() {
    char passportNumber[20];
    printf("Enter passport number to cancel reservation: ");
    scanf("%s", passportNumber);

    struct Reservation* temp = first;
    struct Reservation* prev = NULL;

    while (temp != NULL && strcmp(temp->passportNumber, passportNumber) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("No reservation found with the given passport number.\n");
        return;
    }

    if (prev == NULL) {
        first = temp->next;
    } else {
        prev->next = temp->next;
    }

    if (temp == current) {
        current = prev;
    }

    free(temp);
    printf("Reservation cancelled successfully.\n");
}

// Function to display all reservations
void displayReservations() {
    struct Reservation* temp = first;

    if (temp == NULL) {
        printf("No reservations found.\n");
        return;
    }

    while (temp != NULL) {
        printf("Passport Number: %s\n", temp->passportNumber);
        printf("Name: %s\n", temp->name);
        printf("Seat Number: %d\n", temp->seatNumber);
        printf("Email: %s\n\n", temp->email);
        temp = temp->next;
    }
}

// Function to save reservations to a file
void saveToFile() {
    FILE* file = fopen("reservations.txt", "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    struct Reservation* temp = first;
    while (temp != NULL) {
        fprintf(file, "Passport Number: %s\n", temp->passportNumber);
        fprintf(file, "Name: %s\n", temp->name);
        fprintf(file, "Seat Number: %d\n", temp->seatNumber);
        fprintf(file, "Email: %s\n\n", temp->email);
        temp = temp->next;
    }

    fclose(file);
    printf("Reservations saved to file successfully.\n");
}

// Function to get reservation details from user
void getDetails(char* passportNumber, char* name, char* email) {
    printf("Enter passport number: ");
    scanf("%s", passportNumber);
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter email: ");
    scanf("%s", email);
}
