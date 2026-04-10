#include <windows.h>
#include "data.h"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Product* inventory = NULL;
    int count = 0;
    int choice;

    loadFromFile(&inventory, &count); // Автозагрузка

    while (1) {
        printf("1. Добавить товар\n");
        printf("2. Редактировать товар\n");
        printf("3. Вставить товар по индексу\n");
        printf("4. Поиск по критерию\n");
        printf("5. Удалить последний товар\n");
        printf("6. Удалить товар по индексу\n");
        printf("7. Сортировать список\n");
        printf("8. Вывести весь список\n");
        printf("9. Очистить весь список\n");
        printf("10. Загрузить из файла\n");
        printf("11. Сохранить в файл\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1: addProduct(&inventory, &count); break;
            case 2: editProduct(inventory, count); break;
            case 3: insProduct(&inventory, &count); break;
            case 4: searchProduct(inventory, count); break;
            case 5: removeLast(&inventory, &count);break;
            case 6: removeA(&inventory, &count); break;
            case 7: sort(inventory, count); break;
            case 8: displayInventory(inventory, count); break;
            case 9: freeInv(&inventory, &count);break;
            case 10: loadFromFile(&inventory, &count);break;
            case 11: saveToFile(inventory, count);break;

            case 0:
                saveToFile(inventory, count); 
                freeInv(&inventory, &count);
                return 0;

        }
    }
}