#include "matchmaker.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>

namespace
{
std::string trimCopy(const std::string& text)
{
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return {};
    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

std::string lowerCopy(const std::string& text)
{
    std::string result = trimCopy(text);
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char character) {
                       return static_cast<char>(std::tolower(character));
                   });
    return result;
}

bool equalsIgnoreCase(const std::string& left, const std::string& right)
{
    return !trimCopy(right).empty() && lowerCopy(left) == lowerCopy(right);
}

bool listContainsIgnoreCase(const std::string& values,
                            const std::string& wanted)
{
    if (trimCopy(wanted).empty()) return true;

    std::stringstream stream(values);
    std::string value;
    while (std::getline(stream, value, ','))
    {
        if (equalsIgnoreCase(value, wanted)) return true;
    }
    return false;
}

double exactScore(const std::string& actual, const std::string& wanted)
{
    return trimCopy(wanted).empty() ? 1.0
                                    : (equalsIgnoreCase(actual, wanted) ? 1.0 : 0.0);
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

std::string PetMatchProfile::toFileString() const
{
    return petID + "|" + size + "|" + activityLevel + "|" +
           livingEnvironments + "|" + temperament + "|" +
           (goodWithChildren ? "1" : "0") + "|" +
           (goodWithOtherPets ? "1" : "0");
}

bool PetMatchProfile::fromFileString(const std::string& line,
                                     PetMatchProfile& out)
{
    std::stringstream stream(line);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(stream, field, '|')) fields.push_back(field);
    if (fields.size() != 7 || trimCopy(fields[0]).empty()) return false;
    if (fields[5] != "0" && fields[5] != "1") return false;
    if (fields[6] != "0" && fields[6] != "1") return false;

    out.petID = trimCopy(fields[0]);
    out.size = trimCopy(fields[1]);
    out.activityLevel = trimCopy(fields[2]);
    out.livingEnvironments = trimCopy(fields[3]);
    out.temperament = trimCopy(fields[4]);
    out.goodWithChildren = fields[5] == "1";
    out.goodWithOtherPets = fields[6] == "1";
    return true;
}

std::vector<PetMatchProfile> Matchmaker::loadProfiles(const std::string& fileName)
{
    std::vector<PetMatchProfile> profiles;
    std::ifstream input(fileName);
    if (!input) return profiles;

    std::string line;
    while (std::getline(input, line))
    {
        if (trimCopy(line).empty()) continue;
        PetMatchProfile profile;
        if (PetMatchProfile::fromFileString(line, profile))
            profiles.push_back(profile);
    }
    return profiles;
}

double Matchmaker::calculateScore(const Pet& pet,
                                  const PetMatchProfile& profile,
                                  const MatchPreferences& preferences)
{
    const double species = exactScore(pet.getSpecies(), preferences.species);
    const double age = rangeScore(pet.getAge(), preferences.minAge, preferences.maxAge);
    const double location = exactScore(pet.getLocation(), preferences.location);
    const double size = exactScore(profile.size, preferences.size);
    const double activity = exactScore(profile.activityLevel, preferences.activityLevel);
    const double living = listContainsIgnoreCase(profile.livingEnvironments,
                                                  preferences.livingEnvironment)
        ? 1.0 : 0.0;
    const double other = otherPreferenceScore(pet, profile, preferences);

    const double score = species * 30.0 + age * 15.0 + location * 15.0 +
                         size * 10.0 + activity * 10.0 + living * 10.0 +
                         other * 10.0;
    return std::max(0.0, std::min(100.0, score));
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

        const auto profile = std::find_if(
            profiles.begin(), profiles.end(),
            [&](const PetMatchProfile& candidate) {
                return candidate.petID == pet.getPetID();
            });
        if (profile == profiles.end()) continue;

        results.push_back({pet, calculateScore(pet, *profile, preferences)});
    }

    std::sort(results.begin(), results.end(),
              [](const MatchResult& left, const MatchResult& right) {
                  if (left.score != right.score)
                      return left.score > right.score;
                  return left.pet.getPetID() < right.pet.getPetID();
              });
    return results;
}
