#include "ParkingLot.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// --- ParkingSlot Implementation ---

ParkingSlot::ParkingSlot(int id) : slotId(id), isOccupied(false), parkedVehicle(nullptr) {}

int ParkingSlot::getSlotId() const { return slotId; }
bool ParkingSlot::getIsOccupied() const { return isOccupied; }
Vehicle* ParkingSlot::getParkedVehicle() const { return parkedVehicle.get(); }

void ParkingSlot::parkVehicle(std::unique_ptr<Vehicle> vehicle) {
    parkedVehicle = std::move(vehicle);
    isOccupied = true;
}

std::unique_ptr<Vehicle> ParkingSlot::removeVehicle() {
    isOccupied = false;
    return std::move(parkedVehicle);
}

// --- ParkingLot Implementation ---

ParkingLot::ParkingLot(int totalSlots) : totalRevenue(0.0) {
    for (int i = 1; i <= totalSlots; ++i) {
        slots.emplace_back(i);
    }
    loadRecords(); // Load existing records upon startup
}

ParkingLot::~ParkingLot() {
    saveRecords(); // Persist data when system exits
}

double ParkingLot::calculateFee(const Vehicle* vehicle) const {
    std::time_t exitTime = std::time(nullptr);
    double durationSeconds = std::difftime(exitTime, vehicle->getEntryTime());
    
    // For demonstration purposes, we calculate per hour, minimum 1 hour.
    // 3600 seconds = 1 hour.
    double hours = durationSeconds / 3600.0;
    if (hours < 1.0) hours = 1.0; 
    
    double ratePerHour = 0.0;
    switch (vehicle->getType()) {
        case VehicleType::BIKE: ratePerHour = 10.0; break;
        case VehicleType::CAR:  ratePerHour = 20.0; break;
        case VehicleType::TRUCK: ratePerHour = 50.0; break;
    }
    
    return hours * ratePerHour;
}

bool ParkingLot::parkVehicle(const std::string& regNum, VehicleType type) {
    // Check if the vehicle is already parked
    for (const auto& slot : slots) {
        if (slot.getIsOccupied() && slot.getParkedVehicle()->getRegistrationNumber() == regNum) {
            std::cout << "Vehicle with registration number " << regNum << " is already parked.\n";
            return false;
        }
    }

    // Find the first available slot
    for (auto& slot : slots) {
        if (!slot.getIsOccupied()) {
            slot.parkVehicle(std::make_unique<Vehicle>(regNum, type));
            std::cout << "Vehicle parked successfully at slot " << slot.getSlotId() << ".\n";
            saveRecords(); // Save state immediately
            return true;
        }
    }
    
    std::cout << "Parking lot is full!\n";
    return false;
}

bool ParkingLot::removeVehicle(const std::string& regNum) {
    for (auto& slot : slots) {
        if (slot.getIsOccupied() && slot.getParkedVehicle()->getRegistrationNumber() == regNum) {
            double fee = calculateFee(slot.getParkedVehicle());
            totalRevenue += fee;
            
            std::cout << "Vehicle removed successfully from slot " << slot.getSlotId() << ".\n";
            std::cout << "Parking Fee: $" << std::fixed << std::setprecision(2) << fee << "\n";
            
            slot.removeVehicle();
            saveRecords(); // Save state immediately
            return true;
        }
    }
    
    std::cout << "Vehicle with registration number " << regNum << " not found.\n";
    return false;
}

void ParkingLot::viewAvailableSlots() const {
    int availableCount = 0;
    std::cout << "Available Slots: ";
    for (const auto& slot : slots) {
        if (!slot.getIsOccupied()) {
            std::cout << slot.getSlotId() << " ";
            availableCount++;
        }
    }
    std::cout << "\nTotal available: " << availableCount << "\n";
}

void ParkingLot::searchVehicle(const std::string& regNum) const {
    for (const auto& slot : slots) {
        if (slot.getIsOccupied() && slot.getParkedVehicle()->getRegistrationNumber() == regNum) {
            const Vehicle* v = slot.getParkedVehicle();
            std::cout << "Vehicle Found!\n";
            std::cout << "Slot Number: " << slot.getSlotId() << "\n";
            std::cout << "Registration: " << v->getRegistrationNumber() << "\n";
            std::cout << "Type: " << v->getTypeString() << "\n";
            
            std::time_t entryTime = v->getEntryTime();
            std::cout << "Entry Time: " << std::asctime(std::localtime(&entryTime)); // asctime includes newline
            return;
        }
    }
    std::cout << "Vehicle with registration number " << regNum << " not found.\n";
}

void ParkingLot::displayAllVehicles() const {
    bool isEmpty = true;
    std::cout << std::left << std::setw(10) << "Slot" 
              << std::setw(20) << "Registration" 
              << std::setw(15) << "Type" << "\n";
    std::cout << std::string(45, '-') << "\n";

    for (const auto& slot : slots) {
        if (slot.getIsOccupied()) {
            isEmpty = false;
            const Vehicle* v = slot.getParkedVehicle();
            std::cout << std::left << std::setw(10) << slot.getSlotId()
                      << std::setw(20) << v->getRegistrationNumber()
                      << std::setw(15) << v->getTypeString() << "\n";
        }
    }
    if (isEmpty) {
        std::cout << "No vehicles currently parked.\n";
    }
}

void ParkingLot::showTotalRevenue() const {
    std::cout << "Total Revenue Collected: $" << std::fixed << std::setprecision(2) << totalRevenue << "\n";
}

void ParkingLot::saveRecords() const {
    std::ofstream outFile(dataFile);
    if (!outFile) {
        std::cerr << "Error opening file to save records.\n";
        return;
    }
    
    // Save total revenue on the first line
    outFile << totalRevenue << "\n";
    
    // Save occupied slots
    for (const auto& slot : slots) {
        if (slot.getIsOccupied()) {
            const Vehicle* v = slot.getParkedVehicle();
            outFile << slot.getSlotId() << " "
                    << v->getRegistrationNumber() << " "
                    << v->getTypeString() << " "
                    << v->getEntryTime() << "\n";
        }
    }
}

void ParkingLot::loadRecords() {
    std::ifstream inFile(dataFile);
    if (!inFile) {
        // File might not exist yet, which is expected on first run
        return;
    }
    
    std::string line;
    // Read total revenue
    if (std::getline(inFile, line)) {
        try {
            totalRevenue = std::stod(line);
        } catch (...) {
            totalRevenue = 0.0;
        }
    }
    
    // Read slots
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        int slotId;
        std::string regNum, typeStr;
        std::time_t entryTime;
        
        if (iss >> slotId >> regNum >> typeStr >> entryTime) {
            // Find the slot and park the vehicle
            for (auto& slot : slots) {
                if (slot.getSlotId() == slotId) {
                    slot.parkVehicle(std::make_unique<Vehicle>(regNum, Vehicle::getTypeFromString(typeStr), entryTime));
                    break;
                }
            }
        }
    }
}
