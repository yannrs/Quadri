// Algorithme à implementer
//http://www.starlino.com/imu_guide.html

#ifndef POSITION_H_
#define POSITION_H_

#include "Arduino.h"


class Point{
 public:
  Point();
  Point(float x, float y, float z);
  float get_x();
  float get_y();
  float get_z();
  void set_x(float x_n);
  void set_y(float y_n);
  void set_z(float z_n);
  void set_point(float x_n, float y_n, float z_n);
  void copie_point(Point p);
  
 private:
   float x,y,z; 
  
};


#define Taille_sauvegarde 100;

// Liste/tableau circulaire. -> nombre constant de point sauvegardé. On ecrase les plus anciens.
class Liste_point{
  public:
  Liste_point();
  void ajout_point( Point p);
  Point get_point(int i);  // Renvoie le ième dernier point si i< taille, sinon null
  
  private:
  int nb_point;
  int debut, fin;
  float liste_point_x[Taille_sauvegarde];
  float liste_point_y[Taille_sauvegarde];
  float liste_point_z[Taille_sauvegarde];
};




class Position_cal{
 public:
  Position_cal();
  void actualise_position();
  Point get_position_actuel();
  Point get_position_precedente();
  Point get_position_precedente(int i);

 private:
  Point position_actuel;
  Liste_point position_sauvegarde;
    
};














#endif  
