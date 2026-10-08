#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct User {
    string id;
    string name;
    string role;
    string email;
    string area;
    bool isActive;
};

struct Pet {
    string id;
    string name;
    string breed;
    string status;
};

struct AdoptionApplication {
    string id;
    string petId;
    string petName;
    string applicantName;
    string applicantEmail;
    string submittedAt;
    string status;
};

struct LostFoundReport {
    string id;
    string type;
    string petName;
};

struct ActivityLog {
    string id;
    string timestamp;
    string actor;
    string action;
    string details;
};

struct Conversation {
    string id;
    string adopterName;
    string petId;
    string lastMessage;
    string lastMessageTime;
    int unreadForAdmin;
};

class AdminDashboard {
private:
    vector<User> users;
    vector<Pet> pets;
    vector<AdoptionApplication> applications;
    vector<LostFoundReport> lostFound;
    vector<ActivityLog> activityLogs;
    vector<Conversation> conversations;

    static string lowerCase(string text) {
        transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        return text;
    }

    static void divider(char symbol = '-', int width = 92) {
        cout << string(width, symbol) << '\n';
    }

    int findApplicationIndex(const string& id) const {
        for (size_t i = 0; i < applications.size(); ++i) {
            if (applications[i].id == id) return static_cast<int>(i);
        }
        return -1;
    }

    int findUserIndex(const string& id) const {
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].id == id) return static_cast<int>(i);
        }
        return -1;
    }

    Pet* findPet(const string& id) {
        for (auto& pet : pets) {
            if (pet.id == id) return &pet;
        }
        return nullptr;
    }

    void addLog(const string& action, const string& details) {
        activityLogs.push_back({
            "log-" + to_string(activityLogs.size() + 1),
            "2026-10-08 14:25",
            "Administrator",
            action,
            details
        });
    }

public:
    AdminDashboard() {
        seedData();
    }

    void seedData() {
        users = {
            {"u-admin-1", "System Administrator", "admin", "admin@pawmatch.test", "Central Office", true},
            {"u-101", "Amina Rahman", "adopter", "amina@example.com", "Dhaka", true},
            {"u-102", "Tanvir Hasan", "shelter", "tanvir@shelter.org", "Chattogram", true},
            {"u-103", "Nadia Karim", "veterinarian", "nadia@vet.org", "Sylhet", false},
            {"u-104", "Rafi Islam", "adopter", "rafi@example.com", "Khulna", true}
        };

        pets = {
            {"p-1", "Milo", "Golden Retriever", "Available"},
            {"p-2", "Luna", "Domestic Shorthair", "Available"},
            {"p-3", "Rocky", "German Shepherd", "Adopted"},
            {"p-4", "Coco", "Mixed Breed", "Available"}
        };

        applications = {
            {"app-1", "p-1", "Milo", "Amina Rahman", "amina@example.com", "2026-10-02", "Submitted"},
            {"app-2", "p-1", "Milo", "Rafi Islam", "rafi@example.com", "2026-10-03", "Under Review"},
            {"app-3", "p-2", "Luna", "Sadia Noor", "sadia@example.com", "2026-10-04", "Submitted"},
            {"app-4", "p-3", "Rocky", "Imran Ali", "imran@example.com", "2026-09-20", "Approved"}
        };

        lostFound = {
            {"lf-1", "Lost", "Buddy"},
            {"lf-2", "Found", "Unknown Cat"},
            {"lf-3", "Lost", "Max"}
        };

        activityLogs = {
            {"log-1", "2026-10-01 09:10", "Administrator", "USER_REVIEW", "Reviewed shelter verification documents."},
            {"log-2", "2026-10-02 11:30", "Administrator", "PET_MODERATION", "Approved a new pet listing."}
        };

        conversations = {
            {"conv-1", "Amina Rahman", "p-1", "Can I schedule a visit to meet Milo?", "2026-10-08 10:20", 2},
            {"conv-2", "Rafi Islam", "p-2", "What documents are required for adoption?", "2026-10-07 17:45", 0}
        };
    }

    void showMetrics() const {
        const int availablePets = static_cast<int>(count_if(pets.begin(), pets.end(),
            [](const Pet& pet) { return pet.status == "Available"; }));
        const int completedAdoptions = static_cast<int>(count_if(pets.begin(), pets.end(),
            [](const Pet& pet) { return pet.status == "Adopted"; }));
        const int pendingApps = static_cast<int>(count_if(applications.begin(), applications.end(),
            [](const AdoptionApplication& app) {
                return app.status == "Submitted" || app.status == "Under Review";
            }));
        const int lostPets = static_cast<int>(count_if(lostFound.begin(), lostFound.end(),
            [](const LostFoundReport& report) { return report.type == "Lost"; }));
        const int foundPets = static_cast<int>(count_if(lostFound.begin(), lostFound.end(),
            [](const LostFoundReport& report) { return report.type == "Found"; }));

        divider('=');
        cout << "PAWMATCH GOVERNANCE & MODERATION CONSOLE\n";
        cout << "Admin Dashboard\n";
        divider('=');
        cout << left << setw(26) << "Total Users" << users.size() << '\n';
        cout << left << setw(26) << "Total Pets" << pets.size() << '\n';
        cout << left << setw(26) << "Available Pets" << availablePets << '\n';
        cout << left << setw(26) << "Completed Adoptions" << completedAdoptions << '\n';
        cout << left << setw(26) << "Pending Applications" << pendingApps << '\n';
        cout << left << setw(26) << "Reported Listings" << 8 << '\n';
        cout << left << setw(26) << "Lost Pets" << lostPets << '\n';
        cout << left << setw(26) << "Found Pets" << foundPets << '\n';
    }

    void showApplications() const {
        divider('=');
        cout << "RECENT ADOPTION REQUESTS\n";
        divider();
        cout << left << setw(10) << "ID" << setw(14) << "Pet" << setw(20) << "Applicant"
             << setw(25) << "Email" << setw(14) << "Date" << "Status\n";
        divider();
        for (const auto& app : applications) {
            cout << left << setw(10) << app.id << setw(14) << app.petName
                 << setw(20) << app.applicantName << setw(25) << app.applicantEmail
                 << setw(14) << app.submittedAt << app.status << '\n';
        }
    }

    void approveApplication() {
        showApplications();
        cout << "\nEnter application ID to approve: ";
        string id;
        getline(cin, id);
        int index = findApplicationIndex(id);
        if (index < 0) {
            cout << "Application not found.\n";
            return;
        }

        auto& selected = applications[index];
        if (selected.status != "Submitted" && selected.status != "Under Review") {
            cout << "This application is already settled.\n";
            return;
        }

        selected.status = "Approved";
        Pet* pet = findPet(selected.petId);
        if (pet != nullptr) pet->status = "Adopted";

        for (auto& app : applications) {
            if (app.id != selected.id && app.petId == selected.petId &&
                (app.status == "Submitted" || app.status == "Under Review")) {
                app.status = "Rejected";
            }
        }

        addLog("APPLICATION_APPROVED",
               "Approved " + selected.id + " for " + selected.petName +
               "; competing applications were automatically rejected.");
        cout << "Application approved. Pet marked as Adopted.\n";
    }

    void rejectApplication() {
        showApplications();
        cout << "\nEnter application ID to reject: ";
        string id;
        getline(cin, id);
        int index = findApplicationIndex(id);
        if (index < 0) {
            cout << "Application not found.\n";
            return;
        }
        auto& app = applications[index];
        if (app.status != "Submitted" && app.status != "Under Review") {
            cout << "This application is already settled.\n";
            return;
        }
        app.status = "Rejected";
        addLog("APPLICATION_REJECTED", "Rejected " + app.id + " for " + app.petName + ".");
        cout << "Application rejected.\n";
    }

    void showMessages() const {
        divider('=');
        cout << "ADOPTER MESSAGES & HELPDESK INQUIRIES\n";
        divider();
        for (const auto& conversation : conversations) {
            string petName = "General inquiry";
            for (const auto& pet : pets) {
                if (pet.id == conversation.petId) petName = pet.name + " (" + pet.breed + ")";
            }
            cout << "Conversation: " << conversation.id << '\n'
                 << "Adopter: " << conversation.adopterName << '\n'
                 << "Regarding: " << petName << '\n'
                 << "Last message: " << conversation.lastMessage << '\n'
                 << "Time: " << conversation.lastMessageTime
                 << " | Unread: " << conversation.unreadForAdmin << "\n";
            divider();
        }
    }

    void searchUsers() const {
        cout << "Enter a name, role, or email to search: ";
        string query;
        getline(cin, query);
        query = lowerCase(query);

        divider();
        cout << left << setw(10) << "ID" << setw(22) << "Name" << setw(16) << "Role"
             << setw(28) << "Email" << setw(16) << "Location" << "Status\n";
        divider();
        bool found = false;
        for (const auto& user : users) {
            if (lowerCase(user.name).find(query) != string::npos ||
                lowerCase(user.role).find(query) != string::npos ||
                lowerCase(user.email).find(query) != string::npos) {
                cout << left << setw(10) << user.id << setw(22) << user.name
                     << setw(16) << user.role << setw(28) << user.email
                     << setw(16) << user.area << (user.isActive ? "Active" : "Suspended") << '\n';
                found = true;
            }
        }
        if (!found) cout << "No matching users found.\n";
    }

    void toggleUserStatus() {
        cout << "Enter user ID to suspend or activate: ";
        string id;
        getline(cin, id);
        int index = findUserIndex(id);
        if (index < 0) {
            cout << "User not found.\n";
            return;
        }
        if (users[index].role == "admin") {
            cout << "Administrator accounts cannot be suspended here.\n";
            return;
        }
        users[index].isActive = !users[index].isActive;
        string status = users[index].isActive ? "activated" : "suspended";
        addLog("USER_STATUS_CHANGED", users[index].name + " was " + status + ".");
        cout << users[index].name << " is now "
             << (users[index].isActive ? "Active" : "Suspended") << ".\n";
    }

    void showActivityLogs() const {
        divider('=');
        cout << "ACTIVITY AUDIT TRAIL\n";
        divider();
        for (const auto& log : activityLogs) {
            cout << '[' << log.timestamp << "] " << log.actor << ": " << log.action << '\n'
                 << "  " << log.details << '\n';
        }
    }

    void exportReport() const {
        ofstream file("pawmatch_audit_report.csv");
        if (!file) {
            cout << "Could not create the CSV report.\n";
            return;
        }
        file << "id,timestamp,actor,action,details\n";
        for (const auto& log : activityLogs) {
            file << '"' << log.id << "\",\"" << log.timestamp << "\",\""
                 << log.actor << "\",\"" << log.action << "\",\""
                 << log.details << "\"\n";
        }
        cout << "Report exported as pawmatch_audit_report.csv\n";
    }

    void run() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n";
            showMetrics();
            cout << "\n1. View adoption requests\n"
                 << "2. Approve an application\n"
                 << "3. Reject an application\n"
                 << "4. View adopter messages\n"
                 << "5. Search user accounts\n"
                 << "6. Suspend or activate a user\n"
                 << "7. View activity audit trail\n"
                 << "8. Export audit report to CSV\n"
                 << "0. Exit\n"
                 << "Select an option: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
                cout << "Please enter a valid number.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: showApplications(); break;
                case 2: approveApplication(); break;
                case 3: rejectApplication(); break;
                case 4: showMessages(); break;
                case 5: searchUsers(); break;
                case 6: toggleUserStatus(); break;
                case 7: showActivityLogs(); break;
                case 8: exportReport(); break;
                case 0: cout << "Goodbye.\n"; break;
                default: cout << "Invalid option. Try again.\n";
            }
        }
    }
};

int main() {
    AdminDashboard dashboard;
    dashboard.run();
    return 0;
}
