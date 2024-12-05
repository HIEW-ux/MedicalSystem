#include <map>
#include <unordered_map>
#include <vector>
#include <limits>
#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;
class Patient;
struct Allergy
{
    int id;
    string name;
    string severity;
};
using AllergyMap = unordered_map<int, Allergy>;
class User {
private:
    string username;
    string password;
    string phonenumber;
    string ic;
    int id;
public:
    User(){
    }
    User(string username, string password, string phonenumber, string ic, int id)
        : username(username), password(password), phonenumber(phonenumber), ic(ic), id(id){}

    string username1() {
        return username;
    }

    void set_username(string username) {
        this->username = username;
    }

    string password1() {
        return password;
    }

    void set_password(string password) {
        this->password = password;
    }

    string phonenumber1() {
        return phonenumber;
    }

    void set_phonenumber(string phonenumber) {
        this->phonenumber = phonenumber;
    }

    string ic1() {
        return ic;
    }

    void set_ic(string ic) {
        this->ic = ic;
    }
    int id1(){
        return id;
    }
    void set_id(int id){
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

static int callback(void* data, int argc, char** argv, char** azColName);
void initializedDatabase(sqlite3* db);
void loadPatientInfo();
void loadUserInfo();
void SelectInfo(string table);
void InsertUserInfo(User* u);
void InsertPatientInfo(Patient* p, string username);
void InsertAllergyPatient(string Patientid, int Allergyid);
AllergyMap fetchAllergies();
void displayAllergies(AllergyMap& allergyMap);
void getPatientInfo(string username);
map<string, Patient*> patientMap;
map<string, User*> userMap;

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
}
//Select allergies from database and put in unorderMap
AllergyMap fetchAllergies() {
    sqlite3* db;
    sqlite3_open("medical_appointment_system.db",&db);
    AllergyMap allergyMap;
    const char* sql = "SELECT Allergy_id, Allergy_Name, Severity FROM allergies";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return allergyMap;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int allergy_id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string severity = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        //Put in unorderMap
        allergyMap[allergy_id] = {allergy_id, name, severity};
    }

    sqlite3_finalize(stmt);
    return allergyMap;
}
//Display Allergies
void displayAllergies(AllergyMap& allergyMap) {
    cout << "Allergy List:" << endl;
    for (const auto& [id, allergy] : allergyMap) {
        cout << "ID: " << allergy.id
                  << ", Name: " << allergy.name
                  << ", Severity: " << allergy.severity << endl;
    }
}
void loadPatientInfo()
{
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id,P_Name,P_Age,P_Gender FROM Patient;";
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
        string Name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int Age = stoi(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        string Gender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

        Patient* p = new Patient();
        p->setName(Name);
        p->setAge(Age);
        p->setGender(Gender);
        p->setid(id);
        patientMap[Name] = p;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
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

        User* u = new User();
        u->set_username(username);
        u->set_password(password);
        u->set_phonenumber(phonenumber);
        u->set_ic(IC);
        u->set_id(id);
        userMap[username] = u;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
// Insert User info when register
void InsertUserInfo(User *u)
{
    sqlite3 *DB;
    char *messageError;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    string sql("INSERT INTO users(username,password,phonenumber,IC)VALUES('" + u->username1() + "','" + u->password1() + "','" + u->phonenumber1() + "','" + u->ic1() + "');");
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        cerr << "Error Insert" << messageError;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Records insert successfully\n";
    }
    sqlite3_close(DB);
}

// Insert Patient info, also add foreign key data into table
void InsertPatientInfo(Patient *p, string username)
{
    sqlite3 *DB;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    const char *sql = R"(
        INSERT INTO Patient (P_Name, P_Age, P_Gender, User_id)
        VALUES (?, ?, ?, (SELECT id FROM users WHERE username = ?));
    )";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    sqlite3_bind_text(stmt, 1, p->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, p->getAge());
    sqlite3_bind_text(stmt, 3, p->getGender().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, username.c_str(), -1, SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "Error inserting patient: " << sqlite3_errmsg(DB) << endl;
    }
    else
    {
        cout << "Patient inserted successfully.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}
void InsertAllergyPatient(int Patientid, int Allergyid){
    sqlite3* db;
    sqlite3_open("medical_appointment_system.db",&db);
    const char* sql = "INSERT INTO Allergies_patient (Allergyid, Patientid) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, Patientid);  
    sqlite3_bind_int(stmt, 2, Allergyid);  

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << "Selected allergy inserted successfully into Allergies_patient table.\n";
    } else {
        cerr << "Failed to insert selected allergy: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
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

// Display Patient infomation when user input username
void getPatientInfo(string username)
{
    sqlite3 *DB;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);
    const char *sql = R"(
        SELECT 
            Patient.id, Patient.P_Name, Patient.P_Age, Patient.P_Gender, Patient.User_id
        FROM 
            users 
        INNER JOIN 
            Patient 
        ON 
            users.id = Patient.User_id 
        WHERE 
            users.username = ?;
    )";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        int patientId = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        string gender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        int User_id = sqlite3_column_int(stmt, 4);
        cout << "Patient ID: " << patientId << "\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Gender: " << gender << "\n";
        cout << "User ID: " << User_id << "\n";
    }
    else if (result == SQLITE_DONE)
    {
        cout << "No patient information found for username: " << username << "\n";
    }
    else
    {
        cerr << "Query failed: " << sqlite3_errmsg(DB) << endl;
    }
    sqlite3_finalize(stmt);
}
