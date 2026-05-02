# Inventory Manager (C + C++)

A hybrid inventory management system with C backend for data persistence and C++ frontend for user interface.

## Project Architecture

### C Backend (`src/inventory.c` + `include/inventory.h`)
- Binary file storage (`inventory.dat`)
- Core CRUD operations using `fread/fwrite` and file seeking
- Soft delete implementation (items marked as deleted but not removed)
- Duplicate ID detection
- Functions exposed: `add_item`, `get_item`, `update_item`, `delete_item`, `list_items`

### C++ Frontend (`src/InventoryManager.cpp` + `src/InventoryManager.h` + `src/main.cpp`)
- `InventoryManager` class wrapping C functions
- Interactive console menu
- Uses `std::vector` for temporary item storage
- Uses `std::sort` for sorting items by ID
- Input validation for all operations
- User-friendly formatted output

## Data Structure

Each inventory item contains:
```
int id              (positive, unique)
char name[40]       (non-empty)
int quantity        (0 or more)
float price         (0 or more)
int is_deleted      (0 = active, 1 = deleted)
```

## Features

1. **Add Item** - Store new item with unique ID and details
2. **View Item** - Look up and display a single item by ID
3. **Update Item** - Modify quantity and price of existing item
4. **Delete Item** - Soft delete (marks as deleted, not removed from file)
5. **List All** - Display all active items sorted by ID
6. **Persistent Storage** - All data saved to binary file, survives application restart

## Build Instructions

**Users cloning this repository must build from source code. Do NOT rely on pre-built binaries.**

### Option 1: Windows (PowerShell/Command Prompt) - No Make Required
```powershell
cd d:\Imarticus-Project
gcc -c src/inventory.c -o src/inventory.o
g++ -c -std=c++11 src/InventoryManager.cpp -o src/InventoryManager.o
g++ -c -std=c++11 src/main.cpp -o src/main.o
g++ src/inventory.o src/InventoryManager.o src/main.o -o app.exe
```

### Option 2: Linux/WSL with Make
```bash
cd d/Imarticus-Project
make
./app
```

### Option 3: macOS/Linux Without Make
```bash
cd d/Imarticus-Project
gcc -c src/inventory.c -o src/inventory.o
g++ -c -std=c++11 src/InventoryManager.cpp -o src/InventoryManager.o
g++ -c -std=c++11 src/main.cpp -o src/main.o
g++ src/inventory.o src/InventoryManager.o src/main.o -o app
./app
```

## Run the Application

After building (see Build Instructions above):

### Windows:
```powershell
.\app.exe
```

### Linux/macOS:
```bash
./app
```

The application will start an interactive menu. Your inventory data will be automatically saved to `inventory.dat` in the project directory.

### Clean Build (Remove Compiled Files)
```bash
# On Windows with Make installed
make clean

# Manual cleanup
del src\*.o app.exe inventory.dat
```

---

## Files Overview

| File | Purpose |
|------|---------|
| `include/inventory.h` | C header with struct and function declarations |
| `src/inventory.c` | C implementation: file I/O, CRUD operations |
| `src/InventoryManager.h` | C++ class header |
| `src/InventoryManager.cpp` | C++ implementation: menu, input validation, sorting |
| `src/main.cpp` | Main program entry point |
| `Makefile` | Build configuration (Linux/WSL) |
| `.gitignore` | Excludes compiled files and generated data |
| `README.md` | This file |

**Generated during runtime (not tracked in Git):**
- `src/*.o` - Object files (deleted by `make clean`)
- `app.exe` / `app` - Executable (deleted by `make clean`)
- `inventory.dat` - Persistent data file (user's inventory data)

---

## Menu Options

```
====================================
1. Add Item
2. View Item  
3. Update Item
4. Delete Item
5. List All Items
6. Exit
====================================
```

## Input Validation

The application validates all user inputs:
- **ID**: Must be positive (> 0)
- **Name**: Cannot be empty
- **Quantity**: Must be 0 or more
- **Price**: Must be 0 or more
- **Duplicates**: System rejects duplicate IDs

Invalid inputs trigger error messages and prompt for re-entry.

## Test Cases

### Test 1: Add Multiple Items and Verify Persistence
- Add 3 items with different IDs (e.g., 1, 2, 3)
- Exit application (choose option 6)
- Restart application
- List all items (option 5)
- **Expected**: All 3 items appear with correct data ✔

### Test 2: Update Item and Verify After Restart
- Add item with ID=1, Name="Laptop", Qty=5, Price=1200.00
- Exit and restart
- Update ID=1: Change Qty to 10, Price to 1100.00
- Exit and restart
- View item by ID=1
- **Expected**: Updated values persist (Qty=10, Price=1100.00) ✔

### Test 3: Soft Delete - Item Not Visible After Delete
- Add 2 items (ID=1 "Mouse", ID=2 "Keyboard")
- Delete item ID=1 (option 4)
- List all items (option 5)
- **Expected**: Only ID=2 appears, ID=1 is hidden ✔

### Test 4: Duplicate ID Rejection
- Add item with ID=100, Name="Monitor"
- Try adding another item with ID=100
- **Expected**: System shows "Failed (duplicate ID?)" message ✔

### Test 5: Invalid Input Handling
- Try adding item with negative quantity
- **Expected**: System rejects with "Invalid quantity" message
- Try adding item with empty name
- **Expected**: System rejects with "Name cannot be empty" message
- Try updating with negative price
- **Expected**: System rejects with "Invalid price" message ✔

## Technical Requirements Met

✅ Binary file storage with `fread`/`fwrite`
✅ File seeking with `fseek` for updates/deletes
✅ Soft delete implementation (is_deleted flag)
✅ C backend with exposed functions
✅ C++ class wrapper with STL usage
✅ Multi-file build with proper compilation
✅ Input validation with error handling
✅ Persistent data storage
✅ README with build/run instructions and test cases
