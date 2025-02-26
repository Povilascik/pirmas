#include "duomenys.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

void galutinis_vid(vector<int> nd, int egz, vector<duomenys> &studentai) {
    // skaiciuoja galutini bala pagal vidurki
    duomenys student;
    double vid = 0;
    for (int i = 0; i < nd.size(); i++) {
        vid += nd[i];
    }
    vid /= nd.size();
    student.vid = 0.4 * vid + 0.6 * egz;
    studentai.push_back(student);
}

double galutinis_vid(vector<int> nd, int egz) {
    // skaiciuoja galutini bala pagal vidurki
    double vid = 0;
    for (int i = 0; i < nd.size(); i++) {
        vid += nd[i];
    }
    vid /= nd.size();
    return 0.4 * vid + 0.6 * egz;
}

void galutinis_med(vector<int> nd, int egz, vector<duomenys> &studentai) {
    // skaiciuoja galutini bala pagal mediana
    duomenys student;
    std::sort(nd.begin(), nd.end());
    double med;
    if (nd.size() == 0) {
        med = 0;
    } else if (nd.size() % 2 == 0) {
        med = (nd[nd.size() / 2 - 1] + nd[nd.size() / 2]) / 2.0;
    } else {
        med = nd[nd.size() / 2];
    }
    student.med = 0.4 * med + 0.6 * egz;
    studentai.push_back(student);
}

double galutinis_med(vector<int> nd, int egz) {
    // skaiciuoja galutini bala pagal mediana
    std::sort(nd.begin(), nd.end());
    double med;
    if (nd.size() == 0) {
        med = 0;
    } else if (nd.size() % 2 == 0) {
        med = (nd[nd.size() / 2 - 1] + nd[nd.size() / 2]) / 2.0;
    } else {
        med = nd[nd.size() / 2];
    }
    return 0.4 * med + 0.6 * egz;
}

void read(const string &filename, vector<duomenys> &studentai) {
    ifstream in(filename); // atidarymas is failo
    string line;
    getline(in, line);
    while (getline(in, line)) {
        //ciklas veikia tol, kol nuskaito visa faila
        std::stringstream iss(line); //iss - string stream, skirtas nuskaityti duomenims is failo
        duomenys student;
        iss >> student.vardas >> student.pavarde;
        int paz;
        while (iss >> paz) {
            if (paz >= 0 and paz <= 10) student.nd.push_back(paz);
            //tikrina ar pazymys yra tarp 0 ir 10, o jeigu ne - praleidzia.
        }

        student.egz = student.nd.back(); //egzamino pazymi gauna is paskutinio n.d. pazymio
        student.nd.pop_back(); //istrina egzamino pazymi is n.d. pazymiu vektoriaus
        studentai.push_back(student); //ideda studento duomenis i bendra vektoriu
    }
    in.close(); //uzdaromas failas
    for (int i = 0; i < studentai.size(); i++) {
        studentai[i].vid = galutinis_vid(studentai[i].nd, studentai[i].egz);
        studentai[i].med = galutinis_med(studentai[i].nd, studentai[i].egz);
    }
}

void ss_write(const string &filename, vector<duomenys> &studentai) {
    ofstream out(filename);
    duomenys student;
    std::stringstream ss;
    ss << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    ss << "------------------------------------------------------------" << endl;
    for (int i = 0; i < studentai.size(); i++) {
        ss << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(20) << left <<
                fixed << setprecision(2) << studentai[i].vid << setw(20) << left << fixed << setprecision(2) <<
                studentai[i].med << endl;
    }
    out << ss.str();
    out.close();
}

void write(const string &filename, vector<duomenys> &studentai) {
    //isvedimo funkcija
    fstream out(filename);
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < studentai.size(); i++) {
        cout << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(20) << left
                << fixed << setprecision(2) << galutinis_vid(studentai[i].nd, studentai[i].egz) << setw(20) << left <<
                fixed << setprecision(2) << galutinis_med(studentai[i].nd, studentai[i].egz) << endl;
    }
    out.close();
}

void generuoti_paz(duomenys &student) {
    int paz_sk = rand() % 10 + 1; // sugeneruoja atsitiktini pazymiu skaiciu
    while (paz_sk < 2) paz_sk = rand() % 10 + 1;
    // tikrina ar pazymiu skaicius yra didesnis nei 2, nes buna negerai, jei <2
    for (int i = 0; i < paz_sk; i++) {
        int paz = rand() % 10 + 1; // generuoja atsisitkinius skaicius nuo 1 iki 10
        student.nd.push_back(paz);
    }
    student.egz = student.nd.back(); //egzamino pazymi gauna is paskutinio n.d. pazymio
    student.nd.pop_back(); //istrina egzamino pazymi is n.d. pazymiu vektoriaus
}

void generuoti_paz_ranka(vector<duomenys> &studentai) {
    duomenys student;
    while (true) {
        // ciklas veikia tol, kol neivedamas 'p'
        cout << "Iveskite studento varda (iveskite 'p' norint uzbaigti): ";
        cin >> student.vardas;
        if (student.vardas == "p") break;
        cout << "Iveskite studento pavarde: ";
        cin >> student.pavarde;
        int paz_sk = rand() % 10 + 1; // sugeneruoja atsitiktini pazymiu skaiciu
        while (paz_sk < 2) paz_sk = rand() % 10 + 1;
        // tikrina ar pazymiu skaicius yra didesnis nei 2, nes buna negerai, jei <2
        for (int i = 0; i < paz_sk; i++) {
            int paz = rand() % 10 + 1; // generuoja atsisitkinius skaicius nuo 1 iki 10
            student.nd.push_back(paz);
        }
        student.egz = student.nd.back(); //egzamino pazymi gauna is paskutinio n.d. pazymio
        student.nd.pop_back(); //istrina egzamino pazymi is n.d. pazymiu vektoriaus
        studentai.push_back(student); // ideda studento duomenis i bendra vektoriu
    }
}

void generuoti_vard(vector<duomenys> &studentai) {
    duomenys student;
    int vard_sk = rand() % 100 + 1; // sugeneruoja atsitiktini skaiciu, kuris rodo kiek bus zmoniu
    for (int i = 0; i < vard_sk; i++) {
        student.vardas = rand() % 26 + 65; // generuoja atsitiktini iniciala vardui
        student.vardas.push_back('.');
        student.pavarde = rand() % 26 + 65; // generuoja atsitiktini iniciala pavardei
        student.pavarde.push_back('.');
        generuoti_paz(student); // generuoja pazymius
        studentai.push_back(student); // ideda studento duomenis i bendra vektoriu
    }
}

void sortas(vector<duomenys> &studentai) {
    cout << "Pasirinkite pagal ka norite rusiuoti studentus: \n"
            << "1. Pagal varda \n"
            << "2. Pagal pavarde \n"
            << "3. Pagal galutini bala (vidurkis) \n"
            << "4. Pagal galutini bala (mediana) \n";
    int pasirinkimas;
    cin >> pasirinkimas;
    switch (pasirinkimas) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                return a.vid > b.vid;
            });
            break;
        case 4:
            sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                return a.med > b.med;
            });
            break;
    }
}