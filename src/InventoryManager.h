#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "../include/inventory.h"

class InventoryManager {
public:
    void addItem();
    void viewItem();
    void updateItem();
    void deleteItem();
    void listItems();
};

#endif
