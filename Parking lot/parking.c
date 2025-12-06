#include <stdio.h>
#include <string.h>

#define MAX_SLOTS 50
#define MAX_QUEUE 50

int slots[MAX_SLOTS];
char queue[MAX_QUEUE][20];
int front = 0, rear = -1;
int totalSlots = 0;

void enqueue(char vehicle[]) {
    if (rear == MAX_QUEUE - 1) {
        printf("Queue Full! Cannot add more vehicles.\n");
        return;
    }
    strcpy(queue[++rear], vehicle);
    printf("Vehicle %s added to waiting queue.\n", vehicle);
}

int dequeue(char vehicle[]) {
    if (front > rear)
        return 0;
    strcpy(vehicle, queue[front++]);
    return 1;
}

int findFreeSlot() {
	int i;
    for (i = 0; i < totalSlots; i++)
        if (slots[i] == 0)
            return i;
    return -1;
}

void addVehicle() {
    char vehicle[20];
    printf("Enter vehicle number: ");
    scanf("%19s", vehicle);

    int slot = findFreeSlot();

    if (slot != -1) {
        slots[slot] = 1;
        printf("Vehicle %s assigned to Slot %d\n", vehicle, slot + 1);
    } else {
        enqueue(vehicle);
    }
}

void removeVehicle() {
    int slot;
    printf("Enter slot number to free (1-%d): ", totalSlots);
    if (scanf("%d", &slot) != 1) { 
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Invalid input!\n");
        return;
    }

    if (slot < 1 || slot > totalSlots || slots[slot - 1] == 0) {
        printf("Invalid slot!\n");
        return;
    }

    slots[slot - 1] = 0;
    printf("Slot %d is now free.\n", slot);

    char vehicle[20];
    if (dequeue(vehicle)) {
        slots[slot - 1] = 1;
        printf("Vehicle %s automatically assigned to Slot %d\n", vehicle, slot);
    }
}

void displayFreeSlots() {
    printf("\nFree Slots: ");
    int found = 0,i;

    for ( i = 0; i < totalSlots; i++) {
        if (slots[i] == 0) {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("No free slots.");

    printf("\n");
}

void displayQueue() {
    if (front > rear) {
        printf("Waiting queue empty.\n");
        return;
    }

    printf("\nVehicles in Waiting Queue:\n");
    int i;
    for ( i = front; i <= rear; i++)
        printf("%s\n", queue[i]);
}

int main() {
    int choice,i;

    printf("Enter number of parking slots available (1-%d): ", MAX_SLOTS);
    if (scanf("%d", &totalSlots) != 1) {
        printf("Invalid input. Exiting.\n");
        return 0;
    }
    if (totalSlots < 1) totalSlots = 1;
    if (totalSlots > MAX_SLOTS) totalSlots = MAX_SLOTS;

    for (i = 0; i < totalSlots; ++i) slots[i] = 0;

    while (1) {
        printf("\n--- SMART PARKING LOT MENU ---\n");
        printf("1. Add Vehicle\n");
        printf("2. Remove Vehicle\n");
        printf("3. Show Free Slots\n");
        printf("4. Show Waiting Queue\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid choice!\n");
            continue;
        }

        switch (choice) {
            case 1: addVehicle(); break;
            case 2: removeVehicle(); break;
            case 3: displayFreeSlots(); break;
            case 4: displayQueue(); break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

