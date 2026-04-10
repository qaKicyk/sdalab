#include "data.h"

void saveToFile(Product* inventory, int count) {
    FILE* f = fopen(FILE_NAME, "wb");
    if (f) {
        fwrite(&count, sizeof(int), 1, f);
        fwrite(inventory, sizeof(Product), count, f);
        fclose(f);
        printf("Данные сохранены.\n");
    }
}

void loadFromFile(Product** inventory, int* count) {
    FILE* f = fopen(FILE_NAME, "rb");
    if (!f) return;
    int newCount;
    fread(&newCount, sizeof(int), 1, f);
    rellocateInv(inventory, 0, newCount);
    fread(*inventory, sizeof(Product), newCount, f);
    *count = newCount;
    fclose(f);
    printf("Данные загружены.\n");
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

void searchProduct(Product* inventory, int count){
    if (count <= 0 || inventory == NULL) {
        printf("Инвентарь пуст.\n");
        return;
    }
    int type;
    printf("Критерий поиска: 1 - По названию/поставщику, 2 - По цене (дешевле чем): ");
    scanf("%d", &type);

    char names[STR_LEN];
    float maxPrice;
    int found = 0;

    if (type==1){
        printf("Введите наззвание или потсавщика для поиска");
        scanf(" %[^\n]",names);
    }
    else if (type==2){
        printf("Введите максимальную цену: ");
        scanf(" %f",&maxPrice);
    }
    else {
        printf("Неверный выбор");
        return;
    }

    printf("Результаты поиска:\n");
    for(int i=0;i<count;i++){
        int mat=0;

        if (type==1){
            if(strstr(inventory[i].name,names)||strstr(inventory[i].supplier,names)){
                mat=1;
            }
        }
        else{
            if(inventory[i].price<=maxPrice){
                mat=1;
            }
        }
        if(mat){
            printf("ID %d: %-15s | Цена: %-8.2f | Поставщик: %-15s\n", i,inventory[i].name,inventory[i].price,inventory[i].supplier);
            found=1;
        }
    }
    if (!found) printf("Совпадений не найдено\n");
}

void removeA(Product** inventory, int*count){
   if (*count<=0){
    printf("Список пуст\n");
    return;
   }
   int idx;
   printf("Введите индекс для удаления:",*count-1);
   scanf("%d",&idx);

   if(idx<0||idx>=*count){
    printf("Ошибка!");
    return;
   }

   for (int i=idx;i<*count-1;i++){
    (*inventory)[i]=(*inventory)[i+1];
   }
   rellocateInv(inventory,*count,*count-1);
   (*count)--;
   printf("Товар удален.\n");
}

void insProduct(Product** inventory, int*count){
    int idx;
    printf("Введите позицию для вставки(0-%d)",*count);
    scanf("%d",&idx);

    if(idx<0||idx>*count){
        printf("Неверный индекс!");
        return;
    }
    rellocateInv(inventory,*count,*count+1);
    for(int i=*count;i>idx;i--){
        (*inventory)[i]=(*inventory)[i-1];
    }
    Product* p=&((*inventory)[idx]);
    printf("Название: ");
    scanf(" %[^\n]",p->name);
    printf("Цена: ");
    scanf(" %f",&p->price);
    printf("Количество: ");
    scanf(" %d",&p->quantity);
    printf("Поставщик: ");
    scanf(" %[^\n]",p->supplier);
    printf("Срок годности: ");
    scanf(" %[^\n]",p->expiry_date);

    (*count)++;
    printf("Товар добавлен на позицию %d",idx);
}

void sort(Product* inventory, int count){
    if (count<2){
        printf("Недостаточно элементов для сортировки");
        return;
    }
    int choice;
    printf("Сортировать по: 1-Названию, 2-Цене, 3-Сроку годности: ");
    scanf("%d", &choice);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swapNeeded = 0;
            
            if (choice == 1) {
                if (strcmp(inventory[j].name, inventory[j + 1].name) > 0) swapNeeded = 1;
            } else if (choice == 2) {
                if (inventory[j].price > inventory[j + 1].price) swapNeeded = 1;
            } else if (choice == 3) {
                if (strcmp(inventory[j].expiry_date, inventory[j + 1].expiry_date) > 0) swapNeeded = 1;
            }

            if (swapNeeded) {
                Product temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;
            }
        }
    }
    printf("Сортировка завершена.\n");
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