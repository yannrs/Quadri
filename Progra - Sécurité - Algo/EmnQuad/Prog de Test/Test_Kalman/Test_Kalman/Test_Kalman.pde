/*************************************************/
/*                   Test_Kalman                 */
/*************************************************/
/*
Interface permettant de visualiser l'orientation de la centrale à inertie.
*/

import processing.serial.*; // importation de la librairie de communication serie


/*************************************************/
/*                   Variables                   */
/*************************************************/
Repere monRepere = new Repere(100, 100, 100, color(255));

Serial maConnection; // Crée un objet de communication série
int N=200;
float[] evol_x= new float[N];
float[] evol_y= new float[N];
float[] evol_z= new float[N];
int i = 0;

    // Variables Graphiques
int Temps_max = 300;
int instant = 0; // Actuel
int Amplitude_max = 50;    
    
    

/*************************************************/
/*                   Setup                       */
/*************************************************/    
void setup() {
  smooth(); //Lissage des dessins
  size(700, 600,P3D); //Taille de la fenêtre
  String NomDuPort = Serial.list()[0]; // récupère la première interface serie trouvée
    println("connection a "+NomDuPort);
    maConnection = new Serial(this, NomDuPort, 19200); // création de la connexion série
    
    for(int j = 0; j<N; j++){
     evol_x[j]=0;
     evol_y[j]=0;
     evol_z[j]=0;
    }
}


/*************************************************/
/*                   Draw                        */
/*************************************************/  
// Equivalant de loop()
void draw() {
  smooth();
  noStroke();

  //Déplacement et affichage de la balle
  monRepere.bouge();
  pushMatrix();
  monRepere.display();  
  popMatrix();
  pushMatrix();
  monRepere.graph_evolution();
  popMatrix();
  //delay(200);
}

// J'ai eu une petite fleme de faire plusieurs fichiers
/*************************************************/
/*               Classe Repere                   */
/*************************************************/  
class Repere {
  //Déclaration des paramètres de base de la balle
  float x;
  float y;
  float z;
  color couleur;

  //Constructeur de la balle
  Repere (float nouvX, float nouvY,float nouvZ, color nouvCouleur) {
    x          = nouvX;
    y          = nouvY;
    z          = nouvZ;
    couleur    = nouvCouleur;


  }

  /************   Dessin du repere  ***************/
  void display() {
    
   background(255);
   
   // On commence par faire le carré de contour
   stroke(0);
   noFill();
   rect(150,50,400,300); 
   
   translate(width/2 ,200,0);
   
   // Tourner en fonction de l'orientation de l'IMU
   rotateX(x);
   rotateY(y);
   rotateZ(z);
   
   // dessiner une boite = Centre du repère
   stroke(0);
   fill(127);
   box(25.0, 25.0, 25.0);
   
   // tracer une ligne = axe
   stroke(0,0,0);
   line(0,0,75,0);
   fill(0); // text noir
   text(" Y ",80,5);
   
   // se souvenir de cette position/orientation
   pushMatrix();
   
   // se déplacer au bout de la ligne
   translate(75,0,0);
   
   // dessiner une sphère
   stroke(0,0,0,3);
   fill(255,0,0);
   sphere(10.0);
   
   // revenir à la précedente position/orientation
   popMatrix();
 
   pushMatrix(); // resauvegarde
   
   // tracer une deuxième ligne
   stroke(0,0,0);
   line(0,0,0,75);
   fill(0); // text noir
   text(" X ",5,80);
   // se déplacer au bout de la ligne
   translate(0,75,0);
   
   // dessiner une sphère
   stroke(0,0,0,2);
   fill(255,0,0); // sphere rouge
   sphere(10.0);
   
   
   popMatrix();
   rotateX(PI/2);
   // tracer une 3eme ligne
   stroke(0,0,0);
   line(0,0,0,75);
   fill(0); // text noir
   text(" Z ",5,80);
   // se déplacer au bout de la ligne
   translate(0,75,0);
   
   // dessiner une sphère
   stroke(0,0,0,2);
   fill(255,0,0);
   sphere(10.0);
   
    
  }

  /*************** Lecture des données provenant de l'Arduino *****************/
  void bouge() {
    String[] input = (split(maConnection.readStringUntil('\n'), ',')); // Ligne par ligne, extrait les differentes zones de texte délimité par une ','
    
    if (input != null ) { //si l'input n'est pas vide
      if(input[0].equals("PitchRoll") && input.length == 4){
       x=float(input[1])*0.1 % 62; 
       y=float(input[2])*0.1 % 62; 
       //z=float(input[3]) % 62;   
      }
    }
  }


  /*************** Affichage du graphique d'évolution des paramètres d'orientation du repère *****************/
  void graph_evolution(){
    
    instant= (instant + 1) % (N-2); //Nouvelle instant
    
      evol_x[instant]= x % 62;
      evol_y[instant]= y % 62;
      evol_z[instant]= z % 62;
    
    translate(50,500,0);
    
    // Contour
    fill(241,226,190);
    stroke(0);
    rect(-30,-Amplitude_max-30, Temps_max + 110 , Amplitude_max + 100); 
    
    // Affiche les données
    for(int j=0; j<N; j++){
     stroke(0,250,0);
     line( 10 + (j)*Temps_max/N , evol_x[(j+instant) % (N-1)]*Amplitude_max/62 , 10 + (j+1)*Temps_max/N , evol_x[(j+1+instant) % (N-1)]*Amplitude_max/62);
     stroke(0,255,255);
     line( 10 + (j)*Temps_max/N , evol_y[(j+instant) % (N-1)]*Amplitude_max/62 , 10 + (j+1)*Temps_max/N , evol_y[(j+1+instant) % (N-1)]*Amplitude_max/62);
    // stroke(255,250,0);
    // line( 10 + (j)*Temps_max/N , evol_z[(j+instant) % (N-1)]*Amplitude_max/62 , 10 + (j+1)*Temps_max/N , evol_z[(j+1+instant) % (N-1)]*Amplitude_max/62);
     
    }
    
    // Les axes du repère
    int cote = 3;
    fill(0);
    stroke(0,0,0); 
    line( 10, 0, Temps_max +10 , 0);
    triangle(Temps_max +10, -cote   ,Temps_max +10 + cote*2,0,   Temps_max +10, +cote);
    text("Temps (s)", Temps_max + 20 , 10);
    
    stroke(0,0,0);
    line( 10, Amplitude_max, 10 , - Amplitude_max);
    triangle(10 - cote,- Amplitude_max,  10,- Amplitude_max-2*cote,  10+cote , - Amplitude_max);
    text("Amplitude ", -10,-Amplitude_max-10);
    
    
    // Legendes
    fill(241,226,190);
    stroke(0);
    rect(Temps_max + 130, - Amplitude_max -30, Temps_max + 100, - Amplitude_max + 120); 
    //X
    fill(0);
    stroke(0,250,0);
    line( Temps_max + 150, - Amplitude_max, Temps_max + 190,  - Amplitude_max);    
    text( " : X", Temps_max + 190,  - Amplitude_max);
    //Y
    stroke(0,255,255);
    line( Temps_max + 150, - Amplitude_max+10, Temps_max + 190,  - Amplitude_max+10);
    text( " : Y", Temps_max + 190,  - Amplitude_max+10);
    //Z
   /* stroke(255,250,0);
    line( Temps_max + 150, - Amplitude_max+20, Temps_max + 190,  - Amplitude_max+20);
    text( " : Z", Temps_max + 190,  - Amplitude_max+20);
    */
    text("Légende :", Temps_max + 150, - Amplitude_max - 15);
    
    
    //println(instant);
    
  }

  
}
