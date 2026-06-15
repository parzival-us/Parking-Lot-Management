#include <iostream>
#include <string>
#include <limits>
#include "ParkingLot.h"

// Helper function to display the main menu
void displayMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "      Parking Lot Management System      \n";
    std::cout << "=========================================\n";
    std::cout << "1. Park Vehicle\n";
    std::cout << "2. Remove Vehicle\n";
    std::cout << "3. View Available Slots\n";
    std::cout << "4. Search Vehicle by Registration Number\n";
    std::cout << "5. Display All Parked Vehicles\n";
    std::cout << "6. Show Total Revenue\n";
    std::cout << "7. Exit\n";
    std::cout << "=========================================\n";
    std::cout << "Enter your choice (1-7): ";
}

// Helper function to handle and validate integer input
int getValidChoice() {
    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > 7) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter a number between 1 and 7: ";
    }
    return choice;
}

int main() {
    // Initialize the parking lot with a total of 50 slots
    ParkingLot parkingLot(50);
    bool running = true;

    while (running) {
        displayMenu();
        int choice = getValidChoice();

        switch (choice) {
            case 1: {
                std::string regNum;
                int typeChoice;
                std::cout << "Enter Registration Number: ";
                std::cin >> regNum;
                
                std::cout << "Select Vehicle Type (1: Bike, 2: Car, 3: Truck): ";
                while (!(std::cin >> typeChoice) || typeChoice < 1 || typeChoice > 3) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Select (1: Bike, 2: Car, 3: Truck): ";
                }
                
                VehicleType type = VehicleType::CAR; // Default
                if (typeChoice == 1) type = VehicleType::BIKE;
                else if (typeChoice == 2) type = VehicleType::CAR;
                else if (typeChoice == 3) type = VehicleType::TRUCK;
                
                parkingLot.parkVehicle(regNum, type);
                break;
            }
            case 2: {
                std::string regNum;
                std::cout << "Enter Registration Number of vehicle to remove: ";
                std::cin >> regNum;
                parkingLot.removeVehicle(regNum);
                break;
            }
            case 3:
                parkingLot.viewAvailableSlots();
                break;
            case 4: {
                std::string regNum;
                std::cout << "Enter Registration Number to search: ";
                std::cin >> regNum;
                parkingLot.searchVehicle(regNum);
                break;
            }
            case 5:
                parkingLot.displayAllVehicles();
                break;
            case 6:
                parkingLot.showTotalRevenue();
                break;
            case 7:
                std::cout << "Exiting system. Data saved. Have a nice day!\n";
                running = false;
                break;
            default:
                std::cout << "Unknown error occurred.\n";
                break;
        }
    }

    return 0;
}
