#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

//creare structura pentru un nod dintr-o lista dublu inlantuita

//creare structura pentru Lista Dubla 

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(ListaDubla lista) {

	Nod* p = lista.prim;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

//Nod* p = lista.prim;
//while (p) {
//	afisareMasina(p->info);
//	p = p->prev;
//}

void adaugaMasinaInLista(ListaDubla* ld, Masina masinaNoua) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = ld->ultim;
	if (ld->ultim) {
		ld->ultim->next = nou;
	}
	else {
		ld->prim = nou;
	}
	ld->ultim = nou;
}

void adaugaLaInceputInLista(ListaDubla* ld, Masina masinaNoua) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = ld->prim;
	nou->prev = NULL;
	if (ld->prim) {
		ld->prim->prev = nou;
	}
	else {
		ld->ultim = nou;
	}
	ld->prim = nou;

}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	if (f) {
		ListaDubla ld;
		ld.prim = ld.ultim = NULL;
		while (!feof(f)) {
			adaugaMasinaInLista(&ld, citireMasinaDinFisier(f));
		}
		fclose(f);
		return ld;
	}
}

void dezalocareLDMasini(ListaDubla* ld) {

	while (ld->prim && ld->prim->next) {
		Nod* temp = ld->prim;
		ld->prim = ld->prim->next;

		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}

	if (ld->prim) {
		free(ld->prim->info.model);
		free(ld->prim->info.numeSofer);
		free(ld->prim);
		ld->prim = NULL;
	}

	ld->ultim = NULL;
}

float calculeazaPretMediu(ListaDubla lista) {
	Nod* p = lista.prim;
	float suma = 0;
	int nr = 0;

	while (p) {
		suma += p->info.pret;
		nr++;
		p = p->next;
	}

	if (nr == 0) {
		return 0;
	}

	return suma / nr;
}

void stergeMasinaDupaID(ListaDubla* ld, int id) {
	Nod* p = ld->prim;

	while (p) {
		if (p->info.id == id) {

			// cazul: primul nod
			if (p->prev == NULL) {
				ld->prim = p->next;
				if (ld->prim) {
					ld->prim->prev = NULL;
				}
				else {
					ld->ultim = NULL;
				}
			}
			// cazul: ultimul nod
			else if (p->next == NULL) {
				ld->ultim = p->prev;
				ld->ultim->next = NULL;
			}
			// cazul: mijloc
			else {
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}

			free(p->info.model);
			free(p->info.numeSofer);
			free(p);
			return;
		}
		p = p->next;
	}

	/*  saau cum a scris el la seminar poate are erori idk l am scris in comentariu
	* if(ld->prim && ld->prim->info.id==ld){
		free(ld->prim->info.model);
		free(ld->prim->info.numeSofer);
		ld->prim = ld.prim->next;
		if(ld->prim) {
			free(ld->prim->prev);
		} 
		else {
		free(ld->ultim);
		ld->ultim=NULL;
		} 
		return;
	}
	Nod* p= ld->prim;
	while(p && p->info.id != id){
	p=p->next;
	} 
	if(p) {
		if(p->prev) {
			p->prev->next=p->next;
		};
		if (p->next){
			p->next->prev=p->prev;
		} 
		else {
			p->prev->next=NULL;
			ld->ultim-p->prev;
		}
		free(ld->info.model);
		free(ld->info.numeSofer);
		free(p);
	}
	*/
}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {
	if (lista.prim == NULL) {
		return NULL;
	}

	Nod* p = lista.prim;
	float max = p->info.pret;
	char* nume = p->info.numeSofer;

	p = p->next;

	while (p) {
		if (p->info.pret > max) {
			max = p->info.pret;
			nume = p->info.numeSofer;
		}
		p = p->next;
	}

	return nume;
}

int main() {

	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");

	printf("Lista initiala:\n");
	afisareListaMasini(lista);

	printf("Pret mediu: %.2f\n", calculeazaPretMediu(lista));

	char* nume = getNumeSoferMasinaScumpa(lista);
	if (nume) {
		printf("Sofer masina cea mai scumpa: %s\n", nume);
	}

	// stergere dupa ID (exemplu)
	int idDeSters = 2;
	stergeMasinaDupaID(&lista, idDeSters);

	printf("\nLista dupa stergere:\n");
	afisareListaMasini(lista);

	dezalocareLDMasini(&lista);

	return 0;
}