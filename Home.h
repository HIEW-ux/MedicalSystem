#include "function_insert_user.h"
using namespace std;
void publicSignin();
bool checkUserName(string username);
bool contains(string username);
bool checkIc(string ic);
bool checkPhoneNumber(string phonenumber);
void signIn();
void logIn();
void insertPersonalInfo()
{
    int count = 0;
    string username;
    while (count == 0)
    {
        cout << "First time login(0 for first time)?(0/1):\n";
        cin >> count;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (count == 1)
        {
            break;
        }
        Patient *p = new Patient();
        int NumberInput;
        string StringInput;
        cout << "Fill in your basic information.\n";
        cout << "Name:\n";
        cin >> StringInput;
        p->setName(StringInput);
        cout << "gender:\n";
        cin >> StringInput;
        p->setGender(StringInput);
        cout << "age:\n";
        cin >> NumberInput;
        p->setAge(NumberInput);
        cout << "Enter the username to associate with the patient: ";
        cin >> username;
        if (username.empty())
        {
            std::cerr << "Username cannot be empty.\n";
            return;
        }
        patientMap[username] = p;
        InsertPatientInfo(p, username);
        count = 1;
    }
    cout << "Please enter your username to get your information: ";
    cin >> username;
    getPatientInfo(username);
}
Allergy selectAllergy(AllergyMap &allergyMap)
{
    int choice;
    while (true)
    {
        cout << "Enter the ID of the allergy you want to select: ";
        cin >> choice;
        if (allergyMap.find(choice) != allergyMap.end())
        {
            return allergyMap.at(choice);
        }
        else
        {
            cout << "Invalid ID. Please try again." << endl;
        }
    }
}
void signIn()
{
    while (true)
    {
        cout << "Please select account type: 1. Admin 2. Doctor 3. Patient 4. Exit\n";
        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            publicSignin();
            break;
        case 2:
            publicSignin();
            break;
        case 3:
            publicSignin();
            break;
        case 4:
            cout << "Exit\n";
            return;
        default:
            cout << "Invalid choice\n";
        }
    }
}
void publicSignin()
{
    User *u = new User();
    string input;
    bool flag;
    while (true)
    {
        cout << "Please enter username:\n";
        cin >> input;
        u->set_username(input);
        if (!checkUserName(u->username1()) || contains(u->username1()))
        {
            cout << "Username format wrong or duplicate username, please try again\n";
            continue;
        }
        else
        {
            cout << "Username correct.\n";
            break;
        }
    }
    while (true)
    {
        string confirmpassword;
        cout << "Please enter your password:\n";
        cin >> input;
        u->set_password(input);
        cout << "Confirm password\n";
        cin >> confirmpassword;
        if (u->password1() == confirmpassword)
        {
            cout << "valid password\n";
            break;
        }
        else
        {
            cout << "Password different, please try again.\n";
        }
    }
    while (true)
    {
        cout << "Please enter your IC:\n";
        cin >> input;
        u->set_ic(input);
        flag = checkIc(u->ic1());
        if (flag)
        {
            cout << "Valid IC\n";
            break;
        }
        else
        {
            cout << "Invalid IC, please try again.\n";
        }
    }
    while (true)
    {
        cout << "Please enter your phone number:\n";
        cin >> input;
        u->set_phonenumber(input);
        flag = checkPhoneNumber(u->phonenumber1());
        if (flag)
        {
            cout << "Valid phone number.\n";
            break;
        }
        else
        {
            cout << "Invalid phone number, please try again.\n";
        }
    }
    InsertUserInfo(u);
}
bool checkUserName(string username)
{
    int len = username.length();
    if (len < 3 || len > 15)
    {
        cout << "Username too short or too long, please try again.\n";
        return false;
    }
    for (int i = 0; i < username.length(); i++)
    {
        char c = username.at(i);
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
        {
            cout << "Invalid character, please try again.\n";
            return false;
        }
    }
    int count = 0;
    for (int i = 0; i < username.length(); i++)
    {
        char c = username.at(i);
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            count++;
            break;
        }
    }
    return count > 0;
}
bool contains(string username)
{
    return userMap.find(username) != userMap.end();
}
bool checkIc(string ic)
{
    int len = ic.length();
    if (len != 12)
    {
        cout << "Invalid IC number(Must be 12-digit), please try again\n";
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        char c = ic.at(i);
        if (!(c >= '0' && c <= '9'))
        {
            return false;
        }
    }
    return true;
}
bool checkPhoneNumber(string phonenumber)
{
    int len = phonenumber.length();
    if (len < 10)
    {
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        char c = phonenumber.at(i);
        if (!(c >= '0' && c <= '9'))
        {
            return false;
        }
    }
    return true;
}
void logIn()
{
    Patient *p = new Patient();
    string cpassword;
    string cusername;
    string username;
    string password;
    int choice;
    bool flag = true;
    while (flag)
    {
        cout << "Please select acc type: 1. admin 2. doctor 3. patient 4. exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            flag = false;
            break;
        case 2:
            flag = false;
            break;
        case 3:
            flag = false;
            break;
        case 4:
            return;
        default:
            cout << "Invalid choose.\n";
        }
    }
    User *user = new User();
    cout << "please enter username:\n";
    cin >> username;
    cout << "Please enter password\n";
    cin >> password;
    if (userMap.find(username) != userMap.end())
    {
        user = userMap[username];
        if (user->password1() == password && choice == 3)
        {
            cout << "Patient login success!\n";
            p->patientPlatForm();
        }
        else if (user->password1() == password && choice == 2)
        {
            cout << "Doctor login success!\n";
        }
        else if (user->password1() == password && choice == 1)
        {
            cout << "Admin login success!\n";
        }
    }
    else
    {
        cout << "username or password incorrect\n";
    }
}

int Patient ::patientPlatForm()
{
    int choice;
    while (true)
    {
        cout << "-----Welcome to patient service platform!-----\n"
             << "---------Please select your service.----------\n";
        cout << "1. Me \n2. Booking appointment \n3. Check appointment status\n4. Medical Record\n5. Exit";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            information();
            break;
        case 2:
            break;
        }
    }
}

void Patient ::information()
{
    int choice;
    while (true)
    {
        cout << "-----------------Your profile page------------------\n"
             << "--------------Please select your service.-----------\n";
        cout << "1. Personal info\n2. Allergies\n3. Check appointment status\n4. Medical Record\n5. Exit";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            insertPersonalInfo();
            break;
        case 2:
            string patientid;
            while (true)
            {
                bool flag;
                cout << "Please enter your patient ID: ";
                cin >> patientid;
                for (const auto &entry : patientMap)
                {
                    if (entry.first == patientid)
                    {
                        flag = true;
                    }
                    else
                    {
                        flag = false;
                    }
                }
                if (flag)
                    {
                        cout << "Invalid Patient ID. Please try again." << endl;
                    }
                    else
                    {
                        cout << "Patient ID is valid. Proceeding to allergy selection." << endl;
                        break;
                    }
            }
            AllergyMap allergyMap = fetchAllergies();
            if (allergyMap.empty())
            {
                cout << "No allergies found in the database." << endl;
            }
            displayAllergies(allergyMap);
            Allergy selectedAllergy = selectAllergy(allergyMap);
            cout << "You selected:" << endl;
            cout << "ID: " << selectedAllergy.id
                 << ", Name: " << selectedAllergy.name
                 << ", Severity: " << selectedAllergy.severity << endl;
            break;
            InsertAllergyPatient(patientid,selectedAllergy.id);
        }
    }
}