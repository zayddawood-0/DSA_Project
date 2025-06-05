#include <iostream>
#include <string>
using namespace std;

const int MAX_MEMBERS = 25;

struct Registration {
    string name, Job_title, e_mail, address;
    long double cnic_number, cell_number;
};

struct Payment {
    string payment_method;
    double amount;
    int payment_pin;
};

struct Membership_type {
    string plan;
};

Registration members[MAX_MEMBERS];
Payment payments[MAX_MEMBERS];
Membership_type memberships[MAX_MEMBERS];
int num_members = 0;

int search_member_by_cnic(long double cnic) {
    for (int i = 0; i < num_members; i++) {
        if (members[i].cnic_number == cnic) {
            return i; 
        }
    }
    return -1; 
}

int search_member_by_name(const string& name) {
    for (int i = 0; i < num_members; i++) {
        if (members[i].name == name) {
            return i; 
        }
    }
    return -1; 
}


void sort_members_by_name() {
    for (int i = 0; i < num_members - 1; i++) {
        for (int j = 0; j < num_members - i - 1; j++) {
            if (members[j].name > members[j + 1].name) {
                swap(members[j], members[j + 1]);
                swap(payments[j], payments[j + 1]);
                swap(memberships[j], memberships[j + 1]);
            }
        }
    }
}

void sort_members_by_payment_amount() {
    for (int i = 0; i < num_members - 1; i++) {
        for (int j = 0; j < num_members - i - 1; j++) {
            if (payments[j].amount > payments[j + 1].amount) {
                swap(members[j], members[j + 1]);
                swap(payments[j], payments[j + 1]);
                swap(memberships[j], memberships[j + 1]);
            }
        }
    }
}

void display_members(const Registration members[], const Payment payments[], const Membership_type memberships[], int num_members) {
    if (num_members == 0) {
        cout << "\nNo members added yet." << endl;
    }
    else {
        cout << "\nMember Details:" << endl;
        for (int i = 0; i < num_members; ++i) {
            cout << "\nMember " << i + 1 << ":" << endl;
            cout << "Name: " << members[i].name << endl;
            cout << "Mobile number: " << members[i].cell_number << endl;
            cout << "CNIC number: " << members[i].cnic_number << endl;
            cout << "E-mail: " << members[i].e_mail << endl;
            cout << "Job Title: " << members[i].Job_title << endl;
            cout << "Membership Plan: " << memberships[i].plan << endl;

            if (!payments[i].payment_method.empty()) {
                cout << "\nPayment details: " << endl;
                cout << "Payment method: " << payments[i].payment_method << endl;
                cout << "Payment amount: " << payments[i].amount << endl;
                if (payments[i].payment_method == "Credit Card" || payments[i].payment_method == "Visa card") {
                    cout << "Payment PIN: " << payments[i].payment_pin << endl;
                }
            }
            else {
                cout << "No payment information available for this member." << endl;
            }
        }
    }
}

void add_member() {
    if (num_members < MAX_MEMBERS) {
        Registration user;
        Payment payment;
        Membership_type membership;

        cout << "\nEnter member's name: ";
        cin.ignore(); 
        getline(cin, user.name);
        cout << "Enter job title: ";
        getline(cin, user.Job_title);
        cout << "Enter email: ";
        getline(cin, user.e_mail);
        cout << "Enter address: ";
        getline(cin, user.address);
        cout << "Enter CNIC number: ";
        cin >> user.cnic_number;
        cout << "Enter mobile number: ";
        cin >> user.cell_number;

        cout << "Enter payment method (Credit Card, Paypal, Visa Card): ";
        cin.ignore(); 
        getline(cin, payment.payment_method);
        cout << "Enter payment amount: ";
        cin >> payment.amount;

        if (payment.payment_method == "Credit Card" || payment.payment_method == "Visa Card") {
            cout << "Enter payment PIN: ";
            cin >> payment.payment_pin;
        }

        cout << "Enter membership plan (Gold, Platinum, Bronze): ";
        cin.ignore(); 
        getline(cin, membership.plan);

        members[num_members] = user;
        payments[num_members] = payment;
        memberships[num_members] = membership;
        num_members++;

        cout << "Member added successfully!" << endl;
    } else {
        cout << "Maximum member limit reached!" << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. Add member\n2. Display all members\n3. Search member by CNIC\n4. Search member by name\n5. Sort members by name\n6. Sort members by payment amount\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            add_member();
            break;
        case 2:
            display_members(members, payments, memberships, num_members);
            break;
        case 3:
            {
                long double cnic;
                cout << "Enter CNIC to search: ";
                cin >> cnic;
                int index = search_member_by_cnic(cnic);
                if (index != -1) {
                    cout << "Member found: " << members[index].name << endl;
                } else {
                    cout << "Member not found!" << endl;
                }
            }
            break;
        case 4:
            {
                string name;
                cout << "Enter name to search: ";
                cin.ignore();
                getline(cin, name);
                int index = search_member_by_name(name);
                if (index != -1) {
                    cout << "Member found: " << members[index].name << endl;
                } else {
                    cout << "Member not found!" << endl;
                }
            }
            break;
        case 5:
            sort_members_by_name();
            cout << "Members sorted by name." << endl;
            break;
        case 6:
            sort_members_by_payment_amount();
            cout << "Members sorted by payment amount." << endl;
            break;
        case 7:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 7);

    return 0;
}

