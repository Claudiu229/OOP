/*Gestionarea activitatii unei companii care pune la dispozitie servicii de streaming video(filme, seriale).
atribute specifice precum: pret abonament, durata, colectie de filme, colectie de seriale
   se vor defini operatorii += si -= pentru adaugarea/eliminarea unuei productii din colectie
   definiti operatorul de conversie la double, care va returna cea mai vizionata productie
   specializati o clasa existenta pentru a gestiona diferite tipuri de productii de streaming(filme, seriale, documentare, etc.)
   implementati o metoda care determina primele cinci filme si primele cinci seriale, cele mai vizionate
   exemplificati conceptul de metoda/clasa template in c++*/

#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#include <iostream>
#include <fstream>

using namespace std;

class streaming
{
private:
	float pretAbon;
	string* colectieHorror;
	int nrFilmeColec;
	float durataFilm;
	bool abonPlatit;
	static int anInfiintare;

public:
	streaming()
	{
		pretAbon = 0;
		colectieHorror = new string[0];
		nrFilmeColec = 0;
		durataFilm = 0;
		abonPlatit = false;

	}
	streaming(float pretAbon, string* colectieHorror, int nrFilmeColec, float durataFilm, bool abonPlatit) : pretAbon(pretAbon), nrFilmeColec(nrFilmeColec), durataFilm(durataFilm), abonPlatit(abonPlatit)
	{
		this->colectieHorror = new string[this->nrFilmeColec];
		for (int i = 0; i < this->nrFilmeColec; i++)
		{
			this->colectieHorror[i] = colectieHorror[i];
		}
	}
	~streaming()
	{
		delete[] colectieHorror;
	}

	streaming(const streaming& s)
	{

		pretAbon = s.pretAbon;
		this->colectieHorror = new string[s.nrFilmeColec];
		for (int i = 0; i < s.nrFilmeColec; i++)
		{
			this->colectieHorror[i] = s.colectieHorror[i];
		}
		nrFilmeColec = s.nrFilmeColec;
		durataFilm = s.durataFilm;
		abonPlatit = s.abonPlatit;
	}

	streaming& operator=(const streaming& s)
	{
		delete[] colectieHorror;
		pretAbon = s.pretAbon;
		this->colectieHorror = new string[s.nrFilmeColec];
		for (int i = 0; i < s.nrFilmeColec; i++)
		{
			this->colectieHorror[i] = s.colectieHorror[i];
		}
		nrFilmeColec = s.nrFilmeColec;
		durataFilm = s.durataFilm;
		abonPlatit = s.abonPlatit;
		return *this;
	}

	friend ostream& operator<<(ostream& out, streaming& s)
	{
		cout << "pret abonament: " << s.pretAbon << endl;
		for (int i = 0; i < s.nrFilmeColec; i++)
			cout << "filmul nr: " << i << " din colectie este: " << s.colectieHorror[i] << endl;
		cout << "nr de filme din colectie este: " << s.nrFilmeColec << endl;
		cout << "durata filmului care va fi vizionat este: " << s.durataFilm << endl;
		cout << "abonamentul este: " << (s.abonPlatit ? "platit" : "neplatit") << endl;
		cout << " Platforma de streaming a fost infiintata in: " << streaming::anInfiintare << endl;

		return out;
	}
	streaming& operator+=(string filmNou)
	{

		string* copie = new string[nrFilmeColec];
		for (int i = 0; i < nrFilmeColec; i++)
		{
			copie[i] = colectieHorror[i];
		}
		delete[] colectieHorror;
		colectieHorror = new string[nrFilmeColec + 1];
		for (int i = 0; i < nrFilmeColec; i++)
		{
			colectieHorror[i] = copie[i];
		}
		colectieHorror[nrFilmeColec] = filmNou;
		delete[] copie;
		nrFilmeColec++;
		return *this;

	}

	streaming& operator-=(int nrFilm)
	{
		string* copie = new string[nrFilmeColec - 1];
		int j = 0;
		for (int i = 0; i < nrFilmeColec; i++)
		{
			if (i != nrFilm)
				copie[j++] = colectieHorror[i];
		}
		delete[] colectieHorror;
		colectieHorror = new string[nrFilmeColec - 1];
		for (int i = 0; i < nrFilmeColec - 1; i++)
		{
			colectieHorror[i] = copie[i];
		}
		delete[] copie;
		nrFilmeColec--;
		return *this;
	}
};

int streaming::anInfiintare = 2009;

int main()
{
	streaming s1;
	cout << s1 << endl;

	string h[] = { "last day", "judgement day", "the purge", "deadly snow" };
	streaming s2(75.6, h, 4, 120.7, true);
	cout << s2 << endl;
	s1 = s2;
	streaming s3(74, h, 4, 140, false);
	streaming s4 = s3;
	cout << s4 << endl;
	s4 += "IT";
	cout << s4;
	s3 -= 2;
	cout << s3 << endl;


}