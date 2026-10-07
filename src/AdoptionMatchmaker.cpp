#include "AdoptionMatchmaker.h"

std::vector<Pet> AdoptionMatchmaker::findMatches(const std::vector<Pet>& pets, const AdopterCriteria& criteria) const {
    std::vector<Pet> matches;

    for (const auto& pet : pets) {
        if (pet.getAdoptionStatus() != "Available") {
            continue;
        }

        if (!criteria.preferredSpecies.empty() && pet.getSpecies() != criteria.preferredSpecies) {
            continue;
        }

        if (!isHouseTypeCompatible(pet, criteria.houseType)) {
            continue;
        }

        if (!isActivityLevelCompatible(pet, criteria.activityLevel)) {
            continue;
        }

        matches.push_back(pet);
    }

    return matches;
}

bool AdoptionMatchmaker::isHouseTypeCompatible(const Pet& pet, const std::string& houseType) const {
    // TODO: Member 2 implement feature here - refine compatibility rules by breed/size.
    if (houseType == "Apartment" && pet.getSpecies() == "Dog" && pet.getAge() < 2) {
        return false;
    }

    return true;
}

bool AdoptionMatchmaker::isActivityLevelCompatible(const Pet& pet, const std::string& activityLevel) const {
    // TODO: Member 2 implement feature here - replace with a richer scoring model.
    if (activityLevel == "Low" && pet.getSpecies() == "Dog" && pet.getAge() < 3) {
        return false;
    }

    return true;
}
