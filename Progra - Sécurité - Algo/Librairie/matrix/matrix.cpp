/**
 * Pour des raisons de performance, on utilise le c classique et pas de OO en C++
 * Lib matrix
 **/

#include "matrix.h" 
extern int errno;


/**********************************************
 * Operations de base entre deux double
 *********************************************/
double add_Double(double a, double b){return a+b;}
double sub_Double(double a, double b){return a-b;}
double mult_Double(double a, double b){return a*b;}
double div_Double(double a, double b){return a/b;}


//=================================================
//=================================================
//        Operation sur la structure matrix
//=================================================
//=================================================

/*
 * Charge une matrice depuis un fichier 
 */
Matrix* matrix_load(char* file){
	FILE *fp;
	// Ouvre le fichier
	fp = fopen(file, "r");

	if (fp == NULL){
	  printf("Can't open input file !\n");
	  return NULL;
	}

	// Lire la taille de la matrice
	int r, c;
	fscanf(fp, "%d %d", &r, &c);

	// Allocation de la matrice
	Matrix* res = matrix_Alloc(r, c);
	if(res == NULL) {
	  printf("Error creating matrix !\n");
	  return NULL;
	}

	// Remplissage de la matrice
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			if(fscanf(fp, "%lf", &(res->matrix[i][j])) == EOF) {
	  			printf("Error handling matrix !\n");
	  			return NULL;
			}

	fclose(fp);
	return res;
}


/*
 * Sauvegarde une matrice dans un fichier 
 */
void matrix_save(Matrix* m, char* file){
	FILE *fp;
	// Ouvre le fichier
	fp = fopen(file, "w");

	if (fp == NULL){
	  printf("Can't create output file !\n");
	  return;
	}

	// Ecrit les éléments de la matrice
	fprintf(fp, "%d %d\n", m->r, m->c);
	for (int i = 0; i < m->r; ++i){
		for (int j = 0; j < m->c; ++j){
			fprintf(fp, "%f ", m->matrix[i][j]);
		}
		fprintf(fp," \n");
	}
	fclose(fp);
}

/*
 * Affiche la matrice
 */
void matrix_print(Matrix* m){
	printf("\nMatrice  %d lignes  %d colonnes\n", m->r, m->c);
	for (int i = 0; i < m->r; ++i){
		for (int j = 0; j < m->c; ++j){
			printf("%f ", m->matrix[i][j]);
		}
		printf("\n");
	}
}

/*
 * Initialize la matrice avec la valeur v
 */
void matrix_initialize(Matrix* m, double v){
	for (int i = 0; i < m->r; ++i){
		for (int j = 0; j < m->c; ++j){
			m->matrix[i][j] = v;
		}
	}
/*
	for (int i = 0; i < (*m)->r; ++i){
		for (int j = 0; j < (*m)->c; ++j){
			(*m)->matrix[i][j] = v;
		}
	}
*/
}

/*
 * Crée une matrice de r lignes et c colonnes
 */
Matrix* matrix_Alloc(size_t r, size_t c){
	// Allocation de la struture pour la matrice
	Matrix* m = (Matrix*) malloc(sizeof(Matrix));
	if(m == NULL) goto error;
	
	// Allocation des lignes
	m->matrix = (double**) malloc(r*sizeof(double*));
	if(m->matrix == NULL) goto error;

	// Allocation des colonnes
	for (int i = 0; i < r; ++i){
		m->matrix[i] = (double*) malloc(c*sizeof(double));
		if(m->matrix[i] == NULL) goto error;
	}

	m->r = r;
	m->c = c;

	return m;

	error:
		puts("Malloc failed !");
		//puts(strerror(errno));
		free(m);
		return NULL;
}

/*
 * Détruit la matrice et libère l'espace mémoire alloué
 */
void matrix_Free(Matrix* m){
	for (int i = 0; i < m->r; ++i)
		free(m->matrix[i]);
	free(m->matrix);
	free(m);
}



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
void matrix_op(Matrix* m1, Matrix* m2, Matrix* result, double (*fx)(double, double) ){
	// Vérifie que les matrices ont la même taille
	if( (m1->r != m2->r | m1->r != result->r) | (m1->c != m2->c | m1->c != result->c) ) 
		puts("Operation failed !");

	for (int i = 0; i < m1->r; ++i){
		for (int j = 0; j < m1->c; ++j){
			result->matrix[i][j] = (*fx)(m1->matrix[i][j], m2->matrix[i][j]);
		}
	}
}


/*
 * Fonction générique applique la fonction f entre les éléments d'une matrice et un scalaire
 */
void matrix_scalaire_op(Matrix* m, Matrix* result, double s, double (*fx)(double, double) ){
	for (int i = 0; i < m->r; ++i){
		for (int j = 0; j < m->c; ++j)
			result->matrix[i][j] = (*fx)(m->matrix[i][j], s);
	}
}


/*
 * Déterminant d'une matrice
 */
int matrix_det(Matrix* m){
	// Calcul simple pour les matrices carrées de taille 2 et 3
	if(m->r == m->c){
		if(m->r == 2) return (m->matrix[0][0]*m->matrix[1][1])-(m->matrix[0][1]*m->matrix[1][0]);
		if(m->r == 3) return (m->matrix[0][0]*m->matrix[1][1]*m->matrix[2][2])+(m->matrix[1][0]*m->matrix[2][1]*m->matrix[0][2])+(m->matrix[2][0]*m->matrix[0][1]*m->matrix[1][2])-
							 (m->matrix[0][2]*m->matrix[1][1]*m->matrix[2][0])-(m->matrix[1][2]*m->matrix[2][1]*m->matrix[0][0])-(m->matrix[2][2]*m->matrix[0][1]*m->matrix[1][0]);
	}

	// la matrice temporaire
	Matrix *mat = matrix_Alloc(m->r, m->c);
	int det;
	int i,j;
  
	// Copie de la matrice
	for(i=0; i < m->r; i++) 
  		for(j=0; j < m->c; j++) 
 	  		mat->matrix[i][j] = m->matrix[i][j]; 

  
	// on calcule le determinant par la methode des pivots de Gauss
	// on rend la matrice triangulaire superieur tout en conservant 
	// le determinant de la matrice a chaque iteration
	det = 1; 
  
	// Parcours des lignes 
	for(j=0; j < m->r-1; j++){ 
  		int rankMax,rank; 
  		double coeffMax;
  		double coeff;
		double tmp;

		// ( etape 1 ) 
	  	rankMax = j; 
	  	for(rank=j+1; rank < m->r; rank++) 
	    	if(fabs(mat->matrix[rankMax][j]) < fabs(mat->matrix[rank][j])) 
	    		rankMax = rank; 
  
  		coeffMax = mat->matrix[rankMax][j]; 
  		if(fabs(coeffMax) <= 0.001){ 
    		det = 0.; 
    		goto label_end; 
    	} 
  		
  		// ( etape 2 ) 
  		if(rankMax != j){ 
    		for(i=j; i<m->r; i++){ 
      			tmp = mat->matrix[j][i]; 
      			mat->matrix[j][i] = mat->matrix[rankMax][i]; 
      			mat->matrix[rankMax][i] = tmp; 
      		}
    		det *= -1.; 
    	}
  
  		det *= coeffMax; 
  		// ( etape 3 ) 
  		for(rank=j+1; rank< m->r; rank++){
    		coeff = mat->matrix[rank][j]/coeffMax; 
    		for(i=j; i<m->r; i++) 
	      		mat->matrix[rank][i] -= coeff*mat->matrix[j][i]; 
    	}
  	} 
  
	det *= mat->matrix[m->r-1][m->c-1]; 
  
	// on libere <mat> 
	label_end: 
		matrix_Free(mat);
		return det; 
}


/*
 * Inversion d'une matrice
 * A Vérifier !
 */
Matrix* matrix_reverse(Matrix* m){
    // Méthode de Gauss

    // Allocation de la matrice resultat
	Matrix* res = matrix_Alloc(m->r, m->c);
    if(res == NULL) {
		printf("Error creating matrix !");
		return NULL;
    }
      
    //Initialise le resultat : res = Id
    matrix_initialize(res, 0);     
    for(int i = 0; i< res->c ; i++){
       res->matrix[i][i] = 1;
    }
              
    double coeff1 = 1;
    double coeff2 = 1;
    double aux1 = 0;
    double aux2 = 0;
    double coeff = 0;

    for(int i = 0 ; i< (m->r)-1 ; i++){
       
        // cas ou le pivot est nul, on permute 2 lignes
        if(m->matrix[i][i]==0){ 
           int h = 1;
           
            // Recherche d'un pivot non nulle, il existe car on suppose la matrice inversible
            while( i+h < m->r && m->matrix[i+h][i]==0){
              h++; 
            }
            if(i+h >= m->r) {
				printf("Matrice NON inversible - dansinversion matrice !");
				return NULL;
            }
           
            //Permutation des lignes
            for(int k = i ; k< m->c ; k++){
              aux1 = m->matrix[i][k];
              m->matrix[i][k] = m->matrix[i+h][k];
              m->matrix[i+h][k] = aux1;
              // Reapplique sur la matrice résultat
              aux2 = res->matrix[i][k];
              res->matrix[i][k] = res->matrix[i+h][k];
              res->matrix[i+h][k] = aux2;
            }
        }
       
       // Sans fraction
       	for(int j = i+1 ; j< m->r; j++){// Pour chaque ligne
        	coeff = m->matrix[j][i];
        	//coeff2 = res->matrix[j][i];
         	for(int k = 0 ; k < m->c; k++){ // On l'applique sur toute la ligne, On est obligé de commencer à 0 pour le resultat ...        
            	m->matrix[j][k] = m->matrix[i][k] * m->matrix[j][k] - coeff * m->matrix[i][k];
            	// Reapplique sur la matrice résultat            
            	res->matrix[j][k] = m->matrix[i][k] * res->matrix[j][k] - coeff * res->matrix[i][k];
        	}
       	}   
     }
   
   	//Maintenant on a une matrice triangulaire supérieur, il n'y a plus qu'à remonter
    for(int i = (m->r)-1 ; i > 1 ; i--){// On part de la fin       
       	for(int j = i-1 ; j > 0; j--){// Pour chaque ligne en remontant
        	m->matrix[j][i] = m->matrix[i][i] * m->matrix[j][i] - coeff1 * m->matrix[i][i];
        	coeff = m->matrix[j][i];
        	//coeff2 = res->matrix[j][i];
        	for(int k = m->c-1 ; k >= 0; k--){ // On l'applique sur toute la ligne          
            	res->matrix[j][k] = m->matrix[i][k] * res->matrix[j][k] - coeff * res->matrix[i][k];
         	}
       	}   
    }
   
	return res; 
}

/*
 * Matrice transposée
 */
Matrix* matrix_transpose(Matrix* m){
	// Allocation
	Matrix* res = matrix_Alloc(m->c, m->r);
	if(res == NULL) {
		printf("Error creating matrix !");
		return NULL;
	}

	for (int i = 0; i < res->r; ++i)
		for (int j = 0; j < res->c; ++j)
			res->matrix[i][j] = m->matrix[j][i];

	return res;
}

// Opérations Scalaire
void matrix_scalaire_add(Matrix* m, Matrix* result, double s){
	matrix_scalaire_op(m, result, s, add_Double);
}

void matrix_scalaire_sub(Matrix* m, Matrix* result, double s){
	matrix_scalaire_op(m, result, s, sub_Double);
}

void matrix_scalaire_div(Matrix* m, Matrix* result, double s){
	matrix_scalaire_op(m, result, s, div_Double);
}

void matrix_scalaire_mult(Matrix* m, Matrix* result, double s){
	matrix_scalaire_op(m, result, s, mult_Double);
}


//=================================================
//=================================================
//       Operations de base entre deux matrices
//=================================================
//=================================================
void matrix_add(Matrix* m1, Matrix* m2, Matrix* result){
	matrix_op(m1, m2, result, add_Double);
}

void matrix_sub(Matrix* m1, Matrix* m2, Matrix* result){
	matrix_op(m1, m2, result, sub_Double);
}

void matrix_div(Matrix* m1, Matrix* m2, Matrix* result){
	matrix_op(m1, m2, result, div_Double);
}


/*
 * Produit matriciel ordinaire
 */
Matrix* matrix_mult(Matrix* m1, Matrix* m2){
	if(m1->c != m2->r) {
		printf("Incorrect matrix size : M1 cols %d != M2 row %d",m1->c, m2->r);
		return NULL;
	}

	double tmp = 0;

	// Allocation de la matrice result
    Matrix* res = matrix_Alloc(m1->r, m2->c);
    
    // Parcours des lignes de M1
    for(int i = 0; i < m1->r; ++i){
		for(int j = 0; j < m2->c; ++j){
    		tmp = 0;
			for(int k = 0; k < m1->c; ++k)
				tmp += m1->matrix[i][k] * m2->matrix[k][j];
			res->matrix[i][j] = tmp;
    	}    	
    }
    return res;    	
}


/*
 * Produit d'Hadamard
 */
Matrix* matrix_hmult(Matrix* m1, Matrix* m2){
	matrix_op(m1, m2, m1, mult_Double);
}


/*
 * Produit de Kronecker
 * TODO : NOT WORKING CORRECTLY (Modulo pb)
 */
Matrix* matrix_kmult(Matrix* m1, Matrix* m2){
	// Allocation de la matrice resultat
	Matrix* res = matrix_Alloc(m1->r*m2->r, m1->c*m2->c);

	for (int i = 0; i < res->r; ++i){
		for (int j = 0; j < res->c; ++j){
			res->matrix[i][j] = m1->matrix[i%m2->r][j%m2->c] * m2->matrix[i%m2->r][j%m2->c];
		}
	}
	return res;
}





/*********************************
 *             Test
 ********************************/
int main(){
	printf("-----------------------------\n");
	Matrix* m1 = matrix_Alloc(3,2);
	Matrix* m2 = matrix_Alloc(2,4);
	matrix_initialize(m1, 2.0);
	matrix_initialize(m2, 3.0);

	//matrix_print(m1);
	//matrix_print(m2);
	//matrix_save(m2, "tests/m3.mat");
	//Matrix* res = matrix_kmult(m1,m2);
	Matrix* res1 = matrix_load( (char *)"tests/m1.mat");
	Matrix* res2 = matrix_load( (char *)"tests/m2.mat");
	matrix_print(res2);
	Matrix* res = matrix_transpose(res2);
	matrix_print(res);

	Matrix* res3 = matrix_load( (char *)"tests/m3.mat");
	matrix_print(res3);
	printf("det %d\n", matrix_det(res3));
	//Matrix* res4 = matrix_reverse(res3);
	//matrix_print(res4);


	free(m1);
	free(m2);

	//main2();
	return 0;
}
