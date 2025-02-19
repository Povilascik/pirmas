#include "libr.h"
#include  "saugojimas_masyve.h"

vector <duomenys> studentai;

int main()
{
    srand(time(0));
    int a;
    cout << "norint ivesti duomenis ranka, iveskite 1. \n"
     << "norint sugeneruoti pazymius, iveskite 2. \n"
     << "norint sugeneruotus pazymius ir vardus, iveskite 3. \n"
     << "norint baigti darba, iveskite 4.";
    cin >> a;

    switch (a) {
        case 1:
            ivedimas();
        write1("C:/Users/PC/Documents/GitHub/pirmas/rez.txt");
        break;
        case 2:
        generuoti_paz_ranka(studentai);
        write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt", studentai);
        break;
        case 3:
        generuoti_vard(studentai);
        write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt", studentai);
        break;
        case 4:
            cout << "Darbas baigtas." << endl;
        break;
        case 5:
            read("C:/Users/PC/Documents/GitHub/pirmas/studentai1000000.txt", studentai);
        write("C:/Users/PC/Documents/GitHub/pirmas/kursiokai.txt", studentai);
        break;
        default:
            cout << "Neteisingas pasirinkimas." << endl;
        break;
    }


    // Truncate the file at the end of the program
    std::ofstream out("C:/Users/PC/Documents/GitHub/pirmas/duomenys1.txt", std::ios::trunc);
    out.close();

    return 0;
}
