#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Constituency {
    string name;
    int population;
public:
    Constituency(string name, int population) : name(name), population(population) {}
    string getDetails() const {
        return "Constituency: " + name + ", Population: " + to_string(population);
    }
};

class Bill {
    string title;
    string description;
    string status;
public:
    Bill(string title, string description) : title(title), description(description), status("proposed") {}
    string getTitle() const {
        return title;
    }
    string getDetails() const {
        return "Title: " + title + ", Description: " + description + ", Status: " + status;
    }
};

class Session {
    string date;
    string agenda;
public:
    Session(string date, string agenda) : date(date), agenda(agenda) {}
    string getAgenda() const {
        return agenda;
    }
    string getDate() const {
        return date;
    }
};

class Member {
    string name;
    Constituency constituency;
    string party;
    string contactInfo;
public:
    Member(string name, Constituency constituency, string party, string contactInfo) 
        : name(name), constituency(constituency), party(party), contactInfo(contactInfo) {}

    string getName() const {
        return name;
    }

    Constituency getConstituency() const {
        return constituency;
    }

    string getParty() const {
        return party;
    }

    string getContactInfo() const {
        return contactInfo;
    }

    void proposeBill(const Bill& bill) const {
        cout << name << " has proposed the bill: " + bill.getTitle() << endl;
    }

    void voteOnBill(const Bill& bill, const string& vote) const {
        cout << name << " has voted " << vote << " on the bill: " + bill.getTitle() << endl;
    }
};

class LegislativeAssembly {
    string name;
    string location;
    vector<Member> members;
    vector<Session> sessions;
public:
    LegislativeAssembly(string name, string location) : name(name), location(location) {}

    void addMember(const Member& member) {
        members.push_back(member);
    }

    void scheduleSession(const Session& session) {
        sessions.push_back(session);
    }

    vector<Member> getMembers() const {
        return members;
    }
};

LegislativeAssembly assembly("Goa Legislative Assembly", "Panaji");

void addMember() {
    string name, constituencyName, party, contactInfo;
    int population;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Constituency Name: ";
    getline(cin, constituencyName);
    cout << "Enter Population: ";
    cin >> population;
    cin.ignore();
    Constituency constituency(constituencyName, population);
    cout << "Enter Party: ";
    getline(cin, party);
    cout << "Enter Contact Info: ";
    getline(cin, contactInfo);
    Member member(name, constituency, party, contactInfo);
    assembly.addMember(member);
    cout << "Member added successfully." << endl;
}

void scheduleSession() {
    string date, agenda;
    cout << "Enter Session Date: ";
    cin.ignore();
    getline(cin, date);
    cout << "Enter Agenda: ";
    getline(cin, agenda);
    Session session(date, agenda);
    assembly.scheduleSession(session);
    cout << "Session scheduled successfully." << endl;
}

Member* findMemberByName(const string& name) {
    auto members = assembly.getMembers();
    for (auto& member : members) {
        if (member.getName() == name) {
            return &member;
        }
    }
    return nullptr;
}

void proposeBill() {
    string name, title, description;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, name);
    Member* member = findMemberByName(name);
    if (member != nullptr) {
        cout << "Enter Bill Title: ";
        getline(cin, title);
        cout << "Enter Bill Description: ";
        getline(cin, description);
        Bill bill(title, description);
        member->proposeBill(bill);
        cout << "Bill proposed successfully." << endl;
    } else {
        cout << "Member not found." << endl;
    }
}

void voteOnBill() {
    string name, title, vote;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, name);
    Member* member = findMemberByName(name);
    if (member != nullptr) {
        cout << "Enter Bill Title: ";
        getline(cin, title);
        cout << "Enter Vote (yes/no): ";
        getline(cin, vote);
        Bill bill(title, "");
        member->voteOnBill(bill, vote);
        cout << "Vote recorded successfully." << endl;
    } else {
        cout << "Member not found." << endl;
    }
}

void displayMembers() {
    auto members = assembly.getMembers();
    if (members.empty()) {
        cout << "No members found." << endl;
    } else {
        cout << "Members of the Goa Legislative Assembly:" << endl;
        for (const auto& member : members) {
            cout << "Name: " << member.getName() << ", " << member.getConstituency().getDetails()
                << ", Party: " << member.getParty() << ", Contact Info: " << member.getContactInfo() << endl;
        }
    }
}

int main() {
    int choice;
    do {
        cout << "\nGoa Legislative Assembly Management System" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Schedule Session" << endl;
        cout << "3. Propose Bill" << endl;
        cout << "4. Vote on Bill" << endl;
        cout << "5. Display Members" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                scheduleSession();
                break;
            case 3:
                proposeBill();
                break;
            case 4:
                voteOnBill();
                break;
            case 5:
                displayMembers();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
