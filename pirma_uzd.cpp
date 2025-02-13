#include "libr.h"
#include  "saugojimas_masyve.h"

vector <duomenys> studentai;

int main()
{
    int a;
    cout << "norint įvesti duomenis ranka, įveskite 1. \n norint sugeneruoti pazymius, įveskite 2. \n norint sugeneruotus pazymius ir vardus, įveskite 3. \n norint baigti darbą, įveskite 4.";
    cin>>a;
    if(a==1) {
        ivedimas();
        write1("C:/Users/PC/Documents/GitHub/pirmas/rez.txt");
    }
    else if (a==3){
        srand(time(0));
        generuoti_vard();
        read("C:/Users/PC/Documents/GitHub/pirmas/duomenys.txt",studentai);
        write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt",studentai);
    }
    else if (a==2) {
        int n;
        srand(time(0));
        cout << "Iveskite studentu skaiciu: ";
        cin>>n;
        for(int i=0; i<n; i++) {
            generuoti_paz(studentai);
        }
        write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt",studentai);

    }
    return 0;
}
