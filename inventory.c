#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

typedef struct InventoryNode {
    Product product;
    struct InventoryNode* next;
} InventoryNode;

InventoryNode* inventoryHead = NULL;

// Initialize inventory with sample data
void initializeInventory() {
    // You can add sample products to the inventory here.
    // For example:
    addProduct(1, "Medicine A", 10.0, 100);
    addProduct(2, "Medicine B", 5.0, 50);
    // Add more products as needed
}

void inventoryMenu() {
    int choice;

    do {
        // Display the inventory menu
        printf("Inventory Menu\n");
        printf("1. Add Product\n");
        printf("2. Remove Product\n");
        printf("3. Update Product\n");
        printf("4. Display Inventory\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int productID;
        char name[50];
        float price;
        int quantity;

        switch (choice) {
            case 1:
                // Add product logic here
                printf("Enter product ID: ");
                scanf("%d", &productID);
                printf("Enter product name: ");
                scanf("%s", name);
                printf("Enter product price: ");
                scanf("%f", &price);
                printf("Enter product quantity: ");
                scanf("%d", &quantity);
                addProduct(productID, name, price, quantity);
                break;
            case 2:
                // Remove product logic here
                printf("Enter product ID to remove: ");
                scanf("%d", &productID);
                removeProduct(productID);
                break;
            case 3:
                // Update product logic here
                printf("Enter product ID to update: ");
                scanf("%d", &productID);
                printf("Enter updated product name: ");
                scanf("%s", name);
                printf("Enter updated product price: ");
                scanf("%f", &price);
                printf("Enter updated product quantity: ");
                scanf("%d", &quantity);
                updateProduct(productID, name, price, quantity);
                break;
            case 4:
                displayInventory();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

void displayInventory() {
    InventoryNode* current = inventoryHead;
    printf("Inventory:\n");
    printf("Product ID\tName\t\tPrice\tQuantity\n");

    while (current != NULL) {
        printf("%d\t\t%s\t\t%.2f\t%d\n", current->product.productID, current->product.name, current->product.price, current->product.quantity);
        current = current->next;
    }
}

int addProduct(int productID, const char* name, float price, int quantity) {
    // Create a new product node
    InventoryNode* newNode = (InventoryNode*)malloc(sizeof(InventoryNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 0; // Return 0 to indicate failure
    }

    // Fill in the product details
    newNode->product.productID = productID;
    strncpy(newNode->product.name, name, sizeof(newNode->product.name));
    newNode->product.price = price;
    newNode->product.quantity = quantity;

    // Add the new product to the inventory
    newNode->next = inventoryHead;
    inventoryHead = newNode;

    return 1; // Return 1 to indicate success
}

int removeProduct(int productID) {
    InventoryNode* current = inventoryHead;
    InventoryNode* prev = NULL;

    while (current != NULL) {
        if (current->product.productID == productID) {
            // Found the product, remove it from the list
            if (prev == NULL) {
                // The product is at the head of the list
                inventoryHead = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            return 1; // Product successfully removed
        }

        prev = current;
        current = current->next;
    }

    return 0; // Product not found, removal failed
}

int updateProduct(int productID, const char* name, float price, int quantity) {
    InventoryNode* current = inventoryHead;

    while (current != NULL) {
        if (current->product.productID == productID) {
            // Found the product, update its details
            strncpy(current->product.name, name, sizeof(current->product.name));
            current->product.price = price;
            current->product.quantity = quantity;
            return 1; // Product successfully updated
        }

        current = current->next;
    }

    return 0; // Product not found, update failed
}

Product* findProduct(int productID) {
    InventoryNode* current = inventoryHead;

    while (current != NULL) {
        if (current->product.productID == productID) {
            // Found the product, return a pointer to it
            return &(current->product);
        }

        current = current->next;
    }

    // Product not found, return NULL
    return NULL;
}
