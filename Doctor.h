#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class DateTime {
public:
    int year, month, day, hour, minute;

    DateTime(int y = 0, int m = 0, int d = 0, int h = 0, int min = 0);
    string toString() const;
};

class Feedback {
public:
    string patientName;
    string content;
    DateTime date;

    Feedback(string pName, string cnt, DateTime dt);
};

class Doctor {
private:
    int doctorID;
    string name;
    int age;
    string gender;
    string specialty;
    char departmentID;
    map<string, vector<DateTime>> availableTimes;
    vector<DateTime> appointments;
    vector<Feedback> feedbacks;
    string username;
    string password;

public:
    Doctor(int docID, string n, int a, string g, string s, char dID, string user, string pass);

    bool login(string user, string pass);
    void showDoctorDashboard();
    void displayDoctorInfo() const;
    void addNewAvailableTime();
    void addAvailableTime(const string& day, const DateTime& time);
    void addAppointment(const DateTime& time);
    void addFeedback(const Feedback& feedback);
    void displayAvailableTimes() const;
    void displayAppointments() const;
    void displayFeedback() const;
    void logout();
    bool isValidDate(int y, int m, int d) const;
    bool isValidTime(int h, int min) const;
};

#endif 
