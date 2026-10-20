#include "PetServices.h"

PetServicesManager::PetServicesManager() {
    
    availableServices.push_back({101, "General Health Checkup", "City Vet Clinic", 500.0, "01700000000"});
    availableServices.push_back({102, "Full Pet Grooming & Bath", "Paws & Care Spa", 800.0, "01800000000"});
    availableServices.push_back({103, "Pet Boarding (Per Day)", "Happy Tails Daycare", 1000.0, "01900000000"});
}

void PetServicesManager::displayServices() const {
    cout << "\n=================================== AVAILABLE PET SERVICES ===================================\n";
    for (const auto& s : availableServices) {
        cout << "ID: " << s.serviceId 
             << " | Service: " << s.serviceName 
             << " | Provider: " << s.providerName 
             << " | Fee: " << s.price << " BDT"
             << " | Contact: " << s.contactNumber << "\n";
    }
    cout << "=============================================================================================\n";
}

void PetServicesManager::addService() {
    Service s;
    cout << "\n--- Add New Service ---\n";
    cout << "Enter Service ID: ";
    cin >> s.serviceId;
    cin.ignore();
    cout << "Enter Service Name: ";
    getline(cin, s.serviceName);
    cout << "Enter Provider Name: ";
    getline(cin, s.providerName);
    cout << "Enter Service Fee (BDT): ";
    cin >> s.price;
    cin.ignore();
    cout << "Enter Contact Number: ";
    getline(cin, s.contactNumber);

    availableServices.push_back(s);
    cout << ">> New Service added successfully!\n";
}

void PetServicesManager::bookService(int serviceId) const {
    for (const auto& s : availableServices) {
        if (s.serviceId == serviceId) {
            cout << "\n>> Service Booking Request Received!";
            cout << "\n   Service: " << s.serviceName;
            cout << "\n   Provider: " << s.providerName;
            cout << "\n   Total Fee: " << s.price << " BDT";
            cout << "\n   Please call " << s.contactNumber << " to confirm appointment time.\n";
            return;
        }
    }
    cout << ">> Invalid Service ID!\n";
}
