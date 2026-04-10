#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 50
#define FILE_NAME "inventory.bin"

typedef struct {
    char name[STR_LEN];
    float price;
    int quantity;
    char supplier[STR_LEN];
    char expiry_date[STR_LEN];
} Product;


void rellocateInv(Product** sof, int current, int NewCount);
void saveToFile(Product* inventory, int count);
void loadFromFile(Product** inventory, int* count);
void addProduct(Product** inventory, int* count);
void editProduct(Product* inventory, int count);
void insProduct(Product** inventory, int* count);
void searchProduct(Product* inventory, int count);
void removeLast(Product** inventory, int* count);
void removeA(Product** inventory, int* count);
void sort(Product* inventory, int count);
void displayInventory(Product* inventory, int count);
void freeInv(Product** inventory, int* count);
void loadFromFile(Product** inventory, int* count);
void saveToFile(Product* inventory, int count);

#endif