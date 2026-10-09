#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct PetNotice {
    int id;
    string name;
    string status;
    string location;
    string phone;
};

class LostFoundManager {
private:
    vector<PetNotice> notices;
    int currentId = 101;

public:
    LostFoundManager() {
        notices.push_back({currentId++, "Milo (Dog)", "LOST", "Uttara", "01711111111"});
        notices.push_back({currentId++, "Persian Cat", "FOUND", "Dhanmondi", "01822222222"});
    }

    void addNotice() {
        PetNotice p;
        p.id = currentId++;

        cout << "\nSelect Status (1. LOST / 2. FOUND): ";
        int choice;
        cin >> choice;
        p.status = (choice == 1) ? "LOST" : "FOUND";

        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Pet Name/Breed: ";
        getline(cin, p.name);

        cout << "Enter Location/Area: ";
        getline(cin, p.location);

        cout << "Enter Contact Phone Number: ";
        getline(cin, p.phone);

        notices.push_back(p);
        cout << ">> Notice added successfully! Assigned Notice ID: " << p.id << endl;
    }

    void showAllNotices() const {
        cout << "\n==========================================" << endl;
        cout << "         LOST & FOUND NOTICE BOARD        " << endl;
        cout << "==========================================" << endl;

        if (notices.empty()) {
            cout << "No notices available right now." << endl;
            return;
        }

        for (const auto& n : notices) {
            cout << "ID: " << n.id 
                 << " | [" << n.status << "] " << n.name 
                 << " | Area: " << n.location 
                 << " | Contact: " << n.phone << endl;
        }
    }

    void searchByArea() const {
        string area;
        cout << "\nEnter Area/Location to Search (e.g., Uttara): ";
        getline(cin, area);

        cout << "\n--- Search Results for Area: '" << area << "' ---" << endl;
        bool found = false;

        for (const auto& n : notices) {
            if (n.location == area) {
                cout << "ID: " << n.id 
                     << " | [" << n.status << "] " << n.name 
                     << " | Contact: " << n.phone << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No pet reports found in this location." << endl;
        }
    }
};

int main() {
    LostFoundManager manager;
    int option;

    do {
        cout << "\n==========================================" << endl;
        cout << "   LOCAL PET CARE - LOST & FOUND SYSTEM   " << endl;
        cout << "==========================================" << endl;
        cout << "1. View All Notices" << endl;
        cout << "2. Post a New Notice" << endl;
        cout << "3. Search Notices by Location" << endl;
        cout << "4. Exit Program" << endl;
        cout << "==========================================" << endl;
        cout << "Enter Choice (1-4): ";
        cin >> option;

        if (option == 1) {
            manager.showAllNotices();
        } else if (option == 2) {
            manager.addNotice();
        } else if (option == 3) {
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            manager.searchByArea();
        }

    } while (option != 4);

    cout << "\nExiting Lost & Found Module. Thank you!" << endl;
    return 0;
}
