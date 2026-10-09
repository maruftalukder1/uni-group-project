#include "search.h"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace
{
    // Lowercase copy, so "Dog", "dog" and "DOG" match
    std::string toLower(const std::string& text)
    {
        std::string result = text;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    // An empty "wanted" value means "don't filter on this field"
    bool matchesText(const std::string& wanted, const std::string& actual)
    {
        return wanted.empty() || toLower(wanted) == toLower(actual);
    }
}

std::vector<Pet> PetSearch::filter(const std::vector<Pet>& pets,
                                   const SearchCriteria& criteria)
{
    std::vector<Pet> results;

    for (const Pet& pet : pets)
    {
        if (!matchesText(criteria.species,  pet.getSpecies()))  continue;
        if (!matchesText(criteria.breed,    pet.getBreed()))    continue;
        if (!matchesText(criteria.gender,   pet.getGender()))   continue;
        if (!matchesText(criteria.location, pet.getLocation())) continue;
        if (!matchesText(criteria.status,   pet.getStatus()))   continue;

        if (criteria.minAge >= 0 && pet.getAge() < criteria.minAge) continue;
        if (criteria.maxAge >= 0 && pet.getAge() > criteria.maxAge) continue;

        results.push_back(pet);
    }

    return results;
}

void PetSearch::displayResults(const std::vector<Pet>& results)
{
    if (results.empty())
    {
        std::cout << "No pets match your search." << std::endl;
        return;
    }

    for (const Pet& pet : results)
    {
        pet.display();
    }
}