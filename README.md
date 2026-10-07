# Local Pet Care & Adoption Matchmaker (CLI)

A beginner-friendly C++17 console starter architecture for a student project focused on local pet care tracking and adoption matching.

## Project Overview & Scope

This starter code demonstrates a clean and modular command-line architecture with separate responsibilities for pet profiles, adoption matching, health care records, and file persistence. It is intentionally lightweight so team members can safely expand each module without stepping on each other's code.

## Team Work Breakdown (5 Members)

- **Member 1 – Pet Profile & Registration**
  - Files: `/home/runner/work/uni-group-project/uni-group-project/include/Pet.h`, `/home/runner/work/uni-group-project/uni-group-project/src/Pet.cpp`
  - Focus: Pet class fields, registration workflow, profile display improvements.

- **Member 2 – Adoption & Matching Logic**
  - Files: `/home/runner/work/uni-group-project/uni-group-project/include/AdoptionMatchmaker.h`, `/home/runner/work/uni-group-project/uni-group-project/src/AdoptionMatchmaker.cpp`
  - Focus: Adopter criteria input and smarter compatibility scoring.

- **Member 3 – Health Care & Vet Records**
  - Files: `/home/runner/work/uni-group-project/uni-group-project/include/HealthCare.h`, `/home/runner/work/uni-group-project/uni-group-project/src/HealthCare.cpp`
  - Focus: Vaccination logs, vet visit history, medication reminder scheduling.

- **Member 4 – File I/O & Data Persistence**
  - Files: `/home/runner/work/uni-group-project/uni-group-project/include/FileManager.h`, `/home/runner/work/uni-group-project/uni-group-project/src/FileManager.cpp`
  - Focus: Robust CSV/TXT persistence, validation, and import/export handling.

- **Member 5 (Team Leader) – CLI Integration**
  - File: `/home/runner/work/uni-group-project/uni-group-project/src/main.cpp`
  - Focus: Main menu flow, module integration, and final polish across features.

## Build and Run

From the project root (`/home/runner/work/uni-group-project/uni-group-project`):

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o petmatchmaker
./petmatchmaker
```

## Current Starter Flow (Initial 10%)

- Register a sample pet.
- List pets currently available for adoption.
- Run a sample adoption match.
- Add and display a sample health record.
- Save/load pet data with a CSV file.

The source files include `// TODO: Member X implement feature here` markers for guided team development.
