#ifndef SALES_H
#define SALES_H

// Structure for a sales transaction
typedef struct {
    int transactionID;
    char customerName[50];
    float totalAmount;
} SalesTransaction;

// Function declarations
void initializeSales();
void salesMenu();
void recordSale(const char* customerName, int productID, int quantity);
void recordSaleMenu();
void displaySalesReport();
float calculateTotalSales();

#endif
