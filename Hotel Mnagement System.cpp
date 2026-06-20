// Hotel Booking Management System
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

// ─────────────────────────────────────────────
//  Sentinel: thrown whenever the user types 0
//  to go back from any sub-function.
// ─────────────────────────────────────────────
struct UserAborted {};

// ─────────────────────────────────────────────
//  Utility helpers
// ─────────────────────────────────────────────

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string &prompt, bool canAbort = false)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            if (value == 0 && canAbort)
                throw UserAborted{};
            if (value >= 0)
                return value;
            cout << "  Please enter a non-negative number.\n";
        }
        else
        {
            clearInput();
            cout << "  Please enter a valid integer.\n";
        }
    }
}

/** Like readInt but requires value > 0 (0 still triggers abort). */
int readPositiveInt(const string &prompt, bool canAbort = false)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            if (value == 0 && canAbort)
                throw UserAborted{};
            if (value > 0)
                return value;
            cout << "  Please enter a positive integer.\n";
        }
        else
        {
            clearInput();
            cout << "  Please enter a valid integer.\n";
        }
    }
}

/**
 * Read a single character that must be in 'allowed'.
 * If canAbort is true, typing '0' throws UserAborted.
 */
char readChar(const string &prompt, const string &allowed, bool canAbort = false)
{
    char ch;
    while (true)
    {
        cout << prompt;
        if (cin >> ch)
        {
            if (ch == '0' && canAbort)
                throw UserAborted{};
            for (char a : allowed)
                if (ch == a)
                    return ch;
            if (canAbort)
                cout << "  Invalid. Allowed: [" << allowed << "] or 0 to go back.\n";
            else
                cout << "  Invalid. Allowed: [" << allowed << "]\n";
        }
        else
        {
            clearInput();
            cout << "  Please enter a single character.\n";
        }
    }
}

double readDouble(const string &prompt, double minVal, double maxVal, bool canAbort = false)
{
    double value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            if (value == 0.0 && canAbort)
                throw UserAborted{};
            if (value >= minVal && value <= maxVal)
                return value;
            if (canAbort)
                cout << "  Please enter a number between " << minVal
                     << " and " << maxVal << " (or 0 to go back).\n";
            else
                cout << "  Please enter a number between " << minVal
                     << " and " << maxVal << ".\n";
        }
        else
        {
            clearInput();
            cout << "  Please enter a valid number.\n";
        }
    }
}

// ─────────────────────────────────────────────
//  Login hierarchy
// ─────────────────────────────────────────────

class Login
{
protected:
    string username;
    int    password = 0;

public:
    virtual ~Login() = default;
    virtual bool login() = 0;
};

class ManagerLogin : public Login
{
public:
    bool login() override
    {
        cout << "Enter your Username : ";
        cin >> username;
        cout << "Enter Password     : ";

        if (!(cin >> password))
        {
            clearInput();
            cout << "  Invalid password format.\n";
            return false;
        }

        if (username == "manager" && password == 12345)
        {
            cout << "\nLogin Successful!\n\n";
            return true;
        }
        cout << "Wrong Username or Password!\n\n";
        return false;
    }
};

class AdminLogin : public Login
{
public:
    bool login() override
    {
        cout << "Enter your Username : ";
        cin >> username;
        cout << "Enter Password     : ";

        if (!(cin >> password))
        {
            clearInput();
            cout << "  Invalid password format.\n";
            return false;
        }

        if (username == "admin" && password == 123)
        {
            cout << "\nLogin Successful!\n\n";
            return true;
        }
        cout << "Wrong Username or Password!\n\n";
        return false;
    }
};

// ─────────────────────────────────────────────
//  Customer
// ─────────────────────────────────────────────

class Customer
{
private:
    string name;
    string address;
    string phone;
    int    days            = 0;
    float  payment_advance = 0.0f;
    double bill            = 0.0;
    int    booking_id      = 0;
    int    room            = 0;
    int    status          = 0; // 1 = checked-in, 0 = checked-out / empty

public:
    Customer() = default;

    // Throws UserAborted if user types "0" at the name prompt.
    // Throws runtime_error for empty fields.
    void accept()
    {
        cout << "\n  (Enter 0 at any prompt to go back)\n";

        cout << "  Customer name    : ";
        cin >> ws;
        getline(cin, name);
        if (name == "0")   throw UserAborted{};
        if (name.empty())  throw runtime_error("Customer name cannot be empty.");

        cout << "  Customer address : ";
        getline(cin, address);
        if (address == "0")   throw UserAborted{};
        if (address.empty())  throw runtime_error("Customer address cannot be empty.");

        cout << "  Mobile number    : ";
        cin >> phone;
        if (phone == "0")  throw UserAborted{};
        if (phone.empty()) throw runtime_error("Mobile number cannot be empty.");
    }

    void display() const
    {
        cout << "\n"
             << "  Booking ID : " << booking_id  << "\n"
             << "  Name       : " << name         << "\n"
             << "  Phone      : " << phone        << "\n"
             << "  Address    : " << address      << "\n"
             << "  Room No.   : " << room         << "\n"
             << "  Status     : " << (status == 1 ? "Checked In" : "Checked Out") << "\n";
    }

    int    getBookingId()      const { return booking_id;      }
    int    getRoom()           const { return room;            }
    int    getStatus()         const { return status;          }
    double getBill()           const { return bill;            }
    float  getAdvancePayment() const { return payment_advance; }
    int    getDays()           const { return days;            }

    void setBookingId(int id)    { booking_id      = id;  }
    void setRoom(int r)          { room            = r;   }
    void setStatus(int s)        { status          = s;   }
    void setBill(double b)       { bill            = b;   }
    void setAdvancePayment(float p) { payment_advance = p; }
    void setDays(int d)          { days            = d;   }
};

// ─────────────────────────────────────────────
//  Room
// ─────────────────────────────────────────────

class Room
{
private:
    char   acType     = '\0';
    char   type       = '\0';
    char   stype      = '\0';
    int    roomNumber = 0;
    double rent       = 0.0;
    int    status     = 0;

public:
    Room() = default;

    // Throws UserAborted if user enters 0 at any step.
    void acceptroom(int rno)
    {
        roomNumber = rno;
        acType = readChar("  AC / Non-AC          (A/N) : ", "AN", true);
        type   = readChar("  Suite / Normal       (S/N) : ", "SN", true);
        stype  = readChar("  Big  / Small         (B/S) : ", "BS", true);
        rent   = readDouble("  Daily rent               : ", 1.0, 80000.0, true);
        status = 0;
        cout << "\n  Room " << roomNumber << " added successfully!\n";
    }

    void displayroom() const
    {
        cout << "\n  +-----------+----------+-------+------+---------+-----------+\n"
             << "  | Room No.  | AC/NonAC | Type  | Size | Rent    | Status    |\n"
             << "  +-----------+----------+-------+------+---------+-----------+\n"
             << "  | " << roomNumber
             << "         | " << acType
             << "        | " << type
             << "     | " << stype
             << "    | " << rent
             << "   | " << (status == 0 ? "Available" : "Booked   ") << " |\n"
             << "  +-----------+----------+-------+------+---------+-----------+\n";
    }

    int    getRoomNumber() const { return roomNumber; }
    char   getAcType()     const { return acType;     }
    char   getType()       const { return type;       }
    char   getStype()      const { return stype;      }
    double getRent()       const { return rent;       }
    int    getStatus()     const { return status;     }
    void   setStatus(int s)      { status = s;        }
};

// ─────────────────────────────────────────────
//  Hotel
// ─────────────────────────────────────────────

class Hotel
{
private:
    static const int MAX_ROOMS = 100;
    static const int MAX_CUSTS = 100;

    Room     rooms[MAX_ROOMS];
    Customer customers[MAX_CUSTS];
    int      nroom = 0;
    int      ncust = 0;

    int findRoomIndex(int rno) const
    {
        for (int i = 0; i < nroom; i++)
            if (rooms[i].getRoomNumber() == rno)
                return i;
        return -1;
    }

    int findCustomerByRoom(int rno) const
    {
        for (int i = 0; i < ncust; i++)
            if (customers[i].getRoom() == rno && customers[i].getStatus() == 1)
                return i;
        return -1;
    }

public:
    // ── Manager operations ──────────────────────

    void addRooms()
    {
        if (nroom >= MAX_ROOMS)
            throw runtime_error("Maximum room capacity reached.");

        cout << "\n  (Enter 0 at any prompt to go back to the menu)\n";

        int count = readPositiveInt("  How many rooms to add? (0=back) : ", true);

        if (nroom + count > MAX_ROOMS)
        {
            cout << "  Warning: only " << (MAX_ROOMS - nroom)
                 << " slot(s) available. Adjusting.\n";
            count = MAX_ROOMS - nroom;
        }

        int added = 0;
        for (int i = 0; i < count; i++)
        {
            cout << "\n--- Room " << (i + 1) << " of " << count << " ---\n";

            int rno;
            while (true)
            {
                rno = readPositiveInt("  Enter room number (0=back) : ", true);
                if (findRoomIndex(rno) != -1)
                    cout << "  Room " << rno << " already exists. Choose another.\n";
                else
                    break;
            }

            try
            {
                rooms[nroom].acceptroom(rno);
                nroom++;
                added++;
            }
            catch (const UserAborted &)
            {
                cout << "  Room entry cancelled. Returning to menu.\n";
                break;
            }
        }

        if (added > 0)
            cout << "\n  " << added << " room(s) added. Database updated.\n";
    }

    void Summary() const
    {
        if (ncust == 0)
        {
            cout << "  No guest records yet.\n";
            return;
        }
        cout << "\n================ Guest Summary ================\n";
        for (int i = 0; i < ncust; i++)
            customers[i].display();
        cout << "===============================================\n";
    }

    // ── Admin operations ────────────────────────

    void availability() const
    {
        if (nroom == 0)
        {
            cout << "  No rooms in the system yet.\n";
            return;
        }
        cout << "\n===== All Rooms =====\n";
        for (int i = 0; i < nroom; i++)
            rooms[i].displayroom();
    }

    void searchroom() const
    {
        if (nroom == 0)
        {
            cout << "  No rooms in the system yet.\n";
            return;
        }

        cout << "\n  (Enter 0 at any prompt to go back)\n";

        char ac1, type1, sty1;
        try
        {
            ac1   = readChar("  AC / Non-AC?      (A/N) : ", "AN",  true);
            type1 = readChar("  Suite / Normal?   (S/N) : ", "SN",  true);
            sty1  = readChar("  Big  / Small?     (B/S) : ", "BS",  true);
        }
        catch (const UserAborted &)
        {
            cout << "  Search cancelled.\n";
            return;
        }

        bool found = false;
        for (int i = 0; i < nroom; i++)
        {
            if (rooms[i].getAcType() == ac1 &&
                rooms[i].getType()   == type1 &&
                rooms[i].getStype()  == sty1)
            {
                rooms[i].displayroom();
                found = true;
            }
        }
        if (!found)
            cout << "  No matching room found.\n";
    }

    void CheckIn()
    {
        if (nroom == 0)
        {
            cout << "  No rooms available. Please contact the Manager.\n";
            return;
        }
        if (ncust >= MAX_CUSTS)
            throw runtime_error("Customer registry is full.");

        int available = 0;
        for (int i = 0; i < nroom; i++)
            if (rooms[i].getStatus() == 0)
                available++;

        if (available == 0)
        {
            cout << "  Sorry! All rooms are currently occupied.\n";
            return;
        }

        cout << "\n  (Enter 0 at any prompt to go back)\n";

        // Pick a room
        int ridx = -1;
        try
        {
            while (true)
            {
                int rno = readPositiveInt("  Room number to book (0=back) : ", true);
                ridx = findRoomIndex(rno);

                if (ridx == -1)
                {
                    cout << "  Room " << rno << " does not exist.\n";
                    continue;
                }
                if (rooms[ridx].getStatus() != 0)
                {
                    cout << "  Room " << rno << " is already booked. Choose another.\n";
                    ridx = -1;
                    continue;
                }
                break;
            }

            rooms[ridx].displayroom();
            char confirm = readChar("  Confirm this room? (Y/N | 0=back) : ", "YNyn", true);
            if (confirm != 'Y' && confirm != 'y')
            {
                cout << "  Booking cancelled.\n";
                return;
            }

            customers[ncust].setBookingId(ncust + 1);
            customers[ncust].accept();  // may throw UserAborted or runtime_error

            int days = readPositiveInt("  Number of days of stay (0=back) : ", true);
            customers[ncust].setDays(days);

            double bill   = days * rooms[ridx].getRent();
            double minAdv = bill / 4.0;
            customers[ncust].setBill(bill);

            cout << "  Approximate total bill : Rs." << bill   << "\n"
                 << "  Minimum advance        : Rs." << minAdv << "\n";

            float adv = static_cast<float>(
                readDouble("  Advance payment : Rs.", minAdv, bill, true));
            customers[ncust].setAdvancePayment(adv);
        }
        catch (const UserAborted &)
        {
            cout << "  Check-in cancelled. Returning to menu.\n";
            return;
        }
        catch (const runtime_error &e)
        {
            cout << "  Error: " << e.what() << "\n  Check-in aborted.\n";
            return;
        }

        rooms[ridx].setStatus(1);
        customers[ncust].setRoom(rooms[ridx].getRoomNumber());
        customers[ncust].setStatus(1);

        cout << "\n  ===== Booking Confirmed =====\n";
        customers[ncust].display();
        cout << "  =============================\n";

        ncust++;
    }

    void searchcust() const
    {
        if (ncust == 0)
        {
            cout << "  No customer records yet.\n";
            return;
        }

        cout << "\n  (Enter 0 to go back)\n";

        int id;
        try { id = readPositiveInt("  Booking ID : ", true); }
        catch (const UserAborted &) { cout << "  Cancelled.\n"; return; }

        bool found = false;
        for (int i = 0; i < ncust; i++)
        {
            if (customers[i].getBookingId() == id)
            {
                customers[i].display();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "  No customer found with Booking ID " << id << ".\n";
    }

    void CheckOut()
    {
        if (nroom == 0 || ncust == 0)
        {
            cout << "  No active bookings.\n";
            return;
        }

        cout << "\n  (Enter 0 to go back)\n";

        int rno;
        try { rno = readPositiveInt("  Room number to check out : ", true); }
        catch (const UserAborted &) { cout << "  Cancelled.\n"; return; }

        int ridx = findRoomIndex(rno);
        if (ridx == -1)
        {
            cout << "  Room " << rno << " does not exist.\n";
            return;
        }
        if (rooms[ridx].getStatus() == 0)
        {
            cout << "  Room " << rno << " is not currently occupied.\n";
            return;
        }

        int cidx = findCustomerByRoom(rno);
        if (cidx == -1)
        {
            cout << "  No active booking found for room " << rno << ".\n";
            return;
        }

        cout << "\n===== Check-Out =====\n";
        customers[cidx].display();
        cout << "  Total bill      : Rs." << customers[cidx].getBill()           << "\n"
             << "  Advance paid    : Rs." << customers[cidx].getAdvancePayment() << "\n"
             << "  Pending payment : Rs."
             << (customers[cidx].getBill() - customers[cidx].getAdvancePayment()) << "\n"
             << "\n  Thank you for staying with us! Visit again :)\n"
             << "=====================\n";

        rooms[ridx].setStatus(0);
        customers[cidx].setStatus(0);
    }
};

// ─────────────────────────────────────────────
//  Menus
// ─────────────────────────────────────────────

void printWelcome()
{
    cout << "\n"
         << "  +-------------------------------------------------------+\n"
         << "  |                                                       |\n"
         << "  |                       WELCOME                         |\n"
         << "  |          Hotel Booking Management System              |\n"
         << "  |                                                       |\n"
         << "  +-------------------------------------------------------+\n\n";
}

void managerMenu(Hotel &h)
{
    while (true)
    {
        cout << "\n---------- MANAGER MENU ----------\n"
             << "  1. Add rooms\n"
             << "  2. View all guest records\n"
             << "  3. Logout\n"
             << "----------------------------------\n";

        int choice = readPositiveInt("Your choice : ");
        switch (choice)
        {
        case 1:
            try { h.addRooms(); }
            catch (const runtime_error &e)
            { cout << "  Error: " << e.what() << "\n"; }
            break;

        case 2:
            h.Summary();
            break;

        case 3:
            cout << "  Logged out from Manager.\n";
            return;

        default:
            cout << "  Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
}

void adminMenu(Hotel &h)
{
    while (true)
    {
        cout << "\n---------- ADMIN MENU ----------\n"
             << "  1. Check room availability\n"
             << "  2. Search room by type\n"
             << "  3. Check In\n"
             << "  4. Search customer\n"
             << "  5. Guest summary\n"
             << "  6. Check Out\n"
             << "  7. Logout\n"
             << "  8. Exit program\n"
             << "--------------------------------\n";

        int choice = readPositiveInt("Your choice : ");
        switch (choice)
        {
        case 1: h.availability(); break;
        case 2: h.searchroom();   break;
        case 3:
            try { h.CheckIn(); }
            catch (const runtime_error &e)
            { cout << "  Error: " << e.what() << "\n"; }
            break;
        case 4: h.searchcust();   break;
        case 5: h.Summary();      break;
        case 6: h.CheckOut();     break;
        case 7:
            cout << "  Logged out from Admin.\n";
            return;
        case 8:
            cout << "  Exiting. Thank you!\n";
            exit(0);
        default:
            cout << "  Invalid choice. Please enter 1–8.\n";
        }
    }
}

// ─────────────────────────────────────────────
//  main
// ─────────────────────────────────────────────

int main()
{
    Hotel        h;
    ManagerLogin managerLogin;
    AdminLogin   adminLogin;

    printWelcome();

    while (true)
    {
        cout << "\n========= MAIN MENU =========\n"
             << "  1. Operate as Manager\n"
             << "  2. Operate as Admin\n"
             << "  3. Exit\n"
             << "=============================\n";

        int choice = readPositiveInt("Enter choice : ");

        switch (choice)
        {
        case 1:
            if (managerLogin.login())
                managerMenu(h);
            else
                cout << "  Access denied.\n";
            break;

        case 2:
            if (adminLogin.login())
                adminMenu(h);
            else
                cout << "  Access denied.\n";
            break;

        case 3:
            cout << "  Thank you! Goodbye.\n";
            return 0;

        default:
            cout << "  Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
}