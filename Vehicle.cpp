#include "Vehicle.h"
#include <algorithm>

Vehicle::Vehicle(std::string regNum, VehicleType type, std::time_t entryTime)
    : registrationNumber(regNum), type(type), entryTime(entryTime) {}

std::string Vehicle::getRegistrationNumber() const {
    return registrationNumber;
}

VehicleType Vehicle::getType() const {
    return type;
}

std::time_t Vehicle::getEntryTime() const {
    return entryTime;
}

std::string Vehicle::getTypeString() const {
    switch (type) {
        case VehicleType::BIKE: return "Bike";
        case VehicleType::CAR: return "Car";
        case VehicleType::TRUCK: return "Truck";
        default: return "Unknown";
    }
}

VehicleType Vehicle::getTypeFromString(const std::string& typeStr) {
    std::string lowerTypeStr = typeStr;
    // Convert to lowercase for case-insensitive matching
    std::transform(lowerTypeStr.begin(), lowerTypeStr.end(), lowerTypeStr.begin(), ::tolower);
    
    if (lowerTypeStr == "bike") return VehicleType::BIKE;
    if (lowerTypeStr == "car") return VehicleType::CAR;
    if (lowerTypeStr == "truck") return VehicleType::TRUCK;
    
    return VehicleType::CAR; // Default fallback
}
