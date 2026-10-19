#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include "pet.h"

// Empty text fields and -1 age values mean "do not filter this field".
struct SearchCriteria
{
    std::string keyword;   // Matches pet name, species, breed, or location.
    std::string species;
    std::string breed;
    std::string gender;
    std::string location;
    std::string status;
    int minAge = -1;
    int maxAge = -1;
    bool availableOnly = false;
};

class PetSearch
{
public:
    static std::vector<Pet> filter(const std::vector<Pet>& pets,
                                   const SearchCriteria& criteria);
    static void displayResults(const std::vector<Pet>& results);
};

#endif
