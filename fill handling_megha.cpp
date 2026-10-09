#include <bits/stdc++.h>
using namespace std;

const string FILE_NAME = "pets.txt";

struct PetRecord {
    int id;
    string name;
    string type;
    string owner;
    int age;
};

void addPet() {
    PetRecord p;

    cout << "\nEnter Pet ID: ";
    cin >> p.id;

    ifstream check(FILE_NAME);
    PetRecord existing;

    while (check >> existing.id >> existing.name
                 >> existing.type >> existing.owner
                 >> existing.age) {
        if (existing.id == p.id) {
            cout << "Pet ID already exists!\n";
            return;
        }
    }
    check.close();

    cout << "Enter Pet Name: ";
    cin >> p.name;

    cout << "Enter Pet Type: ";
    cin >> p.type;

    cout << "Enter Owner Name: ";
    cin >> p.owner;

    cout << "Enter Pet Age: ";
    cin >> p.age;

    if (p.age < 0) {
        cout << "Invalid age!\n";
        return;
    }

    ofstream file(FILE_NAME, ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << p.id << " " << p.name << " "
         << p.type << " " << p.owner << " "
         << p.age << '\n';

    file.close();

    cout << "Pet saved successfully!\n";
}

void viewPets() {
    ifstream file(FILE_NAME);

    if (!file) {
        cout << "\nNo pet records found.\n";
        return;
    }

    PetRecord p;
    bool found = false;

    cout << "\n========== PET RECORDS ==========\n";

    while (file >> p.id >> p.name >> p.type
                >> p.owner >> p.age) {
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Type: " << p.type
             << " | Owner: " << p.owner
             << " | Age: " << p.age << '\n';

        found = true;
    }

    if (!found)
        cout << "No records available.\n";

    file.close();
}

void searchPet() {
    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No pet records found.\n";
        return;
    }

    int id;
    cout << "Enter Pet ID to search: ";
    cin >> id;

    PetRecord p;
    bool found = false;

    while (file >> p.id >> p.name >> p.type
                >> p.owner >> p.age) {
        if (p.id == id) {
            cout << "\nPet found!\n";
            cout << "ID: " << p.id << '\n';
            cout << "Name: " << p.name << '\n';
            cout << "Type: " << p.type << '\n';
            cout << "Owner: " << p.owner << '\n';
            cout << "Age: " << p.age << '\n';

            found = true;
            break;
        }
    }

    if (!found)
        cout << "Pet not found.\n";

    file.close();
}

void updatePet() {
    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No pet records found.\n";
        return;
    }

    int id;
    cout << "Enter Pet ID to update: ";
    cin >> id;

    vector<PetRecord> records;
    PetRecord p;
    bool found = false;

    while (file >> p.id >> p.name >> p.type
                >> p.owner >> p.age) {
        if (p.id == id) {
            cout << "New Pet Name: ";
            cin >> p.name;

            cout << "New Pet Type: ";
            cin >> p.type;

            cout << "New Owner Name: ";
            cin >> p.owner;

            cout << "New Pet Age: ";
            cin >> p.age;

            if (p.age < 0) {
                cout << "Invalid age!\n";
                return;
            }

            found = true;
        }

        records.push_back(p);
    }

    file.close();

    if (!found) {
        cout << "Pet not found.\n";
        return;
    }

    ofstream out(FILE_NAME);

    if (!out) {
        cout << "Error updating file!\n";
        return;
    }

    for (const auto& pet : records) {
        out << pet.id << " " << pet.name << " "
            << pet.type << " " << pet.owner << " "
            << pet.age << '\n';
    }

    out.close();
    cout << "Pet updated successfully!\n";
}

void deletePet() {
    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No pet records found.\n";
        return;
    }

    int id;
    cout << "Enter Pet ID to delete: ";
    cin >> id;

    vector<PetRecord> records;
    PetRecord p;
    bool found = false;

    while (file >> p.id >> p.name >> p.type
                >> p.owner >> p.age) {
        if (p.id == id) {
            found = true;
            continue;
        }

        records.push_back(p);
    }

    file.close();

    if (!found) {
        cout << "Pet not found.\n";
        return;
    }

    ofstream out(FILE_NAME);

    if (!out) {
        cout << "Error updating file!\n";
        return;
    }

    for (const auto& pet : records) {
        out << pet.id << " " << pet.name << " "
            << pet.type << " " << pet.owner << " "
            << pet.age << '\n';
    }

    out.close();
    cout << "Pet deleted successfully!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== PET HEALTHCARE SYSTEM =====\n";
        cout << "1. Add Pet\n";
        cout << "2. View All Pets\n";
        cout << "3. Search Pet\n";
        cout << "4. Update Pet\n";
        cout << "5. Delete Pet\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            return 1;
        }

        switch (choice) {
            case 1: addPet(); break;
            case 2: viewPets(); break;
            case 3: searchPet(); break;
            case 4: updatePet(); break;
            case 5: deletePet(); break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
