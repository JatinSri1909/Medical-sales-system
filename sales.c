#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sales.h"
#include "inventory.h"

typedef struct SalesNode {
    SalesTransaction transaction;
    struct SalesNode* next;
} SalesNode;

SalesNode* salesHead = NULL;

// Initialize sales records (if necessary)
void initializeSales() {
    // If you have saved sales data in a file, you can load it here.
    // For example, if your sales data is stored in a file named "sales_data.txt":

    FILE* file = fopen("sales_data.txt", "r");
    if (file == NULL) {
        // Handle the case where the file couldn't be opened or doesn't exist.
        return;
    }

    // Initialize salesHead by reading data from the file.
    while (!feof(file)) {
        SalesNode* newNode = (SalesNode*)malloc(sizeof(SalesNode));
        if (newNode == NULL) {
            // Handle memory allocation failure.
            fclose(file);
            return;
        }

        // Assuming that the file format is "TransactionID CustomerName TotalAmount".
        if (fscanf(file, "%d %s %f", &newNode->transaction.transactionID, newNode->transaction.customerName, &newNode->transaction.totalAmount) == 3) {
            newNode->next = salesHead;
            salesHead = newNode;
        }
    }

    fclose(file);
}


void salesMenu() {
    int choice;

    do {
        // Display the sales menu
        printf("Sales Menu\n");
        printf("1. Record Sale\n");
        printf("2. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                recordSaleMenu();
                break;
            case 2:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

void recordSale(const char* customerName, int productID, int quantity) {
    Product* product = findProduct(productID);
    if (product == NULL) {
        printf("Product not found.\n");
        return;
    }

    if (product->quantity < quantity) {
        printf("Not enough stock available.\n");
        return;
    }

    // Calculate the total amount
    float totalAmount = product->price * quantity;

    // Deduct sold quantity from inventory
    product->quantity -= quantity;

    // Create a new sales transaction
    SalesNode* newNode = (SalesNode*)malloc(sizeof(SalesNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    newNode->transaction.transactionID = rand(); // A simple way to generate a transaction ID
    strncpy(newNode->transaction.customerName, customerName, sizeof(newNode->transaction.customerName));
    newNode->transaction.totalAmount = totalAmount;

    // Add the new sales transaction to the list
    newNode->next = salesHead;
    salesHead = newNode;

    printf("Sale recorded successfully.\n");
}

void recordSaleMenu() {
    char customerName[50];
    int productID;
    int quantity;

    printf("Enter customer name: ");
    scanf("%s", customerName);

    // Display the available products
    displayInventory();

    printf("Enter product ID: ");
    scanf("%d", &productID);

    // Check if the product exists in the inventory
    Product* product = findProduct(productID);
    if (product == NULL) {
        printf("Product not found in the inventory.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity. Sale not recorded.\n");
        return;
    }

    // Check if there is enough stock
    if (quantity > product->quantity) {
        printf("Insufficient stock. Sale not recorded.\n");
        return;
    }

    // Record the sale
    recordSale(customerName, productID, quantity);
    printf("Sale recorded successfully.\n");
}

void displaySalesReport() {
    SalesNode* current = salesHead;
    printf("Sales Report:\n");
    while (current != NULL) {
        printf("Transaction ID: %d, Customer: %s, Total Amount: %.2f\n", current->transaction.transactionID, current->transaction.customerName, current->transaction.totalAmount);
        current = current->next;
    }
}

float calculateTotalSales() {
    SalesNode* current = salesHead;
    float totalSales = 0;

    while (current != NULL) {
        totalSales += current->transaction.totalAmount;
        current = current->next;
    }

    return totalSales;
}
