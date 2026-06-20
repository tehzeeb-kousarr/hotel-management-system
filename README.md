# 🏨 Hotel Management System

A comprehensive console-based **Hotel Management System** developed in **C++** that enables hotel staff to efficiently manage room inventory, guest reservations, check-ins, check-outs, billing, and customer records through a secure role-based interface.

The project demonstrates the practical implementation of **Object-Oriented Programming (OOP)** concepts, exception handling, input validation, and hotel management workflows in a real-world scenario.

<br>

## ✨ Features

### 🔐 Role-Based Authentication

The system provides separate login portals for:

* Manager
* Administrator

Each role has access to specific operations and management features.

### 🛏️ Room Management

Managers can:

* Add new rooms
* Configure room details
* Set room categories
* Define room rental charges
* View room information

Room attributes include:

* AC / Non-AC
* Suite / Normal
* Big / Small Room
* Daily Rent
* Availability Status

### 👥 Guest Management

Administrators can:

* Register new guests
* Store customer details
* Search guests using Booking ID
* View complete guest records
* Manage room occupancy

### ✅ Check-In System

The system supports:

* Room selection
* Availability verification
* Customer registration
* Stay duration tracking
* Booking confirmation
* Automatic bill calculation

### 🚪 Check-Out System

During check-out:

* Guest details are displayed
* Total bill is calculated
* Advance payment is deducted
* Remaining balance is shown
* Room becomes available again

### 💰 Billing Management

The system automatically calculates:

* Total room charges
* Advance payment
* Remaining payable amount

Formula:

```text
Total Bill = Number of Days × Daily Room Rent
```

### 🔍 Room Search

Rooms can be searched using:

* AC / Non-AC
* Suite / Normal
* Big / Small

allowing administrators to quickly find available rooms matching customer requirements.

### 🛡️ Input Validation & Error Handling

The application includes:

* Invalid input detection
* Numeric validation
* Exception handling
* Safe menu navigation
* User-friendly error messages

<br>

## 🏗️ Object-Oriented Concepts Used

This project demonstrates:

* Classes & Objects
* Encapsulation
* Inheritance
* Polymorphism
* Exception Handling
* Modular Programming

Main classes:

* Login
* ManagerLogin
* AdminLogin
* Customer
* Room
* Hotel

<br>

## 🛠️ Technologies Used

| Technology         | Purpose           |
| ------------------ | ----------------- |
| C++                | Core Development  |
| OOP                | Software Design   |
| STL                | Utility Functions |
| Exception Handling | Error Management  |
| Console Interface  | User Interaction  |

<br>

## 🚀 Installation

### Clone the Repository

```bash
git clone https://github.com/tehzeeb-kousarr/hotel-management-system.git
```

### Navigate to Project Folder

```bash
cd hotel-management-system
```

### Compile the Program

```bash
g++ "Hotel Reservation System.cpp" -o HotelManagementSystem.exe
```

### Run the Program

```bash
HotelManagementSystem.exe
```

<br>

## 📂 Project Structure

```text
hotel-management-system/
│
├── Hotel Management System.cpp
├── Hotel Management System.exe
└── README.md
```

<br>

## 📋 System Workflow

### Manager

1. Login
2. Add Rooms
3. View Guest Summary
4. Logout

### Administrator

1. Login
2. View Room Availability
3. Search Rooms
4. Check-In Guests
5. Search Customer Records
6. View Guest Summary
7. Check-Out Guests
8. Logout

<br>

<table>
<tr>
<td align="center">
<b>Admin</b><br>
<img src="https://github.com/user-attachments/assets/c664760e-e179-4ab4-af7d-1abb6963c6a0" width="100%">
</td>
<td align="center">
<b>Manager</b><br>
<img src="https://github.com/user-attachments/assets/38449b58-dd34-4610-bc6b-e55b2664b7ab" width="100%">
</td>
</tr>
</table>

<br>

## 🎯 Learning Outcomes

Through this project, the following skills were strengthened:

* C++ Programming
* Object-Oriented Design
* Problem Solving
* Input Validation
* Exception Handling
* Menu-Driven Application Development

<br>

## 🔮 Future Enhancements

Potential improvements include:

* Database Integration (MySQL)
* File-Based Data Persistence
* Graphical User Interface (GUI)
* Online Reservation System
* Customer Feedback Module
* Employee Management System
* Payment Gateway Integration
* Hotel Analytics Dashboard

<br>

## ⭐ Support

If you found this project useful, please consider giving it a ⭐ on GitHub.

Your support is greatly appreciated.
