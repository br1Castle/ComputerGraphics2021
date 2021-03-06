#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"bresenham.h"
#include"vertex.h"
#include"drawing.h"

static const double f = 200; /* focal distance for perpective projection */
double xIni, yIni, xEnd, yEnd;	/* Variables for Bresenham */
double slope = 0;	/* Slope */
double aux, auxZB, zbInc;	/* Some auxiliar variables */
int evaluatedSlope;	/* Evaluated slope value */

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
mainBresenham (int n, struct face *faces, struct edge *edges,
	       struct vertex *vertexes, struct pixels ***Raster, char *name)
{
  int i;
  srand (clock ());
  struct vertex faceNormal;
  double backface;
  double **ZBuffer = NULL;
  ZBuffer = createZBuffer ();
  unsigned char rgb[3], rgb2[3];
  struct pixels ***finalRaster = NULL;
  finalRaster = createRaster (); /* Final raster which is gonna be drawn */
  for (i = 0; i < n; i++)
    {
      rgb[0] = /*rand () % 255 */ 128;
      rgb[1] = /*rand () % 255 */ 249;
      rgb[2] = /*rand () % 255 */ 108;
      rgb2[0] = rand () % 255;
      rgb2[1] = rand () % 255;
      rgb2[2] = rand () % 255;
      backface = faceHidding (faces[i], vertexes, edges);
      if (backface > 90 && backface < 270)
	{
	  cleanZBuffer (&ZBuffer);
	  cleanRaster (&Raster);
	  faceNormal = getFaceNormal (faces[i], vertexes, edges);
	  drawBresenham ((int) faces[i].edge1->vertex1->x,
			 (int) faces[i].edge1->vertex1->y,
			 (int) faces[i].edge1->vertex2->x,
			 (int) faces[i].edge1->vertex2->y,
			 faces[i].edge1->vertex1->zb,
			 faces[i].edge1->vertex2->zb, Raster, rgb, ZBuffer,
			 faceNormal.z);
	  drawBresenham ((int) faces[i].edge2->vertex1->x,
			 (int) faces[i].edge2->vertex1->y,
			 (int) faces[i].edge2->vertex2->x,
			 (int) faces[i].edge2->vertex2->y,
			 faces[i].edge2->vertex1->zb,
			 faces[i].edge2->vertex2->zb, Raster, rgb, ZBuffer,
			 faceNormal.z);
	  drawBresenham ((int) faces[i].edge3->vertex1->x,
			 (int) faces[i].edge3->vertex1->y,
			 (int) faces[i].edge3->vertex2->x,
			 (int) faces[i].edge3->vertex2->y,
			 faces[i].edge3->vertex1->zb,
			 faces[i].edge3->vertex2->zb, Raster, rgb, ZBuffer,
			 faceNormal.z);
	  scanline (Raster, ZBuffer, rgb2, faceNormal);
	  for (int i = 0; i < 1920; i++)
	    {
	      for (int j = 0; j < 1080; j++)
		{
		  if (ZBuffer[i][j] > finalRaster[i][j]->zBuffer)
		    {
		      finalRaster[i][j]->rgb[0] = Raster[i][j]->rgb[0];
		      finalRaster[i][j]->rgb[1] = Raster[i][j]->rgb[1];
		      finalRaster[i][j]->rgb[2] = Raster[i][j]->rgb[2];
		      finalRaster[i][j]->zBuffer = ZBuffer[i][j];
		    }
		}
	    }
	}
    }
  generateImage (finalRaster, 1920, 1080, name);
}

/*
  This function decides how the line is gonna be drawn, according
  to its calculated slope, some of the draw functions are special
  cases for Bresenham.
*/
void
drawBresenham (double x0, double y0, double x1, double y1, double zb1,
	       double zb2, struct pixels ***Raster, unsigned char *rgb,
	       double **ZBuffer, double normal)
{
if (x1 < x0)
    {
      xIni = x1;
      yIni = y1;
      xEnd = x0;
      yEnd = y0;
      auxZB = zb1;
      zb1 = zb2;
      zb2 = auxZB;
    }
  else
    {
      xIni = x0;
      yIni = y0;
      xEnd = x1;
      yEnd = y1;
    }
  if (yEnd - yIni == 0)
    {
      fillSpecialCase1 (xIni, yIni, xEnd, yEnd, Raster,
			rgb, zb1, zb2, ZBuffer, normal);
    }
  else if (xEnd - xIni == 0)
    {
      if (yEnd < yIni)
	{
	  aux = yIni;
	  yIni = yEnd;
	  yEnd = aux;
	  auxZB = zb1;
	  zb1 = zb2;
	  zb2 = auxZB;
	}
      fillSpecialCase2 (xIni, yIni, xEnd, yEnd, Raster,
			rgb, zb1, zb2, ZBuffer, normal);
    }
  else
    {
      slope = (yEnd - yIni) / (xEnd - xIni);
      evaluatedSlope = evaluateSlope (slope);
      if (evaluatedSlope == 1)
	{
	  fillSpecialCase3 (xIni, yIni, xEnd, yEnd,
			    Raster, rgb, zb1, zb2, ZBuffer, normal);
	}
      else if (evaluatedSlope == 2)
	{
	  aux = xIni;
	  xIni = yIni;
	  yIni = aux;
	  aux = xEnd;
	  xEnd = yEnd;
	  yEnd = aux;
	  fillRasterBresenham (xIni, yIni, xEnd, yEnd,
			       Raster, evaluatedSlope, rgb, zb1, zb2,
			       ZBuffer, normal);
	}
      else if (evaluatedSlope == 3)
	{
	  aux = yIni;
	  yIni = yEnd;
	  yEnd = aux;
	  auxZB = zb1;
	  zb1 = zb2;
	  zb2 = auxZB;
	  fillRasterBresenham (xIni, yIni, xEnd, yEnd,
			       Raster, evaluatedSlope, rgb, zb1, zb2,
			       ZBuffer, normal);
	}
      else if (evaluatedSlope == 4)
	{
	  aux = xIni;
	  xIni = yEnd;
	  yEnd = xEnd;
	  xEnd = yIni;
	  yIni = aux;
	  auxZB = zb1;
	  zb1 = zb2;
	  zb2 = auxZB;
	  fillRasterBresenham (xIni, yIni, xEnd, yEnd,
			       Raster, evaluatedSlope, rgb, zb1, zb2,
			       ZBuffer, normal);
	}
      else if (evaluatedSlope == 5)
	{
	  fillSpecialCase4 (xIni, yIni, xEnd, yEnd,
			    Raster, rgb, zb1, zb2, ZBuffer, normal);
	}
      else
	{
	  fillRasterBresenham ((int) xIni, (int) yIni,
			       (int) xEnd, (int) yEnd, Raster,
			       evaluatedSlope, rgb, zb1, zb2, ZBuffer,
			       normal);
	}
    }
}

/*
  This function evaluates the slope of a line.
*/
int
evaluateSlope (double slope)
{
  if (slope > 1)		//The line is in the 2nd or 6th octect
    return 2;
  else if (slope < 0 && slope > -1)	//The line is in the 4th or 8th octect
    return 3;
  else if (slope < -1)		//The slope is in the 3rd or 7th octect
    return 4;
  else if (slope == 1)		//45 degrees positive line
    return 1;
  else if (slope == -1)		//45 degrees negative line
    return 5;
  else				//No problems, the line is in the 1st or 5th octect
    return 0;
}

/*
  This function draw the line in the raster, it's the special case when
  we have a horizontal line.
*/
void
fillSpecialCase1 (int x0, int y0, int x1, int y1,
		  struct pixels ***Raster, unsigned char *rgb, double zb1,
		  double zb2, double **ZBuffer, double normal)
{
  zbInc = (zb2 - zb1) / (x1 - x0);
  for (int i = x0; i <= x1; i++)
    {
      if (i >= 0 && i < 1920 && y0 >= 0 && y0 < 1080)
	{
	  if (ZBuffer[i][(int) y0] < zb1)
	    {
	      putPixel (i, y0, Raster, rgb, normal);
	      ZBuffer[i][(int) y0] = zb1;
	    }
	}
      zb1 += zbInc;
    }
}

/*
  This function draw the line in the raster, it's the special case when
  we have a vertical line.
*/
void
fillSpecialCase2 (int x0, int y0, int x1, int y1,
		  struct pixels ***Raster, unsigned char *rgb, double zb1,
		  double zb2, double **ZBuffer, double normal)
{
  zbInc = (zb2 - zb1) / (y1 - y0);
  for (int i = y0; i <= y1; i++)
    {
      if (x0 >= 0 && x0 < 1920 && i >= 0 && i < 1080)
	{
	  if (ZBuffer[(int) x0][i] < zb1)
	    {
	      putPixel (x0, i, Raster, rgb, normal);
	      ZBuffer[(int) x0][i] = zb1;
	    }
	}
      zb1 += zbInc;
    }
}

/*
  This function draw the line in the raster, it's the special case when
  we have a positive 45 degrees line.
*/
void
fillSpecialCase3 (int x0, int y0, int x1, int y1,
		  struct pixels ***Raster, unsigned char *rgb, double zb1,
		  double zb2, double **ZBuffer, double normal)
{
  zbInc = (zb2 - zb1) / (x1 - x0);
  for (int i = x0; i <= x1; i++)
    {
      if (i >= 0 && i < 1920 && y0 >= 0 && y0 < 1080)
	{
	  if (ZBuffer[i][(int) y0] < zb1)
	    {
	      putPixel (i, y0, Raster, rgb, normal);
	      ZBuffer[i][(int) y0] = zb1;
	    }
	}
      y0++;
      zb1 += zbInc;
    }
}

/*
  This function draw the line in the raster, it's the special case when
  we have a negative 45 degrees line.
*/
void
fillSpecialCase4 (int x0, int y0, int x1, int y1,
		  struct pixels ***Raster, unsigned char *rgb, double zb1,
		  double zb2, double **ZBuffer, double normal)
{
  zbInc = (zb2 - zb1) / (x1 - x0);
  for (int i = x0; i <= x1; i++)
    {
      if (i >= 0 && i < 1920 && y0 >= 0 && y0 < 1080)
	{
	  if (ZBuffer[i][(int) y0] < zb1)
	    {
	      putPixel (i, y0, Raster, rgb, normal);
	      ZBuffer[i][(int) y0] = zb1;
	    }
	}
      zb1 += zbInc;
      y0--;
    }
}

/*
  This function draw the line accoirding to the evaluated slope, uses the
  main Bresenham algorithm.
*/
void
fillRasterBresenham (int x0, int y0, int x1, int y1, struct pixels ***Raster,
		     int evaluatedSlope, unsigned char *rgb, double zb1,
		     double zb2, double **ZBuffer, double normal)
{
  int dx;
  int dy;
  int d;
  int incE;
  int incNE;
  dx = x1 - x0;
  dy = y1 - y0;
  d = 2 * dy - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  if (evaluatedSlope == 0)
    {
      zbInc = (zb2 - zb1) / (x1 - x0);
      if (x0 >= 0 && x0 < 1920 && y0 >= 0 && y0 < 1080)
	{
	  if (ZBuffer[x0][y0] < zb1)
	    {
	      putPixel (x0, y0, Raster, rgb, normal);
	      ZBuffer[x0][y0] = zb1;
	    }
	}
      zb1 += zbInc;
      if (x1 >= 0 && x1 < 1920 && y1 >= 0 && y1 < 1080)
	{
	  if (ZBuffer[x1][y1] < zb2)
	    {
	      putPixel (x1, y1, Raster, rgb, normal);
	      ZBuffer[x1][y1] = zb2;
	    }
	}
      for (int i = x0 + 1; i < x1; i++)
	{
	  if (d <= 0)
	    {
	      d += incE;
	    }
	  else
	    {
	      d += incNE;
	      y0++;
	    }
	  if (i >= 0 && i < 1920 && y0 >= 0 && y0 < 1080)
	    {
	      if (ZBuffer[i][y0] < zb1)
		{
		  putPixel (i, y0, Raster, rgb, normal);
		  ZBuffer[i][y0] = zb1;
		}
	    }
	  zb1 += zbInc;
	}
    }
  else if (evaluatedSlope == 2)
    {
      zbInc = (zb2 - zb1) / (x1 - x0);
      if (y0 >= 0 && y0 < 1920 && x0 >= 0 && x0 < 1080)
	{
	  if (ZBuffer[y0][x0] < zb1)
	    {
	      putPixel (y0, x0, Raster, rgb, normal);
	      ZBuffer[y0][x0] = zb1;
	    }
	}
      zb1 += zbInc;
      if (y1 >= 0 && y1 < 1920 && x1 >= 0 && x1 < 1080)
	{
	  if (ZBuffer[y1][x1] < zb2)
	    {
	      putPixel (y1, x1, Raster, rgb, normal);
	      ZBuffer[y1][x1] = zb2;
	    }
	}
      for (int i = x0 + 1; i < x1; i++)
	{
	  if (d <= 0)
	    {
	      d += incE;
	    }
	  else
	    {
	      d += incNE;
	      y0++;
	    }
	  if (y0 >= 0 && y0 < 1920 && i >= 0 && i < 1080)
	    {
	      if (ZBuffer[y0][i] < zb1)
		{
		  putPixel (y0, i, Raster, rgb, normal);
		  ZBuffer[y0][i] = zb1;
		}
	    }
	  zb1 += zbInc;
	}
    }
  else if (evaluatedSlope == 3)
    {
      zbInc = (zb2 - zb1) / (x1 - x0);
      if (x0 >= 0 && x0 < 1920 && y1 >= 0 && y1 < 1080)
	{
	  if (ZBuffer[0][y1] < zb1)
	    {
	      putPixel (x0, y1, Raster, rgb, normal);
	      ZBuffer[x0][y1] = zb1;
	    }
	}
      zb1 += zbInc;
      if (x1 >= 0 && x1 < 1920 && y0 >= 0 && y0 < 1080)
	{
	  if (ZBuffer[x1][y0] < zb2)
	    {
	      putPixel (x1, y0, Raster, rgb, normal);
	      ZBuffer[x1][y0] = zb2;
	    }
	}
      for (int i = x0 + 1; i < x1; i++)
	{
	  if (d <= 0)
	    {
	      d += incE;
	    }
	  else
	    {
	      d += incNE;
	      y1--;
	    }
	  if (i >= 0 && i < 1920 && y1 >= 0 && y1 < 1080)
	    {
	      if (ZBuffer[i][y1] < zb1)
		{
		  putPixel (i, y1, Raster, rgb, normal);
		  ZBuffer[i][y1] = zb1;
		}
	    }
	  zb1 += zbInc;
	}
    }
  else
    {
      zbInc = (zb2 - zb1) / (x1 - x0);
      if (y0 >= 0 && y0 < 1920 && x1 >= 0 && x1 < 1080)
	{
	  if (ZBuffer[y0][x1] < zb1)
	    {
	      putPixel (y0, x1, Raster, rgb, normal);
	      ZBuffer[y0][x1] = zb1;
	    }
	}
      zb1 += zbInc;
      if (y1 >= 0 && y1 < 1920 && x0 >= 0 && x0 < 1080)
	{
	  if (ZBuffer[y1][x0] < zb2)
	    {
	      putPixel (y1, x0, Raster, rgb, normal);
	      ZBuffer[y1][x0] = zb2;
	    }
	}
      for (int i = (x1 - 1); i > x0; i--)
	{
	  if (d <= 0)
	    {
	      d += incE;
	    }
	  else
	    {
	      d += incNE;
	      y0++;
	    }
	  if (y0 >= 0 && y0 < 1920 && i >= 0 && i < 1080)
	    {
	      if (ZBuffer[y0][i] < zb1)
		{
		  putPixel (y0, i, Raster, rgb, normal);
		  ZBuffer[y0][i] = zb1;
		}
	    }
	  zb1 += zbInc;
	}
    }
}

/*
  This function put a pixel in the Raster
*/
void
putPixel (int x, int y, struct pixels ***Raster, unsigned char *rgb,
	  double normal)
{
  Raster[x][y]->rgb[0] = rgb[0];
  Raster[x][y]->rgb[1] = rgb[1];
  Raster[x][y]->rgb[2] = rgb[2];
  Raster[x][y]->normal = normal;	/* Will be used for illumination. */
}

/*
  This function create the final image, using the final Raster.
*/
void
generateImage (struct pixels ***Raster, int width, int height, char *name)
{
  FILE *line;
  char ppm[50] = { };
  strcpy (ppm, name);
  strcat (ppm, ".ppm");
  line = fopen (ppm, "w");	//Creates the file (if not exists), and overwrite it (if exists)
  fprintf (line, "P3\n");
  fprintf (line, "1920 1080\n");
  fprintf (line, "255\n");
  for (int i = height - 1; i >= 0; i--)
    {
      for (int j = 0; j < width; j++)
	{
	  fprintf (line, " %d %d %d\t", Raster[j][i]->rgb[0],
		   Raster[j][i]->rgb[1], Raster[j][i]->rgb[2]);
	}
      fprintf (line, "\n");
     }
  fclose (line);
}
