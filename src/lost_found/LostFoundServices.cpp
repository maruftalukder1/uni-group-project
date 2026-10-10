#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

namespace {
    int readIntInRange(const string& prompt, int minValue, int maxValue) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= minValue && value <= maxValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }

            cout << "Invalid input. Please enter a number between " << minValue
                 << " and " << maxValue << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string readNonEmptyLine(const string& prompt) {
        string value;
        while (true) {
            cout << prompt;
            getline(cin, value);
            if (!value.empty()) {
                return value;
            }
            cout << "Input cannot be empty. Please try again." << endl;
        }
    }

    string normalizeArea(string text) {
        const size_t first = text.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            return "";
        }

        const size_t last = text.find_last_not_of(" \t\r\n");
        text = text.substr(first, last - first + 1);
        transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
            return static_cast<char>(tolower(ch));
        });
        return text;
    }
}

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

        int choice = readIntInRange("\nSelect Status (1. LOST / 2. FOUND): ", 1, 2);
        p.status = (choice == 1) ? "LOST" : "FOUND";
        p.name = readNonEmptyLine("Enter Pet Name/Breed: ");
        p.location = readNonEmptyLine("Enter Location/Area: ");
        p.phone = readNonEmptyLine("Enter Contact Phone Number: ");

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
        string area = readNonEmptyLine("\nEnter Area/Location to Search (e.g., Uttara): ");
        string normalizedArea = normalizeArea(area);

        cout << "\n--- Search Results for Area: '" << area << "' ---" << endl;
        bool found = false;

        for (const auto& n : notices) {
            if (normalizeArea(n.location) == normalizedArea) {
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
    int option = 4;

    do {
        cout << "\n==========================================" << endl;
        cout << "   LOCAL PET CARE - LOST & FOUND SYSTEM   " << endl;
        cout << "==========================================" << endl;
        cout << "1. View All Notices" << endl;
        cout << "2. Post a New Notice" << endl;
        cout << "3. Search Notices by Location" << endl;
        cout << "4. Exit Program" << endl;
        cout << "==========================================" << endl;
        option = readIntInRange("Enter Choice (1-4): ", 1, 4);

        if (option == 1) {
            manager.showAllNotices();
        } else if (option == 2) {
            manager.addNotice();
        } else if (option == 3) {
            manager.searchByArea();
        }

    } while (option != 4);

    cout << "\nExiting Lost & Found Module. Thank you!" << endl;
    return 0;
}
