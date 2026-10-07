#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Pet.h"

#include <string>
#include <vector>

namespace FileManager {

bool savePetsToCsv(const std::string& filePath, const std::vector<Pet>& pets);
bool loadPetsFromCsv(const std::string& filePath, std::vector<Pet>& pets);

}  // namespace FileManager

#endif
