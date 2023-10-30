#ifndef INVENTORY_H
#define INVENTORY_H

// Structure for a product
typedef struct {
    int productID;
    char name[50];
    float price;
    int quantity;
} Product;

// Function declarations
void initializeInventory();
void inventoryMenu();
void displayInventory();
int addProduct(int productID, const char* name, float price, int quantity);
int removeProduct(int productID);
int updateProduct(int productID, const char* name, float price, int quantity);
Product* findProduct(int productID);

#endif
