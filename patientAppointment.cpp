#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Appointment {
public:
    string date;      // Appointment date (YYYY-MM-DD)
    string time;      // Appointment time (HH:MM AM/PM)
    string about;     // Reason for appointment
    string status;    // Status of appointment

    Appointment(const string& d, const string& t, const string& desc, const string& s = "Pending")
        : date(d), time(t), about(desc), status(s) {}

    void display() const {
        cout << "\n --- Appointment Details ---\n";
        cout << "Date: " << date << "\n";
        cout << "Time: " << time << "\n";
        cout << "About: " << about << "\n";
        cout << "Status: " << status << "\n";
    }
};

// Validate time format (HH:MM AM/PM)
bool isValidTime(const string& time) {
    if (time.length() < 7 || time.length() > 8) return false;
    string hourStr = time.substr(0, 2);
    string minuteStr = time.substr(3, 2);
    string period = time.substr(6, 2);
    if (time[2] != ':' || (period != "AM" && period != "PM")) return false;
    int hour = stoi(hourStr), minute = stoi(minuteStr);
    return (hour >= 1 && hour <= 12) && (minute >= 0 && minute < 60);
}

// Book a new appointment
void bookAppointment(vector<Appointment>& appointments) {
    string date, time, about;
    cout << "Enter appointment date (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, date);

    do {
        cout << "Enter appointment time (HH:MM AM/PM): ";
        getline(cin, time);
        if (isValidTime(time)) break;
        cout << "Invalid time format. Try again.\n";
    } while (true);

    cout << "Enter reason for appointment: ";
    getline(cin, about);

    appointments.emplace_back(date, time, about);
    cout << "Appointment booked successfully!\n";
}

// Check all appointments
void checkAppointments(const vector<Appointment>& appointments) {
    if (appointments.empty()) {
        cout << "No appointments found.\n";
        return;
    }
    cout << "\n---- Your Appointments ----\n";
    for (const auto& appointment : appointments) {
        appointment.display();
    }
}

// Cancel an appointment
void cancelAppointment(vector<Appointment>& appointments) {
    if (appointments.empty()) {
        cout << "No appointments to cancel.\n";
        return;
    }

    string date, time;
    cout << "Enter the date of the appointment to cancel (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, date);

    do {
        cout << "Enter the time of the appointment to cancel (HH:MM AM/PM): ";
        getline(cin, time);
        if (isValidTime(time)) break;
        cout << "Invalid time format. Try again.\n";
    } while (true);

    auto it = remove_if(appointments.begin(), appointments.end(),
                        [&date, &time](const Appointment& app) {
                            return app.date == date && app.time == time;
                        });

    if (it != appointments.end()) {
        appointments.erase(it, appointments.end());
        cout << "Appointment cancelled successfully!\n";
    } else {
        cout << "No matching appointment found.\n";
    }
}

int main() {
    vector<Appointment> appointments;

    while (true) {
        cout << "\nPatient Appointment System\n";
        cout << "1. Book Appointment\n";
        cout << "2. Check Appointments\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookAppointment(appointments);
                break;
            case 2:
                checkAppointments(appointments);
                break;
            case 3:
                cancelAppointment(appointments);
                break;
            case 4:
                cout << "Exiting... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
