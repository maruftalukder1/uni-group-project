#ifndef ADOPTION_MATCHMAKER_H
#define ADOPTION_MATCHMAKER_H

#include "Pet.h"

#include <string>
#include <vector>

struct AdopterCriteria {
    std::string preferredSpecies;
    std::string houseType;
    std::string activityLevel;
};

class AdoptionMatchmaker {
public:
    std::vector<Pet> findMatches(const std::vector<Pet>& pets, const AdopterCriteria& criteria) const;

private:
    bool isHouseTypeCompatible(const Pet& pet, const std::string& houseType) const;
    bool isActivityLevelCompatible(const Pet& pet, const std::string& activityLevel) const;
};

#endif
