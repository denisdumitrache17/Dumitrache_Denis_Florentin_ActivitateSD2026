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
	struct Telefon *vectorNou=NULL;
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = functieCopiere(vector[i]);
	}
	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
}

void copiazaAnumiteElemente(struct Telefon* vector, char nrElemente, float prag, struct Telefon** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon s;
	s.id = 1;

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
	int nrElementeCopiate = 2;
	copiazaPrimeleNElemente(vectorTelefoane, nrElemente, nrElementeCopiate);

	return 0;
}
