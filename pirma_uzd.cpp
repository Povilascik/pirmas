#include "libr.h"
#include  "saugojimas_masyve.h"

vector <duomenys> studentai;

int main()
{
    int a;
    //cout << "norint įvesti duomenis ranka, įveskite 1, norint nuskaityti sugeneruotus duomenis iš failo, įveskite 2: ";
    //cin>>a;
    /*if(a==1) {
        ivedimas();
        write1("C:/Users/PC/Documents/GitHub/pirmas/rez.txt");
    }
    else{*/
        srand(time(0));
        generuoti_vard();
        read("C:/Users/PC/Documents/GitHub/pirmas/duomenys.txt",studentai);
    write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt",studentai);


    return 0;
}
