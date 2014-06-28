// Algorithme à implementer
//http://www.starlino.com/imu_guide.html


#include "Arduino.h"
#include "Position_v2.h"

          // Methode de la class Point

Point::Point(){
  x=0;
  y=0;
  z=0;  
}

Point::Point(float x_n, float y_n, float z_n){
  x=x_n;
  y=y_n;
  z=z_n;
}

float Point::get_x(){
  return x;
}
float Point::get_y(){
  return y;
}
float Point::get_z(){
  return z;
}
void Point::set_x(float x_n){
    x=x_n;
}
void Point::set_y(float y_n){
    y=y_n;
}
void Point::set_z(float z_n){
    z=z_n;
}
void Point::set_point(float x_n, float y_n, float z_n){
  x=x_n;
  y=y_n;
  z=z_n;
}
void Point::copie_point(Point p){
  x=p.get_x();
  y=p.get_y();
  z=p.get_z();
}

                
                
// Objectif de cette class : enregistrer les Taille_total dernière position dans un tableau. -> tableau circulaire
Liste_point::Liste_point(){
 nb_point=0;
 debut = 0;
 fin = 0;
 
  
 /*for(int i =0; i< Taille_sauvegarde;i++}{
   liste_point_x[i]=0;
   liste_point_y[i]=0;
   liste_point_z[i]=0;
 }*/
}


void Liste_point::ajout_point( Point p){
    //liste_point_x[fin]= p.get_x();
    //liste_point_y[fin]= p.get_y();
    //liste_point_z[fin]= p.get_z();
    
    if(nb_point == Taille_sauvegarde){// signifie que l'on a déjà rempli le tableau
      fin=debut;
      debut++;
      
      if(debut==Taille_sauvegarde){
      debut = 0;
      }
      
    }
    else{
      nb_point++;
      fin++;
      if(fin==Taille_sauvegarde){
      fin = 0;
      debut = 1;
      }
      
    }
}

// Renvoie le point de l'instant t-i*dt
Point Liste_point::get_point(int i){
  Point p()//(list_point_x[(debut+i)%Taille_sauvegarde],list_point_y[(debut+i)%Taille_sauvegarde],list_point_z[(debut+i)%Taille_sauvegarde]);
 return p;  
}



                                        // Methode de la class Position
// Enregistre et calcul la position du quad grâce à la centrale à inertie.
Position_cal::Position_cal(): position_actuel(), position_sauvegarde();
{
}

Position_cal::Position_cal(int taille_sauvegarde): position_actuel(), position_sauvegarde(taille_sauvegarde);
{
}



void Position_cal::actualise_position(){
  // algorithme de //http://www.starlino.com/imu_guide.html
  
  
  // Accès aux données du Gyroscope
  gyro.read();
  float x_gyro = gyro.g.x;
  float y_gyro = gyro.g.y;
  float z_gyro = gyro.g.z;
  
  // Accès aux données de l'Accéléromètre
  int x_accel,y_accel,z_accel;  
  adxl.readAccel(&x_accel, &y_accel, &z_accel); //read the accelerometer values and store them in variables  x,y,z
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
}




Point Position_cal::get_position_actuel(){
 return position_actuel;  
}

Point Position_cal::get_position_precedente(){
 return position_sauvegarde.get_point(0);  
}

Point Position_cal::get_position_precedente(int i){
 return position_sauvegarde.get_point(i);  
}








