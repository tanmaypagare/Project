# Inventory Manager (C + C++)

## Build
make

## Run
./app

## Features
- Add item
- View item
- Update item
- Delete (soft delete)
- Persistent storage using binary file

## Test Cases
- Added 3 items → restarted → data persisted ✔
- Updated item → restart → changes persisted ✔
- Deleted item → not visible ✔
- Duplicate ID rejected ✔
- Invalid inputs handled ✔
