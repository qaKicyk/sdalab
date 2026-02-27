#include <stdio.h>
#include <string.h>
#include <windows.h>

#define STR_LEN 50

typedef struct {
    char name[STR_LEN];
    float price;
    int quantity;
    char supplier[STR_LEN];
    char expiry_date[STR_LEN];
} Product;



void rellocateInv(Product** sof, int current, int NewCount);
void removeLast(Product** inventory, int*count);
void addProduct(Product** inventory, int* count);
void freeInv(Product** inventory, int*count);
void displayInventory(Product* inventory, int count);
void editProduct(Product* inventory, int count);
void searchByPrice(Product* inventory, int count);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Product* inventory=NULL;
    int count = 0;
    int choice;

    while (1) {
        printf("1. Добавить товар\n");
        printf("2. Вывести весь список\n");
        printf("3. Редактировать товар\n");
        printf("4. Поиск по цене\n");
        printf("5. Удалить последний товар\n");
        printf("6. Очистить весь списиок\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1: addProduct(&inventory, &count); break;
            case 2: displayInventory(inventory, count); break;
            case 3: editProduct(inventory, count); break;
            case 4: searchByPrice(inventory, count); break;
            case 5: removeLast(&inventory, &count);break;
            case 6: freeInv(&inventory, &count);break;
            case 0:
               freeInv(&inventory,&count);
               return 0;
            default: printf("Неверный выбор!\n");
        }
    }
}

void rellocateInv(Product** sof, int current, int NewCount){
    if (NewCount==0){
        free(*sof);
        *sof=NULL;
        return;
    }
    Product* newArray=(Product*)malloc(NewCount*sizeof(Product));
    if (newArray==NULL) return;
    
    if (*sof!=0){
        int toCopy=(current<NewCount) ? current : NewCount;
        for (int i=0; i < toCopy; i++) {
            newArray[i]=(*sof)[i];
        }
        free(*sof);
    }
    *sof=newArray;
}

void addProduct(Product** inventory, int*count) {
    rellocateInv(inventory, *count, *count+1);
    Product* p = &((*inventory)[*count]); 
    
    printf("Название:");
    scanf(" %[^\n]", p->name);
    printf("Цена:");
    scanf("%f", &p->price);
    printf("Количество:");
    scanf("%d", &p->quantity);
    printf("Поставщик:");
    scanf(" %[^\n]", p->supplier);
    printf("Срок годности:");
    scanf(" %[^\n]", p->expiry_date);
    
    (*count)++;
    printf("Товар добавлен, Память расширена\n");
}

void removeLast(Product** inventory, int*count){
    if(*count<=0){
        printf("Список пуст\n");
        return;
    }
    rellocateInv(inventory, *count, *count-1);
    (*count)--;
    printf("Последний товар удален, размер уменьшен\n");
}

void freeInv(Product** inventory, int* count){
    if (*inventory!=NULL){
        rellocateInv(inventory, *count, 0);
        *count=0;
        printf("Память очищена\n");
    }
}

void displayInventory(Product* inventory, int count) {
    if (count == 0 || inventory==NULL) {
        printf("Инвентарь пуст.\n");
        return;
    }
    printf("\n%-3s | %-15s | %-10s | %-5s | %-15s | %-10s\n", "ID", "Название", "Цена", "Кол.", "Поставщик", "Годен до");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-3d | %-15s | %-10.2f | %-5d | %-15s | %-10s\n", 
               i, inventory[i].name, inventory[i].price, inventory[i].quantity, 
               inventory[i].supplier, inventory[i].expiry_date);
    }
}

void editProduct(Product* inventory, int count) {
    if (count<=0) {
        printf("Нечего редактировать\n");
        return;
    }

    int idx, field;
    printf("Введите индекс товара (0-%d): ", count - 1);
    scanf("%d", &idx);
    if (idx < 0 || idx >= count) {
        printf("Неверный индекс!\n");
        return;
    }

    printf("Что изменить? 1-Название, 2-Цена, 3-Кол-во, 4-Поставщик, 5-Срок: ");
    scanf("%d", &field);

    switch (field) {
    case 1: 
            printf("Новое название: "); 
            scanf(" %[^\n]", inventory[idx].name);
            break;
    case 2: 
            printf("Новая цена: "); 
            scanf(" %f", &inventory[idx].price); 
            break;
    case 3: 
            printf("Новое кол-во: "); 
            scanf(" %d", &inventory[idx].quantity); 
            break;
    case 4: 
            printf("Новый поставщик: "); 
            scanf(" %[^\n]", inventory[idx].supplier);
            break;
    case 5: 
            printf("Новый срок годности: "); 
            scanf(" %[^\n]", inventory[idx].expiry_date);
            break;
    default: printf("Ошибка выбора поля.\n");
    }
}


void searchByPrice(Product* inventory, int count) {
    if (count<=0){
        printf("Список пуст\n");
        return;
    }
    float max_p;
    printf("Показать товары дешевле чем: ");
    scanf("%f", &max_p);
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (inventory[i].price <= max_p) {
            printf("- %s (%.2f руб.)\n", inventory[i].name, inventory[i].price);
            found = 1;
        }
    }
    if (!found) printf("Товары не найдены.\n");
}
