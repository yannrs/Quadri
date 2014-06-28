/**
 * Pour des raisons de performance, on utilise le c classique et pas de OO en C++
 * Lib vector
 **/
#ifndef VECTOR_H_
#define VECTOR_H_  

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
 * Structure de la matrice
 */
typedef struct {
	size_t size;            // Taille
	double* vector;         // Pointeur vers la première case du tableau
} Vector;


// Affiche la matrice
void vector_print(Vector* v);

// Initialize le vecteur avec la valeur v
void vector_initialize(Vector* v, double val);

// Crée un vecteur de taille s
Vector* vector_Alloc(size_t s);

// Détruit le vecteur et libère l'espace mémoire alloué
void vector_Free(Vector* v);

/*
 * Fonction générique applique la fonction f entre deux éléments de deux vecteurs
 * Le resultat se trouve dans result
 * double (*fx)(double, double) : est un pointeur vers une fonction qui prend en paramètre deux 
 * arguments de type double et renvoi un double
 */
void vector_op(Vector* v1, Vector* v2, Vector* result, double (*fx)(double, double) );


// Operations de base entre deux double
double add_Double(double a, double b);
double sub_Double(double a, double b);
double mult_Double(double a, double b);
double div_Double(double a, double b);


// Operations de base entre deux vecteurs
void vector_add(Vector* v1, Vector* v2);
void vector_sub(Vector* v1, Vector* v2);
void vector_mult(Vector* v1, Vector* v2);
void vector_div(Vector* v1, Vector* v2);

// Operation de base sur un vecteur
void vector_reverse(Vector* v);

#endif
