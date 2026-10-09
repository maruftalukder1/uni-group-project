#ifndef PET_H
#define PET_H

#include <string>

class Pet
{
private:
    std::string petID;
    std::string name;
    std::string species;
    std::string breed;
    int age;
    std::string gender;
    std::string location;
    std::string status;   // "Available" or "Adopted"

public:
    Pet();
    Pet(const std::string& petID, const std::string& name,
        const std::string& species, const std::string& breed,
        int age, const std::string& gender,
        const std::string& location, const std::string& status);

    std::string getPetID() const;
    std::string getName() const;
    std::string getSpecies() const;
    std::string getBreed() const;
    int getAge() const;
    std::string getGender() const;
    std::string getLocation() const;
    std::string getStatus() const;

    void setStatus(const std::string& newStatus);

    bool isAvailable() const;
    void display() const;

    // petID|name|species|breed|age|gender|location|status
    std::string toFileString() const;
    static bool fromFileString(const std::string& line, Pet& out);
};

#endif