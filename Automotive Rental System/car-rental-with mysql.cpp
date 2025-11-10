#include <iostream>        // For standard input/output operations
#include <mysql.h>         // MySQL C API header
#include <mysqld_error.h>  // For MySQL error handling
#include <windows.h>       // For Sleep() and system("cls") on Windows
#include <sstream>         // For stringstream (integer to string conversion)
using namespace std;

const char* HOST = "localhost";    // MySQL host
const char* USER = "root";         // MySQL username
const char* PW = "your password";  // MySQL password
const char* DB = "mydb";           // MySQL database name

// Car class definition
class Car {
private:
    string Brand, Model;  // Car brand and model
    int Serial, Rent;     // Serial number and rent per day
    bool Avail;           // Availability (true = available)

public:
    // Constructor to initialize Car object
    Car(int serial, string brand, string model, int rent, bool avail) {
        Serial = serial;
        Brand = brand;
        Model = model;
        Rent = rent;
        Avail = avail;
    }

    // Getter functions for each data member
    int getSerial() { return Serial; }
    string getBrand() { return Brand; }
    string getModel() { return Model; }
    int getRent() { return Rent; }
    bool getAvail() { return Avail; }
};

// Function to check car availability in database
bool isAvail(MYSQL* conn, string toS) {
    string comp = "SELECT Avail FROM cars WHERE Serial='" + toS + "'"; // SQL query
    if (mysql_query(conn, comp.c_str())) {                             // Execute query
        cout << "Error: " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(conn);  // Store query result
    if (result) {
        MYSQL_ROW row = mysql_fetch_row(result);   // Fetch first row
        if (row) {
            int availability = atoi(row[0]);       // Convert result to integer
            mysql_free_result(result);             // Free memory
            return (availability == 1);            // Return true if available
        }
        mysql_free_result(result);
    }
    return false;  // Default return false
}

int main() {
    MYSQL* conn;
    conn = mysql_init(NULL);  // Initialize MySQL connection object

    // Attempt to connect to MySQL database
    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;  // Print error if failed
    } else {
        cout << "Logged in!!" << endl;                   // Success message
    }

    // Create three Car objects
    Car car1(123, "Honda", "Civic", 60, true);
    Car car2(223, "Toyota", "Yaris", 50, true);
    Car car3(323, "Suzuki", "Alto", 30, true);

    // SQL insert statements for the three cars
    string save1 = "INSERT INTO cars (Serial, Brand, Model, Rent, Avail) VALUES(123,'Honda','Civic',60,true)";
    string save2 = "INSERT INTO cars (Serial, Brand, Model, Rent, Avail) VALUES(223,'Toyota','Yaris',50,true)";
    string save3 = "INSERT INTO cars (Serial, Brand, Model, Rent, Avail) VALUES(323,'Suzuki','Alto',30,true)";

    // Execute insert queries and check for errors
    if (mysql_query(conn, save1.c_str()) || mysql_query(conn, save2.c_str()) || mysql_query(conn, save3.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Data saved for cars" << endl;
    }

    Sleep(5000);  // Pause for 5 seconds
    bool exit = false;

    // Main program loop
    while (!exit) {
        system("cls");  // Clear screen
        cout << "Welcome to Car Rental System" << endl;
        cout << "****************************" << endl;

        // Display all cars from database
        string get = "SELECT * FROM cars";
        if (mysql_query(conn, get.c_str())) {
            cout << "Error: " << mysql_error(conn) << endl;
        } else {
            MYSQL_RES* result = mysql_store_result(conn);
            if (result) {
                int num = mysql_num_fields(result);  // Number of columns
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result))) {  // Loop through rows
                    for (int i = 0; i < num; i++) {
                        cout << " " << row[i];  // Print each column value
                    }
                    cout << endl;
                }
                mysql_free_result(result);
            }
        }

        int val;
        cout << "1. Select Car." << endl;
        cout << "0. Exit." << endl;
        cin >> val;  // User input choice

        if (val == 1) {
            int ser;
            cout << "Enter Serial: " << endl;
            cin >> ser;  // Input serial number

            stringstream ss;
            ss << ser;
            string toS = ss.str();  // Convert serial number to string

            // Check which car matches entered serial
            if (car1.getSerial() == ser) {
                if (isAvail(conn, toS)) {  // Check if available
                    string upd = "UPDATE cars SET Avail ='0' WHERE Serial ='" + toS + "'";
                    if (mysql_query(conn, upd.c_str())) {
                        cout << "Error: " << mysql_error(conn);
                    } else {
                        cout << "You have selected following car: " << endl;
                        cout << car1.getBrand() << " " << car1.getModel() << "  $" << car1.getRent() << endl;
                    }
                } else {
                    cout << "Sorry this car is already booked" << endl;
                }
            }

            // Repeat same logic for car2
            if (car2.getSerial() == ser) {
                if (isAvail(conn, toS)) {
                    string upd = "UPDATE cars SET Avail ='0' WHERE Serial ='" + toS + "'";
                    if (mysql_query(conn, upd.c_str())) {
                        cout << "Error: " << mysql_error(conn);
                    } else {
                        cout << "You have selected following car: " << endl;
                        cout << car2.getBrand() << " " << car2.getModel() << "  $" << car2.getRent() << endl;
                    }
                } else {
                    cout << "Sorry this car is already booked" << endl;
                }
            }

            // Repeat for car3
            if (car3.getSerial() == ser) {
                if (isAvail(conn, toS)) {
                    string upd = "UPDATE cars SET Avail ='0' WHERE Serial ='" + toS + "'";
                    if (mysql_query(conn, upd.c_str())) {
                        cout << "Error: " << mysql_error(conn);
                    } else {
                        cout << "You have selected following car: " << endl;
                        cout << car3.getBrand() << " " << car3.getModel() << "  $" << car3.getRent() << endl;
                    }
                } else {
                    cout << "Sorry this car is already booked" << endl;
                }
            }
            Sleep(8000);  // Pause for 8 seconds
        }

        // Exit program
        else if (val == 0) {
            exit = true;
            cout << "BYE!!" << endl;
            Sleep(2000);
        }
    }

    mysql_close(conn);  // Close database connection
    return 0;           // End of program
}
