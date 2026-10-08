#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Room {
private:
    int roomNo;
    string type;
    double price;
    bool isBooked;
public:
    Room() {}
    Room(int r, string t, double p) {
        roomNo = r; type = t; price = p; isBooked = false;
    }
    int getRoomNo() { return roomNo; }
    bool getStatus() { return isBooked; }
    void bookRoom() { isBooked = true; }
    void checkoutRoom() { isBooked = false; }
    void display() {
        cout << "Room No: " << roomNo << " | Type: " << type 
             << " | Price: " << price 
             << " | Status: " << (isBooked ? "Booked" : "Available") << endl;
    }
    string toFileString() {
        return to_string(roomNo) + " " + type + " " + to_string(price) + " " + to_string(isBooked);
    }
};

class Customer {
private:
    string name; int id; int bookedRoomNo;
public:
    Customer(string n, int i, int r) { name = n; id = i; bookedRoomNo = r; }
    void display() { cout << "Customer: " << name << " | ID: " << id << " | Room: " << bookedRoomNo << endl; }
};

class Hotel {
private:
    vector<Room> rooms;
    string fileName = "rooms.txt";
public:
    Hotel() {
        loadFromFile();
        if(rooms.empty()) {
            rooms.push_back(Room(101, "Single", 1000));
            rooms.push_back(Room(102, "Double", 1800));
            rooms.push_back(Room(103, "Deluxe", 3000));
            rooms.push_back(Room(104, "Suite", 5000));
            saveToFile();
        }
    }
    void saveToFile() {
        ofstream fout(fileName);
        for(auto &r : rooms) fout << r.toFileString() << endl;
        fout.close();
    }
    void loadFromFile() {
        ifstream fin(fileName);
        int no, booked; string type; double price;
        while(fin >> no >> type >> price >> booked) {
            Room r(no, type, price);
            if(booked) r.bookRoom();
            rooms.push_back(r);
        }
        fin.close();
    }
    void displayAllRooms() {
        cout << "\n--- ALL ROOMS ---" << endl;
        for(auto &r : rooms) r.display();
    }
    void bookRoom() {
        int rno; cout << "Enter Room No to book: "; cin >> rno;
        for(auto &r : rooms) {
            if(r.getRoomNo() == rno) {
                if(r.getStatus()) {
                    cout << "Error: Room already booked! Double booking not allowed." << endl; return;
                } else {
                    string name; int id;
                    cout << "Enter Customer Name: "; cin >> name;
                    cout << "Enter Customer ID: "; cin >> id;
                    r.bookRoom();
                    Customer c(name, id, rno);
                    saveToFile();
                    cout << "Booking Successful!" << endl; c.display(); return;
                }
            }
        }
        cout << "Room not found!" << endl;
    }
    void checkoutRoom() {
        int rno; cout << "Enter Room No to checkout: "; cin >> rno;
        for(auto &r : rooms) {
            if(r.getRoomNo() == rno) {
                if(!r.getStatus()) { cout << "Room is already available." << endl; return; }
                r.checkoutRoom(); saveToFile();
                cout << "Checkout Successful!" << endl; return;
            }
        }
        cout << "Room not found!" << endl;
    }
    void searchRoom() {
        int rno; cout << "Enter Room No to search: "; cin >> rno;
        for(auto &r : rooms) {
            if(r.getRoomNo() == rno) { r.display(); return; }
        }
        cout << "Room not found!" << endl;
    }
};

int main() {
    Hotel h; int choice;
    do {
        cout << "\n===== HOTEL RESERVATION SYSTEM =====" << endl;
        cout << "1. Display All Rooms\n2. Book Room\n3. Checkout Room\n4. Search Room\n5. Exit" << endl;
        cout << "Enter choice: "; cin >> choice;
        switch(choice) {
            case 1: h.displayAllRooms(); break;
            case 2: h.bookRoom(); break;
            case 3: h.checkoutRoom(); break;
            case 4: h.searchRoom(); break;
            case 5: cout << "Exiting... Data saved to rooms.txt" << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while(choice != 5);
    return 0;
}
