#include <iostream>
#include <string>

using namespace std;

int main() {
    string username, password;
    string registeredUsername, registeredPassword;
    int choice;

    while (true) {
        cout << "\n===== LOGIN AND REGISTER PANEL =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n===== REGISTER =====\n";
            cout << "Enter username: ";
            cin >> registeredUsername;
            cout << "Enter password: ";
            cin >> registeredPassword;

            cout << "Registration successful!\n";
        } else if (choice == 2) {
            if (registeredUsername.empty()) {
                cout << "Please register first!\n";
                continue;
            }

            cout << "\n===== LOGIN =====\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (username == registeredUsername &&
                password == registeredPassword) {
                cout << "Login successful! Welcome, "
                     << username << "!\n";
            } else {
                cout << "Invalid username or password!\n";
            }
        } else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
