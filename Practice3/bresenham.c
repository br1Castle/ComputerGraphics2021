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

/*
  This function send the received paramters to another function used for
  draw the lines of each face, also implements the faceHidding function and
  scanline.
*/
void
mainBresenham ()
{
  
}

/*
  This function decides how the line is gonna be drawn, according
  to its calculated slope, some of the draw functions are special
  cases for Bresenham.
*/
void
drawBresenham ()
{
 
}

/*
  This function evaluates the slope of a line.
*/
int
evaluateSlope ()
{
 
}

/*
  This function draw the line in the raster, it's the special case when
  we have a horizontal line.
*/
void
fillSpecialCase1 ()
{
  
}

/*
  This function draw the line in the raster, it's the special case when
  we have a vertical line.
*/
void
fillSpecialCase2 ()
{

}

/*
  This function draw the line in the raster, it's the special case when
  we have a positive 45 degrees line.
*/
void
fillSpecialCase3 ()
{
 
}

/*
  This function draw the line in the raster, it's the special case when
  we have a negative 45 degrees line.
*/
void
fillSpecialCase4 ()
{
  
}

/*
  This function draw the line accoirding to the evaluated slope, uses the
  main Bresenham algorithm.
*/
void
fillRasterBresenham ()
{
  
}

/*
  This function put a pixel in the Raster
*/
void
putPixel ()
{
  
}

/*
  This function create the final image, using the final Raster.
*/
void
generateImage ()
{
 
}
