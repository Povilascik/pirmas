#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::string;
using std::vector;
using std::fstream;
using std::ifstream;

struct duomenys {           // apsirasoma struktura duomenims saugoti.
    string vardas, pavarde;
    int nd[100];
    int nd_sk;
    int egz;
};

void inputStudentData(vector<duomenys> &studentai) {
    while (true) {
        duomenys student;
        cout << "Įveskite mokinio vardą (įveskite 'p' norint užbaigti): ";
        cin >> student.vardas;
        if (student.vardas == "p") break;
        cout << "Įveskite mokinio pavardę: ";
        cin >> student.pavarde;
        student.nd_sk = 0;
        cout << "Įveskite pažymius už namų darbus (įveskite -1 norint užbaigti): ";
        while (true) {
            int grade;
            cin >> grade;
            if (grade == -1) break;
            if (grade >= 0 && grade <= 10) {
                student.nd[student.nd_sk++] = grade;
            }
        }
        cout << "Įveskite egazmino pažymį: ";
        cin >> student.egz;
        studentai.push_back(student);
    }
}
