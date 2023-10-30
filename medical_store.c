#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "sales.h"

int main() {
    int choice;

    initializeInventory(); // Initialize inventory with sample data (you can modify this)
    initializeSales(); // Initialize sales records (you can modify this)

    do {
        // Display the main menu
        printf("Medical Store Sales System\n");
        printf("1. Manage Inventory\n");
        printf("2. Make a Sale\n");
        printf("3. View Sales Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inventoryMenu();
                break;
            case 2:
                salesMenu();
                break;
            case 3:
                displaySalesReport();
                break;
            case 4:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Clean up memory and perform any necessary tasks before exiting

    return 0;
}
