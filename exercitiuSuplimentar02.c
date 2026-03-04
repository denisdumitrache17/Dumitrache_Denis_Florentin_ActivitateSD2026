#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int nivelBaterie;
	char* denumire;
	float pret;
	char clasaEnergetica;
};
struct Telefon initializare(int id, int nivelBaterie, char* denumire, float pret, char clasaEnergetica) {
	struct Telefon s;
	s.id = id;
	s.nivelBaterie = nivelBaterie;
	s.denumire = malloc((strlen(denumire) + 1) * sizeof(denumire));
	strcpy_s(s.denumire, (strlen(denumire) + 1) * sizeof(denumire), denumire);
	s.pret = pret;
	s.clasaEnergetica = clasaEnergetica;

	return s;
}

struct Telefon functieCopiere(struct Telefon t)
{
	return initializare(t.id, t.nivelBaterie, t.denumire, t.pret, t.clasaEnergetica);
}

void afisare(struct Telefon s) {
	printf("id: %d\n", s.id);
	printf("nivel baterie: %d\n", s.nivelBaterie);
	printf("denumire: %s\n", s.denumire);
	printf("pret: %.2f\n", s.pret);
	printf("clasa energetica: %c\n", s.clasaEnergetica);
}

void afisareVector(struct Telefon* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
	}
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	struct Telefon* vectorNou = malloc(nrElementeCopiate*sizeof(struct Telefon));
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = functieCopiere(vector[i]);
	}
	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	for (int i = 0; i < nrElemente; i++)
	{
		free((*vector)[i].denumire);
	}
	free(*vector);
}

void copiazaAnumiteElemente(struct Telefon* vector, char nrElemente, float pretMin, struct Telefon** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; ++i)
	{
		if (vector[i].pret < pretMin) {
			(*dimensiune)++;
		}
	}

	if (*dimensiune != 0)
	{
		int k = 0;
		*vectorNou = malloc(sizeof(struct Telefon) * (*dimensiune));
		for (int i = 0; i < nrElemente; i++)
		{
			if (vector[i].pret < pretMin) {
				(*vectorNou)[k] = functieCopiere(vector[i]);
				k++;
			}
		}
	}
	else 
		printf("Nu exista elemente cu acelasi pret!");

}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon s;
	s.id = 1;
	for (int i = 0; i < nrElemente; ++i) {
		if (strcmp(vector[i].denumire, conditie)==0)
		{
			s = functieCopiere(vector[i]);
			return s;
		}
	}

	return s;
}



int main() {
	struct Telefon t1 = initializare(1, 76, "Samsung", 3099.99, 'c');
	afisare(t1);
	int nrElemente = 3;
	struct Telefon* vectorTelefoane = malloc(nrElemente * sizeof(struct Telefon));
	vectorTelefoane[0] = t1;
	vectorTelefoane[1] = initializare(2, 87, "Iphone", 2999.32, 'a');
	*(vectorTelefoane + 2) = initializare(3, 94, "Nokia", 1329.99, 'a');
	printf("\nAfisare vector telefoane:\n");
	afisareVector(vectorTelefoane, nrElemente);
	printf("Final vector telefoane!\n");
	struct Telefon* newVector = NULL;
	int newDim = 0;
	printf("Anumite elemente:\n");
	copiazaAnumiteElemente(vectorTelefoane, nrElemente, 3000, &newVector, &newDim);
	afisareVector(newVector,newDim);
	printf("\nFinal anumite elemente\n");
	int nrElementeCopiate = 2;
	copiazaPrimeleNElemente(vectorTelefoane, nrElemente, nrElementeCopiate);
	dezalocare(&vectorTelefoane, nrElemente);


	return 0;
}
