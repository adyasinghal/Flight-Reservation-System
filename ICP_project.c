#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 100
#define MAX_PASSENGERS 200

struct Flight {
    char flightNumber[10];
    char from[50];
    char to[50];
    int totalSeats;
    int availableSeats;
} flights[MAX_FLIGHTS];

struct Passenger {
    char name[50];
    char flightNumber[10];
    int age;
    char phone[20];
} passengers[MAX_PASSENGERS];

int passengerCount = 0;

void initializeFlights() {
    strcpy(flights[0].flightNumber, "AI101");
    strcpy(flights[0].from, "Delhi");
    strcpy(flights[0].to, "Mumbai");
    flights[0].totalSeats = 150;
    flights[0].availableSeats = 150;

    strcpy(flights[1].flightNumber, "AI202");
    strcpy(flights[1].from, "Kolkata");
    strcpy(flights[1].to, "Bangalore");
    flights[1].totalSeats = 200;
    flights[1].availableSeats = 200;
}

void bookFlight() {
    char flightNo[10];
    char passengerName[50];
    int seats;
    printf("Enter Flight Number to book: ");
    scanf("%s", flightNo);
    for(int i = 0; i < MAX_FLIGHTS; i++) {
        if(strcmp(flights[i].flightNumber, flightNo) == 0) {
            if(flights[i].availableSeats > 0) {
                printf("Enter number of seats to book: ");
                scanf("%d", &seats);
                if(flights[i].availableSeats >= seats) {
                    flights[i].availableSeats -= seats;
                    for(int j = 0; j < seats; j++) {
                        printf("Enter passenger name: ");
                        scanf("%s", passengerName);
                        strcpy(passengers[passengerCount].name, passengerName);
                        strcpy(passengers[passengerCount].flightNumber, flightNo);
                        printf("Enter passenger age: ");
                        scanf("%d", &passengers[passengerCount].age);
                        printf("Enter passenger phone number: ");
                        scanf("%s", passengers[passengerCount].phone);
                        passengerCount++;
                    }
                    printf("Booking successful for %d seat(s) to %s.\n", seats, flights[i].to);
                } else {
                    printf("Not enough seats available.\n");
                }
            } else {
                printf("Flight is fully booked.\n");
            }
            return;
        }
    }
    printf("Flight not found.\n");
}

void cancelFlight() {
    char flightNo[10];
    char passengerName[50];
    int seatsToCancel;
    printf("Enter Flight Number to cancel: ");
    scanf("%s", flightNo);
    for(int i = 0; i < MAX_FLIGHTS; i++) {
        if(strcmp(flights[i].flightNumber, flightNo) == 0) {
            printf("Enter number of seats to cancel: ");
            scanf("%d", &seatsToCancel);
            if(flights[i].availableSeats + seatsToCancel <= flights[i].totalSeats) {
                for(int j = 0; j < seatsToCancel; j++) {
                    printf("Enter passenger name to cancel: ");
                    scanf("%s", passengerName);
                    for(int k = 0; k < passengerCount; k++) {
                        if(strcmp(passengers[k].flightNumber, flightNo) == 0 && strcmp(passengers[k].name, passengerName) == 0) {
                            // Removing the passenger entry
                            for(int l = k; l < passengerCount - 1; l++) {
                                passengers[l] = passengers[l + 1];
                            }
                            passengerCount--;
                            break;
                        }
                    }
                }
                flights[i].availableSeats += seatsToCancel;
                printf("Cancellation successful for %d seat(s).\n", seatsToCancel);
            } else {
                printf("Invalid cancellation request.\n");
            }
            return;
        }
    }
    printf("Flight not found.\n");
}

void updatePassengerInfo() {
    char flightNo[10], oldName[50], newName[50], newPhone[20];
    int newAge;
    printf("Enter Flight Number: ");
    scanf("%s", flightNo);
    printf("Enter Passenger Name to update: ");
    scanf("%s", oldName);
    for(int i = 0; i < passengerCount; i++) {
        if(strcmp(passengers[i].flightNumber, flightNo) == 0 && strcmp(passengers[i].name, oldName) == 0) {
            printf("Enter new Name: ");
            scanf("%s", newName);
            printf("Enter new Age: ");
            scanf("%d", &newAge);
            printf("Enter new Phone Number: ");
            scanf("%s", newPhone);
            strcpy(passengers[i].name, newName);
            passengers[i].age = newAge;
            strcpy(passengers[i].phone, newPhone);
            printf("Passenger information updated.\n");
            return;
        }
    }
    printf("Passenger not found.\n");
}

void viewPassengers() {
    char flightNo[10];
    printf("Enter Flight Number to view passengers: ");
    scanf("%s", flightNo);
    printf("Passengers on Flight %s:\n", flightNo);
    int found = 0;
    for(int i = 0; i < passengerCount; i++) {
        if(strcmp(passengers[i].flightNumber, flightNo) == 0) {
            printf("Name: %s, Age: %d, Phone: %s\n", passengers[i].name, passengers[i].age, passengers[i].phone);
            found = 1;
        }
    }
    if(!found) {
        printf("No passengers found on this flight.\n");
    }
}

int main() {
    initializeFlights();
    int choice;
    while(1) {
        printf("\n1. Book Flight\n2. Cancel Booking\n3. Update Passenger Info\n4. View Passengers\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: bookFlight(); break;
            case 2: cancelFlight(); break;
            case 3: updatePassengerInfo(); break;
            case 4: viewPassengers(); break;
            case 5: return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}