#include "pet.h"
#include <iostream>
#include <sstream>
#include <vector>

Pet::Pet() : age(0) {}

Pet::Pet(const std::string& petID, const std::string& name,
         const std::string& species, const std::string& breed,
         int age, const std::string& gender,
         const std::string& location, const std::string& status)
    : petID(petID), name(name), species(species), breed(breed),
      age(age), gender(gender), location(location), status(status) {}

std::string Pet::getPetID() const    { return petID; }
std::string Pet::getName() const     { return name; }
std::string Pet::getSpecies() const  { return species; }
std::string Pet::getBreed() const    { return breed; }
int Pet::getAge() const              { return age; }
std::string Pet::getGender() const   { return gender; }
std::string Pet::getLocation() const { return location; }
std::string Pet::getStatus() const   { return status; }

void Pet::setStatus(const std::string& newStatus) { status = newStatus; }

bool Pet::isAvailable() const { return status == "Available"; }

void Pet::display() const
{
    std::cout << petID << " | " << name << " | " << species << " | "
              << breed << " | " << age << " yrs | " << gender << " | "
              << location << " | " << status << std::endl;
}

std::string Pet::toFileString() const
{
    return petID + "|" + name + "|" + species + "|" + breed + "|" +
           std::to_string(age) + "|" + gender + "|" + location + "|" + status;
}

bool Pet::fromFileString(const std::string& line, Pet& out)
{
    std::stringstream ss(line);
    std::string field;
    std::vector<std::string> parts;

    while (std::getline(ss, field, '|'))
    {
        parts.push_back(field);
    }

    if (parts.size() != 8) return false;

    try
    {
        out = Pet(parts[0], parts[1], parts[2], parts[3],
                  std::stoi(parts[4]), parts[5], parts[6], parts[7]);
    }
    catch (...)
    {
        return false;
    }

    return true;
}