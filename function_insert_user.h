#include <map>
#include <iomanip>
#include <vector>
#include <limits>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include "sqlite3.h"
using namespace std;
//Class forward declaration
class User;
class Patient;
class Doctor;
class Allergy;
class InsuranceList;
class Payment;
class EmergencyContact;
class Department;
class MedicalRecords;
// linked list
struct DepartmentNode
{
    int Departmentid;
    int Hospitalid;
    string DepartmentName;
    string HeadofDepartment;
    DepartmentNode *next;

    DepartmentNode(int id, int Hospitalid, const string &Name, const string &Head) : Departmentid(id), Hospitalid(Hospitalid), DepartmentName(Name), HeadofDepartment(Head), next(nullptr) {}
};
struct InsuranceNode
{
    int insuranceid;
    int patientid;
    string providerName;
    double coveragePercentage; 
    InsuranceNode *next;

    InsuranceNode(string provider, double coverage)
        : providerName(provider), coveragePercentage(coverage), next(nullptr) {}
};
struct MedicalRecordsNode{
    int recordID;
    string date;
    string details;
    int patientID;
    int doctorID;
    MedicalRecordsNode *next;
    MedicalRecordsNode()
        : details(""), patientID(0), doctorID(0), next(nullptr) {
        time_t now = time(0);
        struct tm tstruct;
        localtime_s(&tstruct, &now);
        char buf[11];
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
        date = buf;
    }
    MedicalRecordsNode(const string& date, const string& details, int patientID, int doctorID)
        : date(date), details(details), patientID(patientID), doctorID(doctorID), next(nullptr) {
    }
};
// Class
class User
{
private:
    string username;
    string password;
    string phonenumber;
    string ic;
    int id;

public:
    User()
    {
    }
    User(string username, string password, string phonenumber, string ic, int id)
        : username(username), password(password), phonenumber(phonenumber), ic(ic), id(id) {}

    string username1()
    {
        return username;
    }

    void set_username(string username)
    {
        this->username = username;
    }

    string password1()
    {
        return password;
    }

    void set_password(string password)
    {
        this->password = password;
    }

    string phonenumber1()
    {
        return phonenumber;
    }

    void set_phonenumber(string phonenumber)
    {
        this->phonenumber = phonenumber;
    }

    string ic1()
    {
        return ic;
    }

    void set_ic(string ic)
    {
        this->ic = ic;
    }
    int id1()
    {
        return id;
    }
    void set_id(int id)
    {
        this->id = id;
    }
};
class Patient
{
private:
    string name;
    string gender;
    int id;
    int age;
    int userid;

public:
    Patient() {}
    Patient(int id, const string &n, const string &g, int a, int userid)
        : id(id), name(n), gender(g), age(a), userid(userid) {}

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
    // void bookAppointment(vector<Patient *> &list, vector<Appointment *> &applist, vector<Doctor *> &doctorlist);
    void patientPlatForm();
    void information();
};
class Doctor
{
private:
    int doctorID;
    string name;
    int age;
    string gender;
    string specialty;
    int userid;
    int departmentid;

public:
    Doctor() {}
    Doctor(int id, const string &name, int age, const string &specialty, const string &gender, int userid, int departmentid) : doctorID(id), name(name), age(age), specialty(specialty), gender(gender), userid(userid), departmentid(departmentid) {}
    int getID() const
    {
        return this->doctorID;
    }

    void setID(int id)
    {
        this->doctorID = id;
    }
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
    string getSpecialty() const
    {
        return this->specialty;
    }

    void setSpecialty(string specialty)
    {
        this->specialty = specialty;
    }
    int getUserID() const
    {
        return this->userid;
    }

    void setUserID(int id)
    {
        this->userid = id;
    }
    int getDepartmentID() const
    {
        return this->departmentid;
    }
    void setDepartmentID(int id)
    {
        this->departmentid = id;
    }
    void showDoctorDashboard();
    void displayDoctorInfo();
    void medicalRecordsPlatForm();
};
class Allergy
{
private:
    int id;
    string name;
    string severity;

public:
    Allergy() {}
    Allergy(int allergy_id, const string &allergy_name, const string &allergy_severity)
        : id(allergy_id), name(allergy_name), severity(allergy_severity) {}
    int getId()
    {
        return this->id;
    }
    void setId(int id)
    {
        this->id = id;
    }
    string getName()
    {
        return this->name;
    }
    void setName(string name)
    {
        this->name = name;
    }
    string getSeverity()
    {
        return this->severity;
    }
    void setSeverity(string severity)
    {
        this->severity = severity;
    }
};
class InsuranceList
{
private:
    InsuranceNode *head;

public:
    InsuranceList() : head(nullptr) {}

    void addProvider(const string &provider, double coverage)
    {
        InsuranceNode *newNode = new InsuranceNode(provider, coverage);
        newNode->next = head;
        head = newNode;
    }

    // find insurance coverage by provider name
    double findCoverage(const string &provider) const
    {
        InsuranceNode *current = head;
        string lowerProvider = provider;
        transform(lowerProvider.begin(), lowerProvider.end(), lowerProvider.begin(), ::tolower);

        while (current != nullptr)
        {
            string lowerCurrent = current->providerName;
            transform(lowerCurrent.begin(), lowerCurrent.end(), lowerCurrent.begin(), ::tolower);

            if (lowerCurrent == lowerProvider)
            {
                return current->coveragePercentage;
            }
            current = current->next;
        }
        return -1.0; // Not found
    }

    // Display insurance providers
    void displayProviders() const
    {
        InsuranceNode *current = head;
        cout << "\n--- Available Insurance Providers ---\n";
        while (current != nullptr)
        {
            cout << current->providerName << " - Covers " << current->coveragePercentage << "%\n";
            current = current->next;
        }
    }

    ~InsuranceList()
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
    int paymentid;
    double serviceCost;
    InsuranceList insuranceList;

public:
    Payment(int paymentid, double cost) : paymentid(paymentid), serviceCost(cost) {}

    void makePayment(const string &patientName) const
    {
        cout << "\n Payment Process...\n";
        cout << "Service cost: RM " << fixed << setprecision(2) << serviceCost << "\n";

        char choice;
        cout << "Do you have insurance? (Y/N): ";
        cin >> choice;

        if (toupper(choice) == 'Y')
        {
            string insuranceProvider;
            cout << "Enter your insurance provider: ";
            cin.ignore();
            getline(cin, insuranceProvider);

            processInsurance(insuranceProvider);
        }
        else if (toupper(choice) == 'N')
        {
            payDirectly();
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    void processInsurance(const string &insuranceProvider) const
    {
        double coverage = insuranceList.findCoverage(insuranceProvider);
        if (coverage >= 0)
        {
            double amountToPay = serviceCost * ((100.0 - coverage) / 100.0);
            cout << "Your insurance covers " << coverage << "% of the cost.\n";
            cout << "You need to pay: RM " << fixed << setprecision(2) << amountToPay << "\n";

            choosePaymentMethod();
        }
        else
        {
            cout << "Insurance provider not found. Please proceed with full payment.\n";
            payDirectly();
        }
    }
    // payment method
    void choosePaymentMethod() const
    {
        cout << "\nSelect your payment method:\n";
        cout << "1. Online Banking\n";
        cout << "2. E-Wallet\n";
        cout << "3. Credit/Debit Card\n";

        int method;
        cout << "Enter your choice: ";
        cin >> method;

        switch (method)
        {
        case 1:
            cout << "Processing payment via Online Banking...\n";
            break;
        case 2:
            cout << "Processing payment via E-Wallet...\n";
            break;
        case 3:
            cout << "Processing payment via Credit/Debit Card...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            choosePaymentMethod();
        }
        cout << "Payment successful! Thank you.\n";
        displayPaymentDateTime();
    }
    void payDirectly() const
    {
        cout << "You need to pay the full amount: RM " << fixed << setprecision(2) << serviceCost << "\n";

        choosePaymentMethod();
    }
    void displayPaymentDateTime() const
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        char buf[100];
        strftime(buf, sizeof(buf), "%a %d %b %Y %I:%M:%S %p", ltm);
        cout << "Payment Date and Time: " << buf << "\n";
    }

    void displayInsuranceProviders() const
    {
        insuranceList.displayProviders();
    }
};
class EmergencyContact
{
private:
    int contactid;
    int patientid;
    string contactName;
    string phoneNumber;
    string relationShip;

public:
    EmergencyContact() {}
    EmergencyContact(int id, int patientid, string contactName, string phoneNumber, string relationShip) : contactid(id), patientid(patientid), contactName(contactName), phoneNumber(phoneNumber), relationShip(relationShip) {}
    int getContactID()
    {
        return this->contactid;
    }
    void setContactID(int id)
    {
        this->contactid = id;
    }
    int getPatientID()
    {
        return this->patientid;
    }
    void setPatientID(int id)
    {
        this->patientid = id;
    }
    string getContactName()
    {
        return this->contactName;
    }
    void setContactName(string name)
    {
        this->contactName = name;
    }
    string getPhoneNumber()
    {
        return this->phoneNumber;
    }
    void setPhoneNumber(string phonenumber)
    {
        this->phoneNumber = phonenumber;
    }
    string getRelationShip()
    {
        return this->relationShip;
    }
    void setRelationShip(string relationship)
    {
        this->relationShip = relationship;
    }
};
class Department
{
private:
    DepartmentNode *head;
    DepartmentNode *tail;

public:
    Department() : head(nullptr), tail(nullptr) {}
    ~Department(){
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
    void clear(){
        DepartmentNode *current = head;
        while(current != nullptr){
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
    ~MedicalRecords(){
        clear();
    }
    vector<MedicalRecordsNode*> findRecords(int id){
        vector<MedicalRecordsNode*> result;
        MedicalRecordsNode *current = head;
        while(current != nullptr){
            if(current->patientID == id){
                result.push_back(current);
            }
            current = current->next;
        }
        return result;
    }
    void addRecords(const MedicalRecordsNode &record){
        MedicalRecordsNode* newRecord = new MedicalRecordsNode(record);
        if(!head){
            head = newRecord;
            tail = newRecord;
        }else{
            tail->next = newRecord;
            tail = newRecord;
        }
    }
    void displayRecords() const {
        MedicalRecordsNode* current = head;
        while(current){
             cout << "Record ID: " << current->recordID 
                 << "\n Doctor ID: " << current->doctorID 
                 << "\n Patient ID: " << current->patientID 
                 << "\n Details: " << current->details 
                 << "\n Date: " << current->date << endl;
            current = current->next;
        }
    }
     void clear() {
        MedicalRecordsNode* current = head;
        while (current != nullptr) {
            MedicalRecordsNode* next = current->next; 
            delete current;                           
            current = next;                           
        }
        head = nullptr; 
        tail = nullptr;
    }
};
static int callback(void *data, int argc, char **argv, char **azColName);
void initializedDatabase(sqlite3 *db);
void loadDepartmentInfo();
void loadPatientInfo();
void InsertPatientInfo(Patient *p, const string &username);
bool getPatientInfo(int id);
void displayPatientInfo();
void loadUserInfo();
void InsertUserInfo(User *u);
void SelectInfo(string table);
void loadDoctorInfo();
void InsertDoctorInfo(Doctor *d, const string &username, const string &department);
bool getDoctorInfo(int id);
void InsertAllergyPatient(int Patientid, int Allergyid);
void fetchAllergies();
void displayAllergies();
void InsertEmergencyInfo(int patientid, EmergencyContact *ec);
void getEmergencyContactInfo(int Contactid);
void InsertMedicalRecords(MedicalRecordsNode *record);
void loadMedicalRecords();
void selectHospitalInfo();
map<int, Patient *> patientMap;
map<int, Doctor *> doctorMap;
map<string, User *> userMap;
map<int, Allergy *> allergyMap;
map<int, EmergencyContact *> emergencyMap;
Department DepartmentList;
MedicalRecords recordList;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
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
}
// Select allergies from database and put in Map
void fetchAllergies()
{
    sqlite3 *db;
    int exit = sqlite3_open("medical_appointment_system.db", &db);
    sqlite3_stmt *stmt;

    // 打开数据库
    if (exit != SQLITE_OK)
    {
        cerr << "无法打开数据库: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // SQL 查询语句
    const char *query = "SELECT Allergy_id, Allergy_Name, Severity FROM allergies";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "SQL 准备失败: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }
    // 执行查询并存储数据到 map
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string severity = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        // 添加到全局 map
        allergyMap[id] = new Allergy(id, name, severity);
    }

    // 清理资源
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
// Display Allergies
void displayAllergies()
{
    for (const auto &[id, allergy] : allergyMap)
    {
        cout << "ID: " << id << ", Name: " << allergy->getName() << ", Severity: " << allergy->getSeverity() << "\n";
    }
}
// when program start load user info into userMap
void loadUserInfo()
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id,username,password,phonenumber,IC FROM users;";
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

        userMap[username] = new User(username, password, phonenumber, IC, id);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert User info when register
void InsertUserInfo(User *u)
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

    const char *sql = "INSERT INTO users(username, password, phonenumber, IC) VALUES (?, ?, ?, ?);";
    exit = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    if (exit != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    sqlite3_bind_text(stmt, 1, u->username1().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, u->password1().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, u->phonenumber1().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, u->ic1().c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE)
    {
        cerr << "Error inserting record: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Records inserted successfully\n";
    }
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

        patientMap[id] = new Patient(id, Name, Gender, Age, userid);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert Patient info, also add foreign key data into table
void InsertPatientInfo(Patient *p, const string &username)
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
    sqlite3_bind_text(stmt, 1, p->getName().c_str(), -1, SQLITE_STATIC);   // Bind patient name
    sqlite3_bind_int(stmt, 2, p->getAge());                                // Bind patient age
    sqlite3_bind_text(stmt, 3, p->getGender().c_str(), -1, SQLITE_STATIC); // Bind patient gender
    sqlite3_bind_text(stmt, 4, username.c_str(), -1, SQLITE_STATIC);       // Bind username

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting patient information: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Patient information inserted successfully.\n";
    }

    // Fetch and display the inserted patient information
    getPatientInfo(p->getid());

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Display Patient infomation when user input username
bool getPatientInfo(int id)
{
    int idFind = id;
    auto it = patientMap.find(idFind);
    if (it != patientMap.end())
    {
        Patient *p = it->second;
        cout << "Patient found:\n";
        cout << "ID: " << p->getid() << "\n";
        cout << "Name: " << p->getName() << "\n";
        cout << "Age: " << p->getAge() << "\n";
        cout << "Gender: " << p->getGender() << "\n";
        return true;
    }
    else
    {
        cout << "Patient with ID " << idFind << " not found!\n" << endl;
        return false;
    }
}
// Display all patient Info
void displayPatientInfo(){
     for (const auto& entry : patientMap) {
        Patient* p = entry.second;
        cout << "ID: " << p->getid() << "\n";
        cout << "Name: " << p->getName() << "\n";
        cout << "Age: " << p->getAge() << "\n";
        cout << "Gender: " << p->getGender() << "\n";
        cout << "------------------------------------\n";
    }
}
// Insert Doctor info into database
void InsertDoctorInfo(Doctor *d, const string &username, const string &department)
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
    sqlite3_bind_text(stmt, 1, d->getName().c_str(), -1, SQLITE_STATIC);      // Bind doctor name
    sqlite3_bind_int(stmt, 2, d->getAge());                                   // Bind doctor age
    sqlite3_bind_text(stmt, 3, d->getSpecialty().c_str(), -1, SQLITE_STATIC); // Bind specialty
    sqlite3_bind_text(stmt, 4, d->getGender().c_str(), -1, SQLITE_STATIC);    // Bind gender
    sqlite3_bind_text(stmt, 5, username.c_str(), -1, SQLITE_STATIC);          // Bind username
    sqlite3_bind_text(stmt, 6, department.c_str(), -1, SQLITE_STATIC);        // Bind department name

    // Execute the SQL statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Error inserting doctor information: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Doctor information inserted successfully.\n";
    }

    getDoctorInfo(d->getID());
    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Get doctor infomation from doctorMap
bool getDoctorInfo(int id)
{
    int idFind = id;
    auto it = doctorMap.find(idFind);
    if (it != doctorMap.end())
    {
        Doctor *d = it->second;
        cout << "Doctor found:\n";
        cout << "ID: " << d->getID() << "\n";
        cout << "Name: " << d->getName() << "\n";
        cout << "Age: " << d->getAge() << "\n";
        cout << "Gender: " << d->getGender() << "\n";
        cout << "Specialty: " << d->getSpecialty() << "\n";
        cout << "Department ID: " << d->getDepartmentID() << "\n";
        return true;
    }
    else
    {
        cout << "Doctor with ID " << idFind << " not found!\n" << endl;
        return false;
    }
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

        doctorMap[id] = new Doctor(id, Name, Age, specialty, Gender, userid, Departmentid);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert patient emergency info
void InsertEmergencyInfo(int Patientid, EmergencyContact *ec)
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
    sqlite3_bind_int(stmt, 1, Patientid);                                         // Bind patient ID
    sqlite3_bind_text(stmt, 2, ec->getContactName().c_str(), -1, SQLITE_STATIC);  // Bind Contact Name
    sqlite3_bind_text(stmt, 3, ec->getPhoneNumber().c_str(), -1, SQLITE_STATIC);  // Bind Phone Number
    sqlite3_bind_text(stmt, 4, ec->getRelationShip().c_str(), -1, SQLITE_STATIC); // Bind Relationship

    // Execute the SQL statement
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting patient information: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Patient information inserted successfully.\n";
    }

    getEmergencyContactInfo(ec->getContactID());
    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
// Get the emergency info when input id
void getEmergencyContactInfo(int Contactid)
{
    int idFind = Contactid;
    auto it = emergencyMap.find(idFind);
    if (it != emergencyMap.end())
    {
        EmergencyContact *ec = it->second;
        cout << "Emergency Contact Found:\n";
        cout << "Contact ID: " << ec->getContactID() << "\n";
        cout << "Patient ID: " << ec->getPatientID() << "\n";
        cout << "Contact Name: " << ec->getContactName() << "\n";
        cout << "Phone Number: " << ec->getPhoneNumber() << "\n";
        cout << "Relationship: " << ec->getRelationShip() << "\n";
    }
    else
    {
        cout << "Contact ID with " << idFind << " not found!" << endl;
    }
}
// Load department info when program start
void loadDepartmentInfo()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, Hospitalid, Department_Name, HeadofDepartment FROM Department;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "无法打开数据库: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL 错误: " << sqlite3_errmsg(db) << endl;
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
// Select all data in table (for all tables)
void SelectInfo(string table)
{
    sqlite3 *DB;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.dg", &DB);
    string query = "SELECT * FROM " + table + ";";
    sqlite3_close(DB);
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
void InsertMedicalRecords(MedicalRecordsNode *record){
    sqlite3* db;
        sqlite3_open("medical_appointment_system.db", &db);

        const char* sql = "INSERT INTO Medical_Records (Date, Details, PatientID, DoctorID) VALUES (?, ?, ?, ?);";
        sqlite3_stmt* stmt;


        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, record->date.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, record->details.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 3, record->patientID);
            sqlite3_bind_int(stmt, 4, record->doctorID);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl;
            }
        } else {
            cerr << "SQL preparation error: " << sqlite3_errmsg(db) << endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
}       
void loadMedicalRecords(){
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("medical_appointment_system.db", &db);
    const char* sql = "SELECT RecordID, Date, Details, PatientID, DoctorID FROM Medical_Records;";

    if (sqlite3_open("medical_appointment_system.db", &db))
    {
        cerr << "无法打开数据库: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "SQL 错误: " << sqlite3_errmsg(db) << endl;
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
        recordList.addRecords(MedicalRecordsNode(date, details, PatientID, DoctorID));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
