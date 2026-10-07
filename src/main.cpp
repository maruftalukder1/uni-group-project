#include "AdoptionMatchmaker.h"
#include "FileManager.h"
#include "HealthCare.h"
#include "Pet.h"

#include <iostream>
#include <vector>

namespace {

void printMenu() {
    std::cout << "\n=== Local Pet Care & Adoption Matchmaker ===\n";
    std::cout << "1. Register sample pet\n";
    std::cout << "2. List available pets\n";
    std::cout << "3. Find pet matches\n";
    std::cout << "4. Add sample health record\n";
    std::cout << "5. Save pets to CSV\n";
    std::cout << "6. Load pets from CSV\n";
    std::cout << "0. Exit\n";
    std::cout << "Select option: ";
}

void listAvailablePets(const std::vector<Pet>& pets) {
    bool found = false;
    for (const auto& pet : pets) {
        if (pet.getAdoptionStatus() == "Available") {
            std::cout << "-------------------------\n";
            pet.printDetails();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No pets currently available for adoption.\n";
    }
}

}  // namespace

int main() {
    std::vector<Pet> pets;
    AdoptionMatchmaker matchmaker;
    CareSchedule careSchedule;

    int choice = -1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int nextId = static_cast<int>(pets.size()) + 1;
                pets.emplace_back(nextId,
                                  "Buddy",
                                  "Dog",
                                  "Labrador",
                                  3,
                                  "Healthy",
                                  "Available",
                                  "Up to date");
                // TODO: Member 1 implement feature here - gather pet registration input from the user.
                std::cout << "Sample pet registered with ID " << nextId << ".\n";
                break;
            }
            case 2:
                listAvailablePets(pets);
                break;
            case 3: {
                AdopterCriteria criteria;
                criteria.preferredSpecies = "Dog";
                criteria.houseType = "House";
                criteria.activityLevel = "Medium";
                // TODO: Member 2 implement feature here - collect adopter criteria from user input.

                auto matches = matchmaker.findMatches(pets, criteria);
                std::cout << "Found " << matches.size() << " match(es).\n";
                for (const auto& pet : matches) {
                    std::cout << "-------------------------\n";
                    pet.printDetails();
                }
                break;
            }
            case 4: {
                if (pets.empty()) {
                    std::cout << "Register a pet before creating health records.\n";
                    break;
                }

                HealthRecord record{pets.front().getId(), "2026-10-01", "2026-10-05", "Heartworm medication every month"};
                careSchedule.addOrUpdateRecord(record);
                careSchedule.printRecord(record.petId);
                // TODO: Member 3 implement feature here - add date validation and scheduling reminders.
                break;
            }
            case 5: {
                if (FileManager::savePetsToCsv("pets.csv", pets)) {
                    std::cout << "Pets saved to pets.csv\n";
                } else {
                    std::cout << "Failed to save pets.\n";
                }
                // TODO: Member 4 implement feature here - support configurable export paths.
                break;
            }
            case 6: {
                if (FileManager::loadPetsFromCsv("pets.csv", pets)) {
                    std::cout << "Pets loaded from pets.csv\n";
                } else {
                    std::cout << "Failed to load pets.\n";
                }
                break;
            }
            case 0:
                std::cout << "Exiting application.\n";
                break;
            default:
                std::cout << "Unknown option. Try again.\n";
                break;
        }
    }

    // TODO: Member 5 implement feature here - add role-based menu extensions and reporting tools.
    return 0;
}
