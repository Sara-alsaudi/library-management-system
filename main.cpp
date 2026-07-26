#include <iostream>
#include <string>

using namespace std;

class BorrowRecord {

private:

    struct Node {

        string memberName;
        string contactNumber;
        string bookTitle;
        string author;
        string isbn;
        string borrowDate;
        string dueDate;
        string status;

        double borrowFee;
        double lateFee;
        double totalFee;

        Node* next;
    };

    Node* head;
    Node* tail;

public:

    BorrowRecord() {
        head = NULL;
        tail = NULL;
    }

    void addBorrow() {
        Node* newNode = new Node();

        cout << "--- Enter Borrowing Details ---" << endl;

        cin.ignore();

        cout << "Member Name: ";
        getline(cin, newNode->memberName);

        cout << "Contact Number: ";
        getline(cin, newNode->contactNumber);

        cout << "Book Title: ";
        getline(cin, newNode->bookTitle);

        cout << "Author: ";
        getline(cin, newNode->author);

        cout << "ISBN: ";
        getline(cin, newNode->isbn);

        cout << "Borrow Date (YYYY-MM-DD): ";
        getline(cin, newNode->borrowDate);

        cout << "Due Date (YYYY-MM-DD): ";
        getline(cin, newNode->dueDate);

        newNode->status = "Borrowed";
        newNode->borrowFee = 20.0;
        newNode->lateFee = 0.0;
        newNode->totalFee = newNode->borrowFee + newNode->lateFee;

        newNode->next = NULL;

        // Insert the record in order by borrow date
        if (head == NULL || newNode->borrowDate < head->borrowDate) {
            newNode->next = head;
            head = newNode;

            if (tail == NULL) {
                tail = newNode;
            }
        }
        else {
            Node* current = head;

            while (current->next != NULL &&
                   current->next->borrowDate < newNode->borrowDate) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;

            if (newNode->next == NULL) {
                tail = newNode;
            }
        }

        cout << "\nRecord added successfully.\n";
    }

    void searchBorrow() {
        if (head == NULL) {
            cout << "No borrowing records available.\n";
            return;
        }

        int choice;
        string keyword;
        bool found = false;

        cout << "\nSearch Borrowing Record\n";
        cout << "1. Search by ISBN\n";
        cout << "2. Search by Book Title\n";
        cout << "3. Search by Member Name\n";
        cout << "Enter your choice: ";
        cin >> choice;

        while (choice < 1 || choice > 3) {
            cout << "Invalid input. Please enter 1, 2, or 3: ";
            cin >> choice;
        }

        cin.ignore();

        cout << "Enter search value: ";
        getline(cin, keyword);

        Node* current = head;

        while (current != NULL) {
            if ((choice == 1 && current->isbn == keyword) ||
                (choice == 2 && current->bookTitle == keyword) ||
                (choice == 3 && current->memberName == keyword)) {

                cout << "\nRecord Found!\n";
                cout << "Member Name : " << current->memberName << endl;
                cout << "Contact No. : " << current->contactNumber << endl;
                cout << "Book Title  : " << current->bookTitle << endl;
                cout << "Author      : " << current->author << endl;
                cout << "ISBN        : " << current->isbn << endl;
                cout << "Borrow Date : " << current->borrowDate << endl;
                cout << "Due Date    : " << current->dueDate << endl;
                cout << "Status      : " << current->status << endl;
                cout << "Borrow Fee  : " << current->borrowFee << " SAR" << endl;
                cout << "Late Fee    : " << current->lateFee << " SAR" << endl;
                cout << "Total Due   : " << current->totalFee << " SAR" << endl;

                found = true; }
            
            current = current->next;
        }
        if (!found) {
            cout << "\nRecord not found.\n";
        }
    }

    void returnBook() {
        if (head == NULL) {
            cout << "No borrowing records available.\n";
            return;
        }

        string isbn;
        bool found = false;

        cout << "\n--- Return Book ---\n";
        cin.ignore();
        cout << "Enter ISBN of the book: ";
        getline(cin, isbn);

        Node* current = head;

        while (current != NULL) {
            if (current->isbn == isbn) {

                found = true;

                if (current->status == "Returned") {
                    cout << "This book has already been returned.\n";
                }
                else {
                    char overdue;

                    cout << "Is the book overdue? (y/n): ";
                    cin >> overdue;

                    if (overdue == 'y' || overdue == 'Y') {
                        current->lateFee = 60.0;
                    }
                    else {
                        current->lateFee = 0.0;
                    }

                    current->totalFee = current->borrowFee + current->lateFee;
                    current->status = "Returned";

                    cout << "\nBook returned successfully.\n";
                    cout << "Member Name : " << current->memberName << endl;
                    cout << "Contact No. : " << current->contactNumber << endl;
                    cout << "Book Title  : " << current->bookTitle << endl;
                    cout << "ISBN        : " << current->isbn << endl;
                    cout << "Status      : " << current->status << endl;
                    cout << "Borrow Fee  : " << current->borrowFee << " SAR" << endl;
                    cout << "Late Fee    : " << current->lateFee << " SAR" << endl;
                    cout << "Total Due   : " << current->totalFee << " SAR" << endl;
                }

                return;
            }

            current = current->next;
        }

        if (!found) {
            cout << "Book record not found.\n";
        }
    }

    void renewBook() {
        if (head == NULL) {
            cout << "No borrowing records available to renew.\n";
            return;
        }

        string isbn;
        bool found = false;

        cout << "\n--- Renew Book Borrowing ---\n";
        cin.ignore();
        cout << "Enter ISBN of the book to renew: ";
        getline(cin, isbn);

        Node* current = head;

        while (current != NULL) {
            if (current->isbn == isbn) {

                if (current->status == "Returned") {
                    cout << "Cannot renew a book that has already been returned.\n";
                }
                else {
                    string newDueDate;

                    cout << "Current Due Date: " << current->dueDate << endl;
                    cout << "Enter New Due Date (YYYY-MM-DD): ";
                    getline(cin, newDueDate);

                    current->dueDate = newDueDate;

                    cout << "\nBorrowing renewed successfully!\n";
                    cout << "New Due Date: " << current->dueDate << endl;
                }

                found = true;
                return;
            }
            current = current->next;
        }

        if (!found) {
            cout << "Record not found with the given ISBN.\n";
        }
    }

    void displayRecords() {
        if (head == NULL) {
            cout << "\nNo borrowing records to display.\n";
            return;
        }

        cout << "\n=========================================================\n";
        cout << "                ALL BORROWING RECORDS                    \n";
        cout << "=========================================================\n";

        Node* current = head;
        int count = 1;

        while (current != NULL) {
            cout << count << ". Member: " << current->memberName
                 << " | Contact: " << current->contactNumber
                 << " | Book: " << current->bookTitle
                 << " | ISBN: " << current->isbn << endl;

            cout << "   Author: " << current->author << endl;

            cout << "   Borrow Date: " << current->borrowDate
                 << " | Due Date: " << current->dueDate
                 << " | Status: " << current->status << endl;

            cout << "   Borrow Fee: " << current->borrowFee << " SAR"
                 << " | Late Fee: " << current->lateFee << " SAR"
                 << " | Total Due: " << current->totalFee << " SAR" << endl;

            cout << "---------------------------------------------------------\n";

            current = current->next;
            count++;
        }
    }
};

int main() {
    BorrowRecord records;
    int choice;

    do {
        cout << "\n========== Welcome to the Library Book Borrowing System (LBS) ==========\n";
        cout << "\nPlease choose from the following options:\n";
        cout << "1. Borrow a book.\n";
        cout << "2. Search for a borrowing record.\n";
        cout << "3. Return a book.\n";
        cout << "4. Renew a borrowed book.\n";
        cout << "5. display all recoreds.\n";
        cout << "6. Exit.\n";
        cout << "=========================================================\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            records.addBorrow();
            break;
        case 2:
            records.searchBorrow();
            break;
        case 3:
            records.returnBook();
            break;
        case 4:
            records.renewBook();
            break;
        case 5:
            records.displayRecords();
            break;
        case 6:
            cout << "\nExiting program...\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0; }

