#include "FileManager.h"

#include <fstream>
#include <sstream>

namespace FileManager {

bool savePetsToCsv(const std::string& filePath, const std::vector<Pet>& pets) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        return false;
    }

    outFile << "id,name,species,breed,age,healthStatus,adoptionStatus,vaccinationStatus\n";

    for (const auto& pet : pets) {
        outFile << pet.getId() << "," << pet.getName() << "," << pet.getSpecies() << "," << pet.getBreed() << ","
                << pet.getAge() << "," << pet.getHealthStatus() << "," << pet.getAdoptionStatus() << ","
                << pet.getVaccinationStatus() << "\n";
    }

    return true;
}

bool loadPetsFromCsv(const std::string& filePath, std::vector<Pet>& pets) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        return false;
    }

    pets.clear();

    std::string line;
    std::getline(inFile, line);  // Skip header.

    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> fields;

        while (std::getline(ss, token, ',')) {
            fields.push_back(token);
        }

        if (fields.size() != 8) {
            // TODO: Member 4 implement feature here - handle malformed CSV lines with error reporting.
            continue;
        }

        Pet pet;
        pet.setId(std::stoi(fields[0]));
        pet.setName(fields[1]);
        pet.setSpecies(fields[2]);
        pet.setBreed(fields[3]);
        pet.setAge(std::stoi(fields[4]));
        pet.setHealthStatus(fields[5]);
        pet.setAdoptionStatus(fields[6]);
        pet.setVaccinationStatus(fields[7]);
        pets.push_back(pet);
    }

    return true;
}

}  // namespace FileManager
