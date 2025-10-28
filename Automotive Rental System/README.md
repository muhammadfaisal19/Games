
````markdown
# 🚗 Car Rental Management System (C++ + MySQL)

A console-based **Car Rental System** developed in **C++** with a **MySQL database backend**.  
It demonstrates **Object-Oriented Programming (OOP)** principles and **real-time database connectivity** using the **MySQL C API**.

---

## 🧠 Overview

This project allows users to:
- Connect to a MySQL database.
- View all available cars.
- Select and book a car.
- Automatically update car availability in the database.

The system simulates a simple, interactive car rental process with persistent data storage.

---

## ⚙️ Tech Stack

| Component | Technology |
|------------|-------------|
| **Language** | C++ |
| **Database** | MySQL |
| **Libraries** | `<mysql.h>`, `<windows.h>`, `<sstream>`, `<iostream>` |
| **IDE/Compiler** | Code::Blocks / Dev C++ / Visual Studio (MinGW supported) |

---

## 🧩 Database Schema

Before running the program, create the following database and table:

```sql
CREATE DATABASE mydb;

USE mydb;

CREATE TABLE cars (
    Serial INT PRIMARY KEY,
    Brand VARCHAR(50),
    Model VARCHAR(50),
    Rent INT,
    Avail BOOLEAN
);
````

---

## 🧱 Features

✅ Connects to a MySQL database.
✅ Displays all cars stored in the `cars` table.
✅ Allows the user to select a car by serial number.
✅ Checks and updates car availability.
✅ Uses OOP design via a `Car` class.
✅ Handles SQL errors gracefully.

---

## 🧩 Class Structure

### **Car Class**

```cpp
class Car {
private:
    string Brand, Model;
    int Serial, Rent;
    bool Avail;

public:
    Car(int serial, string brand, string model, int rent, bool avail);
    int getSerial();
    string getBrand();
    string getModel();
    int getRent();
    bool getAvail();
};
```

* **Encapsulates** car data and provides getter methods.
* Used to represent and manipulate car objects in the program.

---

## 🧾 Program Flow

1. Connects to MySQL database.
2. Inserts default car data (3 cars).
3. Displays all cars from database.
4. Allows user to:

   * Select a car to rent.
   * Check its availability.
   * Update the database to mark it as booked.
5. Allows exit and closes connection.

---

## 🧮 Flowchart

<img width="500" height="1000" alt="flowchart" src="https://github.com/user-attachments/assets/965f3bdc-86da-4187-b071-796f07d3746b" />

---

## 💻 Example Input/Output

### Example 1 — Booking a Car

**Input:**

```
1
Enter Serial:
123
```

**Output:**

```
You have selected following car:
Honda Civic  $60
```

**Database Update:**

| Serial | Brand  | Model | Rent | Avail |
| ------ | ------ | ----- | ---- | ----- |
| 123    | Honda  | Civic | 60   | 0     |
| 223    | Toyota | Yaris | 50   | 1     |
| 323    | Suzuki | Alto  | 30   | 1     |

---

### Example 2 — Trying to Book an Already Rented Car

**Input:**

```
1
Enter Serial:
123
```

**Output:**

```
Sorry this car is already booked
```

---

### Example 3 — Exit Program

**Input:**

```
0
```

**Output:**

```
BYE!!
```

---

## 🧠 Internal Functions

| Function                           | Purpose                                           |
| ---------------------------------- | ------------------------------------------------- |
| `isAvail(MYSQL* conn, string toS)` | Checks if a car is available in the database.     |
| `mysql_query()`                    | Executes SQL statements (INSERT, SELECT, UPDATE). |
| `mysql_store_result()`             | Retrieves the query result set.                   |
| `mysql_fetch_row()`                | Iterates through query result rows.               |

---

## 🧠 Senior-Level Discussion Points

* Demonstrates **C++ and MySQL integration** using native APIs.
* Uses **OOP encapsulation** for data representation.
* Includes **real-time updates** in MySQL (`UPDATE` statements).
* Incorporates **dynamic query building** using `stringstream`.
* Employs **error handling** via `mysql_error(conn)`.

---

## 🚀 Future Enhancements

* Add **user authentication** (Admin/User roles).
* Implement **return car feature** (set `Avail = 1` again).
* Add **rental history** and **customer info** tables.
* Create **GUI using Qt or C++ WinForms**.
* Prevent duplicate car insertions on each run.

---

## 📦 Setup Instructions

1. Install **MySQL Server** and **MySQL Connector/C**.
2. Create the database and table as shown above.
3. Update these variables in the source code:

   ```cpp
   const char* USER = "root";
   const char* PW = "your_password";
   const char* DB = "mydb";
   ```
4. Compile and run the program.

---

## 🧾 Output Snapshot

```
Logged in!!
Data saved for cars
Welcome to Car Rental System
****************************
123  Honda  Civic  60  1
223  Toyota Yaris  50  1
323  Suzuki Alto   30  1

1. Select Car.
0. Exit.
```

---

