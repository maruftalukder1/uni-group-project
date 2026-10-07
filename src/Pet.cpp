#include "Pet.h"

#include <iostream>

Pet::Pet()
    : id_(0), age_(0), healthStatus_("Unknown"), adoptionStatus_("Available"), vaccinationStatus_("Pending") {}

Pet::Pet(int id,
         const std::string& name,
         const std::string& species,
         const std::string& breed,
         int age,
         const std::string& healthStatus,
         const std::string& adoptionStatus,
         const std::string& vaccinationStatus)
    : id_(id),
      name_(name),
      species_(species),
      breed_(breed),
      age_(age),
      healthStatus_(healthStatus),
      adoptionStatus_(adoptionStatus),
      vaccinationStatus_(vaccinationStatus) {}

int Pet::getId() const { return id_; }
const std::string& Pet::getName() const { return name_; }
const std::string& Pet::getSpecies() const { return species_; }
const std::string& Pet::getBreed() const { return breed_; }
int Pet::getAge() const { return age_; }
const std::string& Pet::getHealthStatus() const { return healthStatus_; }
const std::string& Pet::getAdoptionStatus() const { return adoptionStatus_; }
const std::string& Pet::getVaccinationStatus() const { return vaccinationStatus_; }

void Pet::setId(int id) { id_ = id; }
void Pet::setName(const std::string& name) { name_ = name; }
void Pet::setSpecies(const std::string& species) { species_ = species; }
void Pet::setBreed(const std::string& breed) { breed_ = breed; }
void Pet::setAge(int age) { age_ = age; }
void Pet::setHealthStatus(const std::string& healthStatus) { healthStatus_ = healthStatus; }
void Pet::setAdoptionStatus(const std::string& adoptionStatus) { adoptionStatus_ = adoptionStatus; }
void Pet::setVaccinationStatus(const std::string& vaccinationStatus) { vaccinationStatus_ = vaccinationStatus; }

void Pet::printDetails() const {
    std::cout << "ID: " << id_ << "\n"
              << "Name: " << name_ << "\n"
              << "Species: " << species_ << "\n"
              << "Breed: " << breed_ << "\n"
              << "Age: " << age_ << "\n"
              << "Health Status: " << healthStatus_ << "\n"
              << "Adoption Status: " << adoptionStatus_ << "\n"
              << "Vaccination Status: " << vaccinationStatus_ << "\n";
}
