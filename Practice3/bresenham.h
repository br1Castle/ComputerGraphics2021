#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

struct pixels
{
  unsigned char rgb[3];
  double zBuffer;
  double normal;
};

struct point
{
  double x;
  double y;
  double z;
  double w;
} Point;

struct vertex
{
  int num;
  double x;
  double y;
  double z;
  double zb;
  double w;
  double hash;
};

struct edge
{
  int num;
  struct vertex *vertex1;
  struct vertex *vertex2;
  double hash;
};

struct face
{
  int num;
  struct edge *edge1;
  struct edge *edge2;
  struct edge *edge3;
};
