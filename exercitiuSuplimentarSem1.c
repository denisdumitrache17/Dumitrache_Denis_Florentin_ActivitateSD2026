#include<stdio.h>
#include<stdlib.h>

struct Adidas {
	int marime;
	int id;
	char* marca;
	char* model;
};

struct Adidas initializare(int marime, int id, const char* marca, const char* model) {
	
	struct Adidas a;
	a.marime = marime;
	a.id = id;
	a.marca = malloc((strlen(marca) + 1)*sizeof(char));
	strcpy_s(a.marca, (strlen(marca) + 1)*sizeof(char), marca);
	a.model = malloc((strlen(model) + 1) * sizeof(char));
	strcpy_s(a.model, (strlen(model) + 1) * sizeof(char), model);
	return a;

};

void afisare(struct Adidas a) {

	printf("marime: %d\n", a.marime);
	printf("id: %d\n", a.id);
	printf("marca: %s\n", a.marca);
	printf("model: %s\n", a.model);

};

void modificaModel(const char* model, struct Adidas* a) {

	free(a->model);
	a->model = malloc((strlen(model) + 1) * sizeof(char));
	strcpy_s(a->model, (strlen(model) + 1) * sizeof(char), model);

};

void dezalocare(struct Adidas a){

	free(a.marca);
	free(a.model);
	printf("memorie dezalocata");

};

int main(){

	struct Adidas a = initializare(43, 1, "Nike", "Jordan");
	afisare(a);
	modificaModel("Blazer", &a);
	afisare(a);
	int numarAdidasi = 2;
	struct Adidas* pantofiAdidasi = malloc(sizeof(struct Adidas) * numarAdidasi);
	pantofiAdidasi[0] = a;
	pantofiAdidasi[1] = initializare(37, 2, "Adidas", "Samba");
	afisare(*(pantofiAdidasi+1));
	dezalocare(a);
	return 0;

}



