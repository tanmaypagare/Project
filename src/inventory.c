#include <stdio.h>
#include <string.h>
#include "../include/inventory.h"

#define FILE_NAME "inventory.dat"

// Check duplicate ID
int id_exists(int id) {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;

    Item temp;
    while (fread(&temp, sizeof(Item), 1, fp)) {
        if (temp.id == id && temp.is_deleted == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int add_item(const Item item) {
    if (id_exists(item.id)) return 0;

    FILE* fp = fopen(FILE_NAME, "ab");
    if (!fp) return 0;

    fwrite(&item, sizeof(Item), 1, fp);
    fclose(fp);
    return 1;
}

int get_item(int id, Item* out) {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;

    Item temp;
    while (fread(&temp, sizeof(Item), 1, fp)) {
        if (temp.id == id && temp.is_deleted == 0) {
            *out = temp;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int update_item(int id, const Item* updated) {
    FILE* fp = fopen(FILE_NAME, "rb+");
    if (!fp) return 0;

    Item temp;
    while (fread(&temp, sizeof(Item), 1, fp)) {
        if (temp.id == id && temp.is_deleted == 0) {
            fseek(fp, -sizeof(Item), SEEK_CUR);
            fwrite(updated, sizeof(Item), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int delete_item(int id) {
    FILE* fp = fopen(FILE_NAME, "rb+");
    if (!fp) return 0;

    Item temp;
    while (fread(&temp, sizeof(Item), 1, fp)) {
        if (temp.id == id && temp.is_deleted == 0) {
            temp.is_deleted = 1;
            fseek(fp, -sizeof(Item), SEEK_CUR);
            fwrite(&temp, sizeof(Item), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int list_items(Item* buffer, int max_items) {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;

    Item temp;
    int count = 0;

    while (fread(&temp, sizeof(Item), 1, fp)) {
        if (temp.is_deleted == 0 && count < max_items) {
            buffer[count++] = temp;
        }
    }

    fclose(fp);
    return count;
}
