
#ifndef LIBR_H
#define LIBR_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::cout;
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
    vector <int> nd;
    int egz;
};

void read(const string &filename, vector<duomenys> &studentai){
    ifstream in(filename);          // atidarymas is failo
    if (!in) {          //tikrina ar faila galima atidaryti
        std::cerr << "Nepavyko atidaryti failo: " << filename << endl;          //cerr - klaidos isvedimas
        return;
    }

    string line;
    while (getline(in, line)) {         //ciklas veikia tol, kol nuskaito visa faila
        std::stringstream iss(line);          //iss - string stream, skirtas nuskaityti duomenims is failo
        duomenys student;
        iss >> student.vardas >> student.pavarde;
        int paz;
        while (iss >> paz) {
            if (paz>=0 and paz<=10) student.nd.push_back(paz);          //tikrina ar pazymys yra tarp 0 ir 10, o jeigu ne - praleidzia.
        }
        student.egz = student.nd.back();            //egzamino pazymi gauna is paskutinio n.d. pazymio
        student.nd.pop_back();                      //istrina egzamino pazymi is n.d. pazymiu vektoriaus
        studentai.push_back(student);               //ideda studento duomenis i bendra vektoriu
    }
    in.close();
}
//if(iss.fail()) {          //bandziau padaryti, kad ne skaicius butu praleistas, bet neveike :(((
//    iss.clear();
//    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
//}
//else and !iss.eof()

double galutinis_vid(vector<int> nd, int egz) {         // skaiciuoja galutini bala pagal vidurki
    double vid = 0;
    for (int i = 0; i < nd.size(); i++) {
        vid += nd[i];
    }
    vid /= nd.size();
    return 0.4 * vid + 0.6 * egz;
}

double galutinis_med(vector<int> nd, int egz) {         // skaiciuoja galutini bala pagal mediana
    std::sort(nd.begin(), nd.end());
    double med;
    if (nd.size() == 0) {
        med = 0;
    }else if (nd.size() % 2 == 0) {
        med = (nd[nd.size() / 2 - 1] + nd[nd.size() / 2]) / 2.0;
    } else {
        med = nd[nd.size() / 2];
    }
    return 0.4 * med + 0.6 * egz;
}

void write(const string &filename, vector<duomenys> &studentai) {           //isvedimo funkcija
    fstream out(filename);
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left << "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < studentai.size(); i++) {
        cout <<setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(20) << left << fixed << setprecision(2) << galutinis_vid(studentai[i].nd,studentai[i].egz) << setw(20) << left << fixed << setprecision(2) << galutinis_med(studentai[i].nd,studentai[i].egz) <<endl;
    }
    out.close();
}
#endif //LIBR_H
