#include <iostream>
#include"regulator.h"

// Functie care realizeaza initializarea tuturor matricelor si tablourilor folosite.
void Initializari(float functiiEroare[NUMAR_FUNCTII_APARTENENTA_EROARE],
	float functiiDerivataEroare[NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	float matriceApartenenta[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	float iesire[NUMAR_FUNCTII_APARTENENTA_EROARE])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < NUMAR_FUNCTII_APARTENENTA_EROARE; i++)
	{
		functiiEroare[i] = 0;
		iesire[i] = 0;
	}

	for (i = 0; i < NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII; i++)
	{
		functiiDerivataEroare[i] = 0;
	}

	for (i = 0; i < NUMAR_FUNCTII_APARTENENTA_EROARE; i++)
	{
		for (j = 0; j < NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII; j++)
		{
			matriceApartenenta[i][j] = 0;
		}
	}
}

//Functia de apartenenta triunghi.
float triunghi(float a, float b, float c, float x)
{
	if ((x < a) || (x > c))
	{
		return 0;
	}
	else if ((x >= a) && (x <= c))
	{
		return ((x - a) / (b - a));
	}
	else
	{
		return ((c - x) / (c - b));
	}
}

//Functia de apartenenta trapez.
float trapez(float a, float b, float c, float d, float x)
{
	if (x < a)
	{
		return 0;
	}
	else if ((x >= a) && (x <= b))
	{
		return (x - a) / (b - a); //cu triunghiuri asemenea
	}
	else if ((x > b) && (x < c))
	{
		return 1; //inaltime trapez
	}
	else if ((x >= c) && (x <= d))
	{
		return (d - x) / (d - c);
	}
	else
	{
		return 0;
	}
}

//Calcularea centrelor pentru defuzificare.
float CalculCentruTriunghi(float a, float b, float c, float y)
{
	float y1, y2;
	if (y != 0)
	{
		y1 = y * (b - a) + a;
		y2 = c - (y * (c - b));

		return (y1 + y2) / 2;

	}
	else return 0;
}

float CalculCentruTrapez(float a, float b, float c, float d, float y)
{
	float y1, y2;
	if (y != 0)
	{
		y1 = y * (b - a) + a; //ec dreptei (colt stanga & varf)
		y2 = d - y * (d - c); //ec dreptei (colt dreapta & varf)

		return (y1 + y2) / 2;
	}
	else return 0;
}

/**
Functie de fuzificare a erorii.
Variabilele lingvistice folosite si definirea acestora se realizeaza in cadrul acestei functii.
NB - Negative Big
NS - Negative Small
ZE - ZEro
PS - Positive Small
PB - Positive Big
*/

void EroareFuzificare(float e, float functiiEroare[NUMAR_FUNCTII_APARTENENTA_EROARE])
{
	functiiEroare[0] = trapez(-1, -1, -0.25, -0.2, e);		//NB
	functiiEroare[1] = trapez(-0.3, -0.15, -0.1, 0, e);		//NS
	functiiEroare[2] = triunghi(-0.1, 0, 0.1, e);			//ZE
	functiiEroare[3] = trapez(0, 0.1, 0.15, 0.25, e);		//PS
	functiiEroare[4] = trapez(0.15, 0.25, 1, 1, e);		//PB
}
/**
Functie de fuzificare a derivatei erorii.
Derivata erorii este folosita pentru a putea determina semnul erorii intr-un anumit moment.
Ceea ce va ajuta foarte mult in a determina cum se comporta eroarea si ce trebuie facut pentru
a reduce eroarea.
NE - Negative
ZE - Zero
PO - Positive
*/
void DerivataFuzificare(float de, float functiiDerivataEroare[NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII])
{
	functiiDerivataEroare[0] = trapez(-1, -1, -0.9, 0, de);		//NE
	functiiDerivataEroare[1] = triunghi(-0.9, 0, 0.17, de);		//ZE
	functiiDerivataEroare[2] = trapez(0, 0.17, 1, 1, de);		//PO
}
/**
In aceasta functie se realizeaza inferenta fuzzy.
Metoda folosita presupune ca pentru construirea tabelei de inferenta sa se aleaga minimul valorii functiilor
de apartenenta ale erorii si derivatei erorii in functie de baza de reguli.
*/
void Inferenta(float functiiEroare[NUMAR_FUNCTII_APARTENENTA_EROARE],
	float functiiDerivataEroare[NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	float matriceApartenenta[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (functiiEroare[i] > functiiDerivataEroare[j])
			{
				matriceApartenenta[i][j] = functiiDerivataEroare[j];
			}
			else
			{
				matriceApartenenta[i][j] = functiiEroare[i];
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << matriceApartenenta[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//Se realizeaza functia de compunere.
float Compunere(float matriceApartenenta[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	std::string reguli[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	std::string variabila)
{
	float min = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (reguli[i][j]._Equal(variabila))
			{
				if (min < matriceApartenenta[i][j])
					min = matriceApartenenta[i][j];
			}
		}
	}
	return min;
}

//Functia care realizeaza defuzificarea.
float CalculDefuzificare(float y1, float y2, float y3, float y4,
	float y5, float c1, float c2, float c3, float c4, float c5)
{
	float defuzificare = 0;

	defuzificare = (y1 * c1 + y2 * c2 + y3 * c3 + y4 * c4 + y5 * c5) / (y1 + y2 + y3 + y4 + y5);

	return defuzificare;
}
