/**
 * Pour des raisons de performance, on utilise le c classique et pas de OO en C++
 * Lib matrix
 **/
#ifndef MATRIX_H_
#define MATRIX_H_  

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/*
 * Structure de la matrice
 */
typedef struct {
	size_t r;                // Nombre de lignes
	size_t c;                // Nombre de colonnes
	double** matrix;         // Pointeur vers la première case de la matrice
} Matrix;


//=================================================
//=================================================
//        Operation sur la structure matrix
//=================================================
//=================================================

// Affiche la matrice
void matrix_print(Matrix* m);

// Initialize la matrice avec la valeur v
void matrix_initialize(Matrix* m, double v);

// Crée une matrice de r lignes et c colonnes
Matrix* matrix_Alloc(size_t r, size_t c);

// Détruit la matrice et libère l'espace mémoire alloué
void matrix_Free(Matrix* m);


//=================================================
//=================================================
//        Operations sur une matrice
//=================================================
//=================================================

/*
 * Fonction générique applique la fonction f entre deux éléments des deux matrices
 * Le resultat se trouve dans result
 * double (*fx)(double, double) : est un pointeur vers une fonction qui prend en paramètre deux 
 * arguments de type double et renvoi un double
 */
void matrix_op(Matrix* m1, Matrix* m2, Matrix* result, double (*fx)(double, double) );


// Inversion
Matrix* matrix_reverse(Matrix* m);

// Matrice transposée
Matrix* matrix_transpose(Matrix* m);

// Déterminant d'une matrice
int matrix_det(Matrix* m);

// Opérations Scalaire
void matrix_scalaire_add(Matrix* m, Matrix* result, double s);
void matrix_scalaire_sub(Matrix* m, Matrix* result, double s);
void matrix_scalaire_div(Matrix* m, Matrix* result, double s);
void matrix_scalaire_mult(Matrix* m, Matrix* result, double s);


//=================================================
//=================================================
//       Operations de base entre deux matrices
//=================================================
//=================================================
void matrix_add(Matrix* m1, Matrix* m2, Matrix* result);
void matrix_sub(Matrix* m1, Matrix* m2, Matrix* result);
void matrix_div(Matrix* m1, Matrix* m2, Matrix* result);

// Produit matriciel ordinaire
Matrix* matrix_mult(Matrix* m1, Matrix* m2);

// Produit d'Hadamard
Matrix* matrix_hmult(Matrix* m1, Matrix* m2);

// Produit de Kronecker
Matrix* matrix_kmult(Matrix* m1, Matrix* m2);


// Utils
// Operations de base entre deux double
double add_Double(double a, double b);
double sub_Double(double a, double b);
double mult_Double(double a, double b);
double div_Double(double a, double b);
#endif