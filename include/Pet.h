#ifndef PET_H
#define PET_H

#include <string>

class Pet {
public:
    Pet();
    Pet(int id,
        const std::string& name,
        const std::string& species,
        const std::string& breed,
        int age,
        const std::string& healthStatus,
        const std::string& adoptionStatus,
        const std::string& vaccinationStatus);

    int getId() const;
    const std::string& getName() const;
    const std::string& getSpecies() const;
    const std::string& getBreed() const;
    int getAge() const;
    const std::string& getHealthStatus() const;
    const std::string& getAdoptionStatus() const;
    const std::string& getVaccinationStatus() const;

    void setId(int id);
    void setName(const std::string& name);
    void setSpecies(const std::string& species);
    void setBreed(const std::string& breed);
    void setAge(int age);
    void setHealthStatus(const std::string& healthStatus);
    void setAdoptionStatus(const std::string& adoptionStatus);
    void setVaccinationStatus(const std::string& vaccinationStatus);

    void printDetails() const;

private:
    int id_;
    std::string name_;
    std::string species_;
    std::string breed_;
    int age_;
    std::string healthStatus_;
    std::string adoptionStatus_;
    std::string vaccinationStatus_;
};

#endif
