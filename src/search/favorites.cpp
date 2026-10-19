#include "favorites.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <utility>

FavoriteManager::FavoriteManager(std::string fileName)
    : fileName(std::move(fileName)) {}

std::vector<std::pair<std::string, std::string>> FavoriteManager::records() const
{
    std::vector<std::pair<std::string, std::string>> result;
    std::ifstream input(fileName);
    if (!input) return result; // No file yet means no favourites.

    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream stream(line);
        std::string userID;
        std::string petID;
        if (std::getline(stream, userID, '|') && std::getline(stream, petID, '|') &&
            !userID.empty() && !petID.empty())
        {
            result.emplace_back(userID, petID);
        }
    }
    return result;
}

bool FavoriteManager::save(
    const std::vector<std::pair<std::string, std::string>>& values) const
{
    const std::filesystem::path path(fileName);
    if (path.has_parent_path()) std::filesystem::create_directories(path.parent_path());

    const std::string temporaryName = fileName + ".tmp";
    std::ofstream output(temporaryName, std::ios::trunc);
    if (!output) return false;

    for (const auto& [userID, petID] : values)
        output << userID << '|' << petID << '\n';

    output.close();
    if (!output) return false;

    std::error_code error;
    std::filesystem::rename(temporaryName, fileName, error);
    if (error)
    {
        std::filesystem::remove(fileName, error);
        error.clear();
        std::filesystem::rename(temporaryName, fileName, error);
    }
    return !error;
}

bool FavoriteManager::contains(const std::string& userID, const std::string& petID) const
{
    for (const auto& record : records())
        if (record.first == userID && record.second == petID) return true;
    return false;
}

bool FavoriteManager::add(const std::string& userID, const std::string& petID)
{
    if (userID.empty() || petID.empty() || contains(userID, petID)) return false;
    auto values = records();
    values.emplace_back(userID, petID);
    return save(values);
}

bool FavoriteManager::remove(const std::string& userID, const std::string& petID)
{
    auto values = records();
    const auto oldSize = values.size();
    values.erase(std::remove_if(values.begin(), values.end(),
        [&](const auto& record) {
            return record.first == userID && record.second == petID;
        }), values.end());

    return values.size() != oldSize && save(values);
}

std::vector<std::string> FavoriteManager::petIDsFor(const std::string& userID) const
{
    std::vector<std::string> result;
    for (const auto& [savedUserID, petID] : records())
        if (savedUserID == userID) result.push_back(petID);
    return result;
}

std::vector<Pet> FavoriteManager::petsFor(const std::string& userID,
                                          const std::vector<Pet>& pets) const
{
    const auto ids = petIDsFor(userID);
    std::vector<Pet> result;
    for (const Pet& pet : pets)
        if (std::find(ids.begin(), ids.end(), pet.getPetID()) != ids.end())
            result.push_back(pet);
    return result;
}
