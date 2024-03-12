/* Se considera o aplicatie pt gestiunea unei colectii de markere folosite pt scrierea pe o tabla dintr-o sala. Se vor urmari
aspectele comune privind culoare, dimensiune, producator, etc. Pt datele membre private sunt puse la dispozitie metode
de acces. Clasa contine cel putin patru campuri, dintre care unul este alocat dinamic, constructori, metodele specifice
claselor cu membri alocati dinamic. Folositi un membru static sau const.
    --supraincarcati operator<< pentru afisarea unui marker
    --specializati clasa care descrie un marker electronic avand noi campuri precum baterie, raza actiune, etc.
    --oferiti posibilitatea de comparare a doua markere prin operator==, compararea realizandu se pentru mini doua atribute*/



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <crtdbg.h>
#include <string.h>

using namespace std;

class inventar
{
private:
    char* numeProd;
    float grosimeMM;
    float lungimeMM;
    bool nou;
    string culoare;
    static int numar_colectii;
public:
    inventar()
    {
        numeProd = new char[strlen("nedefinit") + 1];
        strcpy(numeProd, "nedefinit");
        grosimeMM = 0;
        lungimeMM = 0;
        nou = false;
        culoare = "-";
}
    inventar(const char* numeProd, float grosimeMM, float lungimeMM, bool nou, string culoare) : grosimeMM(grosimeMM), lungimeMM(lungimeMM), nou(nou), culoare(culoare)
    {

        this->numeProd = new char[strlen(numeProd) + 1];
        strcpy(this->numeProd, numeProd);
    }
   
    ~inventar()
    {
        delete[] numeProd;
    }

    inventar(const inventar& i)
    {
        this->numeProd = new char[strlen(i.numeProd) + 1];
        strcpy_s(this->numeProd, strlen(i.numeProd) + 1, i.numeProd);
        this->grosimeMM = i.grosimeMM;
        this->lungimeMM = i.lungimeMM;
        this->nou = i.nou;
        this->culoare = i.culoare;

    }

    inventar& operator=(const inventar& i)
    {
        delete[] numeProd;
        this->numeProd = new char[strlen(i.numeProd) + 1];
        strcpy_s(this->numeProd, strlen(i.numeProd) + 1, i.numeProd);
        this->grosimeMM = i.grosimeMM;
        this->lungimeMM = i.lungimeMM;
        this->nou = i.nou;
        this->culoare = i.culoare;
        return *this;
    }

    friend ostream& operator<<(ostream& out,const inventar& i)
    {
        out << "nume producator: " << i.numeProd << endl;
        out << "grosime marker: " << i.grosimeMM << endl;
        out << "lungime marker: " << i.lungimeMM << endl;
        out << "markerul este: " << (i.nou ? "Nou" : "Vechi") << endl;
        out << "culoare markerului este: " << i.culoare << endl;
        return out;
    }

    char* getNume()
    {
        return numeProd;
    }
    float getGrosime()
    {
        return grosimeMM;
    }
    float getLungime()
    {
        return lungimeMM;
    }
    bool getNou()
    {
        return nou;
    }
    string getCuloare()
    {
        return culoare;
    }
    static int getNrColectii()
    {
        return numar_colectii;
    }
};
class mElectronic: public inventar
{
private:
    bool baterieSanatoasa;
    float razaAct;
    int durataViata;
public:
    mElectronic(const char* numeProd, float grosimeMM, float lungimeMM, bool nou, string culoare, bool baterieSanatoasa, float razaAct, int durataViata) 
        :inventar(numeProd, grosimeMM,lungimeMM,nou,culoare),baterieSanatoasa(baterieSanatoasa),razaAct(razaAct),durataViata(durataViata)
    {}

    void afisareMarkerElec()
    {
        cout << "nume producator: " << getNume() << endl;
        cout << "grosime marker: " << getGrosime() <<"milimetri"<< endl;
        cout << "lungime marker: " << getLungime()<<"milimetri"<< endl;
        cout << "markerul este: " << (getNou() ? "Nou" : "Vechi") << endl;
        cout << "culoare markerului este: " << getCuloare() << endl;
        cout << "bateria markerului este: " << (baterieSanatoasa ? "sanatoasa" : "Nesanatoasa") << endl;
        cout << "raza de actiune a markerului este: " << razaAct <<"metri"<< endl;
        cout << "durata de viata este:" << durataViata << "ore"<<endl;
    }
    friend bool operator==( mElectronic& m1, mElectronic& m2) {
        return(strcmp(m1.getNume(), m2.getNume()) == 0 && (m1.getNou() == m2.getNou()));
    }
};
int inventar::numar_colectii = 23;

int main()
{
    inventar m1;
    cout << m1 << endl;
    inventar m2("Milboa", 4.5, 14.6, true, "galben");
    cout << m2 << endl;
    m1 = m2;
    cout << m1 << endl;
    inventar m4 = m2;
    cout << m4 << endl;
    mElectronic m6("Miunec",6.5,12.76, true, "rosu", true, 15.5, 30);
    m6.afisareMarkerElec();
    mElectronic m7("Miunec", 4.2, 14.5, true, "galben", true, 32.4, 64);
    if (m7 == m6)
    {
        cout << "ambele markere sunt noi si au acelasi producator " << endl;
    }
    cout << inventar::getNrColectii();
}