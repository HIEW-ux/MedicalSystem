#include <map>
#include <vector>
#include <limits>
#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;
class Patient;
class Doctor;
class Allergy;
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
     Patient(int id, const string& n, const string& g, int a)
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
class Doctor {
private:
    int doctorID;
    string name;
    int age;
    string gender;
    string specialty;

public:
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
    void showDoctorDashboard();
    void displayDoctorInfo();
};
class Allergy{
    private:
    int id;
    string name;
    string severity;
    public:
    Allergy(){}
     Allergy(int allergy_id, const string& allergy_name, const string& allergy_severity)
        : id(allergy_id), name(allergy_name), severity(allergy_severity) {}
    int getId(){
        return this->id;
    }
    void setId(int id){
        this->id = id;
    }
    string getName(){
        return this->name;
    }
    void setName(string name){
        this->name = name;
    }
    string getSeverity(){
        return this->severity;
    }
    void setSeverity(string severity){
        this->severity = severity;
    }
};
static int callback(void* data, int argc, char** argv, char** azColName);
void initializedDatabase(sqlite3* db);
// void loadPatientInfo();
// void loadUserInfo();
void SelectInfo(string table);
void InsertUserInfo(User* u);
void InsertPatientInfo(Patient* p, string username);
void InsertDoctorInfo(Doctor* d, string username, string department);
void InsertAllergyPatient(int Patientid, int Allergyid);
void fetchAllergies();
void displayAllergies();
void getPatientInfo(string name);
// void getDoctorInfo(string username);
map<string, Patient*> patientMap;
map<string, Doctor*> doctorMap;
map<string, User*> userMap;
map<int, Allergy*> allergyMap;


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
    //Hospital table
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
}
//Select allergies from database and put in unorderMap
void fetchAllergies() {
    sqlite3* db;
    int exit = sqlite3_open("medical_appointment_system.db",&db);
    sqlite3_stmt* stmt;

    // 打开数据库
    if (exit != SQLITE_OK) {
        cerr << "无法打开数据库: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // SQL 查询语句
    const char* query = "SELECT Allergy_id, Allergy_Name, Severity FROM allergies";

     if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL 准备失败: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }
    // 执行查询并存储数据到 map
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string severity = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        // 添加到全局 map
        allergyMap[id] = new Allergy(id,name,severity);
    }

    // 清理资源
    sqlite3_finalize(stmt);
    sqlite3_close(db);

}
//Display Allergies
void displayAllergies() {
    for (const auto& [id, allergy] : allergyMap) {
        cout << "ID: " << id << ", Name: " << allergy->getName() << ", Severity: " << allergy->getSeverity() << "\n";
    }
}
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

        patientMap[Name] = new Patient(id,Name,Gender,Age);
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
        
        userMap[username] = new User(username, password, phonenumber, IC, id);
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
        cerr << "打开数据库时出错: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    // 插入 Patient 表的 SQL 语句
    string sql = R"(
        INSERT INTO Patient (P_Name, P_Age, P_Gender, User_id)
        VALUES (?, ?, ?, (SELECT id FROM users WHERE username = ?));
    )";
    sqlite3_stmt *stmt;

    // 准备插入语句
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "准备语句时出错: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    // 绑定参数
    sqlite3_bind_text(stmt, 1, p->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, p->getAge());
    sqlite3_bind_text(stmt, 3, p->getGender().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, username.c_str(), -1, SQLITE_STATIC);

    // 执行插入操作
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "插入患者信息时出错: " << sqlite3_errmsg(DB) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return;
    }
    else
    {
        cout << "患者信息插入成功。\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

void InsertDoctorInfo(Doctor *d, string username, string department)
{
    sqlite3 *DB;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);

    if (exit != SQLITE_OK)
    {
        cerr << "打开数据库时出错: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    // 插入医生信息的 SQL 语句
    string sql = R"(
        INSERT INTO Doctor (D_Name, D_Age, Specialty, D_Gender, Userid, Departmentid)
        VALUES (?, ?, ?, ?, 
                (SELECT id FROM users WHERE username = ?), 
                (SELECT id FROM Department WHERE Department_Name = ?));
    )";
    sqlite3_stmt *stmt;

    // 准备插入语句
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "准备语句时出错: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    // 绑定参数
    sqlite3_bind_text(stmt, 1, d->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, d->getAge());
    sqlite3_bind_text(stmt, 3, d->getSpecialty().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, d->getGender().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, department.c_str(), -1, SQLITE_STATIC);

    // 执行插入操作
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cerr << "插入医生信息时出错: " << sqlite3_errmsg(DB) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return;
    }
    else
    {
        cout << "医生信息插入成功。\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

void InsertAllergyPatient(int Patientid, int Allergyid){
    sqlite3* db;
    sqlite3_open("medical_appointment_system.db",&db);
    const char* sql = "INSERT INTO Allergies_Patient (Allergyid, Patientid VALUES (?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, Allergyid);  
    sqlite3_bind_int(stmt, 2, Patientid);  

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "执行插入失败: " << sqlite3_errmsg(db) << "\n";
    } else {
        cout << "过敏信息成功存储到 Allergies_Patient 表中。\n";
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

// // Display Patient infomation when user input username
void getPatientInfo(string name)
{
   string nameFind = name;
   auto it = patientMap.find(nameFind);
   if (it != patientMap.end()) {
    Patient* p = it->second;
        cout << "Patient found:\n";
        cout << "ID: " << p->getid() << "\n";
        cout << "Name: " << p->getName() << "\n";
        cout << "Age: " << p->getAge() << "\n";
        cout << "Gender: " << p->getGender() << "\n";
    } else {
        cout << "Patient with Name " << nameFind << " not found!" << endl;
    }
}
// void getDoctorInfo(string username)
// {
//     sqlite3 *DB;
//     int exit = sqlite3_open("medical_appointment_system.db", &DB);
//     const char *sql = R"(
//         SELECT 
//             Doctor.id, Doctor.D_Name, Doctor.D_Age, Doctor.D_Gender, Doctor.Specialty, Doctor.userid, Doctor.Departmentid
//         FROM 
//             users 
//         INNER JOIN 
//             Doctor 
//         ON 
//             users.id = Doctor.Userid 
//         WHERE 
//             users.username = ?;
//     )";
//     sqlite3_stmt *stmt;
//     if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
//     {
//         cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
//         return;
//     }
//     sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
//     int result = sqlite3_step(stmt);
//     if (result == SQLITE_ROW)
//     {
//         int doctorID = sqlite3_column_int(stmt, 0);
//         string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
//         int age = sqlite3_column_int(stmt, 2);
//         string gender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
//         string specialty = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
//         int User_id = sqlite3_column_int(stmt, 5);
//         int department_id = sqlite3_column_int(stmt, 6);
//         cout << "Patient ID: " << doctorID << "\n";
//         cout << "Name: " << name << "\n";
//         cout << "Age: " << age << "\n";
//         cout << "Gender: " << gender << "\n";
//         cout << "Specialty: " << specialty << "\n";
//         cout << "User ID: " << User_id << "\n";
//         cout << "Department ID: " << department_id << "\n";
//     }
//     else if (result == SQLITE_DONE)
//     {
//         cout << "No Doctor information found for username: " << username << "\n";
//     }
//     else
//     {
//         cerr << "Query failed: " << sqlite3_errmsg(DB) << endl;
//     }
//     sqlite3_finalize(stmt);
// }