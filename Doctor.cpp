#include "Doctor.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

DateTime::DateTime(int y, int m, int d, int h, int min)
    : year(y), month(m), day(d), hour(h), minute(min) {}

string DateTime::toString() const {
    return to_string(year) + "-" + to_string(month) + "-" + to_string(day) +
           " " + to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
}

Feedback::Feedback(string pName, string cnt, DateTime dt)
    : patientName(pName), content(cnt), date(dt) {}

Doctor::Doctor(int docID, string n, int a, string g, string s, char dID, string user, string pass)
    : doctorID(docID), name(n), age(a), gender(g), specialty(s),
      departmentID(dID), username(user), password(pass) {}

bool Doctor::login(string user, string pass) {
    return (username == user && password == pass);
}

void Doctor::showDoctorDashboard() {
    int choice;
    do {
        cout << "\n=== Doctor Dashboard ===" << endl;
        cout << "1. View Personal Information" << endl;
        cout << "2. View Appointments" << endl;
        cout << "3. View Available Times" << endl;
        cout << "4. View Patient Feedback" << endl;
        cout << "5. Add Available Time" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayDoctorInfo();
                break;
            case 2:
                displayAppointments();
                break;
            case 3:
                displayAvailableTimes();
                break;
            case 4:
                displayFeedback();
                break;
            case 5:
                addNewAvailableTime();
                break;
            case 6:
                logout();
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);
}

void Doctor::displayDoctorInfo() const {
    cout << "\n=== Personal Information ===" << endl;
    cout << "Doctor ID: " << doctorID << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Specialization: " << specialty << endl;
    cout << "Department ID: " << departmentID << endl;
}

void Doctor::addNewAvailableTime() {
    string day;
    int y, m, d, h, min;

    cout << "Enter day (e.g., Monday): ";
    cin.ignore();
    getline(cin, day);

    cout << "Enter date and time (YYYY MM DD HH MM): ";
    while (!(cin >> y >> m >> d >> h >> min) || !isValidDate(y, m, d) || !isValidTime(h, min)) {
        cout << "Invalid input. Please enter valid date and time (YYYY MM DD HH MM): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    addAvailableTime(day, DateTime(y, m, d, h, min));
    cout << "Available time added successfully!" << endl;
}

void Doctor::addAvailableTime(const string& day, const DateTime& time) {
    availableTimes[day].push_back(time);
}

void Doctor::addAppointment(const DateTime& time) {
    appointments.push_back(time);
}

void Doctor::addFeedback(const Feedback& feedback) {
    feedbacks.push_back(feedback);
}

void Doctor::displayAvailableTimes() const {
    cout << "\n=== Available Times ===" << endl;
    for (const auto& day : availableTimes) {
        cout << day.first << ": ";
        for (const auto& time : day.second) {
            cout << time.toString() << " ";
        }
        cout << endl;
    }
}

void Doctor::displayAppointments() const {
    cout << "\n=== Current Appointments ===" << endl;
    for (const auto& appointment : appointments) {
        cout << appointment.toString() << endl;
    }
}

void Doctor::displayFeedback() const {
    cout << "\n=== Patient Feedback ===" << endl;
    for (const auto& feedback : feedbacks) {
        cout << "Patient: " << feedback.patientName << endl;
        cout << "Date: " << feedback.date.toString() << endl;
        cout << "Feedback: " << feedback.content << endl;
        cout << "------------------------" << endl;
    }
}

void Doctor::logout() {
    cout << name << " logged out successfully." << endl;
}

bool Doctor::isValidDate(int y, int m, int d) const {
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false;
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;
    if (m == 2) {
        return (d <= 28 || (d == 29 && (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0)));
    }
    return true;
}

bool Doctor::isValidTime(int h, int min) const {
    return (h >= 0 && h < 24 && min >= 0 && min < 60);
}
int main() {
    Doctor doctor1(1, "Dr. Ali", 45, "Male", "Cardiology", 'A', "smith", "password");
    doctor1.showDoctorDashboard(); 
    return 0;
}