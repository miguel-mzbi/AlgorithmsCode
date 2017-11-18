#include <iostream>
#include <stack>
#include <stdlib.h>
#include <random>
#include <fstream>

using namespace std;

struct Point {
    int x, y;
};

Point pg0;

Point nextTop(stack<Point> &S) {
    Point top = S.top();
    S.pop();
    Point toReturn = S.top();
    S.push(top);
    return toReturn;
}

void swap(Point &p1, Point &p2) {
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distanceSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// 0 - p, q and r are colinear
// 1 - Clockwise
// 2 - Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) {
        return 0;  // colinear
    }
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2) {
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 
   // Find orientation
   int o = orientation(pg0, *p1, *p2);
   if (o == 0)
     return (distanceSq(pg0, *p2) >= distanceSq(pg0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}

stack<Point> graham(Point points[], int n) {
   
    // Find the bottommost point
    int yMin = points[0].y;
    int min = 0;

    for(int i = 1; i < n; i++) {
        int y = points[i].y;
    
        // Pick the bottom-most
        if(y < yMin || (yMin == y && points[i].x < points[min].x)) {
            yMin = points[i].y;
            min = i;
        }
    }
    
    // Place the bottom-most point at first position
    swap(points[0], points[min]);
    
    // Sort n-1 points with respect to the first point.
    // A point comes first if has lower polar angle (Counterclock)
    pg0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);
    
    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    int m = 1; // Initialize size of modified array
    for(int i = 1; i < n; i++) {
        while(i < n-1 && orientation(pg0, points[i], points[i+1]) == 0) {
            i++;
        }   
    
        points[m] = points[i];
        m++;
    }
    
    if (m < 3) {
        stack<Point> s;
        return s;
    }
    
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    
    for (int i = 3; i < m; i++) {
        // Keep removing if no left-turn
        while (orientation(nextTop(S), S.top(), points[i]) != 2) {
            S.pop();
        }
        S.push(points[i]);
    }

    return S;
    
    
}

int main() {

    ofstream myfile, myfileC, myfileH;
    myfile.open("GrahamResults.txt");
    myfileH.open("GrahamHulls.txt");
    myfileC.open("GrahamCoords.txt");

    int toG = 1000;

    for(int i = 10; i <= 2000; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 5000);
        
        Point points[i];
        for(int j = 0; j < i; j++) {
            Point t = {dis(gen), dis(gen)};
            if(i == toG) {
                myfileC << t.x << "," << t.y << "\n";
            }
            points[j] = t;
        }

        clock_t begin, end;
        begin = clock();
        stack<Point> S = graham(points, i);
        end = clock();
        double executionTime = (end - begin);
        myfile << i << "," << executionTime << "\n";
        cout << i << ", " << executionTime << endl;

        while (!S.empty()) {
            Point p = S.top();
            //cout << "(" << p.x << ", " << p.y <<")" << endl;
            if(i == toG) {
                myfileH << p.x << "," << p.y << "\n";
            }
            S.pop();
        }
    }

    myfile.close();
    myfileC.close();
    myfileH.close();
}