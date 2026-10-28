
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class Item {
private:
    int id;
    string name;
    string category;
    string location;
    string date;
    string status;

public:
    Item(int i, string n, string c, string l,
         string d, string s)
        : id(i), name(n), category(c),
          location(l), date(d), status(s) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getStatus() const { return status; }

    void updateStatus(string newStatus) {
        status = newStatus;
    }

    void display() const {
        cout << left << setw(6) << id
             << setw(20) << name
             << setw(16) << category
             << setw(18) << location
             << setw(14) << date
             << status << '\n';
    }

    string toFile() const {
        return to_string(id) + "|" + name + "|" +
               category + "|" + location + "|" +
               date + "|" + status;
    }
};

class LostAndFound {
private:
    vector<Item> items;
    int nextId = 1;
    const string fileName = "items.txt";

    void loadRecords() {
        ifstream file(fileName);
        string line;

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);
            size_t p4 = line.find('|', p3 + 1);
            size_t p5 = line.find('|', p4 + 1);

            if (p1 == string::npos ||
                p2 == string::npos ||
                p3 == string::npos ||
                p4 == string::npos ||
                p5 == string::npos)
                continue;

            try {
                int id = stoi(line.substr(0, p1));
                string name = line.substr(p1 + 1, p2 - p1 - 1);
                string category = line.substr(p2 + 1, p3 - p2 - 1);
                string location = line.substr(p3 + 1, p4 - p3 - 1);
                string date = line.substr(p4 + 1, p5 - p4 - 1);
                string status = line.substr(p5 + 1);

                if (id > 0 &&
                    (status == "Lost" || status == "Found" ||
                     status == "Returned")) {
                    items.emplace_back(id, name, category,
                                       location, date, status);
                    if (id >= nextId)
                        nextId = id + 1;
                }
            } catch (...) {
                // Ignore invalid records.
            }
        }
    }

    void saveRecords() const {
        ofstream file(fileName);

        if (!file) {
            cout << "Error saving records!\n";
            return;
        }

        for (const auto &item : items)
            file << item.toFile() << '\n';
    }

    string readField(const string &prompt) {
        string value;

        while (true) {
            cout << prompt;
            getline(cin, value);

            if (!value.empty() &&
                value.find('|') == string::npos)
                return value;

            cout << "Please enter a valid, non-empty value "
                    "without the | character.\n";
        }
    }

public:
    LostAndFound() {
        loadRecords();
    }

    void registerItem(const string &status) {
        string name = readField("Enter item name: ");
        string category = readField("Enter category: ");
        string location = readField("Enter campus location: ");
        string date = readField("Enter date (DD-MM-YYYY): ");

        items.emplace_back(nextId++, name, category,
                           location, date, status);

        saveRecords();
        cout << "Item registered successfully! ID: "
             << nextId - 1 << '\n';
    }

    void viewItems() const {
        if (items.empty()) {
            cout << "No item records available.\n";
            return;
        }

        cout << '\n' << left
             << setw(6) << "ID"
             << setw(20) << "Item"
             << setw(16) << "Category"
             << setw(18) << "Location"
             << setw(14) << "Date"
             << "Status\n";

        for (const auto &item : items)
            item.display();
    }

    void searchItem() const {
        string keyword = readField("Enter item name to search: ");
        bool found = false;

        for (const auto &item : items) {
            if (item.getName().find(keyword) != string::npos) {
                if (!found)
                    cout << "\nMatching records:\n";

                item.display();
                found = true;
            }
        }

        if (!found)
            cout << "No matching items found.\n";
    }

    void updateStatus() {
        int id;

        cout << "Enter item ID to update: ";
        if (!(cin >> id)) {
            cout << "Invalid ID.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (auto &item : items) {
            if (item.getId() == id) {
                cout << "1. Lost\n2. Found\n3. Returned\n";
                cout << "Choose new status: ";

                int choice;
                if (!(cin >> choice)) {
                    cout << "Invalid choice.\n";
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');
                    return;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice == 1)
                    item.updateStatus("Lost");
                else if (choice == 2)
                    item.updateStatus("Found");
                else if (choice == 3)
                    item.updateStatus("Returned");
                else {
                    cout << "Invalid status choice.\n";
                    return;
                }

                saveRecords();
                cout << "Status updated successfully.\n";
                return;
            }
        }

        cout << "Item ID not found.\n";
    }
};

int main() {
    LostAndFound system;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << " CAMPUS LOST-AND-FOUND MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Register Lost Item\n";
        cout << "2. Register Found Item\n";
        cout << "3. View All Items\n";
        cout << "4. Search Item\n";
        cout << "5. Update Item Status\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                system.registerItem("Lost");
                break;
            case 2:
                system.registerItem("Found");
                break;
            case 3:
                system.viewItems();
                break;
            case 4:
                system.searchItem();
                break;
            case 5:
                system.updateStatus();
                break;
            case 6:
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
