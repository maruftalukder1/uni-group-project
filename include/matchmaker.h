#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include <string>
#include <vector>
#include "pet.h"

// Extra attributes are separate from Pet because the current shared Pet file
// format has eight fields. They can later be moved into Pet by team agreement.
struct PetMatchProfile
{
    std::string petID;
    std::string size;                    // Small, Medium, Large
    std::string activityLevel;           // Low, Medium, High
    std::string livingEnvironments;      // e.g. "Apartment,House,Yard"
    std::string temperament;
    bool goodWithChildren = false;
    bool goodWithOtherPets = false;
};

struct MatchPreferences
{
    std::string species;
    std::string breed;
    std::string gender;
    std::string location;
    std::string size;
    std::string activityLevel;
    std::string livingEnvironment;
    std::string temperament;
    int minAge = -1;
    int maxAge = -1;
    bool hasChildren = false;
    bool hasOtherPets = false;
};

struct MatchResult
{
    Pet pet;
    double score = 0.0; // Percentage from 0 to 100.
};

class Matchmaker
{
public:
    static std::vector<MatchResult> rank(
        const std::vector<Pet>& pets,
        const std::vector<PetMatchProfile>& profiles,
        const MatchPreferences& preferences);

    static double calculateScore(const Pet& pet,
                                 const PetMatchProfile& profile,
                                 const MatchPreferences& preferences);
};

#endif
