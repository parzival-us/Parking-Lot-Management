# Parking Lot Management System

A complete C++ console-based Parking Lot Management System built using Object-Oriented Programming (OOP) principles.

## Features

1. **Park Vehicle**: Automatically assigns the first available slot to a new vehicle (Bike, Car, or Truck).
2. **Remove Vehicle**: Removes a vehicle using its registration number and calculates the parking fee based on the duration and vehicle type.
3. **View Available Slots**: Lists all currently empty slots.
4. **Search Vehicle**: Find a parked vehicle using its registration number.
5. **Display All Parked Vehicles**: View a tabular list of all currently parked vehicles.
6. **Show Total Revenue**: Display the total parking fees collected so far.
7. **Persistent Storage**: Parking records and total revenue are automatically saved to `parking_records.txt` and loaded upon startup.

## Requirements

- C++17 or higher
- A C++ compiler like `g++` (GCC), `clang++`, or MSVC

## Compilation

To compile the code, navigate to the project directory in your terminal and run the following command:

```bash
g++ -std=c++17 main.cpp Vehicle.cpp ParkingLot.cpp -o ParkingLotSystem
```

## Usage

After compiling, run the generated executable:

```bash
# On Windows
./ParkingLotSystem.exe

# On Linux / macOS
./ParkingLotSystem
```

Follow the on-screen menu instructions. Entering an invalid option will prompt you to try again.

### Fee Structure
- **Bike**: $10.00 / hour
- **Car**: $20.00 / hour
- **Truck**: $50.00 / hour

*(Note: The minimum fee charged is for 1 hour, even if parked for a shorter duration.)*
