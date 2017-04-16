#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point
{
    int a, b;
};
Point P0;

Point nextToTop(stack<Point> &S)
{
    Point P = S.top();
    S.pop();
    Point res = S.top();
    S.push(P);
    return res;
}
int swap(Point &P1, Point &P2)
{
    Point temp = P1;
    P1 = P2;
    P2 = temp;
}
int distSq(Point P1, Point P2)
{
    return (P1.a - P2.a)*(P1.a - P2.a) +
          (P1.b - P2.b)*(P1.b - P2.b);
}
int orientation(Point P, Point c, Point d)
{
    int val = (c.b - P.b) * (d.a - c.a) -
              (c.a - P.a) * (d.b - c.b);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
int compare(const void *vp1, const void *vp2)
{
   Point *P1 = (Point *)vp1;
   Point *P2 = (Point *)vp2;
   int o = orientation(P0, *P1, *P2);
   if (o == 0)
     return (distSq(P0, *P2) >= distSq(P0, *P1))? -1 : 1;

   return (o == 2)? -1: 1;
}

void convexHull(Point points[], int n)
{
   int bmin = points[0].b, min = 0;
   for (int i = 1; i < n; i++)
   {
     int b = points[i].b;
     if ((b < bmin) || (bmin == b &&
         points[i].a < points[min].a))
        bmin = points[i].b, min = i;
   }
   swap(points[0], points[min]);
   P0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);


   int m = 1;
   for (int i=1; i<n; i++)
   {
       while (i < n-1 && orientation(P0, points[i],
                                    points[i+1]) == 0)
          i++;


       points[m] = points[i];
       m++;
   }
   if (m < 3) return;
   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   for (int i = 3; i < m; i++)
   {
      while (orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }
   while (!S.empty())
   {
       Point P = S.top();
       cout << "(" << P.a << ", " << P.b <<")" << endl;
       S.pop();
   }
}
int main()
{
    cout<<"enter the number of points\n";
    int n;
    cin>>n;
    cout<<"enter the points\n";
    Point points[n];
    for(int i=0;i<n;i++)
        cin>>points[i].a>>points[i].b;
    cout<<"the convex hull is\n";
    convexHull(points, n);
    return 0;
}
