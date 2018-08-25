#ifndef PATH_H
#define PATH_H

typedef struct
{
  double x;
  double y;
  double heading;//can be derived from x and y , but useful for storing robot point
}Point;

typedef struct
{
  Point waypoints[50];

}Path;

#endif
