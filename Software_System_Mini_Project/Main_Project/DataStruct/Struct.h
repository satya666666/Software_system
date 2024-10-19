// Structure to store transaction history
struct trans_histroy
{
    int acc_no;           // Account number related to the transaction
    char hist[1024];      // Transaction history details stored as a string
};

// Structure to store feedback from users or employees
struct FeedBack
{
    char feedback[1024];  // Feedback message from the user
};

// Structure to store employee details
struct Employee {
    int empID;            // Unique Employee ID
    char firstName[20];   // Employee's first name
    char lastName[20];    // Employee's last name
    char password[256];   // Encrypted password for authentication
    int role;             // Role of the employee: 0 -> Manager, 1 -> Employee
};

// Structure to store loan details
struct LoanDetails {
    int empID;            // ID of the employee handling the loan
    int accountNumber;     // Customer's account number associated with the loan
    int loanID;           // Unique Loan ID
    int loanAmount;       // Amount of loan requested by the customer
    int status;           // Loan status: 0 -> requested, 1 -> pending, 2 -> approved, 3 -> rejected
};

// Structure to store customer details
struct Customer {
    int accountNumber;     // Unique Account number of the customer
    float balance;         // Current balance in the customer's account
    char customerName[20]; // Name of the customer
    char password[256];    // Encrypted password for customer's login
    int activeStatus;      // Account status: 0 -> deactivate, 1 -> activate
};

// Structure to store a counter value
struct Counter {
    int count;             // A general-purpose counter, can be used for tracking various items
};
