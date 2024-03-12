/*se considera o aplicatie pentru gestionarea petitiilor primite in cadrul unei localitati. Definiti o clasa care modeleaza o astfel de solicitare. Se vor urmari atribute specifice,
precum: data depunerii, numele si prenumele solicitantului, categoria in care se incadreaza petitia, descrierea solicitarii etc. Datele membre sunt private si sunt puse la
la dispozitie metode de acces. Clasa contine cel putin 4 campuri, dintre care unul este alocat dinamic, constructorii, metodele specifice claselor
cu membri alocati dinamic si operatorul de afisare. Folositi un membru static sau const.
   Se va defini operatorul ! pentru a indica daca o petitie nu are raspuns si a depasit termenul legal(30 de zile)
   se va defini operatorul ~ pentru a schimba starea unei petitii( deschisa -> rezolvata)
   definiti operatorii << si >> pentru scrierea/citirea in/din fisiere text
   specializati clasa definita si exemplificati conceptul de virtualizare
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <crtdbg.h>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class petitie
{
private:
	char* numePrenume;
	int zi;
	int luna;
	int an;
	string categorie;
	bool stare;
	
	int zileDepunere;
public:
	static int nr_petitii;
	petitie()
	{
		numePrenume = new char[strlen("nedefinita") + 1];
		strcpy(numePrenume, "nedefinita");
		zi = 0;
		luna = 0;
		an = 0;
		categorie = "-";
		stare = false;
		zileDepunere;

		petitie::nr_petitii++;
	}
	petitie(const char* numePrenume, int zi, int luna, int an, string categorie, bool stare, int zileDepunere) : zi(zi), luna(luna), an(an), categorie(categorie), stare(stare),zileDepunere(zileDepunere)
	{
		if (numePrenume != nullptr)
		{
			this->numePrenume = new char[strlen(numePrenume) + 1];
			strcpy_s(this->numePrenume, strlen(numePrenume) + 1, numePrenume);
		}
		else
			this->numePrenume = nullptr;
		petitie::nr_petitii++;
	}
	~petitie()
	{
		delete[] numePrenume;
		petitie::nr_petitii--;
	}

	petitie(const petitie& p)
	{
		this->numePrenume = new char[strlen(p.numePrenume) + 1];
		strcpy_s(this->numePrenume, strlen(p.numePrenume) + 1, p.numePrenume);
		zi = p.zi;
		luna = p.luna;
		an = p.an;
		categorie = p.categorie;
		stare = p.stare;
		zileDepunere = p.zileDepunere;
	}

	petitie& operator=(const petitie& pet)
	{
		if (this == &pet)
			return *this;
		delete[] numePrenume;
		this->numePrenume = new char[strlen(pet.numePrenume) + 1];
		strcpy_s(this->numePrenume, strlen(pet.numePrenume) + 1, pet.numePrenume);
		zi = pet.zi;
		luna = pet.luna;
		an = pet.an;
		categorie = pet.categorie;
		stare = pet.stare;
		zileDepunere = pet.zileDepunere;

		return *this;
	}
	friend ostream& operator<<(ostream& out, petitie p)
	{
		out << "Nume Prenume:" << p.numePrenume << endl;
		out << "Data depunere:" << p.zi << "." << p.luna << "." << p.an << endl;
		out << "Categorie:" << p.categorie << endl;
		out << "stare petitie:" << (p.stare ? "Rezolvata" : "Deschisa") << endl;
		out << "zile de la depunere:" << p.zileDepunere << endl;
		return out;
		
	}
	//operator de negare care returneaza true daca masina nu a fost spalata in interior sau exterior
	const char* operator!()
	{

		if (!stare && zileDepunere>30 )
			return  "Petitie anulata";
		else
			return  "Petitie in curs";
	}

	//citire fisier text
	void citireFisText(const char* petitie) {
		ifstream fisier(petitie);

		if (!fisier) {
			cout << "Nu exista fisierul" << endl;
			return;
		}

		fisier >> numePrenume>> zi>>luna>>an>>categorie>>stare>>zileDepunere;

		fisier.close();
	}

	// scrierea datelor in fisier text
	void scriereFisText(const char* petitie) {
		ofstream fisier(petitie);

		if (!fisier) {
			cout << "Nu exista fisierul" << endl;
			return;
		}
		fisier << "NumePrenume: " << numePrenume << endl;
		fisier << "Data: " << zi << "." << luna << "." << an << endl;
		fisier << "categoriePet: " << categorie << endl;
		fisier << "Stare: "<<stare << endl;
		fisier <<"zile depunere: "<<zileDepunere << endl;
		

		fisier.close();
	}
};

int petitie::nr_petitii = 0;

int main()
{
	
	petitie pet1;
	cout << pet1 << endl;
	petitie pet2("Marian Vasile", 29, 01, 2023, "Pensie", false, 45);
	cout << pet2 << endl;
	pet1 = pet2;
	cout << pet1 << endl;
	const char* petitieAnulata = !pet2;
	cout << petitieAnulata << endl;

	petitie pet4 = pet2;
	petitie pet3("gheorghe Ion", 24, 6, 2023, "pensie", true, 22);
	pet3.scriereFisText("petitie.txt");
	pet3.citireFisText("petitie.txt");

	cout<<pet1.nr_petitii;

	return 0;
	


	
}

