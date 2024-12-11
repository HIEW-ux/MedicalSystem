#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits> 

using namespace std;

class Feedback {
private:
    string patientName;
    string doctorName;
    string feedbackText;
    int rating;

public:
    Feedback(const string& pName, const string& dName, const string& feedback, int rate) 
        : patientName(pName), doctorName(dName), feedbackText(feedback), rating(rate) {}

    // display feedback
    void displayFeedback() const {
        cout << "\n--- Feedback ---\n";
        cout << "Patient: " << patientName << "\n";
        cout << "Doctor: Dr. " << doctorName << "\n";
        cout << "Rating: " << rating << " / 5\n";
        cout << "Feedback: " << feedbackText << "\n";
    }
};

// class to manage feedback records
class FeedbackManager {
private:
    vector<Feedback> feedbackList;

public:
    void addFeedback(const string& patientName, const string& doctorName, const string& feedbackText, int rating) {
        if (rating < 1 || rating > 5) {
            cout << "Invalid rating! Please enter a rating between 1 and 5.\n";
            return;
        }

        if (feedbackText.empty()) {
            cout << "Feedback cannot be empty. Please provide your feedback.\n";
            return;
        }

        Feedback feedback(patientName, doctorName, feedbackText, rating);
        feedbackList.push_back(feedback);
        cout << "Feedback submitted successfully!\n";
        feedback.displayFeedback(); //display at the end
    }
};

int main() {
    FeedbackManager manager;

    while (true) {
        cout << "\n------Patient Feedback Platform------\n";
        cout << "1. Submit Feedback\n";
        cout << "2. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (choice) { 
            case 1: { 
                string patientName, doctorName, feedbackText; 
                int rating;

                 cout << "Enter your name: "; 
                 getline(cin, patientName); 
                 
                 cout << "Enter the doctor's name: Dr. "; 
                 getline(cin, doctorName); 
                 
                 cout << "Enter your feedback: "; 
                 getline(cin, feedbackText); 
                 
                 cout << "Enter your rating (1-5): "; 
                 cin >> rating; 
                 
                 manager.addFeedback(patientName, doctorName, feedbackText, rating); 
                 break; } 
                 
            case 2: 
            cout << "Exiting the system... Goodbye!\n"; 
            return 0; 
            default: 
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
