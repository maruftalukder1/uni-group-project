#include "matchmaker.h"
#include <algorithm>
#include <cctype>
#include <string>

namespace
{
std::string lowerCopy(const std::string& text)
{
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char character) {
                       return static_cast<char>(std::tolower(character));
                   });
    return result;
}

bool equalsIgnoreCase(const std::string& left, const std::string& right)
{
    return !right.empty() && lowerCopy(left) == lowerCopy(right);
}

bool listContainsIgnoreCase(const std::string& values,
                            const std::string& wanted)
{
    if (wanted.empty()) return true;

    std::string value;
    for (char character : values)
    {
        if (character == ',')
        {
            if (equalsIgnoreCase(value, wanted)) return true;
            value.clear();
        }
        else if (!std::isspace(static_cast<unsigned char>(character)))
        {
            value += character;
        }
    }
    return equalsIgnoreCase(value, wanted);
}

double exactScore(const std::string& actual, const std::string& wanted)
{
    return wanted.empty() ? 1.0 : (equalsIgnoreCase(actual, wanted) ? 1.0 : 0.0);
}

double rangeScore(int age, int minimum, int maximum)
{
    if (minimum < 0 && maximum < 0) return 1.0;
    if (minimum >= 0 && age < minimum) return 0.0;
    if (maximum >= 0 && age > maximum) return 0.0;
    return 1.0;
}

double otherPreferenceScore(const Pet& pet,
                            const PetMatchProfile& profile,
                            const MatchPreferences& preferences)
{
    double total = 0.0;
    int considered = 0;

    if (!preferences.gender.empty())
    {
        total += exactScore(pet.getGender(), preferences.gender);
        ++considered;
    }
    if (!preferences.breed.empty())
    {
        total += exactScore(pet.getBreed(), preferences.breed);
        ++considered;
    }
    if (!preferences.temperament.empty())
    {
        total += exactScore(profile.temperament, preferences.temperament);
        ++considered;
    }
    if (preferences.hasChildren)
    {
        total += profile.goodWithChildren ? 1.0 : 0.0;
        ++considered;
    }
    if (preferences.hasOtherPets)
    {
        total += profile.goodWithOtherPets ? 1.0 : 0.0;
        ++considered;
    }

    return considered == 0 ? 1.0 : total / static_cast<double>(considered);
}
}

double Matchmaker::calculateScore(const Pet& pet,
                                  const PetMatchProfile& profile,
                                  const MatchPreferences& preferences)
{
    const bool hasProfile = !profile.petID.empty();
    const double species = exactScore(pet.getSpecies(), preferences.species);
    const double age = rangeScore(pet.getAge(), preferences.minAge, preferences.maxAge);
    const double location = exactScore(pet.getLocation(), preferences.location);
    const double size = !hasProfile ? 1.0 : exactScore(profile.size, preferences.size);
    const double activity = !hasProfile ? 1.0 : exactScore(profile.activityLevel,
                                                             preferences.activityLevel);
    const double living = !hasProfile || preferences.livingEnvironment.empty()
        ? 1.0
        : (listContainsIgnoreCase(profile.livingEnvironments,
                                  preferences.livingEnvironment) ? 1.0 : 0.0);
    const double other = otherPreferenceScore(pet, profile, preferences);

    const double score = species * 30.0 + age * 15.0 + location * 15.0 +
                         size * 10.0 + activity * 10.0 + living * 10.0 +
                         other * 10.0;
    return std::clamp(score, 0.0, 100.0);
}

std::vector<MatchResult> Matchmaker::rank(
    const std::vector<Pet>& pets,
    const std::vector<PetMatchProfile>& profiles,
    const MatchPreferences& preferences)
{
    std::vector<MatchResult> results;

    for (const Pet& pet : pets)
    {
        if (!pet.isAvailable()) continue;

        PetMatchProfile profile;
        for (const PetMatchProfile& candidate : profiles)
        {
            if (candidate.petID == pet.getPetID())
            {
                profile = candidate;
                break;
            }
        }

        results.push_back({pet, calculateScore(pet, profile, preferences)});
    }

    std::sort(results.begin(), results.end(),
              [](const MatchResult& left, const MatchResult& right) {
                  if (left.score != right.score)
                      return left.score > right.score;
                  return left.pet.getPetID() < right.pet.getPetID();
              });
    return results;
}
