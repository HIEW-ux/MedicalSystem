#include <map>
#include <iomanip>
#include <vector>
#include <limits>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <regex>
#include "sqlite3.h"
using namespace std;
// Class forward declaration
class User;
class Patient;
class Doctor;
class Allergy;
class InsuranceList;
class Payment;
class EmergencyContact;
class Department;
class MedicalRecords;
class PatientAddress;
class Service;
class Appointment;
class feedback;
class Medicine;
class Prescription;
class Admin;
// linked list
struct UserNode
{
    string username;
    string password;
    string phonenumber;
    string ic;
    string role;
    int id;
    UserNode *next;

    UserNode() : next(nullptr) {}
    UserNode(const string &username, const string &password, const string &phonenumber, const string &ic, const string &role)
        : username(username), password(password), phonenumber(phonenumber), ic(ic), role(role), next(nullptr) {}
    void setID(int id)
    {
        this->id = id;
    }
};
struct PatientNode
{
    string name;
    string gender;
    int id;
    int age;
    int userid;
    PatientNode *next;

    PatientNode() {}
    PatientNode(const string &n, const string &g, int a, int userid)
        : name(n), gender(g), age(a), userid(userid), next(nullptr) {}

    void setID(int id)
    {
        this->id = id;
    }
};
struct DoctorNode
{
    int doctorID;
    string name;
    int age;
    string gender;
    string specialty;
    int userid;
    int departmentid;
    DoctorNode *next;

    DoctorNode() {}
    DoctorNode(const string &name, int age, const string &specialty, const string &gender, int userid, int departmentid)
        : name(name), age(age), specialty(specialty), gender(gender), userid(userid), departmentid(departmentid) {}

    void setID(int id)
    {
        this->doctorID = id;
    }
};
struct AllergyNode
{
    int AllergyID;
    string name;
    string severity;
    AllergyNode *next;

    AllergyNode() {}
    AllergyNode(int allergy_id, const string &allergy_name, const string &allergy_severity)
        : AllergyID(allergy_id), name(allergy_name), severity(allergy_severity), next(nullptr) {}

    void setID(int id)
    {
        this->AllergyID = id;
    }
};
struct EmergencyContactNode
{
    int contactid;
    int patientid;
    string contactName;
    string phoneNumber;
    string relationShip;
    EmergencyContactNode *next;

    EmergencyContactNode() : next(nullptr) {}
    EmergencyContactNode(int patientid, string contactName, string phoneNumber, string relationShip)
        : patientid(patientid), contactName(contactName), phoneNumber(phoneNumber), relationShip(relationShip), next(nullptr) {}

    void setID(int id)
    {
        this->contactid = id;
    }
};
struct DepartmentNode
{
    int Departmentid;
    int Hospitalid;
    string DepartmentName;
    string HeadofDepartment;
    DepartmentNode *next;

    DepartmentNode() {}
    DepartmentNode(int id, int Hospitalid, const string &Name, const string &Head)
        : Departmentid(id), Hospitalid(Hospitalid), DepartmentName(Name), HeadofDepartment(Head), next(nullptr) {}
};
struct InsuranceNode
{
    int insuranceid;
    string providerName;
    double coveragePercentage;
    InsuranceNode *next;

    InsuranceNode() {}
    InsuranceNode(int insuranceid, string provider, double coverage)
        : insuranceid(insuranceid), providerName(provider), coveragePercentage(coverage), next(nullptr) {}
};
struct MedicalRecordsNode
{
    int recordID;
    string date;
    string details;
    int patientID;
    int doctorID;
    MedicalRecordsNode *next;

    MedicalRecordsNode() {}
    MedicalRecordsNode(const string &date, const string &details, int patientID, int doctorID)
        : date(date), details(details), patientID(patientID), doctorID(doctorID), next(nullptr)
    {
    }
    void setRecordID(int id)
    {
        recordID = id;
    }
};
struct PaymentNode
{
    int PaymentID;
    int amount;
    string date;
    string time;
    string paymentMethod;
    int AppointmentID;
    PaymentNode *next;

    PaymentNode() {}
    PaymentNode(int amount, const string &date, const string &time, const string &Method, int AppointmentID)
        : amount(amount), date(date), time(time), paymentMethod(Method), AppointmentID(AppointmentID), next(nullptr) {}

    void setID(int id)
    {
        this->PaymentID = id;
    }
};
struct AddressNode
{
    int PatientID;
    string country;
    string city;
    string street;
    string postcode;
    AddressNode *next;

    AddressNode() {}
    AddressNode(int PatientID, const string &country, const string &city, const string &street, const string &postcode)
        : PatientID(PatientID), country(country), city(city), street(street), postcode(postcode), next(nullptr) {}
};
struct ServiceNode
{
    int ServiceID;
    string name;
    int price;
    string category;
    ServiceNode *next;

    ServiceNode() {}
    ServiceNode(int ID, const string &name, int price, const string &category)
        : ServiceID(ID), name(name), price(price), category(category), next(nullptr) {}
};
struct AppointmentNode
{
    int AppointmentID;
    string date;
    string time;
    string status;
    int PatientID;
    int DoctorID;
    int ServiceID;
    AppointmentNode *next;

    AppointmentNode() {}
    AppointmentNode(const string &date, const string &time, const string &status, int PatientID, int DoctorID, int ServiceID)
        : date(date), time(time), status(status), PatientID(PatientID), DoctorID(DoctorID), ServiceID(ServiceID), next(nullptr) {}

    void setID(int id)
    {
        AppointmentID = id;
    }
};
struct FeedbackNode
{
    int feedbackID;
    string describe;
    int rating;
    int patientID;
    int doctorID;
    int appointmentID;
    FeedbackNode *next;

    FeedbackNode() {}
    FeedbackNode(const string &describe, int rating, int patientID, int doctorID, int appointmentID)
        : describe(describe), rating(rating), patientID(patientID), doctorID(doctorID), appointmentID(appointmentID), next(nullptr) {}

    void setID(int id)
    {
        this->feedbackID = id;
    }
};
struct MedicineNode
{
    int MedicineID;
    string name;
    string description;
    MedicineNode *next;

    MedicineNode() {}
    MedicineNode(const string &name, const string &description)
        : name(name), description(description), next(nullptr) {}

    void setID(int id)
    {
        this->MedicineID = id;
    }
};
struct PrescriptionNode
{
    int PrescriptionID;
    int PatientID;
    string date;
    string instructions;
    int DoctorID;
    PrescriptionNode *next;

    PrescriptionNode() {}

    PrescriptionNode(int PatientID, const string &date, const string &instruction, int DoctorID)
        : PatientID(PatientID), date(date), instructions(instruction), DoctorID(DoctorID), next(nullptr) {}

    void setID(int id)
    {
        this->PrescriptionID = id;
    }
};
struct AdminNode
{
    int AdminID;
    string name;
    int UserID;
    AdminNode *next;

    AdminNode() {}
    AdminNode(const string &name, int UserID)
        : name(name), UserID(UserID), next(nullptr) {}

    void setID(int id)
    {
        this->AdminID = id;
    }
};
// Class
class User
{
private:
    UserNode *head;
    UserNode *tail;

public:
    User() : head(nullptr), tail(nullptr) {}
    ~User()
    {
        clear();
    }
    void addUser(const UserNode &user)
    {
        UserNode *newUser = new UserNode(user);
        if (!head)
        {
            head = newUser;
            tail = newUser;
        }
        else
        {
            tail->next = newUser;
            tail = newUser;
        }
    }
    bool findUser(int id)
    {
        UserNode *current = head;
        while (current != nullptr)
        {
            if (current->id == id)
            {
                cout << "-----------------------------------------\n";
                cout << "User found:\n";
                cout << "ID: " << current->id << "\n";
                cout << "Username: " << current->username << "\n";
                cout << "Password: " << current->password << "\n";
                cout << "Phone Number: " << current->phonenumber << "\n";
                cout << "IC: " << current->ic << "\n";
                cout << "-----------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        cout << "Doctor with ID " << id << " not found!\n"
             << endl;
        return false;
    }
    void displayUser() const
    {
        UserNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "ID: " << current->id << "\n";
            cout << "Username: " << current->username << "\n";
            cout << "Password: " << current->password << "\n";
            cout << "Phone Number: " << current->phonenumber << "\n";
            cout << "IC: " << current->ic << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
    bool isDuplicate(const string &username)
    {
        UserNode *current = head;
        while (current != nullptr)
        {
            if (current->username == username)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    bool loginAuth(const string &username, const string &password, const string &role)
    {
        UserNode *current = head;
        while (current != nullptr)
        {
            if (current->username == username && current->password == password && current->role == role)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void updateUser(UserNode *user)
    {
        UserNode *current = head;
        while (current != nullptr)
        {
            if (current->id == user->id)
            {
                current->username = user->username;
                current->password = user->password;
                current->phonenumber = user->phonenumber;
                current->ic = user->ic;
                break;
            }
            current = current->next;
        }
    }
    void deleteUser(int userID)
    {
        UserNode *current = head;
        UserNode *previous = nullptr;

        while (current != nullptr)
        {
            if (current->id == userID)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == tail)
                {
                    tail = previous;
                }

                delete current;
                cout << "User with ID " << userID << " deleted.\n";
                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "User with ID " << userID << " not found.\n";
    }
    void clear()
    {
        UserNode *current = head;
        while (current != nullptr)
        {
            UserNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
class Patient
{
private:
    PatientNode *head;
    PatientNode *tail;

public:
    Patient() : head(nullptr), tail(nullptr) {}
    ~Patient()
    {
        clear();
    }
    void addPatient(const PatientNode &patient)
    {
        PatientNode *newPatient = new PatientNode(patient);
        if (!head)
        {
            head = newPatient;
            tail = newPatient;
        }
        else
        {
            tail->next = newPatient;
            tail = newPatient;
        }
    }
    bool findPatient(int id)
    {
        PatientNode *current = head;
        while (current != nullptr)
        {
            if (current->id == id)
            {
                cout << "-----------------------------------------\n";
                cout << "Patient found:\n";
                cout << "ID: " << current->id << "\n";
                cout << "Name: " << current->name << "\n";
                cout << "Age: " << current->age << "\n";
                cout << "Gender: " << current->gender << "\n";
                cout << "-----------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        cout << "Patient with ID " << id << " not found!\n"
             << endl;
        return false;
    }
    void displayPatients() const
    {
        PatientNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "ID: " << current->id << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "Age: " << current->age << "\n";
            cout << "Gender: " << current->gender << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
    void updatePatient(PatientNode *patient)
    {
        PatientNode *current = head;
        while (current != nullptr)
        {
            if (current->id == patient->id)
            {
                current->name = patient->name;
                current->age = patient->age;
                current->gender = patient->gender;
                break;
            }
            current = current->next;
        }
    }
    void deletePatient(int PatientID)
    {
        PatientNode *current = head;
        PatientNode *previous = nullptr;

        while (current != nullptr)
        {
            if (current->id == PatientID)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == tail)
                {
                    tail = previous;
                }

                delete current;
                cout << "Patient with ID " << PatientID << " deleted.\n";
                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "Patient with ID " << PatientID << " not found.\n";
    }
    void clear()
    {
        PatientNode *current = head;
        while (current != nullptr)
        {
            PatientNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
class Doctor
{
private:
    DoctorNode *head;
    DoctorNode *tail;

public:
    Doctor() : head(nullptr), tail(nullptr) {}
    ~Doctor()
    {
        clear();
    }
    void addDoctor(const DoctorNode &doctor)
    {
        DoctorNode *newDoctor = new DoctorNode(doctor);
        if (!head)
        {
            head = newDoctor;
            tail = newDoctor;
        }
        else
        {
            tail->next = newDoctor;
            tail = newDoctor;
        }
    }
    bool findDoctor(int id)
    {
        DoctorNode *current = head;
        while (current != nullptr)
        {
            if (current->doctorID == id)
            {
                cout << "-----------------------------------------\n";
                cout << "Doctor found:\n";
                cout << "ID: " << current->doctorID << "\n";
                cout << "Name: " << current->name << "\n";
                cout << "Age: " << current->age << "\n";
                cout << "Gender: " << current->gender << "\n";
                cout << "Specialty: " << current->specialty << "\n";
                cout << "-----------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        cout << "Doctor with ID " << id << " not found!\n";
        return false;
    }
    void displayDoctors() const
    {
        DoctorNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "ID: " << current->doctorID << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "Age: " << current->age << "\n";
            cout << "Gender: " << current->gender << "\n";
            cout << "Specialty: " << current->specialty << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
   void bubbleSorting() {
    if (!head || !head->next) {
        return;
    }

    bool swapped;
    DoctorNode* end = nullptr;

    do {
        swapped = false;
        DoctorNode* prev = nullptr;
        DoctorNode* current = head;

        while (current->next != end) {
            if (current->age > current->next->age) {
                DoctorNode* temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if (prev) {
                    prev->next = temp;
                } else {
                    head = temp; 
                }

                swapped = true;
                prev = temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
        end = current;
    } while (swapped);
}

    void updateDoctor(DoctorNode *doctor)
    {
        DoctorNode *current = head;
        while (current != nullptr)
        {
            if (current->doctorID == doctor->doctorID)
            {
                current->name = doctor->name;
                current->age = doctor->age;
                current->gender = doctor->gender;
                current->specialty = doctor->specialty;
                current->departmentid = doctor->departmentid;
                break;
            }
            current = current->next;
        }
    }
    void deleteDoctor(int DoctorID)
    {
        DoctorNode *current = head;
        DoctorNode *previous = nullptr;

        while (current != nullptr)
        {
            if (current->doctorID == DoctorID)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == tail)
                {
                    tail = previous;
                }

                delete current;
                cout << "Doctor with ID " << DoctorID << " deleted.\n";
                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "Doctor with ID " << DoctorID << " not found.\n";
    }
    void clear()
    {
        DoctorNode *current = head;
        while (current != nullptr)
        {
            DoctorNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
class Allergy
{
private:
    AllergyNode *head;
    AllergyNode *tail;

public:
    Allergy() : head(nullptr), tail(nullptr) {}
    ~Allergy()
    {
        AllergyNode *current = head;
        while (current != nullptr)
        {
            AllergyNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addAllergy(const AllergyNode &allergy)
    {
        AllergyNode *newAllergy = new AllergyNode(allergy);
        if (!head)
        {
            head = newAllergy;
            tail = newAllergy;
        }
        else
        {
            tail->next = newAllergy;
            tail = newAllergy;
        }
    }
    bool findAllergy(int id)
    {
        AllergyNode *current = head;
        while (current != nullptr)
        {
            if (current->AllergyID == id)
            {
                cout << "-----------------------------------------\n";
                cout << "Allergy found:\n";
                cout << "ID: " << current->AllergyID << "\n";
                cout << "Name: " << current->name << "\n";
                cout << "Severity: " << current->severity << "\n";
                cout << "-----------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        cout << "Allergy with ID " << id << " not found!\n"
             << endl;
        return false;
    }
    void displayAllergy() const
    {
        AllergyNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "ID: " << current->AllergyID << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "Severity: " << current->severity << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
};
class Insurance
{
private:
    InsuranceNode *head;
    InsuranceNode *tail;

public:
    Insurance() : head(nullptr), tail(nullptr) {}

    void addProvider(int InsuranceID, const string &provider, double coverage)
    {
        InsuranceNode *newNode = new InsuranceNode(InsuranceID, provider, coverage);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Display insurance providers
    void displayProviders() const
    {
        InsuranceNode *current = head;
        cout << "\n--------------- Available Insurance Providers --------------\n";
        while (current != nullptr)
        {
            cout << "-------------------------------------------------------------\n";
            cout << "Insurance ID: " << current->insuranceid << "\n";
            cout << "Provider Name: " << current->providerName << "\n";
            cout << "Coverage Percentage: " << current->coveragePercentage << "\n";
            cout << "-------------------------------------------------------------\n";
            current = current->next;
        }
    }

    ~Insurance()
    {
        while (head != nullptr)
        {
            InsuranceNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};
class Payment
{
private:
    PaymentNode *head;
    PaymentNode *tail;

public:
    Payment() : head(nullptr), tail(nullptr) {}
    ~Payment()
    {
        PaymentNode *current = head;
        while (current != nullptr)
        {
            PaymentNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addPayment(const PaymentNode &payment)
    {
        PaymentNode *newPayment = new PaymentNode(payment);
        if (!head)
        {
            head = newPayment;
            tail = newPayment;
        }
        else
        {
            tail->next = newPayment;
            tail = newPayment;
        }
    }
    bool findPayment(int id)
    {
        PaymentNode *current = head;
        while (current != nullptr)
        {
            if (current->PaymentID == id)
            {
                cout << "-----------------------------------------\n";
                cout << "Payment found:\n";
                cout << "ID: " << current->PaymentID << "\n";
                cout << "Amount: " << current->amount << "\n";
                cout << "Date: " << current->date << "\n";
                cout << "Time: " << current->time << "\n";
                cout << "Method: " << current->paymentMethod << "\n";
                cout << "Appointment ID: " << current->AppointmentID << "\n";
                cout << "-----------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        cout << "Payment with ID " << id << " not found!\n"
             << endl;
        return false;
    }
    void displayPayments() const
    {
        PaymentNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "ID: " << current->PaymentID << "\n";
            cout << "Amount: " << current->amount << "\n";
            cout << "Date: " << current->date << "\n";
            cout << "Time: " << current->time << "\n";
            cout << "Method: " << current->paymentMethod << "\n";
            cout << "Appointment ID: " << current->AppointmentID << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
};
class EmergencyContact
{
private:
    EmergencyContactNode *head;
    EmergencyContactNode *tail;

public:
    EmergencyContact() : head(nullptr), tail(nullptr) {}
    ~EmergencyContact()
    {
        EmergencyContactNode *current = head;
        while (current != nullptr)
        {
            EmergencyContactNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addEmergencyContact(const EmergencyContactNode &emergency)
    {
        EmergencyContactNode *newEmergency = new EmergencyContactNode(emergency);
        if (!head)
        {
            head = newEmergency;
            tail = newEmergency;
        }
        else
        {
            tail->next = newEmergency;
            tail = newEmergency;
        }
    }
    bool findEmergencyContact(int id)
    {
        EmergencyContactNode *current = head;
        while (current != nullptr)
        {
            if (current->patientid == id)
            {
                cout << "-----------------------------------------\n";
                cout << "Emergency contact found:\n";
                cout << "ID: " << current->contactid << "\n";
                cout << "Name: " << current->contactName << "\n";
                cout << "Phone number: " << current->phoneNumber << "\n";
                cout << "Relationship: " << current->relationShip << "\n";
                cout << "Patient ID: " << current->patientid << "\n";
                cout << "-----------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        cout << "Emergency contact with ID " << id << " not found!\n"
             << endl;
        return false;
    }
    void displayEmergencyContact() const
    {
        EmergencyContactNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "ID: " << current->contactid << "\n";
            cout << "Name: " << current->contactName << "\n";
            cout << "Phone number: " << current->phoneNumber << "\n";
            cout << "Relationship: " << current->relationShip << "\n";
            cout << "Patient ID: " << current->patientid << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
};
class Department
{
private:
    DepartmentNode *head;
    DepartmentNode *tail;

public:
    Department() : head(nullptr), tail(nullptr) {}
    ~Department()
    {
        clear();
    }
    // Insert new record
    void InsertDepartment(const DepartmentNode &dept)
    {
        DepartmentNode *newNode = new DepartmentNode(dept);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    // Printing Department Info
    void printDepartment() const
    {
        DepartmentNode *current = head;
        while (current != nullptr)
        {
            cout << "Department ID: " << current->Departmentid << "\n"
                 << "Hospital ID: " << current->Hospitalid << "\n"
                 << "Department Name: " << current->DepartmentName << "\n"
                 << "head of Department: " << current->HeadofDepartment << "\n";
            cout << "------------------------------------------\n";
            current = current->next;
        }
    }

    bool exists(string &deptname) const
    {
        DepartmentNode *current = head;
        while (current != nullptr)
        {
            if (current->DepartmentName == deptname)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void clear()
    {
        DepartmentNode *current = head;
        while (current != nullptr)
        {
            DepartmentNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
class MedicalRecords
{
private:
    MedicalRecordsNode *head;
    MedicalRecordsNode *tail;

public:
    MedicalRecords() : head(nullptr), tail(nullptr) {}
    ~MedicalRecords()
    {
        clear();
    }
    void displayPatientMedicalRecords(int id)
    {
        MedicalRecordsNode *current = head;
        bool found = false;
        while (current != nullptr)
        {
            if (current->patientID == id)
            {
                if (!found)
                {
                    cout << "Found medical records for Patient ID " << id << ":\n";
                    found = true;
                }
                cout << "-----------------------------------------\n";
                cout << "Record ID: " << current->recordID
                     << "\n Doctor ID: " << current->doctorID
                     << "\n Patient ID: " << current->patientID
                     << "\n Details: " << current->details
                     << "\n Date: " << current->date << endl;
                cout << "-----------------------------------------\n";
            }
            current = current->next;
        }
        if (!found)
        {
            cout << "No records found for Patient ID " << id << "\n";
        }
    }
    void displayDoctorMedicalRecords(int id)
    {
        MedicalRecordsNode *current = head;
        bool found = false;
        while (current != nullptr)
        {
            if (current->doctorID == id)
            {
                if (!found)
                {
                    cout << "Found medical records for Doctor ID " << id << ":\n";
                    found = true;
                }
                cout << "-----------------------------------------\n";
                cout << "Record ID: " << current->recordID
                     << "\n Doctor ID: " << current->doctorID
                     << "\n Patient ID: " << current->patientID
                     << "\n Details: " << current->details
                     << "\n Date: " << current->date << endl;
                cout << "-----------------------------------------\n";
            }
            current = current->next;
        }
        if (!found)
        {
            cout << "No records found for Doctor ID " << id << "\n";
        }
    }
    void addRecords(const MedicalRecordsNode &record)
    {
        MedicalRecordsNode *newRecord = new MedicalRecordsNode(record);
        if (!head)
        {
            head = newRecord;
            tail = newRecord;
        }
        else
        {
            tail->next = newRecord;
            tail = newRecord;
        }
    }
    void displayRecords() const
    {
        MedicalRecordsNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "Record ID: " << current->recordID
                 << "\n Doctor ID: " << current->doctorID
                 << "\n Patient ID: " << current->patientID
                 << "\n Details: " << current->details
                 << "\n Date: " << current->date << endl;
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
    void clear()
    {
        MedicalRecordsNode *current = head;
        while (current != nullptr)
        {
            MedicalRecordsNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
class PatientAddress
{
private:
    AddressNode *head;
    AddressNode *tail;

public:
    PatientAddress() : head(nullptr), tail(nullptr) {}
    ~PatientAddress()
    {
        clear();
    }
    void addAddress(const AddressNode &address)
    {
        AddressNode *newAddress = new AddressNode(address);
        if (!head)
        {
            head = newAddress;
            tail = newAddress;
        }
        else
        {
            tail->next = newAddress;
            tail = newAddress;
        }
    }
    bool findAddress(int id)
    {
        AddressNode *current = head;
        while (current != nullptr)
        {
            if (current->PatientID == id)
            {
                cout << "Address found: " << "\n";
                cout << "Country: " << current->country << "\n";
                cout << "City: " << current->city << "\n";
                cout << "Street: " << current->street << "\n";
                cout << "Postal Code: " << current->postcode << "\n";
                return true;
            }
            current = current->next;
        }
        cout << "Patient address with patient ID " << id << " not found!\n"
             << endl;
        return false;
    }
    void clear()
    {
        AddressNode *current = head;
        while (current != nullptr)
        {
            AddressNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
class Service
{
private:
    ServiceNode *head;
    ServiceNode *tail;

public:
    Service() : head(nullptr), tail(nullptr) {}
    void InsertService(int ID, const string &name, int price, const string &category)
    {
        ServiceNode *newService = new ServiceNode(ID, name, price, category);
        if (!head)
        {
            head = newService;
            tail = newService;
        }
        else
        {
            tail->next = newService;
            tail = newService;
        }
    }
    void displayService()
    {
        ServiceNode *current = head;
        cout << "\n--- Available Health Services ---\n";
        while (current != nullptr)
        {
            cout << "-------------------------------------------------------------\n";
            cout << "Service ID: " << current->ServiceID << "\n";
            cout << "Service Name: " << current->name << "\n";
            cout << "Price: " << current->price << "\n";
            cout << "category: " << current->category << "\n";
            cout << "-------------------------------------------------------------\n";
            current = current->next;
        }
    }
    ~Service()
    {
        while (head != nullptr)
        {
            ServiceNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};
class Appointment
{
private:
    AppointmentNode *head;
    AppointmentNode *tail;

public:
    Appointment() : head(nullptr), tail(nullptr) {}
    ~Appointment()
     {
        AppointmentNode *current = head;
        while (current != nullptr)
        {
            AppointmentNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addAppointment(const AppointmentNode &appointment)
    {
        AppointmentNode *newAppointment = new AppointmentNode(appointment);
        if (!head)
        {
            head = newAppointment;
            tail = newAppointment;
        }
        else
        {
            tail->next = newAppointment;
            tail = newAppointment;
        }
    }
    // For patient to view their appointment
    void displayPatientAppointments(int id)
    {
        vector<AppointmentNode *> result;
        AppointmentNode *current = head;
        while (current != nullptr)
        {
            if (current->PatientID == id)
            {
                result.push_back(current);
            }
            current = current->next;
        }
        if (!result.empty())
        {
            cout << "Found appointments for Patient ID " << id << ":\n";
            for (const auto &app : result)
            {
                cout << "------------------------------------------\n";
                cout << "Appointment ID: " << app->AppointmentID << "\n"
                     << "Date: " << app->date << "\n"
                     << "Time: " << app->time << "\n"
                     << "Status: " << app->status << "\n"
                     << "Patient ID: " << app->PatientID << "\n"
                     << "Doctor ID: " << app->DoctorID << "\n"
                     << "Service ID: " << app->ServiceID << "\n";
                cout << "------------------------------------------\n";
            }
        }
        else
        {
            cout << "No records found for Patient ID " << id << "\n";
        }
    }
    // For patient view appointments uncompleted
    bool displayPatientPendingAppointments(int id)
    {
        vector<AppointmentNode *> result;
        AppointmentNode *current = head;
        while (current != nullptr)
        {
            if (current->PatientID == id && current->status != "Paid")
            {
                result.push_back(current);
            }
            current = current->next;
        }
        if (!result.empty())
        {
            cout << "Found appointments for Patient ID " << id << ":\n";
            for (const auto &app : result)
            {
                cout << "------------------------------------------\n";
                cout << "Appointment ID: " << app->AppointmentID << "\n"
                     << "Date: " << app->date << "\n"
                     << "Time: " << app->time << "\n"
                     << "Status: " << app->status << "\n"
                     << "Patient ID: " << app->PatientID << "\n"
                     << "Doctor ID: " << app->DoctorID << "\n"
                     << "Service ID: " << app->ServiceID << "\n";
                cout << "------------------------------------------\n";
            }
            return true;
        }
        else
        {
            cout << "No records found for Patient ID " << id << "\n";
            return false;
        }
    }
    // For doctor to view their appointment
    void displayDoctorAppointments(int id)
    {
        vector<AppointmentNode *> result;
        AppointmentNode *current = head;
        while (current != nullptr)
        {
            if (current->DoctorID == id)
            {
                result.push_back(current);
            }
            current = current->next;
        }
        if (!result.empty())
        {
            cout << "Found appointments for Patient ID " << id << ":\n";
            for (const auto &app : result)
            {
                cout << "------------------------------------------\n";
                cout << "Appointment ID: " << app->AppointmentID << "\n"
                     << "Date: " << app->date << "\n"
                     << "Time: " << app->time << "\n"
                     << "Status: " << app->status << "\n"
                     << "Patient ID: " << app->PatientID << "\n"
                     << "Doctor ID: " << app->DoctorID << "\n"
                     << "Service ID: " << app->ServiceID << "\n";
                cout << "------------------------------------------\n";
            }
        }
        else
        {
            cout << "No records found for Doctor ID " << id << "\n";
        }
    }
     void displayAppointment()
    {
        AppointmentNode *current = head;
        cout << "\n--- Appointment history ---\n";
        while (current != nullptr)
        {
            cout << "------------------------------------------\n";
                cout << "Appointment ID: " << current->AppointmentID << "\n"
                     << "Date: " << current->date << "\n"
                     << "Time: " << current->time << "\n"
                     << "Status: " << current->status << "\n"
                     << "Patient ID: " << current->PatientID << "\n"
                     << "Doctor ID: " << current->DoctorID << "\n"
                     << "Service ID: " << current->ServiceID << "\n";
                cout << "------------------------------------------\n";
            current = current->next;
        }
    }
    bool findAppointment(int id)
    {
        AppointmentNode *current = head;
        while (current != nullptr)
        {
            if (current->AppointmentID == id)
            {
                cout << "------------------------------------------\n";
                cout << "Appointment found:\n";
                cout << "Appointment ID: " << current->AppointmentID << "\n"
                     << "Date: " << current->date << "\n"
                     << "Time: " << current->time << "\n"
                     << "Status: " << current->status << "\n"
                     << "Patient ID: " << current->PatientID << "\n"
                     << "Doctor ID: " << current->DoctorID << "\n"
                     << "Service ID: " << current->ServiceID << "\n";
                cout << "------------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void bubbleSorting() {
    bool swapped;
    AppointmentNode* end = nullptr;

    do {
        swapped = false;
        AppointmentNode* prev = nullptr;
        AppointmentNode* current = head;
        AppointmentNode* temp = nullptr;

        while (current->next != end) {
            if (current->date > current->next->date) {
                temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if (prev) {
                    prev->next = temp;
                } else {
                    head = temp;
                }

                swapped = true;
            }

            prev = (swapped ? temp : current);
            current = prev->next;
        }
        end = current;
    } while (swapped);
}
    void updateAppointment(AppointmentNode *appointment)
    {
        AppointmentNode *current = head;
        while (current != nullptr)
        {
            if (current->AppointmentID == appointment->AppointmentID)
            {
                current->date = appointment->date;
                current->DoctorID = appointment->DoctorID;
                current->ServiceID = appointment->ServiceID;
                current->time = appointment->time;
                break;
            }
            current = current->next;
        }
    }
    void deleteAppointment(int AppointmentID)
    {
        AppointmentNode *current = head;
        AppointmentNode *previous = nullptr;

        while (current != nullptr)
        {
            if (current->AppointmentID == AppointmentID)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == tail)
                {
                    tail = previous;
                }

                delete current;
                cout << "Appointment with ID " << AppointmentID << " deleted.\n";
                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "Appointment with ID " << AppointmentID << " not found.\n";
    }

};
class Feedback
{
private:
    FeedbackNode *head;
    FeedbackNode *tail;

public:
    Feedback() : head(nullptr), tail(nullptr) {}
    ~Feedback()
    {
        FeedbackNode *current = head;
        while (current != nullptr)
        {
            FeedbackNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addFeedback(const FeedbackNode &feedback)
    {
        FeedbackNode *newFeedback = new FeedbackNode(feedback);
        if (!head)
        {
            head = newFeedback;
            tail = newFeedback;
        }
        else
        {
            tail->next = newFeedback;
            tail = newFeedback;
        }
    }
    bool findFeedback(int id)
    {
        FeedbackNode *current = head;
        while (current != nullptr)
        {
            if (current->feedbackID == id)
            {
                cout << "feedback found: " << "\n";
                cout << "feedback ID: " << current->feedbackID << "\n";
                cout << "Describe: " << current->describe << "\n";
                cout << "Rating: " << current->rating << "\n";
                cout << "Appointment ID: " << current->appointmentID << "\n";
                cout << "Patient ID: " << current->patientID << "\n";
                cout << "Doctor ID: " << current->doctorID << "\n";
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void displayFeedback() const
    {
        FeedbackNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "feedback ID: " << current->feedbackID << "\n";
            cout << "Describe: " << current->describe << "\n";
            cout << "Rating: " << current->rating << "\n";
            cout << "Appointment ID: " << current->appointmentID << "\n";
            cout << "Patient ID: " << current->patientID << "\n";
            cout << "Doctor ID: " << current->doctorID << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
    void displayPatientFeedback(int id)
    {
        vector<FeedbackNode *> result;
        FeedbackNode *current = head;
        while (current != nullptr)
        {
            if (current->patientID == id)
            {
                result.push_back(current);
            }
            current = current->next;
        }
        if (!result.empty())
        {
            cout << "Found feedback for Patient ID " << id << ":\n";
            for (const auto &feedback : result)
            {
                cout << "-----------------------------------------\n";
                cout << "feedback ID: " << feedback->feedbackID << "\n";
                cout << "Describe: " << feedback->describe << "\n";
                cout << "Rating: " << feedback->rating << "\n";
                cout << "Appointment ID: " << feedback->appointmentID << "\n";
                cout << "Patient ID: " << feedback->patientID << "\n";
                cout << "Doctor ID: " << feedback->doctorID << "\n";
                cout << "-----------------------------------------\n";
            }
        }
        else
        {
            cout << "No records found for Patient ID " << id << "\n";
        }
    }
    void displayDoctorFeedback(int id)
    {
        vector<FeedbackNode *> result;
        FeedbackNode *current = head;
        while (current != nullptr)
        {
            if (current->doctorID == id)
            {
                result.push_back(current);
            }
            current = current->next;
        }
        if (!result.empty())
        {
            cout << "Found feedback for Doctor ID " << id << ":\n";
            for (const auto &feedback : result)
            {
                cout << "-----------------------------------------\n";
                cout << "feedback ID: " << feedback->feedbackID << "\n";
                cout << "Describe: " << feedback->describe << "\n";
                cout << "Rating: " << feedback->rating << "\n";
                cout << "Appointment ID: " << feedback->appointmentID << "\n";
                cout << "Patient ID: " << feedback->patientID << "\n";
                cout << "Doctor ID: " << feedback->doctorID << "\n";
                cout << "-----------------------------------------\n";
            }
        }
        else
        {
            cout << "No records found for Doctor ID " << id << "\n";
        }
    }
};
class Medicine
{
private:
    MedicineNode *head;
    MedicineNode *tail;

public:
    Medicine() : head(nullptr), tail(nullptr) {}
    ~Medicine()
    {
        MedicineNode *current = head;
        while (current != nullptr)
        {
            MedicineNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addMedicine(const MedicineNode &medicine)
    {
        MedicineNode *newMedicine = new MedicineNode(medicine);
        if (!head)
        {
            head = newMedicine;
            tail = newMedicine;
        }
        else
        {
            tail->next = newMedicine;
            tail = newMedicine;
        }
    }
    bool findMedicine(int id)
    {
        MedicineNode *current = head;
        while (current != nullptr)
        {
            if (current->MedicineID == id)
            {
                cout << "---------------------------------------------\n";
                cout << "Medicine found: " << "\n";
                cout << "Medicine ID: " << current->MedicineID << "\n";
                cout << "Name: " << current->name << "\n";
                cout << "Description: " << current->description << "\n";
                cout << "---------------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void displayMedicine() const
    {
        MedicineNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "Medicine ID: " << current->MedicineID << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "Description: " << current->description << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
    void updateMedicine(MedicineNode *medicine)
    {
        MedicineNode *current = head;
        while (current != nullptr)
        {
            if (current->MedicineID == medicine->MedicineID)
            {
                current->name = medicine->name;
                current->description = medicine->description;
                break;
            }
            current = current->next;
        }
    }
    void deleteMedicine(int MedicineID)
    {
        MedicineNode *current = head;
        MedicineNode *previous = nullptr;

        while (current != nullptr)
        {
            if (current->MedicineID == MedicineID)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == tail)
                {
                    tail = previous;
                }

                delete current;
                cout << "Medicine with ID " << MedicineID << " deleted.\n";
                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "Medicine with ID " << MedicineID << " not found.\n";
    }
};
class Prescription
{
private:
    PrescriptionNode *head;
    PrescriptionNode *tail;

public:
    Prescription() : head(nullptr), tail(nullptr) {}
    ~Prescription()
    {
        PrescriptionNode *current = head;
        while (current != nullptr)
        {
            PrescriptionNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addPrescription(const PrescriptionNode &prescription)
    {
        PrescriptionNode *newPrescription = new PrescriptionNode(prescription);
        if (!head)
        {
            head = newPrescription;
            tail = newPrescription;
        }
        else
        {
            tail->next = newPrescription;
            tail = newPrescription;
        }
    }
    void displayPrescription() const
    {
        PrescriptionNode *current = head;
        while (current)
        {
            cout << "-----------------------------------------\n";
            cout << "Prescription ID: " << current->PrescriptionID << "\n";
            cout << "Patient ID: " << current->PatientID << "\n";
            cout << "Date: " << current->date << "\n";
            cout << "Instructions: " << current->instructions << "\n";
            cout << "Doctor ID: " << current->DoctorID << "\n";
            cout << "-----------------------------------------\n";
            current = current->next;
        }
    }
    void displayPatientPrescription(int id)
    {
        PrescriptionNode *current = head;
        bool found = false;
        while (current != nullptr)
        {
            if (current->PatientID == id)
            {
                if (!found)
                {
                    cout << "Found Prescriptions for Patient ID " << id << ":\n";
                    found = true;
                }
                cout << "-----------------------------------------\n";
                cout << "Prescription ID: " << current->PrescriptionID << "\n";
                cout << "Patient ID: " << current->PatientID << "\n";
                cout << "Date: " << current->date << "\n";
                cout << "Instructions: " << current->instructions << "\n";
                cout << "Doctor ID: " << current->DoctorID << "\n";
                cout << "-----------------------------------------\n";
            }
            current = current->next;
        }
        if (!found)
        {
            cout << "No records found for Patient ID " << id << "\n";
        }
    }
    void displayDoctorPrescription(int id)
    {
        vector<PrescriptionNode *> result;
        PrescriptionNode *current = head;
        while (current != nullptr)
        {
            if (current->DoctorID == id)
            {
                result.push_back(current);
            }
            current = current->next;
        }
        if (!result.empty())
        {
            cout << "Found Prescriptions for Doctor ID " << id << ":\n";
            for (const auto &app : result)
            {
                cout << "-----------------------------------------\n";
                cout << "Prescription ID: " << app->PrescriptionID << "\n";
                cout << "Patient ID: " << app->PatientID << "\n";
                cout << "Date: " << app->date << "\n";
                cout << "Instructions: " << app->instructions << "\n";
                cout << "Doctor ID: " << app->DoctorID << "\n";
                cout << "-----------------------------------------\n";
            }
        }
        else
        {
            cout << "No records found for Doctor ID " << id << "\n";
        }
    }
    bool findPrescription(int id)
    {
        PrescriptionNode *current = head;
        while (current != nullptr)
        {
            if (current->PrescriptionID == id)
            {
                cout << "-----------------------------------------\n";
                cout << "Found Prescriptions for Doctor ID " << id << ":\n";
                cout << "Prescription ID: " << current->PrescriptionID << "\n";
                cout << "Patient ID: " << current->PatientID << "\n";
                cout << "Date: " << current->date << "\n";
                cout << "Instructions: " << current->instructions << "\n";
                cout << "Doctor ID: " << current->DoctorID << "\n";
                cout << "-----------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        return false;
    }
};
class Admin
{
private:
    AdminNode *head;
    AdminNode *tail;

public:
    Admin() : head(nullptr), tail(nullptr) {}
    ~Admin()
    {
        AdminNode *current = head;
        while (current != nullptr)
        {
            AdminNode *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void addAdmin(const AdminNode &admin)
    {
        AdminNode *newAdmin = new AdminNode(admin);
        if (!head)
        {
            head = newAdmin;
            tail = newAdmin;
        }
        else
        {
            tail->next = newAdmin;
            tail = newAdmin;
        }
    }
    bool findAdmin(int id)
    {
        AdminNode *current = head;
        while (current != nullptr)
        {
            if (current->AdminID == id)
            {
                cout << "---------------------------------------------\n";
                cout << "Admin found: " << "\n";
                cout << "Admin ID: " << current->AdminID << "\n";
                cout << "Name: " << current->name << "\n";
                cout << "---------------------------------------------\n";
                return true;
            }
            current = current->next;
        }
        cout << "Admin not found.\n";
        return false;
    }
    void displayAdmin() const
    {
        AdminNode *current = head;
        while (current)
        {
            cout << "---------------------------------------------\n";
            cout << "Admin ID: " << current->AdminID << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "---------------------------------------------\n";
            current = current->next;
        }
    }
};
void initializedDatabase(sqlite3 *db);
void loadDepartmentInfo();
void loadInsuranceInfo();
// Patients insert, update, select and delete function
void loadPatientInfo();
void InsertPatientInfo(PatientNode *patient, const string &username);
void UpdatePatientInfo(PatientNode *patient);
void DeletePatientInfo(int PatientID);
// Users insert, update, select and delete function
void loadUserInfo();
void InsertUserInfo(UserNode *user);
void UpdateUserInfo(UserNode *user);
void DeleteUserInfo(int UserID);
// Doctors insert, update, select and delete function
void loadDoctorInfo();
void InsertDoctorInfo(DoctorNode *doctor, const string &username, const string &department);
void UpdateDoctorInfo(DoctorNode *doctor, const string &deptName);
void DeleteDoctorInfo(int DoctorID);
// Admin insert, select function
void loadAdminInfo();
void InsertAdminInfo(AdminNode *admin, const string &username);
//Allergies load, insert function
void InsertAllergyPatient(int Patientid, int Allergyid);
void loadAllergies();
//Emergency contact load and insert function
void InsertEmergencyInfo(EmergencyContactNode *ec);
void loadEmergencyContactInfo();
//Medical Records load and insert function
void InsertMedicalRecords(MedicalRecordsNode *record);
void loadMedicalRecords();
//Patient address and insurance insert function
void InsertPatientInsurance(int PatientID, int InsuranceID);
void InsertPatientAddress(AddressNode *address);
void loadPatientAddress();
//Health service info load in linked list
void loadServiceInfo();
//Insert, update and delete function of appointment info
void InsertAppointmentInfo(AppointmentNode *appointment);
void loadAppointmentInfo();
void UpdateAppointmentInfo(AppointmentNode *appointment);
bool updateAppointmentStatus(sqlite3 *db, int appointmentID);
void deleteAppointment(int id);
//Insert payment info and load into linked list
void InsertPaymentInfo(PaymentNode *payment);
void loadPaymentInfo();
//Feedback function
void InsertFeedbackInfo(FeedbackNode *feedback);
void loadFeedbackInfo();
//Admin to insert, update and delete medicine info
void InsertMedicineInfo(MedicineNode *medicine);
void UpdateMedicineInfo(MedicineNode *medicine);
void DeleteMedicineInfo(int MedicineID);
void loadMedicineInfo();
//Doctor to add prescription and medicine include info
int InsertPrescriptionInfo(PrescriptionNode *prescription);
void loadPrescriptionInfo();
void InsertPrescriptionMedicine(int PrescriptionID, int MedicineID);
void selectHospitalInfo();

User UserList;
Patient PatientList;
Doctor DoctorList;
Allergy AllergyList;
EmergencyContact EmergencyContactList;
Department DepartmentList;
MedicalRecords recordList;
Insurance InsuranceList;
PatientAddress AddressList;
Service ServiceList;
Appointment AppointmentList;
Payment PaymentList;
Feedback FeedbackList;
Medicine MedicineList;
Prescription PrescriptionList;
Admin AdminList;

// Create all tables in database
void initializedDatabase(sqlite3 *db)
{
    // User table
    string userTable("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT,username TEXT NOT NULL UNIQUE,password TEXT NOT NULL,phonenumber TEXT NOT NULL,IC TEXT NOT NULL UNIQUE)");
    char *messageError;
    if (sqlite3_exec(db, userTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Patient table
    string patientTable("CREATE TABLE IF NOT EXISTS Patient (id INTEGER PRIMARY KEY AUTOINCREMENT,P_Name TEXT NOT NULL UNIQUE,P_Age INT NOT NULL,P_Gender TEXT NOT NULL,User_id INTEGER,FOREIGN KEY (User_id) REFERENCES users (id))");
    if (sqlite3_exec(db, patientTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Patient Address table
    string PatientAddressTable("CREATE TABLE IF NOT EXISTS Patient_Address (Patient_id INTEGER, Country TEXT NOT NULL, City TEXT NOT NULL, Street TEXT NOT NULL, PostalCode INTEGER NOT NULL, FOREIGN KEY (Patient_id) REFERENCES Patient (id))");
    if (sqlite3_exec(db, PatientAddressTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Allergies table
    string AllergiesTable("CREATE TABLE IF NOT EXISTS Allergies (Allergy_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, Allergy_Name TEXT NOT NULL, Severity TEXT NOT NULL)");
    if (sqlite3_exec(db, AllergiesTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Allergies_Patient table
    string Allergies_Patient("CREATE TABLE IF NOT EXISTS Allergies_Patient (Allergyid INTEGER NOT NULL, Patientid INTEGER NOT NULL, PRIMARY KEY (Patientid, Allergyid),FOREIGN KEY (Patientid) REFERENCES Patient(id), FOREIGN KEY (Allergyid) REFERENCES Allergies(Allergy_id))");
    if (sqlite3_exec(db, Allergies_Patient.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Doctor table
    string DoctorTable("CREATE TABLE IF NOT EXISTS Doctor (id INTEGER PRIMARY KEY AUTOINCREMENT, D_Name TEXT NOT NULL, D_Age INTEGER NOT NULL, Specialty TEXT NOT NULL, D_Gender TEXT NOT NULL, Userid INTEGER NOT NULL, Departmentid INTEGER NOT NULL, FOREIGN KEY (Userid) REFERENCES users(id), FOREIGN KEY (Departmentid) REFERENCES Department(id))");
    if (sqlite3_exec(db, DoctorTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Department table
    string DepartmentTable("CREATE TABLE IF NOT EXISTS Department (id INTEGER PRIMARY KEY AUTOINCREMENT, Hospitalid INTEGER, Department_Name TEXT NOT NULL, HeadofDepartment TEXT NOT NULL, FOREIGN KEY (Hospitalid) REFERENCES Hospital(id))");
    if (sqlite3_exec(db, DepartmentTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Hospital table
    string HospitalTable("CREATE TABLE IF NOT EXISTS Hospital (id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Address TEXT NOT NULL,ContactInfo TEXT NOT NULL)");
    if (sqlite3_exec(db, HospitalTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Emergency Contact table
    string emergencyContactTable("CREATE TABLE IF NOT EXISTS Emergency_Contact (id INTEGER PRIMARY KEY AUTOINCREMENT, Patientid INTEGER NOT NULL UNIQUE, ContactName TEXT NOT NULL, PhoneNumber TEXT NOT NULL, RelationShip TEXT NOT NULL, FOREIGN KEY (Patientid) REFERENCES Patient(id))");
    if (sqlite3_exec(db, emergencyContactTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Medical Records table
    string medicalRecordsTable("CREATE TABLE IF NOT EXISTS Medical_Records (RecordID INTEGER PRIMARY KEY AUTOINCREMENT, Date TEXT NOT NULL, Details TEXT NOT NULL, PatientID INTEGER NOT NULL UNIQUE, DoctorID INTEGER NOT NULL UNIQUE, FOREIGN KEY (PatientID) REFERENCES Patient(id), FOREIGN KEY (DoctorID) REFERENCES Doctor(id));");
    if (sqlite3_exec(db, medicalRecordsTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Insurance table
    string insuranceTable("CREATE TABLE IF NOT EXISTS Insurance (InsuranceID INTEGER PRIMARY KEY AUTOINCREMENT, Provider_Name TEXT NOT NULL, Coverage_Percentage REAL NOT NULL);");
    if (sqlite3_exec(db, insuranceTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Insurance_Patient table
    string insurancePatientTable("CREATE TABLE IF NOT EXISTS Insurance_Patient (InsuranceID INTEGER NOT NULL, PatientID INTEGER NOT NULL, PRIMARY KEY (InsuranceID, PatientID),FOREIGN KEY (PatientID) REFERENCES Patient(id), FOREIGN KEY (InsuranceID) REFERENCES Insurance(InsuranceID))");
    if (sqlite3_exec(db, insurancePatientTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Service table
    string serviceTable("CREATE TABLE IF NOT EXISTS Health_Service (ServiceID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Price INTEGER NOT NULL, Category TEXT NOT NULL)");
    if (sqlite3_exec(db, serviceTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Appointment table
    string appointmentTable("CREATE TABLE IF NOT EXISTS Appointment (AppointmentID INTEGER PRIMARY KEY AUTOINCREMENT, Date TEXT NOT NULL, Time TEXT NOT NULL, Status TEXT NOT NULL, PatientID INTEGER NOT NULL, DoctorID INTEGER NOT NULL, ServiceID INTEGER NOT NULL, FOREIGN KEY (PatientID) REFERENCES Patient(id), FOREIGN KEY (DoctorID) REFERENCES Doctor(id), FOREIGN KEY (ServiceID) REFERENCES Health_Service(ServiceID));");
    if (sqlite3_exec(db, appointmentTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Payment table
    string paymentTable("CREATE TABLE IF NOT EXISTS Payment (PaymentID INTEGER PRIMARY KEY AUTOINCREMENT, Amount INTEGER NOT NULL, Date TEXT NOT NULL, Time TEXT NOT NULL, Payment_Method TEXT NOT NULL, AppointmentID INTEGER NOT NULL, FOREIGN KEY (AppointmentID) REFERENCES Appointment(AppointmentID))");
    if (sqlite3_exec(db, paymentTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Feedback table
    string feedbackTable("CREATE TABLE IF NOT EXISTS Feedback (FeedbackID INTEGER PRIMARY KEY AUTOINCREMENT,Describe TEXT NOT NULL,Rating INTEGER NOT NULL, PatientID INTEGER NOT NULL, AppointmentID INTEGER NOT NULL UNIQUE, DoctorID INTEGER NOT NULL, FOREIGN KEY (PatientID) REFERENCES Patient(id), FOREIGN KEY (AppointmentID) REFERENCES Appointment(AppointmentID), FOREIGN KEY (DoctorID) REFERENCES Doctor(id));");
    if (sqlite3_exec(db, feedbackTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Medicine table
    string medicineTable("CREATE TABLE IF NOT EXISTS Medicine (MedicineID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Description TEXT NOT NULL);");
    if (sqlite3_exec(db, medicineTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Prescription table
    string prescriptionTable("CREATE TABLE IF NOT EXISTS Prescription (PrescriptionID INTEGER PRIMARY KEY AUTOINCREMENT, PatientID INTEGER NOT NULL, Date TEXT NOT NULL, Instructions TEXT NOT NULL, DoctorID INTEGER NOT NULL, FOREIGN KEY (PatientID) REFERENCES Patient(id), FOREIGN KEY (DoctorID) REFERENCES Doctor(id));");
    if (sqlite3_exec(db, prescriptionTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
    // Prescription Medicine table
    string prescriptionMedicineTable("CREATE TABLE IF NOT EXISTS Prescription_Medicine (PrescriptionID INTEGER NOT NULL, MedicineID INTEGER NOT NULL, FOREIGN KEY (PrescriptionID) REFERENCES Prescription(PrescriptionID), FOREIGN KEY (MedicineID) REFERENCES Medicine(MedicineID));");
    if (sqlite3_exec(db, prescriptionMedicineTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
     // Admin table
    string adminTable("CREATE TABLE IF NOT EXISTS Admin (id INTEGER PRIMARY KEY AUTOINCREMENT, A_Name TEXT NOT NULL UNIQUE, UserID INTEGER NOT NULL, FOREIGN KEY (UserID) REFERENCES users(id));");
    if (sqlite3_exec(db, adminTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK)
    {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Table initialize successfully.\n";
    }
}
// Select allergies from database and put in Map
void loadAllergies()
{
    sqlite3 *db;
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    sqlite3_stmt *stmt;

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database:  " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char *query = "SELECT Allergy_id, Allergy_Name, Severity FROM allergies";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = stoi(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string severity = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        AllergyNode *allergy = new AllergyNode(id, name, severity);
        allergy->setID(id);
        AllergyList.addAllergy(*allergy);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
// Admin Insert patient's allergy info into database
void InsertAllergyPatient(int Patientid, int Allergyid)
{
    sqlite3 *db;

    // Open the database connection
    sqlite3_open("medical_appointment_system.db", &db);

    // SQL query to insert data into Allergies_Patient table
    const char *sql = "INSERT INTO Allergies_Patient (Allergyid, Patientid) VALUES (?, ?)";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    // Bind the Allergy ID to the first parameter
    sqlite3_bind_int(stmt, 1, Allergyid);

    // Bind the Patient ID to the second parameter
    sqlite3_bind_int(stmt, 2, Patientid);

    // Execute the SQL statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to execute insert: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Allergy information successfully stored in Allergies_Patient table.\n";
    }

    // Finalize the SQL statement to release resources
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(db);
}
// when program start load user info into userMap
void loadUserInfo()
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id,username,password,phonenumber,IC, role FROM users;";
    UserList.clear();
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = stoi(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        string username = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string phonenumber = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        string IC = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        string role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        UserNode *user = new UserNode(username, password, phonenumber, IC, role);
        user->setID(id);
        UserList.addUser(*user);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert User info when register
void InsertUserInfo(UserNode *user)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    const char *sql = "INSERT INTO users(username, password, phonenumber, IC, role) VALUES (?, ?, ?, ?, ?);";
    exit = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    if (exit != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    sqlite3_bind_text(stmt, 1, user->username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user->password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user->phonenumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user->ic.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, user->role.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE)
    {
        cerr << "Error inserting record: " << sqlite3_errmsg(DB) << endl;
    }
    int id = sqlite3_last_insert_rowid(DB);
    user->setID(id);

    UserList.addUser(*user);

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Admin used to update user info
void UpdateUserInfo(UserNode *user)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "UPDATE users SET username = ?, password = ?, phonenumber = ?, IC = ? WHERE id = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, user->username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user->password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user->phonenumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user->ic.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, user->id);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to update user: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "User information updated successfully in database.\n";

        UserList.updateUser(user);

        sqlite3_close(DB);
        sqlite3_finalize(stmt);
    }
}
// Delete user info
void DeleteUserInfo(int UserID)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "DELETE FROM users WHERE id = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, UserID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error executing delete statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return;
    }

    cout << "User with ID " << UserID << " deleted from database.\n";
    UserList.deleteUser(UserID);

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// When program start load patient info into patientMap
void loadPatientInfo()
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id,P_Name,P_Age,P_Gender,User_id FROM Patient;";
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string Name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int Age = sqlite3_column_int(stmt, 2);
        string Gender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        int userid = sqlite3_column_int(stmt, 4);
        PatientNode *patient = new PatientNode(Name, Gender, Age, userid);
        patient->setID(id);
        PatientList.addPatient(*patient);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert Patient info, also add foreign key data into table
void InsertPatientInfo(PatientNode *patient, const string &username)
{
    sqlite3 *DB;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    // SQL query to insert into the Patient table
    const char *sql = R"(
        INSERT INTO Patient (P_Name, P_Age, P_Gender, User_id)
        VALUES (?, ?, ?, (SELECT id FROM users WHERE username = ?));
    )";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, patient->name.c_str(), -1, SQLITE_STATIC);   // Bind patient name
    sqlite3_bind_int(stmt, 2, patient->age);                                // Bind patient age
    sqlite3_bind_text(stmt, 3, patient->gender.c_str(), -1, SQLITE_STATIC); // Bind patient gender
    sqlite3_bind_text(stmt, 4, username.c_str(), -1, SQLITE_STATIC);        // Bind username

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting patient information: " << sqlite3_errmsg(DB) << endl;
    }

    int id = sqlite3_last_insert_rowid(DB);
    patient->setID(id);

    PatientList.addPatient(*patient);
    // Fetch and display the inserted patient information
    PatientList.findPatient(id);

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Update patient info
void UpdatePatientInfo(PatientNode *patient)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "UPDATE Patient SET P_Name = ?, P_Age = ?, P_Gender = ? WHERE id = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, patient->name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, patient->age);
    sqlite3_bind_text(stmt, 3, patient->gender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, patient->id);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to update user: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Patient information updated successfully in database.\n";

        PatientList.updatePatient(patient);

        sqlite3_close(DB);
        sqlite3_finalize(stmt);
    }
}
// Delete patient info
void DeletePatientInfo(int PatientID)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "DELETE FROM Patient WHERE id = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, PatientID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error executing delete statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return;
    }

    cout << "Patient with ID " << PatientID << " deleted from database.\n";
    PatientList.deletePatient(PatientID);

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert Doctor info into database
void InsertDoctorInfo(DoctorNode *doctor, const string &username, const string &department)
{
    sqlite3 *DB;

    // Open the database connection
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    // SQL query to insert doctor information
    const char *sql = R"(
        INSERT INTO Doctor (D_Name, D_Age, Specialty, D_Gender, Userid, Departmentid)
        VALUES (?, ?, ?, ?, 
                (SELECT id FROM users WHERE username = ?), 
                (SELECT id FROM Department WHERE Department_Name = ?));
    )";

    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, doctor->name.c_str(), -1, SQLITE_STATIC);      // Bind doctor name
    sqlite3_bind_int(stmt, 2, doctor->age);                                   // Bind doctor age
    sqlite3_bind_text(stmt, 3, doctor->specialty.c_str(), -1, SQLITE_STATIC); // Bind specialty
    sqlite3_bind_text(stmt, 4, doctor->gender.c_str(), -1, SQLITE_STATIC);    // Bind gender
    sqlite3_bind_text(stmt, 5, username.c_str(), -1, SQLITE_STATIC);          // Bind username
    sqlite3_bind_text(stmt, 6, department.c_str(), -1, SQLITE_STATIC);        // Bind department name

    // Execute the SQL statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error inserting doctor information: " << sqlite3_errmsg(DB) << endl;
    }
    int id = sqlite3_last_insert_rowid(DB);
    doctor->setID(id);

    DoctorList.addDoctor(*doctor);
    DoctorList.findDoctor(doctor->doctorID);
    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Load Doctor info when program start
void loadDoctorInfo()
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, D_Name, D_Age, Specialty, D_Gender, Userid, Departmentid FROM Doctor;";
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string Name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int Age = sqlite3_column_int(stmt, 2);
        string specialty = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        string Gender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        int userid = sqlite3_column_int(stmt, 5);
        int Departmentid = sqlite3_column_int(stmt, 6);
        DoctorNode *doctor = new DoctorNode(Name, Age, specialty, Gender, userid, Departmentid);
        doctor->setID(id);
        DoctorList.addDoctor(*doctor);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Update doctor info
void UpdateDoctorInfo(DoctorNode *doctor, const string &deptName)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "UPDATE Doctor SET D_Name = ?, D_Age = ?, Specialty = ?, D_Gender = ?, Departmentid = (SELECT id FROM Department WHERE Department_Name = ?) WHERE id = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, doctor->name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, doctor->age);
    sqlite3_bind_text(stmt, 3, doctor->specialty.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, doctor->gender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, deptName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, doctor->doctorID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to update doctor: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Doctor information updated successfully in database.\n";

        DoctorList.updateDoctor(doctor);

        sqlite3_close(DB);
        sqlite3_finalize(stmt);
    }
}
// Delete doctor info
void DeleteDoctorInfo(int DoctorID)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "DELETE FROM Doctor WHERE id = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, DoctorID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error executing delete statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return;
    }

    cout << "Doctor with ID " << DoctorID << " deleted from database.\n";
    DoctorList.deleteDoctor(DoctorID);

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
//load admin info into linkedlist
void loadAdminInfo()
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, A_Name, UserID FROM Admin;";
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string Name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int userid = sqlite3_column_int(stmt, 2);
        AdminNode *admin = new AdminNode(Name, userid);
        admin->setID(id);
        AdminList.addAdmin(*admin);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
//Insert admin info into database
void InsertAdminInfo(AdminNode *admin, const string &username)
{
    sqlite3 *DB;

    // Open the database connection
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    // SQL query to insert doctor information
    const char *sql = R"(
        INSERT INTO Admin (A_Name, UserID)
        VALUES (?, (SELECT id FROM users WHERE username = ?));
    )";

    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, admin->name.c_str(), -1, SQLITE_STATIC);      // Bind doctor name                                  // Bind doctor age
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC); // Bind specialty
       // Bind department name

    // Execute the SQL statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error inserting admin information: " << sqlite3_errmsg(DB) << endl;
    }
    int id = sqlite3_last_insert_rowid(DB);
    admin->setID(id);

    AdminList.addAdmin(*admin);
    AdminList.findAdmin(admin->AdminID);
    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert patient emergency info
void InsertEmergencyInfo(EmergencyContactNode *ec)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to insert into the Patient table
    const char *sql = R"(
        INSERT INTO Emergency_Contact (Patientid, ContactName, PhoneNumber, RelationShip)
        VALUES (?, ?, ?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_int(stmt, 1, ec->patientid);                                // Bind patient ID
    sqlite3_bind_text(stmt, 2, ec->contactName.c_str(), -1, SQLITE_STATIC);  // Bind Contact Name
    sqlite3_bind_text(stmt, 3, ec->phoneNumber.c_str(), -1, SQLITE_STATIC);  // Bind Phone Number
    sqlite3_bind_text(stmt, 4, ec->relationShip.c_str(), -1, SQLITE_STATIC); // Bind Relationship

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting patient information: " << sqlite3_errmsg(db) << endl;
    }
    int id = sqlite3_last_insert_rowid(db);
    ec->setID(id);

    EmergencyContactList.addEmergencyContact(*ec);

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void loadEmergencyContactInfo()
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, Patientid, ContactName, PhoneNumber, RelationShip FROM Emergency_Contact;";
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int patientid = sqlite3_column_int(stmt, 1);
        string contactname = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string phonenumber = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        string relationship = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        EmergencyContactNode *ec = new EmergencyContactNode(patientid, contactname, phonenumber, relationship);
        ec->setID(id);
        EmergencyContactList.addEmergencyContact(*ec);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Load department info when program start
void loadDepartmentInfo()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, Hospitalid, Department_Name, HeadofDepartment FROM Department;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int hospitalid = sqlite3_column_int(stmt, 1);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string headofdepartment = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        DepartmentList.InsertDepartment(DepartmentNode(id, hospitalid, name, headofdepartment));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
// Display hospital info
void selectHospitalInfo()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, Name, Address, ContactInfo FROM Hospital;";
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }
    cout << "+-----+-------------------------+---------------------------------------------------+--------------------+" << endl;
    cout << "| ID  | Hospital Name           | Address                                           | Contact Info       |" << endl;
    cout << "+-----+-------------------------+---------------------------------------------------+--------------------+" << endl;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *address = sqlite3_column_text(stmt, 2);
        const unsigned char *contact = sqlite3_column_text(stmt, 3);

        cout << "| " << setw(3) << id << " | "
             << setw(23) << (name ? reinterpret_cast<const char *>(name) : "N/A") << " | "
             << setw(51) << (address ? reinterpret_cast<const char *>(address) : "N/A") << " | "
             << setw(18) << (contact ? reinterpret_cast<const char *>(contact) : "N/A") << " |" << endl;
    }

    cout << "+-----+-------------------------+---------------------------------------------------+--------------------+" << endl;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
// Insert medical record
void InsertMedicalRecords(MedicalRecordsNode *record)
{
    sqlite3 *db = nullptr;
    sqlite3_stmt *stmt = nullptr;

    // Open the database connection
    if (sqlite3_open("medical_appointment_system.db", &db) != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query for insertion
    const char *sql = "INSERT INTO Medical_Records (Date, Details, PatientID, DoctorID) VALUES (?, ?, ?, ?);";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL preparation error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db); // Ensure database is closed
        return;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, record->date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, record->details.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, record->patientID);
    sqlite3_bind_int(stmt, 4, record->doctorID);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        int id = sqlite3_last_insert_rowid(db);
        record->setRecordID(id);

        recordList.addRecords(*record);
        cout << "Record inserted successfully." << endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void loadMedicalRecords()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open("medical_appointment_system.db", &db);
    const char *sql = "SELECT RecordID, Date, Details, PatientID, DoctorID FROM Medical_Records;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string details = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        int PatientID = sqlite3_column_int(stmt, 3);
        int DoctorID = sqlite3_column_int(stmt, 4);
        MedicalRecordsNode *record = new MedicalRecordsNode(date, details, PatientID, DoctorID);
        record->setRecordID(id);
        recordList.addRecords(*record);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void loadInsuranceInfo()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT InsuranceID, Provider_Name, Coverage_Percentage FROM Insurance;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        double coverage = sqlite3_column_double(stmt, 2);
        InsuranceList.addProvider(id, name, coverage);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void InsertPatientInsurance(int PatientID, int InsuranceID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to insert into the Patient table
    const char *sql = R"(
        INSERT INTO Insurance_Patient (InsuranceID, PatientID)
        VALUES (?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_int(stmt, 1, InsuranceID);
    sqlite3_bind_int(stmt, 2, PatientID);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting Insurance and patient information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Patient and insurance information inserted successfully.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void InsertPatientAddress(AddressNode *address)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to insert into the Patient table
    const char *sql = R"(
        INSERT INTO Patient_Address (Patient_id, Country, City, Street, PostalCode)
        VALUES (?, ?, ?, ?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_int(stmt, 1, address->PatientID);
    sqlite3_bind_text(stmt, 2, address->country.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, address->city.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, address->street.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, address->postcode.c_str(), -1, SQLITE_STATIC);
    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting patient address information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Patient address inserted successfully.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void loadPatientAddress()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT Patient_id, Country, City, Street, PostalCode FROM Patient_Address;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string country = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string city = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string street = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        string postcode = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        AddressNode *address = new AddressNode(id, country, city, street, postcode);
        AddressList.addAddress(*address);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void loadServiceInfo()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ServiceID, Name, Price, Category FROM Health_Service;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error: "<< sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int price = sqlite3_column_int(stmt, 2);
        string category = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        ServiceList.InsertService(id, name, price, category);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void InsertAppointmentInfo(AppointmentNode *appointment)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to insert into the Patient table
    const char *sql = R"(
        INSERT INTO Appointment (Date, Time, Status, PatientID, DoctorID, ServiceID)
        VALUES (?, ?, ?, ?, ?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, appointment->date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, appointment->time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, appointment->status.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, appointment->PatientID);
    sqlite3_bind_int(stmt, 5, appointment->DoctorID);
    sqlite3_bind_int(stmt, 6, appointment->ServiceID);

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting appointment information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        int id = sqlite3_last_insert_rowid(db);
        appointment->setID(id);
        AppointmentList.addAppointment(*appointment);
        cout << "Appointment information inserted successfully.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void loadAppointmentInfo()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT AppointmentID, Date, Time, Status, PatientID, DoctorID, ServiceID FROM Appointment;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string time = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        int PatientID = sqlite3_column_int(stmt, 4);
        int DoctorID = sqlite3_column_int(stmt, 5);
        int ServiceID = sqlite3_column_int(stmt, 6);
        AppointmentNode *app = new AppointmentNode(date, time, status, PatientID, DoctorID, ServiceID);
        app->setID(id);
        AppointmentList.addAppointment(*app);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
bool updateAppointmentStatus(sqlite3 *db, int appointmentID)
{
    const char *updateQuery = "UPDATE Appointment SET Status = 'Paid' WHERE AppointmentID = ?;";
    sqlite3_stmt *updateStmt = nullptr;

    if (sqlite3_prepare_v2(db, updateQuery, -1, &updateStmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(updateStmt, 1, appointmentID);

    bool success = false;
    if (sqlite3_step(updateStmt) == SQLITE_DONE)
    {
        cout << "Payment successful! Appointment marked as Paid.\n";
        success = true;
    }
    else
    {
        cerr << "Error updating appointment status: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(updateStmt);
    return success;
}
//Update appointment info
void UpdateAppointmentInfo(AppointmentNode *appointment)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "UPDATE Appointment SET Date = ?, Time = ?, DoctorID = ?, ServiceID = ? WHERE AppointmentID = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, appointment->date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, appointment->time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, appointment->DoctorID);
    sqlite3_bind_int(stmt, 4, appointment->ServiceID);
    sqlite3_bind_int(stmt, 5, appointment->AppointmentID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to update Appointment: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Appointment information updated successfully in database.\n";

        AppointmentList.updateAppointment(appointment);

        sqlite3_close(DB);
        sqlite3_finalize(stmt);
    }
}
// Cancel Appointment function
void deleteAppointment(int id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    // Open database
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to delete appointment by AppointmentID
    const char *sql = "DELETE FROM Appointment WHERE AppointmentID = ?;";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind the AppointmentID parameter
    sqlite3_bind_int(stmt, 1, id);

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error deleting appointment: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Appointment with ID " << id << " deleted successfully.\n";
    }

    cout << "Appointment with ID " << id << " deleted from database.\n";
    AppointmentList.deleteAppointment(id);

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void InsertPaymentInfo(PaymentNode *payment)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to insert into the Payment table
    const char *sql = R"(
        INSERT INTO Payment (Amount, Date, Time, Payment_Method, AppointmentID)
        VALUES (?, ?, ?, ?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_double(stmt, 1, payment->amount); // Use bind_double for decimal values
    sqlite3_bind_text(stmt, 2, payment->date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, payment->time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, payment->paymentMethod.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, payment->AppointmentID);

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting payment information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        int id = sqlite3_last_insert_rowid(db);
        payment->setID(id);

        PaymentList.addPayment(*payment);
        cout << "Payment information inserted successfully.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt); // Finalize stmt first
    sqlite3_close(db);      // Then close the database
}
void loadPaymentInfo()
{
    sqlite3 *db;
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    sqlite3_stmt *stmt;

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char *query = "SELECT PaymentID, Amount, Date, Time, Payment_Method, AppointmentID FROM Payment";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int amount = sqlite3_column_int(stmt, 1);
        string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string time = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        string method = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        int Appointmentid = sqlite3_column_int(stmt, 5);
        PaymentNode *payment = new PaymentNode(amount, date, time, method, Appointmentid);
        payment->setID(id);
        PaymentList.addPayment(*payment);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void InsertFeedbackInfo(FeedbackNode *feedback)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to insert into the Payment table
    const char *sql = R"(
        INSERT INTO Feedback (Describe, Rating, PatientID, AppointmentID, DoctorID) 
        VALUES (?, ?, ?, ?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, feedback->describe.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, feedback->rating);
    sqlite3_bind_int(stmt, 3, feedback->patientID);
    sqlite3_bind_int(stmt, 4, feedback->appointmentID);
    sqlite3_bind_int(stmt, 5, feedback->doctorID);

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting payment information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        int id = sqlite3_last_insert_rowid(db);
        feedback->setID(id);

        FeedbackList.addFeedback(*feedback);
        cout << "Feedback information inserted successfully.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt); // Finalize stmt first
    sqlite3_close(db);
}
void loadFeedbackInfo()
{
    sqlite3 *db;
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    sqlite3_stmt *stmt;

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char *query = "SELECT FeedbackID, Describe, Rating, PatientID, AppointmentID, DoctorID FROM Feedback";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string describe = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int rating = sqlite3_column_int(stmt, 2);
        int PatientID = sqlite3_column_int(stmt, 3);
        int AppointmentID = sqlite3_column_int(stmt, 4);
        int DoctorID = sqlite3_column_int(stmt, 5);
        FeedbackNode *feedback = new FeedbackNode(describe, rating, PatientID, DoctorID, AppointmentID);
        feedback->setID(id);
        FeedbackList.addFeedback(*feedback);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void loadMedicineInfo()
{
    sqlite3 *db;
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    sqlite3_stmt *stmt;

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char *query = "SELECT MedicineID, Name, Description FROM Medicine";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL preparing error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string description = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        MedicineNode *medicine = new MedicineNode(name, description);
        medicine->setID(id);
        MedicineList.addMedicine(*medicine);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void InsertMedicineInfo(MedicineNode *medicine)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to insert into the Payment table
    const char *sql = R"(
        INSERT INTO Medicine (Name, Description)
        VALUES (?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, medicine->name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, medicine->description.c_str(), -1, SQLITE_STATIC);

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting medicine information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        int id = sqlite3_last_insert_rowid(db);
        medicine->setID(id);

        MedicineList.addMedicine(*medicine);
        cout << "Medicine information inserted successfully.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt); // Finalize stmt first
    sqlite3_close(db);      // Then close the database
}
void UpdateMedicineInfo(MedicineNode *medicine)
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql = "UPDATE Medicine SET Name = ?, Description = ? WHERE MedicineID = ?;";

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, medicine->name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, medicine->description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, medicine->MedicineID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to update Appointment: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Medicine information updated successfully in database.\n";

        MedicineList.updateMedicine(medicine);

        sqlite3_close(DB);
        sqlite3_finalize(stmt);
    }
}
void DeleteMedicineInfo(int MedicineID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    // Open database
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to delete appointment by AppointmentID
    const char *sql = "DELETE FROM Medicine WHERE MedicineID = ?;";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind the AppointmentID parameter
    sqlite3_bind_int(stmt, 1, MedicineID);

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error deleting Medicine: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Medicine with ID " << MedicineID << " deleted successfully.\n";
    }

    cout << "Medicine with ID " << MedicineID << " deleted from database.\n";
    AppointmentList.deleteAppointment(MedicineID);

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
int InsertPrescriptionInfo(PrescriptionNode *prescription)
{
    int id;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    // SQL query to insert into the Payment table
    const char *sql = R"(
        INSERT INTO Prescription (PatientID, Date, Instructions, DoctorID)
        VALUES (?, ?, ?, ?);
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 0;
    }

    // Bind parameters to the SQL statement
    sqlite3_bind_int(stmt, 1, prescription->PatientID); // Use bind_double for decimal values
    sqlite3_bind_text(stmt, 2, prescription->date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, prescription->instructions.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, prescription->DoctorID);

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting payment information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        id = sqlite3_last_insert_rowid(db);
        prescription->setID(id);
        PrescriptionList.addPrescription(*prescription);
        cout << "Prescription information inserted successfully.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt); // Finalize stmt first
    sqlite3_close(db);
    return id; // Then close the database
}
void loadPrescriptionInfo()
{
    sqlite3 *db;
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    sqlite3_stmt *stmt;

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char *query = "SELECT PrescriptionID, PatientID, Date, Instructions, DoctorID FROM Prescription";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL preparing error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int PatientID = sqlite3_column_int(stmt, 1);
        string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string Instruction = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        int DoctorID = sqlite3_column_int(stmt, 4);
        PrescriptionNode *prescription = new PrescriptionNode(PatientID, date, Instruction, DoctorID);
        prescription->setID(id);
        PrescriptionList.addPrescription(*prescription);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void InsertPrescriptionMedicine(int PrescriptionID, int MedicineID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    string sql = "INSERT INTO Prescription_Medicine (PrescriptionID, MedicineID) VALUES (?, ?);";

    int exit = sqlite3_open("medical_appointment_system.db", &db);

    // Check if the database opened successfully
    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_bind_int(stmt, 1, PrescriptionID) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 2, MedicineID) != SQLITE_OK)
    {
        cerr << "Error binding parameters: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error inserting into prescription_Medicine: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Successfully added medicine ID " << MedicineID << " to prescription ID " << PrescriptionID << "." << endl;
    }

    sqlite3_close(db);
    sqlite3_finalize(stmt);
}

