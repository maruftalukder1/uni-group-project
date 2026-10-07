#include "HealthCare.h"

#include <iostream>

void CareSchedule::addOrUpdateRecord(const HealthRecord& record) {
    for (auto& saved : records_) {
        if (saved.petId == record.petId) {
            saved = record;
            return;
        }
    }

    records_.push_back(record);
}

std::optional<HealthRecord> CareSchedule::getRecordByPetId(int petId) const {
    for (const auto& record : records_) {
        if (record.petId == petId) {
            return record;
        }
    }

    return std::nullopt;
}

void CareSchedule::printRecord(int petId) const {
    auto record = getRecordByPetId(petId);
    if (!record.has_value()) {
        std::cout << "No health record found for pet ID " << petId << ".\n";
        return;
    }

    // TODO: Member 3 implement feature here - include future reminder dates and alert status.
    std::cout << "Pet ID: " << record->petId << "\n"
              << "Last Vaccination: " << record->lastVaccinationDate << "\n"
              << "Last Vet Checkup: " << record->lastVetCheckupDate << "\n"
              << "Medication Reminder: " << record->medicationReminder << "\n";
}

void CareSchedule::printAllRecords() const {
    if (records_.empty()) {
        std::cout << "No health records available.\n";
        return;
    }

    for (const auto& record : records_) {
        std::cout << "-------------------------\n";
        std::cout << "Pet ID: " << record.petId << "\n"
                  << "Last Vaccination: " << record.lastVaccinationDate << "\n"
                  << "Last Vet Checkup: " << record.lastVetCheckupDate << "\n"
                  << "Medication Reminder: " << record.medicationReminder << "\n";
    }
}
