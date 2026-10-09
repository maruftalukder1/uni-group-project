#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to store Pet information
struct Pet {
    int id;
    string name;
    string species;
    bool isAdopted;
};

// Structure to store Adoption Application information
struct AdoptionRequest {
    int requestId;
    int petId;
    string adopterName;
    string contactNumber;
    string status; // "Pending", "Approved", "Rejected"
};

class AdoptionSystem {
private:
    vector<Pet> pets;
    vector<AdoptionRequest> requests;
    int nextRequestId = 1001;

public:
    // Sample constructor to populate demo pets
    AdoptionSystem() {
        pets.push_back({1, "Milo", "Cat", false});
        pets.push_back({2, "Buddy", "Dog", false});
        pets.push_back({3, "Luna", "Rabbit", false});
    }

    // 1. Display all available pets for adoption
    void displayAvailablePets() {
        cout << "\n======================================\n";
        cout << "       AVAILABLE PETS FOR ADOPTION    \n";
        cout << "======================================\n";
        bool found = false;
        for (const auto& pet : pets) {
            if (!pet.isAdopted) {
                cout << "Pet ID   : " << pet.id << "\n";
                cout << "Name     : " << pet.name << "\n";
                cout << "Species  : " << pet.species << "\n";
                cout << "--------------------------------------\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No pets are currently available for adoption.\n";
        }
    }

    // 2. Submit an Adoption Application
    void submitAdoptionRequest(int petId, string adopterName, string contact) {
        // Check if pet exists and is available
        bool petExists = false;
        for (const auto& pet : pets) {
            if (pet.id == petId) {
                petExists = true;
                if (pet.isAdopted) {
                    cout << "\n[ERROR] Sorry! Pet ID " << petId << " is already adopted.\n";
                    return;
                }
                break;
            }
        }

        if (!petExists) {
            cout << "\n[ERROR] Invalid Pet ID! Please enter a valid ID.\n";
            return;
        }

        // Create and store request
        AdoptionRequest newReq = {nextRequestId++, petId, adopterName, contact, "Pending"};
        requests.push_back(newReq);

        cout << "\n[SUCCESS] Adoption request submitted successfully!\n";
        cout << "Your Generated Request ID is: " << newReq.requestId << "\n";
    }

    // 3. View All Adoption Applications (Admin / Management View)
    void viewAllRequests() {
        cout << "\n======================================\n";
        cout << "       ALL ADOPTION APPLICATIONS      \n";
        cout << "======================================\n";
        if (requests.empty()) {
            cout << "No adoption applications found.\n";
            return;
        }
        for (const auto& req : requests) {
            cout << "Req ID   : " << req.requestId << " | Pet ID: " << req.petId << "\n";
            cout << "Adopter  : " << req.adopterName << " (" << req.contactNumber << ")\n";
            cout << "Status   : " << req.status << "\n";
            cout << "--------------------------------------\n";
        }
    }

    // 4. Process Application (Approve or Reject)
    void processRequest(int reqId, bool approve) {
        for (auto& req : requests) {
            if (req.requestId == reqId) {
                if (req.status != "Pending") {
                    cout << "\n[NOTICE] This request has already been processed as: " << req.status << "\n";
                    return;
                }

                if (approve) {
                    bool petFound = false;
                    for (auto& pet : pets) {
                        if (pet.id == req.petId) {
                            petFound = true;
                            if (pet.isAdopted) {
                                req.status = "Rejected";
                                cout << "\n[INFO] Request ID " << reqId
                                     << " REJECTED. Pet is already adopted.\n";
                                return;
                            }
                            pet.isAdopted = true;
                            break;
                        }
                    }
                    if (!petFound) {
                        cout << "\n[ERROR] Cannot process request. Pet record not found.\n";
                        return;
                    }
                    req.status = "Approved";
                    cout << "\n[SUCCESS] Request ID " << reqId << " APPROVED! Pet marked as adopted.\n";
                } else {
                    req.status = "Rejected";
                    cout << "\n[INFO] Request ID " << reqId << " REJECTED.\n";
                }
                return;
            }
        }
        cout << "\n[ERROR] Request ID not found!\n";
    }
};

int main() {
    AdoptionSystem system;

    // Step A: View pets
    system.displayAvailablePets();

    // Step B: Submit a request
    system.submitAdoptionRequest(1, "Samiul Islam", "01700000000");

    // Step C: View request list
    system.viewAllRequests();

    // Step D: Admin approves request (Req ID 1001)
    system.processRequest(1001, true);

    // Step E: Verify updated pet status
    system.displayAvailablePets();

    return 0;
}