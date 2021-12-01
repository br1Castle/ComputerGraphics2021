#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

static const double f = 200;
double xIni, yIni, xEnd, yEnd;
double slope = 0;
double aux, auxZB, zbInc;	
int evaluatedSlope;

/* 
  This function translate the 3D object to a convenient position to perform
  rotations using the center of the object.
*/
void
translation ()
{

}

/*
  This function translate and project the 3D vertexes according to the focal
  distance.
*/
void
translateAndProyect ()
{
  
}

/*
  This function performs a 3D rotation over the X axis
*/
void
rotationX ()
{

}

/*
  This function performs a 3D rotation over the Y axis
*/
void
rotationY ()
{
  
}

/*
  This function performs a 3D rotation over the Z axis
*/
void
rotationZ ()
{
  
}

/*
  This function return the 3D object to its original position after being
  moved to a convenient position to perform rotations.
*/
void
returnTranslation ()
{
 
}

/*
  This function return the translation after performing rotations
  applying the matrix.
*/
void
applyMatrixRT ()
{

}

/*
  This function apply the matrix to perform rotations, translations
  (to manipulate the 3D model).
*/
void
applyMatrix ()
{
 
}

/*
  This function transform the 3D vertexes into 2D
*/
void
transform3D ()
{
  

}

/*
  This function scale and translate the 2D vertexes according to the 
  received parameters
*/
void
scaleAndTranslate ()
{
  
}

/*
  This function creates a Raster with a black background (rgb(0,0,0))
  And also uses Z Buffer to know if a pixel is gonna be replaced by other one
*/
struct pixels ***
createRaster ()
{
  
}

/*
  This function cleans the Raster if something was drawn on it.
*/
void
cleanRaster ()
{
  
}

/*
  This function clean the ZBuffer matrix
*/
void
cleanZBuffer ()
{
  
}

/*
  This function calculates the normal of a face.
*/
struct vertex
getFaceNormal ()
{
  
}
