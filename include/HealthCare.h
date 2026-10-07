#ifndef HEALTH_CARE_H
#define HEALTH_CARE_H

#include <optional>
#include <string>
#include <vector>

struct HealthRecord {
    int petId;
    std::string lastVaccinationDate;
    std::string lastVetCheckupDate;
    std::string medicationReminder;
};

class CareSchedule {
public:
    void addOrUpdateRecord(const HealthRecord& record);
    std::optional<HealthRecord> getRecordByPetId(int petId) const;
    void printRecord(int petId) const;
    void printAllRecords() const;

private:
    std::vector<HealthRecord> records_;
};

#endif
