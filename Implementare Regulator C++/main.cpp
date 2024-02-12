#include <iostream>
#include <string>
#include"regulator.h"


int main()
{
	float functiiEroare[NUMAR_FUNCTII_APARTENENTA_EROARE];
	float functiiDerivataEroare[NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII];
	float iesire[NUMAR_FUNCTII_APARTENENTA_EROARE];
	float matriceApartenenta[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII];
	float e, de;

	Initializari(functiiEroare, functiiDerivataEroare, matriceApartenenta, iesire);
	float c1, c2, c3, c4, c5;

	std::string reguli[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII] =
	{ { "NB", "NB", "NB" },
	{ "NB", "NB", "NS" },
	{ "PS", "PS", "NS" },
	{ "PB" ,"PB", "PB" },
	{ "PB", "PB", "PB" } };

	std::cout << "Introduceti o valoare pentru eroare (intre -1 si 1):" << std::endl;
	std::cout << "e = ";
	std::cin >> e;

	std::cout << "Valoarea derivatei erorii (intre -1 si 1): " << std::endl;
	std::cout << "de = ";
	std::cin >> de;
	std::cout << std::endl;

	EroareFuzificare(e, functiiEroare);
	DerivataFuzificare(de, functiiDerivataEroare);

	std::string variabile[] = { "NB", "NS", "ZE", "PS", "PB" };
	std::cout << "Aparteneta eroare." << std::endl;
	for (int i = 0; i < NUMAR_FUNCTII_APARTENENTA_EROARE; i++)
	{
		std::cout << e << " apartine " << functiiEroare[i] << " " + variabile[i] << std::endl;
	}
	std::cout << std::endl;

	std::string variabileDerivata[] = { "NE", "ZE", "PO" };
	std::cout << "Aparteneta derivata eroare" << std::endl;
	for (int i = 0; i < NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII; i++)
	{
		std::cout << de << " apartine " << functiiDerivataEroare[i] << " " + variabileDerivata[i] << std::endl;
	}

	//Se determina tabela de inferenta.
	std::cout << std::endl;
	std::cout << "Tabela de inferenta" << std::endl;
	Inferenta(functiiEroare, functiiDerivataEroare, matriceApartenenta);

	//Se realizeaza compunerea.
	for (int i = 0; i < NUMAR_FUNCTII_APARTENENTA_EROARE; i++)
	{
		iesire[i] = Compunere(matriceApartenenta, reguli, variabile[i]);
	}

	//Se calculeaza centrele.
	c1 = CalculCentruTrapez(-1, -1, -0.25, -0.15, iesire[0]);
	c2 = CalculCentruTrapez(-0.25, -0.15, -0.1, -0, iesire[1]);
	c3 = CalculCentruTriunghi(-0.1, 0, 0.2, iesire[2]);
	c4 = CalculCentruTrapez(0, 0.2, 0.6, 0.9, iesire[3]);
	c5 = CalculCentruTrapez(0.6, 0.9, 1, 1, iesire[4]);

	// Rezultatul defuzificarii.
	std::cout << std::endl;
	std::cout << "Defuzificare = " << CalculDefuzificare(iesire[0], iesire[1], iesire[2], iesire[3],
		iesire[4], c1, c2, c3, c4, c5) << std::endl;

	system("pause");
	return 0;
}
