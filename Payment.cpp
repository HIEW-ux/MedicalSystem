#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
#include <ctime>

using namespace std;

// linked list
struct InsuranceNode {
    string providerName;
    double coveragePercentage; // Coverage %
    InsuranceNode* next;

    InsuranceNode(string provider, double coverage) 
        : providerName(provider), coveragePercentage(coverage), next(nullptr) {}
};

// linked list for insurance providers
class InsuranceList {
private:
    InsuranceNode* head;

public:
    InsuranceList() : head(nullptr) {}

    void addProvider(const string& provider, double coverage) {
        InsuranceNode* newNode = new InsuranceNode(provider, coverage);
        newNode->next = head;
        head = newNode;
    }

    // find insurance coverage by provider name
    double findCoverage(const string& provider) const {
        InsuranceNode* current = head;
        string lowerProvider = provider;
        transform(lowerProvider.begin(), lowerProvider.end(), lowerProvider.begin(), ::tolower);
        
        while (current != nullptr) {
            string lowerCurrent = current->providerName;
            transform(lowerCurrent.begin(), lowerCurrent.end(), lowerCurrent.begin(), ::tolower);
            
            if (lowerCurrent == lowerProvider) {
                return current->coveragePercentage;
            }
            current = current->next;
        }
        return -1.0; // Not found
    }

    // Display insurance providers
    void displayProviders() const {
        InsuranceNode* current = head;
        cout << "\n--- Available Insurance Providers ---\n";
        while (current != nullptr) {
            cout << current->providerName << " - Covers " << current->coveragePercentage << "%\n";
            current = current->next;
        }
    }

    ~InsuranceList() {
        while (head != nullptr) {
            InsuranceNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Patient Payment
class PatientPayment {
private:
    double serviceCost;
    InsuranceList insuranceList;

public:
    PatientPayment(double cost) : serviceCost(cost) {
        // insurance providers
        insuranceList.addProvider("AIA", 80.0);
        insuranceList.addProvider("Prudential", 70.0);
        insuranceList.addProvider("Great Eastern", 60.0);
        insuranceList.addProvider("AXA", 90.0);
        insuranceList.addProvider("Allianz", 85.0); 
    }

    void makePayment(const string& patientName) const {
        cout << "\n Payment Process...\n";
        cout << "Service cost: RM " << fixed << setprecision(2) << serviceCost << "\n";

        char choice;
        cout << "Do you have insurance? (Y/N): ";
        cin >> choice;

        if (toupper(choice) == 'Y') {
            string insuranceProvider;
            cout << "Enter your insurance provider: ";
            cin.ignore();
            getline(cin, insuranceProvider);

            processInsurance(insuranceProvider);
        } else if (toupper(choice) == 'N') {
            payDirectly();
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    void processInsurance(const string& insuranceProvider) const {
        double coverage = insuranceList.findCoverage(insuranceProvider);
        if (coverage >= 0) {
            double amountToPay = serviceCost * ((100.0 - coverage) / 100.0);
            cout << "Your insurance covers " << coverage << "% of the cost.\n";
            cout << "You need to pay: RM " << fixed << setprecision(2) << amountToPay << "\n";
            
            choosePaymentMethod();
        } else {
            cout << "Insurance provider not found. Please proceed with full payment.\n";
            payDirectly();
        }
    }
//payment method
    void choosePaymentMethod() const {
        cout << "\nSelect your payment method:\n";
        cout << "1. Online Banking\n";
        cout << "2. E-Wallet\n";
        cout << "3. Credit/Debit Card\n";
        
        int method;
        cout << "Enter your choice: ";
        cin >> method;

        switch (method) {
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
    void payDirectly() const {
        cout << "You need to pay the full amount: RM " << fixed << setprecision(2) << serviceCost << "\n";

        choosePaymentMethod();
    }
   void displayPaymentDateTime() const { 
    time_t now = time(0); 
    tm *ltm = localtime(&now); 

    char buf[100]; strftime(buf, sizeof(buf), "%a %d %b %Y %I:%M:%S %p", ltm); 
    cout << "Payment Date and Time: " << buf << "\n";
        }

    void displayInsuranceProviders() const {
        insuranceList.displayProviders();
    }
};

int main() {
    while (true) {
        cout << "\n=== Patient Payment System ===\n";
        cout << "1. Make Payment\n";
        cout << "2. View Insurance Providers\n";
        cout << "3. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) {
            double cost;
            cout << "Enter the service cost: RM ";
            cin >> cost;

            string patientName;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, patientName);

            PatientPayment payment(cost);
            payment.makePayment(patientName);
        } else if (choice == 2) {
            PatientPayment dummy(0); // dummy object to access insurance list
            dummy.displayInsuranceProviders();
        } else if (choice == 3) {
            cout << "Exiting the system... Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
