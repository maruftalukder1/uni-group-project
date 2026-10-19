#ifndef FAVORITES_H
#define FAVORITES_H

#include <string>
#include <vector>
#include "pet.h"

class FavoriteManager
{
public:
    explicit FavoriteManager(std::string fileName = "data/favorites.txt");

    bool add(const std::string& userID, const std::string& petID);
    bool remove(const std::string& userID, const std::string& petID);
    bool contains(const std::string& userID, const std::string& petID) const;
    std::vector<std::string> petIDsFor(const std::string& userID) const;
    std::vector<Pet> petsFor(const std::string& userID,
                             const std::vector<Pet>& pets) const;

private:
    std::string fileName;
    std::vector<std::pair<std::string, std::string>> records() const;
    bool save(const std::vector<std::pair<std::string, std::string>>& records) const;
};

#endif
