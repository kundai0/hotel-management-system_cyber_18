#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Room {

    
public:
    int roomNumber;
    string type;
    float rent;
    bool isBooked;

    Room(int rNo, string t, float r, bool booked = false)
        : roomNumber(rNo), type(t), rent(r), isBooked(booked) {}
};

class Customer {
public:
    string name, address, phone;
    int roomNumber, days;
    float paymentAdvance, totalPayment;
    
    bool checkedOut;

    Customer(string n, string a, string p, int rNo, int d, float adv, float total)
        : name(n), address(a), phone(p), roomNumber(rNo), days(d),
          paymentAdvance(adv), totalPayment(total), checkedOut(false) {}
};

class Staff {
public:
    string name, role, phone;

    Staff(string n, string r, string p) : name(n), role(r), phone(p) {}
};

class Hotel {
private:
    vector<Room> rooms;
    vector<Customer> customers;
    vector<Staff> staffList;

public:
    Hotel() {
        // Preload 10 rooms
        rooms = {
            {101, "Deluxe", 2500, true},
            {102, "Standard", 2000, true},
            {103, "Suite", 3000, true},
            {104, "Deluxe", 2500, true},
            {105, "Standard", 2000, false},
            {106, "Deluxe", 2500, false},
            {107, "Suite", 3000, false},
            {108, "Deluxe", 2500, false},
            {109, "Standard", 2000, false},
            {110, "Suite", 3000, false}
        };

        // Preloaded customer bookings
        customers = {
            {"Rahul Sharma", "12 MG Road, Pune, Maharashtra", "9876543210", 101, 3, 3000, 7500},
            {"Priya Nair", "45 Marine Drive, Kochi, Kerala", "9123456789", 102, 2, 2000, 5000},
            {"Amit Verma", "78 Park Street, Kolkata, West Bengal", "9988776655", 103, 5, 6000, 12000},
            {"Neha Singh", "9 Sector 18, Noida, Uttar Pradesh", "9090909090", 104, 4, 4000, 10000}
        };

        // Preload staff
        staffList = {
            {"Ramesh Patel", "Manager", "9823456780"},
            {"Sunita Rao", "Receptionist", "9912345678"},
            {"Arjun Mehta", "Housekeeping", "9845612345"},
            {"Lakshmi Devi", "Cook", "9789012345"}
        };
    }

    // ---------------- ADMIN SECTION ----------------
    void adminMenu() {
        string password;
        cout << "\nEnter Admin Password: ";
        cin >> password;

        if (password != "admin123") {
            cout << "❌ Incorrect password! Access denied.\n";
            return;
        }

        int choice;
        do {
            cout << "\n--- ADMIN MENU ---";
            cout << "\n1. View All Rooms";
            cout << "\n2. View All Bookings";
            cout << "\n3. View Staff";
            cout << "\n4. Add Staff";
            cout << "\n5. Check-Out Customer";
            cout << "\n6. Logout";
            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: viewRooms(); break;
            case 2: viewAllBookings(); break;
            case 3: viewStaff(); break;
            case 4: addStaff(); break;
            case 5: checkOutCustomer(); break;
            case 6: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 6);
    }

    void viewRooms() {
        cout << "\n--- ROOM LIST ---\n";
        cout << left << setw(10) << "Room No"
             << setw(12) << "Type"
             << setw(10) << "Rent"
             << setw(12) << "Status" << endl;
        cout << string(44, '-') << endl;

        for (auto &room : rooms) {
            cout << left << setw(10) << room.roomNumber
                 << setw(12) << room.type
                 << setw(10) << room.rent
                 << setw(12) << (room.isBooked ? "Booked" : "Available") << endl;
        }
    }

    void viewAllBookings() {
        cout << "\n--- ALL BOOKINGS ---\n";
        if (customers.empty()) {
            cout << "No bookings found!\n";
            return;
        }

        cout << left << setw(18) << "Name"
             << setw(25) << "Address"
             << setw(15) << "Phone"
             << setw(8) << "Room"
             << setw(6) << "Days"
             << setw(12) << "Advance"
             << setw(10) << "Total"
             << setw(12) << "Status" << endl;
        cout << string(106, '-') << endl;

        for (auto &cust : customers) {
            cout << left << setw(18) << cust.name
                 << setw(25) << cust.address.substr(0, 23)
                 << setw(15) << cust.phone
                 << setw(8) << cust.roomNumber
                 << setw(6) << cust.days
                 << setw(12) << cust.paymentAdvance
                 << setw(10) << cust.totalPayment
                 << setw(12) << (cust.checkedOut ? "Checked Out" : "Active") << endl;
        }
    }

    void viewStaff() {
        cout << "\n--- STAFF LIST ---\n";
        cout << left << setw(20) << "Name" << setw(20) << "Role"
             << setw(15) << "Phone" << endl;
        cout << string(55, '-') << endl;

        for (auto &s : staffList) {
            cout << left << setw(20) << s.name
                 << setw(20) << s.role
                 << setw(15) << s.phone << endl;
        }
    }

    void addStaff() {
        string name, role, phone;
        cout << "\nEnter staff name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter role: ";
        getline(cin, role);
        cout << "Enter phone number: ";
        getline(cin, phone);

        staffList.emplace_back(name, role, phone);
        cout << "✅ Staff member added successfully!\n";
    }

    void checkOutCustomer() {
        int roomNo;
        cout << "\nEnter Room Number for Check-Out: ";
        cin >> roomNo;

        bool foundCustomer = false;
        for (auto &cust : customers) {
            if (cust.roomNumber == roomNo && !cust.checkedOut) {
                cust.checkedOut = true;
                foundCustomer = true;

                // Update room status to available
                for (auto &room : rooms) {
                    if (room.roomNumber == roomNo) {
                        room.isBooked = false;
                        break;
                    }
                }

                cout << "✅ " << cust.name << " has been checked out successfully.\n";
                cout << "Room " << roomNo << " is now AVAILABLE for booking.\n";
                break;
            }
        }

        if (!foundCustomer)
            cout << "❌ No active booking found for Room " << roomNo << ".\n";
    }

    // ---------------- CUSTOMER SECTION ----------------
    void customerMenu() {
        int choice;
        do {
            cout << "\n--- CUSTOMER MENU ---";
            cout << "\n1. View Available Rooms";
            cout << "\n2. Book a Room";
            cout << "\n3. Exit";
            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: viewAvailableRooms(); break;
            case 2: bookRoom(); break;
            case 3: cout << "Exiting customer menu...\n"; break;
            default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 3);
    }

    void viewAvailableRooms() {
        cout << "\n--- AVAILABLE ROOMS ---\n";
        bool found = false;
        for (auto &room : rooms) {
            if (!room.isBooked) {
                cout << "Room " << room.roomNumber << " (" << room.type
                     << ") - ₹" << room.rent << " per day\n";
                found = true;
            }
        }
        if (!found) cout << "No rooms available right now!\n";
    }

    void bookRoom() {
        string name, address, phone;
        int roomNo, days;
        float advance;

        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter phone number: ";
        getline(cin, phone);

        cout << "\nAvailable Rooms:\n";
        viewAvailableRooms();

        cout << "\nEnter room number to book: ";
        cin >> roomNo;

        bool found = false;
        for (auto &room : rooms) {
            if (room.roomNumber == roomNo && !room.isBooked) {
                found = true;
                cout << "Enter number of days: ";
                cin >> days;
                cout << "Enter advance payment (₹): ";
                cin >> advance;

                float total = room.rent * days;
                customers.emplace_back(name, address, phone, roomNo, days, advance, total);
                room.isBooked = true;

                cout << "\n✅ Booking successful!\n";
                cout << "Room " << roomNo << " booked for " << name << " for " << days << " days.\n";
                return;
            }
        }

        if (!found)
            cout << "❌ Invalid room number or already booked!\n";
    }
};

// ---------------- MAIN ----------------
int main() {
    Hotel h;
    int userChoice;

    do {
        cout << "\n====== HOTEL MANAGEMENT SYSTEM ======\n";
        cout << "1. Admin Login\n";
        cout << "2. Customer Menu\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
        case 1: h.adminMenu(); break;
        case 2: h.customerMenu(); break;
        case 3: cout << "👋 Thank you for using the system!\n"; break;
        default: cout << "Invalid choice!\n"; break;
        }
    } while (userChoice != 3);

    return 0;
}
