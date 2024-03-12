//se considera o aplicatie pentru gestionarea activitatii unei firme care ofera servicii de imprimare 3d, folosind materiale(lemn, plastic, silicon, etc.) pe baza modelelor primite de la clienti. Definiti o clasa care modeleaza
//un aspect propriu acestei activitati. Se vor urmari atribute specifice, precum: tipul materialului, numarul de exemplare, dimensiunile, categorii, costuri etc. Datele membre sunt private si sunt puse la dispozitie metode
//de acces. Clasa contine cel putin patru campuri, dintre care unul este alocat dinamic, constructori, metodele specifice claselor cu membri alocati dinamic si operatorul de afisare. Folositi un membru static sau const
//   -- se va defini operatorul < care permite compararea a doua obiecte si va fi utilizat in cadrul unei functii de sortare.
//   --prin intermediul operatorului += se va combina obiectul curent cu un obiect primit ca parametru.
//   --exemplificati conceptul de relatie de tip "is a" prin specializarea clasei/uneia dintre clasele definite
//   -- implementati cate o metoda pentru scrierea/citirea unui obiect intr-un fisier text.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <crtdbg.h>
#include <string.h>
#include <fstream>

using namespace std;

class comanda3D {
private:
	int id_comanda;
	char* numeImprimanta;
	float pretComanda;
	string* materialeFolosite;
	int nrMateriale;
	bool comandaLunga;
	static int numarComenzi;
public:
	comanda3D() {
		id_comanda = 0;
		this->numeImprimanta = new char[strlen("nedefinit") + 1];
		strcpy_s(this->numeImprimanta,strlen("nedefinit")+1, "nedefinit");
		pretComanda = 0;
		materialeFolosite = nullptr;
		nrMateriale = 0;
		comandaLunga = false;

		comanda3D::numarComenzi++;
	}
	comanda3D(int id_comanda,const char* numeImprimanta, float pretComanda, string* materialeFolosite, int nrMateriale, bool comandaLunga):id_comanda(id_comanda),pretComanda(pretComanda), comandaLunga(comandaLunga) {
		if (numeImprimanta != nullptr)
		{
			this->numeImprimanta = new char[strlen(numeImprimanta) + 1];
			strcpy(this->numeImprimanta, numeImprimanta);
		}
		else this->numeImprimanta = nullptr;

		if (materialeFolosite != nullptr && nrMateriale > 0)
		{
			this->nrMateriale = nrMateriale;
			this->materialeFolosite = new string[nrMateriale];
			for (int i = 0; i < nrMateriale; i++)
				this->materialeFolosite[i] = materialeFolosite[i];
		}
		else
		{
			this->nrMateriale = 0;
			this->materialeFolosite = nullptr;
		}
		comanda3D::numarComenzi++;

	}
	~comanda3D()
	{
		delete[] numeImprimanta;
		delete[] materialeFolosite;
	}

	comanda3D(const comanda3D& c)
	{
		this->id_comanda = c.id_comanda;
		if (c.numeImprimanta != nullptr)
		{
			this->numeImprimanta = new char[strlen(c.numeImprimanta) + 1];
			strcpy(this->numeImprimanta, c.numeImprimanta);
	}
		this->pretComanda = c.pretComanda;
		if (c.materialeFolosite != nullptr && c.nrMateriale > 0)
		{
			this->nrMateriale = c.nrMateriale;
			this->materialeFolosite = new string[c.nrMateriale];
			for (int i = 0; i < c.nrMateriale; i++)
				this->materialeFolosite[i] = c.materialeFolosite[i];
		}
		else {
			this->nrMateriale = 0; this->materialeFolosite = nullptr;
		}
			this->comandaLunga = c.comandaLunga;
	
	}
	comanda3D& operator=(const comanda3D& c) {
		if (this == &c)
			return *this;

		this->id_comanda = c.id_comanda;
		delete[] this->numeImprimanta;
		this->numeImprimanta = new char[strlen(c.numeImprimanta) + 1];
		strcpy_s(this->numeImprimanta, strlen(c.numeImprimanta)+1, c.numeImprimanta);
		this->pretComanda = c.pretComanda;
		this->nrMateriale = c.nrMateriale;
		delete[] this->materialeFolosite;
		if (c.materialeFolosite != nullptr && c.nrMateriale > 0)
		{
		this->materialeFolosite = new string[c.nrMateriale];
		for (int i = 0; i < c.nrMateriale; i++)
			this->materialeFolosite[i] = c.materialeFolosite[i];
		}
		else { this->nrMateriale = 0; this->materialeFolosite = nullptr; }
		this->comandaLunga = c.comandaLunga;

		return *this;
	}

	friend ostream& operator<<(ostream& out, comanda3D& s) {
		out << "id_comanda: " << s.id_comanda << endl;
		out << "nume imprimanta: " << s.numeImprimanta << endl;
		out << "pret comanda: " << s.pretComanda << endl;
		out << "nr materiale folosite: " << s.nrMateriale << endl;
		out << "materialele folosite sunt: " << endl;
		for (int i = 0; i < s.nrMateriale; i++)
			out << s.materialeFolosite[i] << endl;
		out << endl;
		out << "comanda este: " << (s.comandaLunga ? "lunga" : "scurta") << endl;
		
		return out;	
	}
	friend bool operator<(const comanda3D& x, const comanda3D& y) {
		return x.pretComanda<y.pretComanda;
	}
	comanda3D& operator+=(const comanda3D& comandaNoua)
	{
		char* temp = new char[strlen(numeImprimanta) + 1];
		strcpy(temp, numeImprimanta);
		delete[] numeImprimanta;
		numeImprimanta = new char[strlen(numeImprimanta)+strlen( comandaNoua.numeImprimanta) + 1];
		strcpy(numeImprimanta, temp);
		strcat(numeImprimanta, comandaNoua.numeImprimanta);

		pretComanda += comandaNoua.pretComanda;

		string* copie = new string[nrMateriale];
		for (int i = 0; i < nrMateriale; i++)
		{
			copie[i] = materialeFolosite[i];
		}
		delete[] materialeFolosite;
		materialeFolosite = new string[nrMateriale + comandaNoua.nrMateriale];
		for (int i = 0; i < nrMateriale; i++)
		{
			materialeFolosite[i] = copie[i];
		}
		for (int i = nrMateriale; i < nrMateriale +comandaNoua.nrMateriale; i++)
		{
			materialeFolosite[i] = comandaNoua.materialeFolosite[i-nrMateriale];
		}
		delete[] copie;
		nrMateriale+=comandaNoua.nrMateriale;
		
		

		return *this;

	}
	void setNume(char* numeImprimanta) {
		if (numeImprimanta != nullptr)
		{
			this->numeImprimanta = new char[strlen(numeImprimanta) + 1];
			strcpy(this->numeImprimanta, numeImprimanta);
		}
		else
			this->numeImprimanta = nullptr;
	}
	void citireFisText(const char* comanda3D) {
		ifstream fisier(comanda3D);
		if (!fisier) {
			cout << "Nu exista fisierul " << endl;
			return;
		}
		fisier >> id_comanda;
		char tmp[256];
		fisier.getline(tmp, 256);
		setNume(tmp);
		fisier >> pretComanda;
			
		for (int i = 0; i < this->nrMateriale; i++)
		{
			fisier >> this->materialeFolosite[i];
		}

		fisier>> nrMateriale >> comandaLunga;
		
		fisier.close();

	}



	// scrierea datelor in fisier text
	void scriereFisText(const char* comanda3D) {
		ofstream fisier(comanda3D);

		if (!fisier) {
			cout << "Nu exista fisierul" << endl;
			return;
		}
		fisier << id_comanda << endl;
		fisier << numeImprimanta << endl;
		fisier << pretComanda<< endl;
		for (int i = 0; i < this->nrMateriale; i++)
		{
			fisier << this->materialeFolosite[i] << endl;
		}
		fisier << nrMateriale << endl;
		fisier << comandaLunga << endl;


		fisier.close();
	}
	int getId()
	{
		return id_comanda;
	}
	char* getNume() {
		return numeImprimanta;
	}
	float getPret() {
		return pretComanda;
	}
	string* getMateriale()
	{
		return materialeFolosite;
	}
	int getNr()
	{
		return nrMateriale;
	}
	bool getLungime() {
		return comandaLunga;
	}

};
void sorteaza(comanda3D v[], int nr_elem)
{
	for (int i = 0; i < nr_elem - 1; i++)
		for (int j = i + 1; j < nr_elem; j++)
			if (v[j] < v[i])
				swap(v[i], v[j]);
}
class comenziSpeciale : public comanda3D {
private:
	bool tratamentChimic;
	bool matSensibil;
public:
	comenziSpeciale(int id_produs, char* numeImprimanta, float pretComanda, string* materialeFolosite, int nrMateriale, bool comandaLunga)
		: comanda3D(id_produs, numeImprimanta, pretComanda, materialeFolosite, nrMateriale, comandaLunga), tratamentChimic(tratamentChimic), matSensibil(matSensibil) {

	}
	void afisareComSpeciale() {
		cout << "id produs: " << getId() << endl;
		cout << "nume imprimanta: " << getNume() << endl;
		cout << "pret comanda: " << getPret() << endl;
		cout << "materialele folosite: " << getMateriale() << endl;
		cout << "nr materialelor: " << getNr() << endl;
		cout << "comanda lunga: " << getLungime() << endl;
		cout << "tratament chimic: " << (tratamentChimic ? "da" : "nu") << endl;
		cout << "materie sensibil: " << (matSensibil ? "da" : "nu") << endl;
	}
};
int comanda3D::numarComenzi = 0;

int main() {
	comanda3D c1;
	cout << c1;
	string* materialeFolosite = new string[4];
	materialeFolosite[0] = "lemn";
	materialeFolosite[1] = "plastic";
	materialeFolosite[2] = "silicon";
	materialeFolosite[3] = "carbon";
	comanda3D c2(203, "sony", 504, materialeFolosite, 4, true);
	comanda3D c3(123, "samsung", 46, materialeFolosite, 4, false);
	
	comanda3D comanda[3];
	comanda[0] = c1;
	comanda[1] = c2;
	comanda[2] = c3;
	cout << "sortarea obiectelor" << endl;
	sorteaza(comanda, 3);
	cout << comanda[0] << endl;
	cout << comanda[1] << endl;
	cout << comanda[2] << endl;
	c2 += c3;
	cout << c2 << endl;

	c1.scriereFisText("comanda3D.txt");
	c1.citireFisText("comanda3D.txt");
	comenziSpeciale c5(43, "toshiba", 34, materialeFolosite, 4, true, false, true);
	c5.afisareComSpeciale();

		
}