#include <iostream>
#include <vector>
#include <set>
#include <string.h>
#include <string>

using namespace std;

// фирма - набор объектов
vector<set<int>> firms;
// конфликт интересов - набор фирм
vector<set<int>> conflicts;
// история запросов для субъектов - список из последовательностей запросов каждого субъекта
// запрос - индекс объекта + тип запроса
vector<vector<pair<int, string>>> sHistory;
// история запросов для объектов - список из последовательностей запросов каждого объекта
// запрос - индекс субъекта + тип запроса
vector<vector<pair<int, string>>> oHistory;

bool contains(set<int>& s, int elt) {
    return (find(s.begin(), s.end(), elt) != s.end());
}

vector<string> split(string line) {
    vector<string> result = vector<string>();

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            result.push_back(line.substr(0, i));
            vector<string> tail = split(line.substr(i + 1, line.size() - i - 1));
            result.insert(result.end(), tail.begin(), tail.end());
            break;
        }
    }

    if (result.size() == 0) {
        result.insert(result.begin(), line);
    }

    return result;
}

int firmByObj(int o) {
    for (int i = 0; i < firms.size(); i++) {
        if (contains(firms[i], o)) {
            return i;
        }
    }
    return -1;
}

int conflByObj(int o) {
    int firm = firmByObj(o);

    for (int i = 0; i < conflicts.size(); i++) {
        if (contains(conflicts[i], firm)) {
            return i;
        }
    }

    return -1;
};

void printFirmObjects(int fi) {

    for (int const& i : firms[fi])
    {
        std::cout << i << ' ';
    }
   
 
    cout << endl;
}

void printReportForSubject(int si) {
   
    int size = sHistory[si].size();

    if (size != 0) {
        for (int i = 0; i < sHistory[si].size(); i++) {
            int s = sHistory[si][i].first;
            cout << "access " << sHistory[si][i].second << " obj - " << s << " firm - " << firmByObj(s) << endl;
        }
    }
    else {
        cout << "empty history";
    }
   
}

void printReportForObject(int oi) {
    

    int size = oHistory[oi].size();


    if (size != 0) {
        for (int i = 0; i < oHistory[oi].size(); i++) {
            int o = oHistory[oi][i].first;
            cout << "access " << oHistory[oi][i].second << " obj - " << o << " firm - " << firmByObj(o) << endl;
        }
    }
    else {
        cout << "empty history";
    }
}

bool canRead(int si, int oi) {
    int interestGroup = conflByObj(oi);
    int objectFirm = firmByObj(oi);

    set<int> accessGroups = set<int>();
    set<int> firmGroups = set<int>();

    for (int i = 0; i < sHistory[si].size(); i++) {
        accessGroups.insert(conflByObj(sHistory[si][i].first));
        firmGroups.insert(firmByObj(sHistory[si][i].first));
    }

    return !contains(accessGroups, interestGroup) || contains(firmGroups, objectFirm);
}

bool canWrite(int si, int oi) {
    int objectFirm = firmByObj(oi);
    int objectInterest = conflByObj(oi);
    bool isReadFromAnoutherFirm = false;

    set<int> readedFirms = set<int>();

    for (int i = 0; i < sHistory[si].size(); i++) {
        if (sHistory[si][i].second == "r" &&
            firmByObj(sHistory[si][i].first) != objectFirm &&
            conflByObj(sHistory[si][i].first) == objectInterest) {
            isReadFromAnoutherFirm = true;
            break;
        }
    }

    return canRead(si, oi) && !isReadFromAnoutherFirm;
}

void read(int si, int oi) {
    if (canRead(si, oi)) {
        sHistory[si].push_back(pair<int, string>(oi, "r"));
        oHistory[oi].push_back(pair<int, string>(si, "r"));
        cout << "accepted" << endl;
    }
    else {
        cout << "refused" << endl;
    }
}

void write(int si, int oi) {
    if (canWrite(si, oi)) {
        sHistory[si].push_back(pair<int, string>(oi, "w"));
        oHistory[oi].push_back(pair<int, string>(si, "w"));
        cout << "accepted" << endl;
    }
    else {
        cout << "refused" << endl;
    }
}

void start() {
    sHistory = vector<vector<pair<int, string>>>(sHistory.size());
    oHistory = vector<vector<pair<int, string>>>(oHistory.size());
    cout << "history cleared";
}



void executeCommand(string command) {
    vector<string> parts = split(command);

    command = parts[0];


    if (command == "start" || command == "s") {
        start();
    }
    else if (command == "read" || command == "r") {
        int si = stoi(parts[1]);
        int oi = stoi(parts[2]);
        read(si, oi);
    }
    else if (command == "write" || command == "w") {
        int si = stoi(parts[1]);
        int oi = stoi(parts[2]);
        write(si, oi);
    }
    else if (command == "report_subject" || command == "r_s") {
        int si = stoi(parts[1]);
        printReportForSubject(si);
    }
    else if (command == "report_object" || command == "r_o") {
        int oi = stoi(parts[1]);
        printReportForObject(oi);
    }
    else if (command == "brief_case" || command == "b_c") {
        int fi = stoi(parts[1]);
        printFirmObjects(fi);
    }
    else {
        cout << "Unknown command" << endl;
    }

    cout << endl;
}


void initialization(int oc, int sc, int fc, int ic) {
    firms = vector<set<int>>(fc, set<int>());
    conflicts = vector<set<int>>(ic, set<int>());

    sHistory = vector<vector<pair<int, string>>>(sc);
    oHistory = vector<vector<pair<int, string>>>(oc);
}



void create() {

    initialization(7, 1, 3, 2);

    firms[0].insert(0);
    firms[0].insert(2);
    firms[1].insert(1);
    firms[1].insert(3);
    firms[1].insert(4);
    firms[2].insert(5);
    firms[2].insert(6);
    firms[2].insert(7);

    conflicts[0].insert(0);
    conflicts[0].insert(1);
    conflicts[1].insert(2);
}

int main() {


  
    create();

    string command;
   

    while (true) {
        getline(cin, command);
        executeCommand(command);
    }

    return 0;
}