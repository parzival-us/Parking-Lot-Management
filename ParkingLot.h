#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include "Vehicle.h"
#include <vector>
#include <memory>
#include <string>

// Represents an individual slot in the parking lot
class ParkingSlot {
private:
    int slotId;
    bool isOccupied;
    std::unique_ptr<Vehicle> parkedVehicle;

public:
    ParkingSlot(int id);
    
    int getSlotId() const;
    bool getIsOccupied() const;
    Vehicle* getParkedVehicle() const;
    
    void parkVehicle(std::unique_ptr<Vehicle> vehicle);
    std::unique_ptr<Vehicle> removeVehicle();
};

// Manages the entire parking lot system
class ParkingLot {
private:
    std::vector<ParkingSlot> slots;
    double totalRevenue;
    const std::string dataFile = "parking_records.txt";

    // Helper to calculate fee based on vehicle type and time
    double calculateFee(const Vehicle* vehicle) const;

public:
    ParkingLot(int totalSlots);
    ~ParkingLot(); // Destructor saves records automatically
    
    // Core functionalities
    bool parkVehicle(const std::string& regNum, VehicleType type);
    bool removeVehicle(const std::string& regNum);
    void viewAvailableSlots() const;
    void searchVehicle(const std::string& regNum) const;
    void displayAllVehicles() const;
    void showTotalRevenue() const;
    
    // Persistence functionalities
    void saveRecords() const;
    void loadRecords();
};

#endif // PARKING_LOT_H
