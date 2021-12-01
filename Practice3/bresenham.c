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
translation (int n, struct vertex *vertexes, double cX, double cY, double cZ)
{
  double matrix[4][4] = {
    {1, 0, 0, -cX},
    {0, 1, 0, -cY},
    {0, 0, 1, -cZ},
    {0, 0, 0, 1}
  };
  applyMatrix (vertexes, n, matrix);
}

/*
  This function translate and project the 3D vertexes according to the focal
  distance.
*/
void
translateAndProyect (int n, struct vertex *vertexes, double cX, double cY,
		     double cZ)
{
  double matrix[4][4] = { {1, 0, 0, -cX},
  {0, 1, 0, -cY},
  {0, 0, 1, (3 * f) - cZ},
  {0, 0, 1 / f, (((3 * f) - cZ)) / f}
  };
  applyMatrix (vertexes, n, matrix);
}

/*
  This function performs a 3D rotation over the X axis
*/
void
rotationX (struct vertex *vertexes, int n, double alfa)
{
  double cx = cos (alfa * M_PI);
  double sx = sin (alfa * M_PI);
  double matrix[4][4] = { {1, 0, 0, 0},
  {0, cx, -sx, 0},
  {0, sx, cx, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexes, n, matrix);
}

/*
  This function performs a 3D rotation over the Y axis
*/
void
rotationY (struct vertex *vertexes, int n, double beta)
{
  double cy = cos (beta * M_PI);
  double sy = sin (beta * M_PI);
  double matrix[4][4] = { {cy, 0, sy, 0},
  {0, 1, 0, 0},
  {-sy, 0, cy, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexes, n, matrix); 
}

/*
  This function performs a 3D rotation over the Z axis
*/
void
rotationZ (struct vertex *vertexes, int n, double gamma)
{
  double cz = cos (gamma * M_PI);
  double sz = sin (gamma * M_PI);
  double matrix[4][4] = { {cz, -sz, 0, 0},
  {sz, cz, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexes, n, matrix);
}

/*
  This function return the 3D object to its original position after being
  moved to a convenient position to perform rotations.
*/
void
returnTranslation (struct vertex *vertexes, double cX, double cY, double cZ,
		   int n)
{
  double matrix[4][4] = { {1, 0, 0, cX},
  {0, 1, 0, cY},
  {0, 0, 1, cZ},
  {0, 0, 0, 1}
  };
  applyMatrixRT (vertexes, n, matrix);
}

/*
  This function return the translation after performing rotations
  applying the matrix.
*/
void
applyMatrixRT (struct vertex *vertexes, int n, double matrix[4][4])
{
  int i = 0;
  int j = 0;
  int op = 1;
  struct vertex aux;
  for (i = 0; i < n; i++)
    {
      aux.num = vertexes[i].num;
      aux.x = 0.0;
      aux.y = 0.0;
      aux.z = 0.0;
      aux.w = 0.0;
      aux.zb = vertexes[i].zb;
      aux.hash = vertexes[i].hash;
      for (j = 0; j < 4; j++)
	{
	  switch (op)
	    {
	    case 1:
	      aux.x += (matrix[j][0] * vertexes[i].x);
	      aux.x += (matrix[j][1] * vertexes[i].y);
	      aux.x += (matrix[j][2] * vertexes[i].z);
	      aux.x += (matrix[j][3] * vertexes[i].w);
	      op = 2;
	      break;
	    case 2:
	      aux.y += (matrix[j][0] * vertexes[i].x);
	      aux.y += (matrix[j][1] * vertexes[i].y);
	      aux.y += (matrix[j][2] * vertexes[i].z);
	      aux.y += (matrix[j][3] * vertexes[i].w);
	      op = 3;
	      break;
	    case 3:
	      aux.z += (matrix[j][0] * vertexes[i].x);
	      aux.z += (matrix[j][1] * vertexes[i].y);
	      aux.z += (matrix[j][2] * vertexes[i].z);
	      aux.z += (matrix[j][3] * vertexes[i].w);
	      op = 4;
	      break;
	    case 4:
	      aux.w += (matrix[j][0] * vertexes[i].x);
	      aux.w += (matrix[j][1] * vertexes[i].y);
	      aux.w += (matrix[j][2] * vertexes[i].z);
	      aux.w += (matrix[j][3] * vertexes[i].w);
	      op = 1;
	      break;
	    }
	}
      vertexes[i] = aux;
    }
}

/*
  This function apply the matrix to perform rotations, translations
  (to manipulate the 3D model).
*/
void
applyMatrix (struct vertex *vertexes, int n, double matrix[4][4])
{
  int i = 0;
  int j = 0;
  int op = 1;
  struct vertex aux;
  for (i = 0; i < n; i++)
    {
      aux.num = vertexes[i].num;
      aux.x = 0.0;
      aux.y = 0.0;
      aux.z = 0.0;
      aux.w = 0.0;
      aux.zb = 0.0;
      aux.hash = vertexes[i].hash;
      for (j = 0; j < 4; j++)
	{
	  switch (op)
	    {
	    case 1:
	      aux.x += (matrix[j][0] * vertexes[i].x);
	      aux.x += (matrix[j][1] * vertexes[i].y);
	      aux.x += (matrix[j][2] * vertexes[i].z);
	      aux.x += (matrix[j][3] * vertexes[i].w);
	      op = 2;
	      break;
	    case 2:
	      aux.y += (matrix[j][0] * vertexes[i].x);
	      aux.y += (matrix[j][1] * vertexes[i].y);
	      aux.y += (matrix[j][2] * vertexes[i].z);
	      aux.y += (matrix[j][3] * vertexes[i].w);
	      op = 3;
	      break;
	    case 3:
	      aux.z += (matrix[j][0] * vertexes[i].x);
	      aux.z += (matrix[j][1] * vertexes[i].y);
	      aux.z += (matrix[j][2] * vertexes[i].z);
	      aux.z += (matrix[j][3] * vertexes[i].w);
	      aux.zb += (matrix[j][0] * vertexes[i].x);
	      aux.zb += (matrix[j][1] * vertexes[i].y);
	      aux.zb += (matrix[j][2] * vertexes[i].z);
	      aux.zb += (matrix[j][3] * vertexes[i].w);
	      op = 4;
	      break;
	    case 4:
	      aux.w += (matrix[j][0] * vertexes[i].x);
	      aux.w += (matrix[j][1] * vertexes[i].y);
	      aux.w += (matrix[j][2] * vertexes[i].z);
	      aux.w += (matrix[j][3] * vertexes[i].w);
	      op = 1;
	      break;
	    }
	}
      vertexes[i] = aux;
    }
}

/*
  This function transform the 3D vertexes into 2D
*/
void
transform3D (int n, struct vertex *vertexes)
{
  int i = 0;
  for (i = 0; i < n; i++)
    {
      vertexes[i].x /= vertexes[i].w;
      vertexes[i].y /= vertexes[i].w;
      vertexes[i].z /= vertexes[i].w;
    }
}

/*
  This function scale and translate the 2D vertexes according to the 
  received parameters
*/
void
scaleAndTranslate (int n, struct vertex *vertexes, double cX, double cY,
		   double cZ, double sfX, double sfY, double tX, double tY)
{
  tX += cX;
  tY += cY;
  for (int i = 0; i < n; i++)
    {
      vertexes[i].x *= sfX;
      vertexes[i].y *= sfY;
      vertexes[i].x += tX;
      vertexes[i].y += tY;
    }
}

/*
  This function creates a Raster with a black background (rgb(0,0,0))
  And also uses Z Buffer to know if a pixel is gonna be replaced by other one
*/
struct pixels ***
createRaster ()
{
  struct pixels ***Raster;
  Raster = (struct pixels ***) malloc (1920 * sizeof (struct pixels **));
  for (int i = 0; i < 1920; i++)
    {
      Raster[i] = (struct pixels **) malloc (1080 * sizeof (struct pixels *));
      for (int j = 0; j < 1080; j++)
	{
	  Raster[i][j] =
	    (struct pixels *) malloc (3 * sizeof (struct pixels));
	  Raster[i][j]->rgb[0] = 0;
	  Raster[i][j]->rgb[1] = 0;
	  Raster[i][j]->rgb[2] = 0;
	  Raster[i][j]->zBuffer = -10000;
	}
    }
  return Raster;
}

/*
  This function cleans the Raster if something was drawn on it.
*/
void
cleanRaster (struct pixels ****Raster)
{
  for (int i = 0; i < 1920; i++)
    {
      for (int j = 0; j < 1080; j++)
	{
	  (*Raster)[i][j]->rgb[0] = 0;
	  (*Raster)[i][j]->rgb[1] = 0;
	  (*Raster)[i][j]->rgb[2] = 0;
	  (*Raster)[i][j]->zBuffer = -10000;
	}
    }  
}

/*
  This function clean the ZBuffer matrix
*/
void
cleanZBuffer (double ***ZBuffer)
{
  for (int i = 0; i < 1920; i++)
    {
      for (int j = 0; j < 1080; j++)
	{
	  (*ZBuffer)[i][j] = -10000;
	  (*ZBuffer)[i][j] = -10000;
	}
    }
}

/*
  This function calculates the normal of a face.
*/
struct vertex
getFaceNormal (struct face f, struct vertex *vertexes, struct edge *edges)
{
  struct vertex A;
  struct vertex B;
  struct vertex C;
  struct vertex normal;
  A = vertexes[edges[f.edge1->num].vertex1->num];	// Define the 3 vectors
  B = vertexes[edges[f.edge2->num].vertex1->num];
  C = vertexes[edges[f.edge3->num].vertex1->num];
  /* Calculate the normal vector */
  normal.x = (((B.y - A.y) * (C.z - B.z)) - ((B.z - A.z) * (C.y - B.y)));
  normal.y = (((B.x - A.x) * (C.z - B.z)) - ((B.z - A.z) * (C.x - B.x)));
  normal.z = (((B.x - A.x) * (C.y - B.y)) - ((B.y - A.y) * (C.x - B.x)));
  return normal;
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
