/**
 * Pour des raisons de perforvance, on utilise le c classique et pas de OO en C++
 * Lib vector
 **/

#include "vector.h"

extern int errno;

/*
 * Affiche le vecteur
 */
void vector_print(Vector* v){
	printf("\nVecteur taille  %d\n", v->size);
	for (int i = 0; i < v->size; ++i)
			printf("%f ", v->vector[i]);
	printf("\n");
}

/*
 * Initialize le vecteur avec la valeur v
 */
void vector_initialize(Vector* v, double val){
	for (int i = 0; i < v->size; ++i)
			v->vector[i] = val;
}

/*
 * Crée un vecteur de r lignes et c colonnes
 */
Vector* vector_Alloc(size_t s){
	// Allocation de la struture pour le vecteur
	Vector* v = (Vector*) malloc(sizeof(Vector));
	if(v == NULL) goto error;
	
	// Allocation des element
	v->vector = (double*) malloc(s*sizeof(double));
	if(v->vector == NULL) goto error;	
	
	v->size = s;

	return v;

	error:
		puts("Malloc failed !");
		//puts(strerror(errno));
		free(v);
		return NULL;
}

/*
 * Détruit le vecteur et libère l'espace mévoire alloué
 */
void vector_Free(Vector* v){
	free(v->vector);
	free(v);
}


/*
 * Fonction générique applique la fonction f entre deux éléments de deux vecteurs
 * Le resultat se trouve dans result
 * double (*fx)(double, double) : est un pointeur vers une fonction qui prend en paramètre deux 
 * arguments de type double et renvoi un double
 */
void vector_op(Vector* v1, Vector* v2, Vector* result, double (*fx)(double, double) ){
	// Vérifie que les vecteurs ont la mêve taille
	if( (v1->size != v2->size | v1->size != result->size) ) goto error;

	for (int i = 0; i < v1->size; ++i)
			result->vector[i] = (*fx)(v1->vector[i], v2->vector[i]);
	return;
	error:
		puts("Operation failed !");
		//puts(strerror(errno));
}

/**********************************************
 * Operations de base entre deux double
 *********************************************/
double add_Double(double a, double b){return a+b;}
double sub_Double(double a, double b){return a-b;}
double mult_Double(double a, double b){return a*b;}
double div_Double(double a, double b){return a/b;}


/**********************************************
 * Operations de base entre deux vatrices
 *********************************************/
void vector_add(Vector* v1, Vector* v2){
	vector_op(v1, v2, v1, add_Double);
}

void vector_sub(Vector* v1, Vector* v2){
	vector_op(v1, v2, v1, sub_Double);
}

void vector_mult(Vector* v1, Vector* v2){
	vector_op(v1, v2, v1, mult_Double);
}

void vector_div(Vector* v1, Vector* v2){
	vector_op(v1, v2, v1, div_Double);
}




/*********************************
 *             Test
 ********************************/
int main2(){
	printf("-----------------------------\n");
	Vector* v1 = vector_Alloc(3);
	Vector* v2 = vector_Alloc(3);
	vector_initialize(v1, 2.0);
	vector_initialize(v2, 3.0);

	vector_print(v1);
	vector_print(v2);
	vector_mult(v1, v2);
	vector_print(v1);

	free(v1);
	free(v2);
	return 0;
}
