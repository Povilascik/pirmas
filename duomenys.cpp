#include "duomenys.h"
#include "saugojimas_masyve.h"

// #ifndef TEST_FILE_LOCATION
//     #define TEST_FILE_LOCATION "C:/Users/PC/Documents/GitHub/pirmas"
// #endif

std::unordered_map<int, string> umap;

vector<duomenys> blogis;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Container>
void readas(const std::string &filename, Container &studentai) {
    ifstream in(filename);
    string line;
    getline(in, line); // Skip header
    studentai.reserve(10000000);
    while (getline(in, line)) {
        std::stringstream iss(line);
        duomenys student;
        iss >> student.vardas >> student.pavarde;
        int paz;
        student.nd.reserve(6);
        while (iss >> paz) {
            if (paz >= 0 && paz <= 10) student.nd.push_back(paz);
        }
        student.egz = student.nd.back();
        student.nd.pop_back();
        studentai.push_back(move(student));
    }
    cout << "read- baigta\n";
    in.close();

    for (auto &student : studentai) {
        student.vid = galutinis_vid(student.nd, student.egz);
        student.med = galutinis_med(student.nd, student.egz);
    }
    cout << "vid. suskaicuotas\n";
}

template<typename Container>
double dalina(Container &studentai, Container &blogis) {
    auto start = std::chrono::high_resolution_clock::now();
    std::stable_sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
        return a.vid < b.vid;
    });
    auto end = std::chrono::high_resolution_clock::now();
    auto it = std::find_if(studentai.begin(), studentai.end(), [](const duomenys &student) {
        return student.vid >= 5;
    });

    blogis.insert(blogis.end(), std::make_move_iterator(studentai.begin()), std::make_move_iterator(it));
    studentai.erase(studentai.begin(), it);
    cout << "dalina - baigta\n";
    return chrono::duration<double>(end - start).count();
}

template<typename Container>
void sortass(Container &studentai) {
    std::cout << "Pasirinkite pagal ka norite rusiuoti studentus: \n"
            << "1. Pagal varda \n"
            << "2. Pagal pavarde \n"
            << "3. Pagal galutini bala (vidurkis) \n"
            << "4. Pagal galutini bala (mediana) \n";
    // auto start = std::chrono::high_resolution_clock::now();
    try {
        int pasirinkimas;
        std::cin >> pasirinkimas;
        if (std::cin.fail() or pasirinkimas < 1 or pasirinkimas > 4) {
            throw invalid_argument("Neteisingas ivestis.");
        }

        switch (pasirinkimas) {
            case 1:
                stable_sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                    return a.vardas < b.vardas;
                });
                break;
            case 2:
                stable_sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                    return a.pavarde < b.pavarde;
                });
                break;
            case 3:
                stable_sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                    return a.vid > b.vid;
                });
                break;
            case 4:
                stable_sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                    return a.med > b.med;
                });
                break;
        }
    } catch (const exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
    // auto end = chrono::high_resolution_clock::now();
    cout << "sortas- baigta\n";
    // return std::chrono::duration<double>(end - start).count();
}

template<typename Container>
void write_to_file(const std::string &filename, const Container &studentai) {
    std::ofstream out(filename);
    out << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    out << "------------------------------------------------------------" << endl;
    for (const auto &student: studentai) {
        out << setw(20) << left << student.vardas << " " << setw(20) << left << student.pavarde << " " << setw(20) <<
                left << fixed << setprecision(2) << student.vid << setw(20) << left << fixed << setprecision(2) <<
                student.vid << "\n";
    }
    cout << "write - baigta\n";
    out.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void meniu(vector<duomenys> &studentai) {
    try {
        int a;
        cout << "norint ivesti duomenis ranka, iveskite 1. \n"
                << "norint sugeneruoti pazymius, iveskite 2. \n"
                << "norint sugeneruotus pazymius ir vardus, iveskite 3. \n"
                << "norint nuskaityti vardus is failo, iveskite 4. \n"
                << "norint sugeneruoti arba atlikti tyrimus su duomenimis spauskite 5. \n"
                << "norint baigti darba, iveskite 6.";
        cin >> a;
        if (cin.fail() or a < 1 or a > 6) {
            throw std::invalid_argument("Neteisingas ivestis.");
        }
        string path;
        switch (a) {
            case 1:
                ivedimas();
                write1();
                break;
            case 2:
                generuoti_paz_ranka(studentai);
                write(studentai);
                break;
            case 3:
                generuoti_vard(studentai, 2, 0);
                write(studentai);
            break;
            case 4: {
                int pasirinkimas;
                cout << "pasirinkite kuri faila norite nuskaityti: \n"
                        << "1. studentai10000.txt \n"
                        << "2. studentai100000.txt \n"
                        << "3. studentai1000000.txt \n";
                cin >> pasirinkimas;
                if (cin.fail() or pasirinkimas < 1 or pasirinkimas > 3) {
                    throw std::invalid_argument("Neteisingas ivestis.");
                }
                try {
                    switch (pasirinkimas) {
                        case 1:
                            read(test_file_location+"/studentai10000.txt", studentai);
                            break;
                        case 2:
                            read(test_file_location+"/studentai100000.txt", studentai);
                            break;
                        case 3:
                            read(test_file_location+"/studentai1000000.txt", studentai);
                            break;
                        default:
                            cout << "Neteisingas pasirinkimas." << endl;
                            break;
                    }
                } catch (const std::exception &e) {
                }
                if (studentai.empty()) {
                    cout << "Nepavyko nuskaityti failo." << endl;
                } else {
                    sortas(studentai);
                    ss_write(test_file_location+"/kursiokai.txt", studentai);
                }
                break;
            }
            case 5: {
                umap[1] = test_file_location+"/tyrimas_studentai1000";
                umap[2] = test_file_location+"/tyrimas_studentai10000";
                umap[3] = test_file_location+"/tyrimas_studentai100000";
                umap[4] = test_file_location+"/tyrimas_studentai1000000";
                umap[5] = test_file_location+"/tyrimas_studentai10000000";
                int pasirinkimas1;
                cout << "1. sugeneruoti failus." << endl
                        << "2. tirti failus" << endl;
                try {
                    cin >> pasirinkimas1;
                } catch (exception &e) {
                    cout << "Klaida: " << e.what() << endl;
                }

                switch (pasirinkimas1) {
                    case 1: {
                        int paz_sk;
                        cout<<"Iveskite pazymiu skaiciu: ";
                        cin>>paz_sk;
                        if (cin.fail() or paz_sk < 2) {
                            throw std::invalid_argument("Neteisingas ivestis.");
                        }
                        auto start = std::chrono::high_resolution_clock::now();
                        make_file(studentai, test_file_location+"/tyrimas_studentai1000.txt", 1000, paz_sk);
                        make_file(studentai, test_file_location+"/tyrimas_studentai10000.txt", 10000,
                                  paz_sk);
                        make_file(studentai, test_file_location+"/tyrimas_studentai100000.txt", 100000,
                                  paz_sk);
                        make_file(studentai, test_file_location+"/tyrimas_studentai1000000.txt",
                                  1000000, paz_sk);
                        make_file(studentai, test_file_location+"/tyrimas_studentai10000000.txt",
                                  10000000, paz_sk);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> duration = end - start;
                        cout << "laikas, kuri uztruko sugeneruoti visus duomenis: " << duration.count() << " seconds."
                                << endl;
                        break;
                    }
                    case 2: {
                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        double sorto_laikas;
                        std::cout << "Pasirinkite konteinerio tipa: \n"
                                << "1. std::vector \n"
                                << "2. std::list \n"
                                << "3. std::deque \n";
                        int pasirinkimas;
                        std::cin >> pasirinkimas;
                        if (std::cin.fail() or pasirinkimas < 1 or pasirinkimas > 3) {
                            throw std::invalid_argument("Neteisinga ivestis.");
                            break;
                        }
                        using ContainerType = vector<duomenys>;
                        if (pasirinkimas == 1) using ContainerType = std::vector<duomenys>;
                        else if (pasirinkimas == 2) using ContainerType = std::list<duomenys>;
                        else if (pasirinkimas == 3) using ContainerType = std::deque<duomenys>;
                        else std::cout << "Neteisingas pasirinkimas." << std::endl;
                        ContainerType studentai;
                        ContainerType blogis;
                        cout << "Pasirinkite kuri faila norite nuskaityti: \n"
                                << "1. studentai1000.txt \n"
                                << "2. studentai10000.txt \n"
                                << "3. studentai100000.txt \n"
                                << "4. studentai1000000.txt \n"
                                << "5. studentai10000000.txt \n";
                        cin >> pasirinkimas1;
                        if (cin.fail() or pasirinkimas1 < 1 or pasirinkimas1 > 5) {
                            throw std::invalid_argument("Neteisingas ivestis.");
                        }
                        if (pasirinkimas1 > 5 or pasirinkimas1 < 1) {
                            throw std::invalid_argument("Neteisingas ivestis.");
                        }
                        auto nuskaitymas_pradzia = chrono::high_resolution_clock::now();
                        readas(umap[pasirinkimas1] + ".txt", studentai);
                        auto nuskaitymas_pabaiga = chrono::high_resolution_clock::now();
                        ////////////////////////////////////////////////////////////////////////////////////
                        auto dalinimo_pradzia = chrono::high_resolution_clock::now();
                        sorto_laikas=dalina(studentai,blogis);
                        auto dalinimo_pabaiga = chrono::high_resolution_clock::now();
                        ////////////////////////////////////////////////////////////////////////////////////
                        cout << "Pazangus studentai: \n";
                        sortass(studentai);
                        cout << "Nepazangus studentai: \n";
                        sortass(blogis);

                        write_to_file(umap[pasirinkimas1] + "_stud_rez.txt", studentai);
                        write_to_file(umap[pasirinkimas1] + "_blogi_rez.txt", blogis);

                        cout << "\n Nuskaitymo laikas: " << std::chrono::duration<double>(
                            nuskaitymas_pabaiga - nuskaitymas_pradzia).count() << "s" << endl;
                        cout << "\n rusiavimo laikas: "  << sorto_laikas << "s" << endl;
                        cout << "\n dalinimo laikas: " << std::chrono::duration<double>(
                            dalinimo_pabaiga - dalinimo_pradzia).count() << "s" << endl;
                        cout << "\n Is viso laiko: " << std::chrono::duration<double>(
                            nuskaitymas_pabaiga - nuskaitymas_pradzia).count() + sorto_laikas + std::chrono::duration<double>(
                            dalinimo_pabaiga - dalinimo_pradzia).count() << "s" << endl;
                        break;
                    }
                    default:
                        cout << "Neteisingas pasirinkimas." << endl;
                        break;
                }
            }
            case 6: {
                cout << "\nDarbas baigtas." << endl;
                break;
            }
            default:
                cout << "Neteisingas pasirinkimas." << endl;
                break;
        }
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}

void galutinis_vid(vector<int> nd, int egz, vector<duomenys> &studentai) {
    // skaiciuoja galutini bala pagal vidurki
    duomenys student;
    double vid = 0;
    try {
        for (int i = 0; i < nd.size(); i++) {
            vid += nd[i];
        }
        vid /= nd.size();

        student.vid = 0.4 * vid + 0.6 * egz;
        studentai.push_back(student);
    } catch (const std::exception &e) {
        std::cerr << "Error calculating average: " << e.what() << std::endl;
    }
}

double galutinis_vid(vector<int> nd, int egz) {
    // skaiciuoja galutini bala pagal vidurki
    double vid = 0;
    try {
        for (int i = 0; i < nd.size(); i++) {
            vid += nd[i];
        }
        vid /= nd.size();
    } catch (const std::exception &e) {
        std::cerr << "Error calculating average: " << e.what() << std::endl;
    }
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
    std::stringstream ss;
    ss << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    ss << "------------------------------------------------------------" << endl;
    for (int i = 0; i < studentai.size(); i++) {
        ss << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(20) <<
                left << fixed << setprecision(2) << studentai[i].vid << setw(20) <<
                left << fixed << setprecision(2) << studentai[i].med << endl;
    }
    out << ss.str();
    out.close();
}

void write(vector<duomenys> &studentai) {
    //isvedimo funkcija
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < studentai.size(); i++) {
        cout << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(20) <<
                left
                << fixed << setprecision(2) << galutinis_vid(studentai[i].nd, studentai[i].egz) << setw(20) << left
                <<
                fixed << setprecision(2) << galutinis_med(studentai[i].nd, studentai[i].egz) << endl;
    }
}

void write_file(const string &filename, std::vector<duomenys> &studentai, int nd_skaicius) {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("negalima atidaryti failo: " + filename);
    }
    stringstream ss;
    ss << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde";
    for (int i = 1; i <= nd_skaicius - 1; i++) {
        ss << setw(20) << left << "ND" + to_string(i);
    }
    ss << setw(20) << left << "EGZAMINAS" << endl;
    while (!studentai.empty()) {
        // int lines_to_write = std::min(1000, static_cast<int>(studentai.size()));
        for (auto i: studentai) {
            ss << setw(20) << left << i.vardas
                    << setw(20) << left << i.pavarde;
            for (auto k: i.nd) {
                // ss << i.nd.size() << " -size ";
                ss << setw(20) << left << k;
            }
            ss << setw(20) << left << i.egz;
            ss << endl;
        }
        out << ss.str();
        studentai.erase(studentai.begin(), studentai.end());
    }

    out.close();
}

void make_file(vector<duomenys> &studentai, const string &filename, int mok_sk, int paz_sk) {
    generuoti_vard(studentai, paz_sk, mok_sk);
    write_file(filename, studentai, paz_sk);
}

void generuoti_paz(duomenys &student, int paz_sk) {
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
        try {
            cout << "Iveskite studento varda (iveskite 'p' norint uzbaigti): ";
            cin >> student.vardas;
            if (student.vardas == "p") break;
            cout << "Iveskite studento pavarde: ";
            cin >> student.pavarde;
            if (cin.fail()) {
                throw std::invalid_argument("Neteisingas ivestis.");
            }
            int paz_sk = rand() % 10 + 1; // sugeneruoja atsitiktini pazymiu skaiciu
            generuoti_paz(student, paz_sk); // generuoja pazymius
            studentai.push_back(student); // ideda studento duomenis i bendra vektoriu
        } catch (const std::exception &e) {
            cout << "Klaida: " << e.what() << endl;
            cin.clear();
        }
    }
}

void generuoti_vard(vector<duomenys> &studentai, int paz_sk1, int mok_sk) {
    int vard_sk;
    if (mok_sk != 0) vard_sk = mok_sk;
    else vard_sk = rand() % 100 + 1; // sugeneruoja atsitiktini skaiciu, kuris rodo kiek bus zmoniu
    int paz_sk;
    if (paz_sk1 != 0) paz_sk = paz_sk1;
    else paz_sk = rand() % 10 + 1; // sugeneruoja atsitiktini pazymiu skaiciu
    for (int i = 0; i < vard_sk; i++) {
        duomenys student;
        student.vardas = rand() % 26 + 65; // generuoja atsitiktini iniciala vardui
        student.vardas += ".";
        student.pavarde = rand() % 26 + 65; // generuoja atsitiktini iniciala pavardei
        student.pavarde += ".";
        generuoti_paz(student, paz_sk); // generuoja pazymius
        studentai.push_back(student); // ideda studento duomenis i bendra vektoriu
    }
}

void sortas(vector<duomenys> &studentai) {
    cout << "Pasirinkite pagal ka norite rusiuoti studentus: \n"
            << "1. Pagal varda \n"
            << "2. Pagal pavarde \n"
            << "3. Pagal galutini bala (vidurkis) \n"
            << "4. Pagal galutini bala (mediana) \n";
    try {
        int pasirinkimas;
        cin >> pasirinkimas;
        if (cin.fail() or pasirinkimas < 1 or pasirinkimas > 4) {
            throw std::invalid_argument("Neteisingas ivestis.");
        }

        switch (pasirinkimas) {
            case 1:
                sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                    return a.vardas < b.vardas;
                });
                break;
            case 2:
                sort(studentai.begin(), studentai.end(), [](const duomenys &a, const duomenys &b) {
                    return a.pavarde < b.pavarde;
                });
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
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}