#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"bresenham.h"
#include"vertex.h"

int main (int argc, char *argv[])
{
 if (argc == 10)
    {
      double alfa = atof (argv[1]);
      double beta = atof (argv[2]);
      double gamma = atof (argv[3]);
      double sfX = atof (argv[4]);
      double sfY = atof (argv[5]);
      double tX = atof (argv[6]);
      double tY = atof (argv[7]);
      VLF (alfa, beta, gamma, sfX, sfY, tX, tY, argv[8], argv[9]);	
      return 0;
    }
  else
    {
      printf ("Arguments are not enough \n");
      printf ("(Or maybe you sent more)\n");
      printf ("Try with the following pattern:\n");
      printf ("./a.out alfa beta gamma sfX sfY tX tY outputName inputName\n");
      printf ("Where:\n");
      printf ("alfa\t: Rotation angle in the X axis\n");
      printf ("beta\t: Rotation angle in the Y axis\n");
      printf ("gamma\t: Rotation angle in the Z axis\n");
      printf ("sfX\t: X axis scale factor\n");
      printf ("sfY\t: Y axis scale factor\n");
      printf ("tX\t: Translation in the X axis\n");
      printf ("tY\t: Translation in the Y axis\n");
      printf ("outputName\t: The name your ppm image is going to have (Just the name, extension its not necessary)\n");
      printf ("inputName\t: The raw file name  (Add the extension Ej.: cube.raw )\n");
      printf ("An example could be:\n");
      printf ("./a.out -0.5 0.1 0.2 1200 1200 960 540 myppm cube.raw\n");
    }
}
