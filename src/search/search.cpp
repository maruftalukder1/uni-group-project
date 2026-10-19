#include "search.h"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace
{
std::string lowerCopy(const std::string& text)
{
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

bool containsIgnoreCase(const std::string& text, const std::string& query)
{
    return query.empty() || lowerCopy(text).find(lowerCopy(query)) != std::string::npos;
}

bool matchesField(const std::string& wanted, const std::string& actual)
{
    return wanted.empty() || lowerCopy(actual) == lowerCopy(wanted);
}
}

std::vector<Pet> PetSearch::filter(const std::vector<Pet>& pets,
                                   const SearchCriteria& criteria)
{
    std::vector<Pet> results;

    for (const Pet& pet : pets)
    {
        const bool keywordMatches = criteria.keyword.empty() ||
            containsIgnoreCase(pet.getName(), criteria.keyword) ||
            containsIgnoreCase(pet.getSpecies(), criteria.keyword) ||
            containsIgnoreCase(pet.getBreed(), criteria.keyword) ||
            containsIgnoreCase(pet.getLocation(), criteria.keyword);

        if (!keywordMatches) continue;
        if (!matchesField(criteria.species, pet.getSpecies())) continue;
        if (!matchesField(criteria.breed, pet.getBreed())) continue;
        if (!matchesField(criteria.gender, pet.getGender())) continue;
        if (!matchesField(criteria.location, pet.getLocation())) continue;
        if (!matchesField(criteria.status, pet.getStatus())) continue;
        if (criteria.availableOnly && !pet.isAvailable()) continue;
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
        std::cout << "No pets match your search.\n";
        return;
    }

    for (const Pet& pet : results) pet.display();
}
