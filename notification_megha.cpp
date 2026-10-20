#include <iostream>
#include <vector>
using namespace std;

class Notification {
public:
    string title;
    string message;

    Notification(string t, string m) {
        title = t;
        message = m;
    }

    void display() {
        cout << "\n[" << title << "] "
             << message << endl;
    }
};

int main() {
    vector<Notification> notifications;

    notifications.push_back(
        Notification("Welcome",
                     "User logged in successfully"));

    notifications.push_back(
        Notification("Alert",
                     "Low battery detected"));

    notifications.push_back(
        Notification("Update",
                     "Software updated successfully"));

    cout << "---- Notifications ----" << endl;

    for (auto &n : notifications) {
        n.display();
    }

    return 0;
}
