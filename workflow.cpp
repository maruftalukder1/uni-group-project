#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct AdoptionRequest {
    int requestId;
    int petId;
    string applicantName;
    string contactNumber;
    string status;
};

class AdoptionManager {
private:
    vector<AdoptionRequest> requests;
    int nextRequestId = 101;

public:
    void submitApplication(int petId, string applicantName, string contactNumber) {
        AdoptionRequest newReq;
        newReq.requestId = nextRequestId++;
        newReq.petId = petId;
        newReq.applicantName = applicantName;
        newReq.contactNumber = contactNumber;
        newReq.status = "Pending";
        
        requests.push_back(newReq);
        cout << "\n[Success] Adoption application submitted successfully!" << endl;
        cout << "Application ID: " << newReq.requestId << endl;
    }

    void viewAllApplications() const {
        if (requests.empty()) {
            cout << "\nNo adoption applications found." << endl;
            return;
        }

        cout << "\n--- Adoption Applications ---" << endl;
        for (const auto& req : requests) {
            cout << "Req ID: " << req.requestId 
                 << " | Pet ID: " << req.petId 
                 << " | Applicant: " << req.applicantName 
                 << " | Contact: " << req.contactNumber 
                 << " | Status: " << req.status << endl;
        }
    }

    void updateStatus(int requestId, string newStatus) {
        for (auto& req : requests) {
            if (req.requestId == requestId) {
                req.status = newStatus;
                cout << "\n[Success] Request ID " << requestId << " status updated to: " << newStatus << endl;
                return;
            }
        }
        cout << "\n[Error] Application ID not found!" << endl;
    }
};

int main() {
    AdoptionManager manager;
    int choice;

    while (true) {
        cout << "\n=== ADOPTION WORKFLOW SYSTEM ===" << endl;
        cout << "1. Apply for Pet Adoption" << endl;
        cout << "2. View All Applications" << endl;
        cout << "3. Update Application Status" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int petId;
            string name, phone;
            cout << "Enter Pet ID to Adopt: ";
            cin >> petId;
            cin.ignore();
            cout << "Enter Applicant Name: ";
            getline(cin, name);
            cout << "Enter Phone Number: ";
            getline(cin, phone);
            
            manager.submitApplication(petId, name, phone);

        } else if (choice == 2) {
            manager.viewAllApplications();

        } else if (choice == 3) {
            int reqId;
            string status;
            cout << "Enter Request ID: ";
            cin >> reqId;
            cout << "Enter New Status (Approved/Rejected): ";
            cin >> status;

            manager.updateStatus(reqId, status);

        } else if (choice == 4) {
            cout << "\nExiting System. Goodbye!" << endl;
            break;
        } else {
            cout << "\nInvalid choice! Try again." << endl;
        }
    }

    return 0;
}