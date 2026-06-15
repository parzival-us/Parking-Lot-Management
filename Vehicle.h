#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>

// Enumeration for supported vehicle types
enum class VehicleType {
    BIKE,
    CAR,
    TRUCK
};

// Vehicle class encapsulates vehicle details
class Vehicle {
private:
    std::string registrationNumber;
    VehicleType type;
    std::time_t entryTime;

public:
    // Constructor with default parameter for current time
    Vehicle(std::string regNum, VehicleType type, std::time_t entryTime = std::time(nullptr));
    
    // Getters
    std::string getRegistrationNumber() const;
    VehicleType getType() const;
    std::time_t getEntryTime() const;
    
    // Utility methods for file persistence and display
    std::string getTypeString() const;
    static VehicleType getTypeFromString(const std::string& typeStr);
};

#endif // VEHICLE_H
