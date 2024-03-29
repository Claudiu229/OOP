﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <crtdbg.h>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class masina {
protected:  //protected pentru a putea avea acces la tributele din clasa masina in clasa masinaSpeciala
	char* nume;
	float pret_sp; //pret_spalare
	bool masina_mare;
	bool exterior;
	bool interior;
	int nr_client;
public:


	masina()                       //operatorul fara parametrii
	{
		nume = new char[strlen("nedefinita") + 1];
		strcpy(nume, "nedefinita");
		masina_mare = false;
		exterior = false;
		interior = false;
		pret_sp = 0;
		nr_client = 0;
	}
	masina(const char* nume, bool masina_mare, bool exterior, bool interior, float pret_sp, int nr_client)                     //operatorul cu parametrii
		:  masina_mare(masina_mare), exterior(exterior), interior(interior),pret_sp(pret_sp), nr_client(nr_client)
	{
		if (nume != nullptr)                                       //verificam daca e null ca sa nu dea exceptie strlen
		{
			this->nume = new char[strlen(nume) + 1];    
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
			this->nume = nullptr;

		discount();                              //apelam discount la instantiere pentru apelare automata
	}
	~masina()           //destructorul
	{
		delete[] nume;
	}

	//constructorul de copiere
	masina(const masina& sp)                   
	{
		this->nume = new char[strlen(sp.nume) + 1];
		strcpy_s(this->nume, strlen(sp.nume) + 1, sp.nume);
		masina_mare = sp.masina_mare;
		exterior = sp.exterior;
		interior = sp.interior;
		pret_sp = sp.pret_sp;
		nr_client = sp.nr_client;
	}

	//operatorul de atribuie
	masina& operator=(const masina& spal)      
	{
		if (this == &spal)
			return *this;

		delete[] nume;
		nume = new char[strlen(spal.nume) + 1];
		strcpy(nume, spal.nume);
		masina_mare = spal.masina_mare;
		exterior = spal.exterior;
		interior = spal.interior;
		pret_sp = spal.pret_sp;
		nr_client = spal.nr_client;

		return *this;
	}

	void setNume(const char* nume)           
	{
		if (nume != nullptr)
		{
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else
			this->nume = nullptr;
	}

	//operator de iesire
	friend ostream& operator<<(ostream& out, masina m) {               
		out << "Nume: " << m.nume << "\n";
		out << "Masina mare: " << (m.masina_mare ? "Da" : "Nu") << "\n";
		out << "Exterior: " << (m.exterior ? "Da" : "Nu") << "\n";
		out << "Interior: " << (m.interior ? "Da" : "Nu") << "\n";
		out << "Pret spalare: " << m.pret_sp << "\n";
		out << "Nr. client: " << m.nr_client << "\n";
		return out;
	}

	friend istream& operator>>(istream& in, masina& m) {       //operator de intrare
		
		cout << "Introduceti numele masinii: ";  //citeste numele clientului
		char tmp[256];                                      
		in.getline(tmp, 256);       
		m.setNume(tmp);
		

		cout << "Masina mare? (1 - Da, 0 - Nu): ";  //citeste 1/0 , daca masina e mare sau nu
		in >> m.masina_mare;

		cout << "Spalare exterior? (1 - Da, 0 - Nu): "; //citeste 1/0 , daca masina e spalata pe exterior
		in >> m.exterior;

		cout << "Spalare interior? (1 - Da, 0 - Nu): "; // citeste 1/0 , daca masina e spalata pe interior
		in >> m.interior;

		cout << "Introduceti pretul spalarii: "; //citeste pretul spalarii
		in >> m.pret_sp;

		cout << "Numarul clientului: ";  // citeste nr. de tel. al clientului
		in >> m.nr_client;

		m.discount();                   //apelam functia discount la citirea datelor pentru a aplica automat

		return in;
	}


	//operatorii relationali

	//compara numele masinilor si marimea lor
	friend bool operator==(const masina& m1, const masina& m2)     
	{
		return (strcmp(m1.nume, m2.nume) == 0) && (m1.masina_mare == m2.masina_mare);
	}

	//compara pretul spalarii masinilor
	friend bool operator<(const masina& m1, const masina& m2) {      
		return m1.pret_sp < m2.pret_sp;
	}


	//operatorul de conversie
	operator float() const {
		return pret_sp;
	}
	

	//metoda specifica pentru actualizarea pretului la 100 pentru masini scumpe
		void pretPremium() { 
			const char* masiniScumpe[] = { "BMW", "AUDI", "MERCEDES" };

			for (int i = 0; i < 3; i++) {
				if (_stricmp(nume, masiniScumpe[i]) == 0) {    //stricmp pentru compararea non case sensitive
					pret_sp = 100;
					
				}
			}
			// Daca nu este o masina scumpe pretul ramane neschimbat
			discount();
		}
		//metoda specifica pentru discount alocat primilor 10 clienti
		void discount()
		{
			if (nr_client <= 10)
			{
				pret_sp -= 10;
			}
	}

//3 operatori 
// 
		//operator de functie care afiseaza numele masinii daca aceasta este mare
		 void operator()() {                  
			if (masina_mare) {
				cout<< "Masina este mare fiind marca: " << nume;
			}
			else {
				cout<< "Masina nu este mare";
			}
		}

		 //operatorul de adunare pentru insumarea preturilor de spalare a doua masini
		 friend float operator+(const masina& m1, const masina& m2)     
		 {
			 return m1.pret_sp + m2.pret_sp;
		 }

		 //operator de negare care returneaza true daca masina nu a fost spalata in interior sau exterior
		const char* operator!()               
		{    
			 
			 if (!exterior || !interior)
				 return  "Masina este nespalata" ;
			 else
				return  "Masina este spalata" ;
		 }

		float getPret_sp() const 
		{
			return pret_sp;
		}

		float getNr_client() const 
		{
			return nr_client;
		}
		
		virtual void afiseazaDetaliiEco() const{	}

		//citire fisier text
	   void citireFisText(const char* spalatorie) {
			ifstream fisier(spalatorie);

			if (!fisier) {
				cout << "Nu exista fisierul"<<endl;
				return;
			}

			fisier >> nume >> masina_mare >> exterior >> interior >>pret_sp>> nr_client;

			fisier.close();
		}

		// scrierea datelor in fisier text
		void scriereFisText(const char* spalatorie)  {
			ofstream fisier(spalatorie);

			if (!fisier) {
				cout << "Nu exista fisierul"<<endl;
				return;
			} 
			fisier << "Nume: " << nume << endl;
			fisier << "Masina mare: " << (masina_mare ? "Da" : "Nu") << endl;
			fisier << "Exterior: " << (exterior ? "Da" : "Nu") << endl;
			fisier << "Interior: " << (interior ? "Da" : "Nu") << endl;
			fisier << "Pret spalare: " << pret_sp << endl;
			fisier << "Nr. client: " << nr_client << endl;

			fisier.close();
		}
		// Metoda pentru citirea dintr-un fișier binar
		void citireFisBinar(const char* spalatorie) {
			ifstream fisier(spalatorie, ios::binary);

			if (!fisier) {
				cout << "Nu exista fisierul" << endl;
				return;
			}

			fisier.read(reinterpret_cast<char*>(this), sizeof(*this));

			fisier.close();
		}

		// Metoda pentru scrierea într-un fișier binar
		void scriereFisBinar(const char* spalatorie) {
			ofstream fisier(spalatorie, ios::binary);

			if (!fisier) {
				cout << "Nu exista fisierul" << endl;
				return;
			}

			fisier.write(reinterpret_cast<const char*>(this), sizeof(*this));

			fisier.close();
		}
};



//o clasa care extinde clasa "masina" cu noi atribute si metode (sub forma de comentariu)

/*class masinaSpeciala : public masina {
private:
	bool vopsea_sensibila;
	bool cerinte_speciale;
	int secunde_teflon;

public:
	masinaSpeciala(const char* nume, bool masina_mare, bool exterior, bool interior, float pret_sp, int nr_client, bool vopsea_sensibila, bool cerinte_speciale, int secunde_teflon)
		: masina(nume, masina_mare, exterior, interior, pret_sp, nr_client), vopsea_sensibila(vopsea_sensibila), cerinte_speciale(cerinte_speciale), secunde_teflon(secunde_teflon) {
	}

	void afiseazaMasSpeciala() {
		cout << "Nume: " << nume << endl;
		cout << "Masina mare: " << (masina_mare ? "Da" : "Nu") << endl;
		cout << "Exterior: " << (exterior ? "Da" : "Nu") << endl;
		cout << "Interior: " << (interior ? "Da" : "Nu") << endl;
		cout << "Pret spalare: " << pret_sp << endl;
		cout << "Nr. client: " << nr_client << endl;
		cout << "Vopsea sensibila: " << (vopsea_sensibila ? "Da" : "Nu") << endl;
		cout << "Cerinte speciale: " << (cerinte_speciale ? "Da" : "Nu") << endl;
		cout << "Secunde teflon: " << secunde_teflon << endl;
	}*/

//o clasa de tip lista

class ListaMasini {
private:
	vector<masina*> masini;

public:

	void operator+=(const masina& m) {
		masina* masinaNoua = new masina(m);
		masini.push_back(masinaNoua);
	}

	void operator-=(const masina& m) {
		auto it = find_if(masini.begin(), masini.end(), [&](const masina* ptr) {
			return *ptr == m;
			});

		if (it != masini.end()) {
			delete* it;
			masini.erase(it);
		}
	}

	// Suprascrie operatorul de indexare pentru a accesa o masina în lista
	masina& operator[](int index) {
		if (index >= 0 && index < masini.size()) {
			return *masini[index];
		}
		throw out_of_range("Index invalid");
	}

	// Returneaza numarul total de masini în lista
	int getSize() const {
		return masini.size();
	}

	// Metoda pentru sortarea masinilor dupa pretul de spalare
	void sortareDupaPret() {
	
		sort(masini.begin(), masini.end(), [](const masina* a, const masina* b) {
			return a->getPret_sp() < b->getPret_sp();
			});
	}

	// Suprascrie operatorul de iesire pentru afisarea iontregii liste
	friend ostream& operator<<(ostream& out, const ListaMasini& lista) {
		for (const auto& m : lista.masini) {
			out << *m << endl;
		}
		return out;
	}

	// Destructor pentru a elibera memoria alocată dinamic pentru fiecare masină
	~ListaMasini() {
		for (const auto& m : masini) {
			delete m;
		}
	}

	//Metoda pentru afisarea masinii dupa nr_clientului
	vector<masina*> cautaDupaClient(int NrClient) const {
		vector<masina*> rezultate;
		for (const auto& m : masini) {
			if (m->getNr_client() == NrClient) {
				rezultate.push_back(m);
			}
		}
		return rezultate;
	}
	

//CERINTA 2: Modificarea clasei lista sa devina generica

/*template <typename T>
class Lista {
private:
	vector<T*> elemente;

public:
	void operator+=(const T& elem) {
		T* elemNou = new T(elem);
		elemente.push_back(elemNou);
	}

	void operator-=(const T& elem) {
		auto it = find_if(elemente.begin(), elemente.end(), [&](const T* ptr) {
			return *ptr == elem;
			});

		if (it != elemente.end()) {
			delete* it;
			elemente.erase(it);
		}
	}

	T& operator[](int index) {
		if (index >= 0 && index < elemente.size()) {
			return *elemente[index];
		}
		throw out_of_range("Index invalid");
	}

	int getSize() const {
		return elemente.size();
	}

	void sortareDupaPret() {
		sort(elemente.begin(), elemente.end(), [](const T* a, const T* b) {
			return a->getPret_sp() < b->getPret_sp();
			});
	}

	friend ostream& operator<<(ostream& out, const Lista<T>& lista) {
		for (const auto& elem : lista.elemente) {
			out << *elem << endl;
		}
		return out;
	}

	~Lista() {
		for (const auto& elem : elemente) {
			delete elem;
		}
	}

	vector<T*> cautaDupaClient(int NrClient) const {
		vector<T*> rezultate;
		for (const auto& elem : elemente) {
			if (elem->getNr_client() == NrClient) {
				rezultate.push_back(elem);
			}
		}
		return rezultate;
	}*/
};

//clasa derivata care arata virtualizare si polimorfism comentata in cod

/*class MasinaEco : public masina {
private:
	int nivel_emisii; // nivelul de emisii în grame pe kilometru

public:
	MasinaEco(const char* nume, bool masina_mare, bool exterior, bool interior, float pret_sp, int nr_client, int nivel_emisii)
		: masina(nume, masina_mare, exterior, interior, pret_sp, nr_client), nivel_emisii(nivel_emisii) {
	}

	// Suprascriere a operatorului de << pentru afisarea detaliilor masiniiEco
	friend ostream& operator<<(ostream& out, const MasinaEco& masinaEco) {
		out << (const masina&)(masinaEco); // Afișează detaliile din clasa de bază
		out << "Nivel emisii: " << masinaEco.nivel_emisii << " g/km" << endl;
		return out;
	}

	// Suprascrierea lui afiseazaDetaliiEco din clasa masina
	void afiseazaDetaliiEco() const override {
		cout << "Nivel emisii: " << nivel_emisii << " g/km" << endl;
	}*/




int main() {
	masina masina1;   //creare masina1
	
	//citirea masinii1
	cout << "Introduceti informatiile pentru prima masina:" << endl;           
	cin >> masina1;
	
	//afisarea masinii1
	cout << "Informatiile despre prima masina:" << endl;        
	cout << masina1;

	masina masina2("BMW", true, false, true, 60, 8);
	masina masina3("BMW", false, true, true, 70, 5);

	masina2.pretPremium();       // actualizarea pretului masinii2 daca este premium

	
	//compararea masinilor 2 si 3 cu ajutorul operatorilor relationali
	if (masina2 == masina3) {
		cout << "Cele doua masini sunt identice." << endl;         
	}
	else if (masina2 < masina3) {
		cout << "Masina1 are un pret mai mic pentru spalare decat Masina2." << endl;
	}
	else {
		cout << "Masina1 are un pret mai mare pentru spalare decat Masina2." << endl;
	}

	//apelarea operatorului de conversie pentru conversie in float returnand pretul
	float pret = (float)(masina2);                
	cout << "Pretul masinii este= "<< pret<<endl;
	pret = (float)(masina3);
	cout << "pretul masinii m3 este= " << pret<<endl;

	//operatorul de functie
	masina2();                

	//calculeaza suma masinilor m2 si m3 dupa acestea au primit modificari de pret
	cout << endl;                         
	cout << masina2 + masina3 << endl;         
	
	//apel operator de negare care returneaza "nespalat" daca masina este nespalata interior sau exterior si spalat daca masina este spalata interior si exterior
	const char* spalat = !masina3;        
	cout << spalat << endl;
	
//afisarea detaliilor masinii speciale masina5 
	//masinaSpeciala masina5("Golf 7", true, true, true, 80, 15, true, false, 50);
	//masina5.afiseazaMasSpeciala();
	
	masina masina8("peugeot", false, true, false, 80, 89);
	masina8.scriereFisText("spalatorie.txt");  //scrierea fisierului text spalatorie
	masina8.citireFisText("spalatorie.txt");   //citirea fisierului text spalatorie

	masina masina7("Toyota", true, true, false, 50, 15);  //creare masina7
	masina7.scriereFisBinar("masina7.bin");     //scrierea fisierului binar masina7
	masina1.citireFisBinar("masina1.bin");      //citirea fisierului binar masina7
	
	//verifiacrea in main a clasei lista generica
	/*
	Lista<masina> listaMasini;
	listaMasini += masina1;
	listaMasini += masina2;
	listaMasini += masina3;

	cout << "Lista initiala:" << endl;
	cout << listaMasini;

	listaMasini.sortareDupaPret();

	cout << "Lista sortata dupa pret:" << endl;
	cout << listaMasini;

	cout << "Numarul total de masini din lista este: " << listaMasini.getSize() << endl;

	int nrCautat;
	cout << "Introduceti numarul de client pentru cautare: ";
	cin >> nrCautat;

	vector<masina*> masiniGasite = listaMasini.cautaDupaClient(nrCautat);

	if (!masiniGasite.empty()) {
		cout << "Masinile pentru clientul cu numarul " << nrCautat << " sunt:" << endl;
		for (const auto& m : masiniGasite) {
			cout << *m << endl;
		}
	}
	else {
		cout << "Nu s-au gasit masini pentru clientul cu numarul " << nrCautat << "." << endl;
	}
	*/
	ListaMasini lista;
	masina masina6("Ford", false, true, true, 66, 78);

	//afisarea listei cu masini
	lista += masina1;                         
	lista += masina2;
	lista += masina3;

	cout << "Lista initiala:" << endl;
	cout << lista;

	//sortarea listei de masini dupa pret
	lista.sortareDupaPret();   

	cout << "Lista sortata dupa pret:" << endl;
	cout << lista;

	//afisarea nr de masini din lista
	cout << "Numarul total de masini din lista este: " << lista.getSize() << endl;    

	//apelarea functie pentru cautarea masinilor dupa nr_clientului
	int nrCautat;     
	cout << "Introduceti numarul de client pentru cautare: ";
	cin >> nrCautat;

	vector<masina*> masiniGasite = lista.cautaDupaClient(nrCautat);

	if (!masiniGasite.empty()) {
		cout << "Masinile pentru clientul cu numarul " << nrCautat << " sunt:" << endl;
		for (const auto& m : masiniGasite) {
			cout << *m << endl;
		}
	}
	else {
		cout << "Nu s-au gasit masini pentru clientul cu numarul " << nrCautat << "." << endl;
	}
	

//Verificarea in main a clasei derivate MasinaEco (coemntata)

// Creare obiect de tip MasinaEco
	//MasinaEco masinaEco1("Tesla", true, true, true, 90, 20, 0);         
	//MasinaEco masinaEco2("DaciaSolenza", true, true, true, 30, 60, 100);


// Adaugarea la lista (ListaMasini) - folosind operatorul +=
	//lista += masinaEco1;

// Afișarea listei
	//cout << "Lista cu MasinaEco:" << endl;    
	//cout << lista;

//Afisarea emisiilor masinilorEco
	//masinaEco1.afiseazaDetaliiEco();   
	//masinaEco2.afiseazaDetaliiEco();

	return 0;

};

	

	