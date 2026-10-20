#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include <string>
#include <vector>
#include "pet.h"

struct PetMatchProfile
{
    std::string petID;
    std::string size;
    std::string activityLevel;
    std::string livingEnvironments;
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
    double score = 0.0;
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
