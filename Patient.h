#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "function_insert_user.h"
using namespace std;

int patientPlatForm();

class Patient
{
private:
    string name;
    string gender;
    int id;
    int age;

public:
    Patient() {}
    Patient(int id, string n, string g, int a)
        : id(id), name(n), gender(g), age(a) {}

    string getName() const
    {
        return this->name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getGender() const
    {
        return this->gender;
    }

    void setGender(string gender)
    {
        this->gender = gender;
    }

    int getAge() const
    {
        return this->age;
    }

    void setAge(int age)
    {
        this->age = age;
    }
    int getid() const
    {
        return this->id;
    }

    void setid(int id)
    {
        this->id = id;
    }
    //void bookAppointment(vector<Patient *> &list, vector<Appointment *> &applist, vector<Doctor *> &doctorlist);
    int patientPlatForm();
    void information();
};

