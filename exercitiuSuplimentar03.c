#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraTelefon {
	int id;
	int nrSim; //numarPortiere
	float pret;
	char* model;
	char* numeUtilizator; //numeSofer
	unsigned char serie;
};
typedef struct StructuraTelefon Telefon;

void afisareTelefon(Telefon telefon) {
	printf("id:%d\n", telefon.id);
	printf("numar simuri:%d\n", telefon.nrSim);
	printf("pret:%.2f\n", telefon.pret);
	printf("model:%s\n", telefon.model);
	printf("nume utilizator:%s\n", telefon.numeUtilizator);
	printf("serie:%c\n", telefon.serie);
}

void afisareVectorTelefoane(Telefon* telefoane, int nrTelefoane) {
	for (int i = 0; i < nrTelefoane; i++)
	{
		afisareTelefon(telefoane[i]);
	}
}

void adaugaMasinaInVector(Telefon** telefoane, int * nrTelefoane, Telefon telefonNou) {

	Telefon* aux = malloc(sizeof(Telefon) * (*nrTelefoane + 1));

	for (int i = 0; i < (*nrTelefoane); i++)
	{
		aux[i] = (*telefoane)[i];
	}

	aux[*nrTelefoane] = telefonNou; //shallow copy
	free(*telefoane);
	(*telefoane) = aux;
	++(*nrTelefoane);

}

Telefon citireTelefonFisier(FILE* file) {
	Telefon t;
	char sep[4] = ",;\n";
	char buffer[100];
	fgets(buffer, 100, file);
	t.id = atoi(strtok(buffer, sep));
	t.nrSim = atoi(strtok(NULL,sep));
	t.pret = atof(strtok(NULL, sep));
	char* aux;
	aux = strtok(NULL, sep);
	t.model = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(t.model, (strlen(aux) + 1), aux);
	aux = strtok(NULL, sep);
	t.numeUtilizator = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(t.numeUtilizator, (strlen(aux) + 1), aux);
	t.serie = strtok(NULL, sep)[0];
	return t;
	
}

Telefon* citireVectorTelefoaneFisier(const char* numeFisier, int* nrMasiniCitite) {

	fopen(numeFisier, "r");
	Telefon* vectorTelefoane = NULL;
	*nrMasiniCitite = 0;
	Telefon aux;
	while (!feof(numeFisier))
	{
		adaugaMasinaInVector(&vectorTelefoane, nrMasiniCitite, citireTelefonFisier(numeFisier));
	}
	fclose(numeFisier);
	return vectorTelefoane;
}

void dezalocareVectorMasini(Telefon** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {
	FILE* file = fopen("telefoane.txt", "r");
	Telefon telefon = citireTelefonFisier(file);
	afisareTelefon(telefon);
	int nrTelefoane = 0;
	Telefon* telefoane = citireVectorTelefoaneFisier(file, &nrTelefoane);
	afisareVectorTelefoane(telefoane, nrTelefoane);
	return 0;
}
