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
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

bool equalIgnoreCase(const std::string& left, const std::string& right)
{
    return !right.empty() && lowerCopy(left) == lowerCopy(right);
}

bool listContainsIgnoreCase(const std::string& commaSeparatedValues,
                            const std::string& wanted)
{
    if (wanted.empty()) return true;
    std::string value;
    for (char character : commaSeparatedValues)
    {
        if (character == ',')
        {
            if (equalIgnoreCase(value, wanted)) return true;
            value.clear();
        }
        else if (!std::isspace(static_cast<unsigned char>(character)))
        {
            value += character;
        }
    }
    return equalIgnoreCase(value, wanted);
}

double exactOrNeutral(const std::string& actual, const std::string& wanted)
{
    return wanted.empty() ? 1.0 : (equalIgnoreCase(actual, wanted) ? 1.0 : 0.0);
}

double ageScore(int age, int minimum, int maximum)
{
    if (minimum < 0 && maximum < 0) return 1.0;
    if (minimum >= 0 && age < minimum) return 0.0;
    if (maximum >= 0 && age > maximum) return 0.0;
    return 1.0;
}
}

double Matchmaker::calculateScore(const Pet& pet,
                                   const PetMatchProfile& profile,
                                   const MatchPreferences& preferences)
{
    // Repository weights: species 30, age 15, location 15, size 10,
    // activity 10, living environment 10, other preferences 10.
    const double species = exactOrNeutral(pet.getSpecies(), preferences.species);
    const double age = ageScore(pet.getAge(), preferences.minAge, preferences.maxAge);
    const double location = exactOrNeutral(pet.getLocation(), preferences.location);
    const double size = exactOrNeutral(profile.size, preferences.size);
    const double activity = exactOrNeutral(profile.activityLevel, preferences.activityLevel);
    const double living = listContainsIgnoreCase(profile.livingEnvironments,
                                                  preferences.livingEnvironment) ? 1.0 : 0.0;

    double other = 0.0;
    int considered = 0;
    if (!preferences.gender.empty())
    {
        other += exactOrNeutral(pet.getGender(), preferences.gender);
        ++considered;
    }
    if (!preferences.breed.empty())
    {
        other += exactOrNeutral(pet.getBreed(), preferences.breed);
        ++considered;
    }
    if (!preferences.temperament.empty())
    {
        other += exactOrNeutral(profile.temperament, preferences.temperament);
        ++considered;
    }
    if (preferences.hasChildren)
    {
        other += profile.goodWithChildren ? 1.0 : 0.0;
        ++considered;
    }
    if (preferences.hasOtherPets)
    {
        other += profile.goodWithOtherPets ? 1.0 : 0.0;
        ++considered;
    }
    if (considered == 0) other = 1.0;
    else other /= static_cast<double>(considered);

    const double score = species * 30.0 + age * 15.0 + location * 15.0 +
                         size * 10.0 + activity * 10.0 + living * 10.0 + other * 10.0;
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
        if (!pet.isAvailable()) continue; // Never recommend an adopted pet.

        PetMatchProfile profile;
        for (const auto& candidate : profiles)
            if (candidate.petID == pet.getPetID()) { profile = candidate; break; }

        results.push_back({pet, calculateScore(pet, profile, preferences)});
    }

    std::sort(results.begin(), results.end(), [](const MatchResult& left,
                                                 const MatchResult& right) {
        if (left.score != right.score) return left.score > right.score;
        return left.pet.getPetID() < right.pet.getPetID();
    });
    return results;
}
