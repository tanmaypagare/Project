#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "../include/inventory.h"

class InventoryManager {
public:
    void addItem();
    void viewItem();
    void updateItem();
    void deleteItem();
    void listItems();
};

void InventoryManager::addItem() {
    Item item;
    std::cout << "Enter ID: ";
    std::cin >> item.id;

    if (item.id <= 0) {
        std::cout << "Invalid ID\n";
        return;
    }

    std::cout << "Enter name: ";
    std::cin.ignore();
    std::cin.getline(item.name, 40);

    if (strlen(item.name) == 0) {
        std::cout << "Name cannot be empty\n";
        return;
    }

    std::cout << "Enter quantity: ";
    std::cin >> item.quantity;
    if (item.quantity < 0) {
        std::cout << "Invalid quantity\n";
        return;
    }

    std::cout << "Enter price: ";
    std::cin >> item.price;
    if (item.price < 0) {
        std::cout << "Invalid price\n";
        return;
    }

    item.is_deleted = 0;

    if (add_item(item))
        std::cout << "Item added\n";
    else
        std::cout << "Failed (duplicate ID?)\n";
}

void InventoryManager::viewItem() {
    int id;
    std::cout << "Enter ID: ";
    std::cin >> id;

    Item item;
    if (get_item(id, &item)) {
        std::cout << "ID: " << item.id << "\nName: " << item.name
                  << "\nQty: " << item.quantity << "\nPrice: " << item.price << "\n";
    } else {
        std::cout << "Item not found\n";
    }
}

void InventoryManager::updateItem() {
    int id;
    std::cout << "Enter ID to update: ";
    std::cin >> id;

    Item item;
    if (!get_item(id, &item)) {
        std::cout << "Item not found\n";
        return;
    }

    std::cout << "Enter new name: ";
    std::cin.ignore();
    std::cin.getline(item.name, 40);

    std::cout << "Enter new quantity: ";
    std::cin >> item.quantity;

    std::cout << "Enter new price: ";
    std::cin >> item.price;

    if (update_item(id, &item))
        std::cout << "Updated successfully\n";
    else
        std::cout << "Update failed\n";
}

void InventoryManager::deleteItem() {
    int id;
    std::cout << "Enter ID: ";
    std::cin >> id;

    if (delete_item(id))
        std::cout << "Deleted\n";
    else
        std::cout << "Not found\n";
}

void InventoryManager::listItems() {
    std::vector<Item> items(100);

    int count = list_items(items.data(), 100);
    items.resize(count);

    std::sort(items.begin(), items.end(), [](Item a, Item b) {
        return a.id < b.id;
    });

    for (const auto& item : items) {
        std::cout << "ID: " << item.id
                  << " | Name: " << item.name
                  << " | Qty: " << item.quantity
                  << " | Price: " << item.price << "\n";
    }
}
