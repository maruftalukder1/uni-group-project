#include "favorites.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <utility>

FavoriteManager::FavoriteManager(std::string fileNameValue)
    : fileName(std::move(fileNameValue))
{
}

std::vector<std::pair<std::string, std::string>> FavoriteManager::records() const
{
    std::vector<std::pair<std::string, std::string>> result;
    std::ifstream input(fileName);
    if (!input) return result;

    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream stream(line);
        std::string userID;
        std::string petID;
        std::string extra;
        if (std::getline(stream, userID, '|') &&
            std::getline(stream, petID, '|') &&
            !std::getline(stream, extra, '|') &&
            !userID.empty() && !petID.empty())
        {
            const std::pair<std::string, std::string> record(userID, petID);
            if (std::find(result.begin(), result.end(), record) == result.end())
                result.push_back(record);
        }
    }
    return result;
}

bool FavoriteManager::save(
    const std::vector<std::pair<std::string, std::string>>& values) const
{
    const std::filesystem::path path(fileName);
    if (path.has_parent_path())
        std::filesystem::create_directories(path.parent_path());

    const std::string temporaryName = fileName + ".tmp";
    std::ofstream output(temporaryName, std::ios::trunc);
    if (!output) return false;

    for (const auto& record : values)
        output << record.first << '|' << record.second << '\n';

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

bool FavoriteManager::contains(const std::string& userID,
                               const std::string& petID) const
{
    const auto values = records();
    return std::find(values.begin(), values.end(),
                     std::make_pair(userID, petID)) != values.end();
}

bool FavoriteManager::add(const std::string& userID, const std::string& petID)
{
    if (userID.empty() || petID.empty() || contains(userID, petID))
        return false;

    auto values = records();
    values.emplace_back(userID, petID);
    return save(values);
}

bool FavoriteManager::remove(const std::string& userID,
                             const std::string& petID)
{
    auto values = records();
    const auto oldSize = values.size();
    values.erase(std::remove(values.begin(), values.end(),
                             std::make_pair(userID, petID)), values.end());

    return values.size() != oldSize && save(values);
}

std::vector<std::string> FavoriteManager::petIDsFor(
    const std::string& userID) const
{
    std::vector<std::string> result;
    for (const auto& record : records())
        if (record.first == userID)
            result.push_back(record.second);
    return result;
}

std::vector<Pet> FavoriteManager::petsFor(
    const std::string& userID, const std::vector<Pet>& pets) const
{
    const auto ids = petIDsFor(userID);
    std::vector<Pet> result;
    for (const Pet& pet : pets)
    {
        if (std::find(ids.begin(), ids.end(), pet.getPetID()) != ids.end())
            result.push_back(pet);
    }
    return result;
}
