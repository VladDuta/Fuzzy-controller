#pragma once

#define NUMAR_FUNCTII_APARTENENTA_EROARE          5
#define NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII 3


void Initializari(float functiiEroare[NUMAR_FUNCTII_APARTENENTA_EROARE],
	float functiiDerivataEroare[NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	float matriceApartenenta[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	float iesire[NUMAR_FUNCTII_APARTENENTA_EROARE]);
float triunghi(float a, float b, float c, float x);
float trapez(float a, float b, float c, float d, float x);
float CalculCentruTriunghi(float a, float b, float c, float y);
float CalculCentruTrapez(float a, float b, float c, float d, float y);
void EroareFuzificare(float e, float functiiEroare[NUMAR_FUNCTII_APARTENENTA_EROARE]);
void DerivataFuzificare(float de, float functiiDerivataEroare[NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII]);
void Inferenta(float functiiEroare[NUMAR_FUNCTII_APARTENENTA_EROARE],
	float functiiDerivataEroare[NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	float matriceApartenenta[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII]);
float Compunere(float matriceApartenenta[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	std::string reguli[NUMAR_FUNCTII_APARTENENTA_EROARE][NUMAR_FUNCTII_APARTENENTA_DERIVATA_ERORII],
	std::string variabila);
float CalculDefuzificare(float y1, float y2, float y3, float y4, float y5, float c1, float c2, float c3, float c4, float c5);
