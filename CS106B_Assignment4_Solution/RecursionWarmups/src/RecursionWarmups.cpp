// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

int countPaths(int street, int avenue) {
    // TODO: write this function
    if(street==1 && avenue==1) return 0;
    else if(street==1 && avenue!=1) return 1+countPaths(street,avenue-1);
    else if(street!=1 && avenue==1) return 1+countPaths(street-1,avenue);
    else {
        return 1+countPaths(street,avenue-1);
        return 1+countPaths(street-1,avenue);
    }
}

bool isBalanced(string exp) {
    // TODO: write this function
    int i;
    bool flag=false;
    if(exp=="") return true;
    else{
        for(i=0;i<exp.length()-1;i++) {
            if(exp[i]=='['&&exp[i+1]==']') { flag=true; break;}
            if(exp[i]=='{'&&exp[i+1]=='}') { flag=true; break;}
            if(exp[i]=='('&&exp[i+1]==')') { flag=true; break;}
        }
        if(flag) { exp.erase(i,2); return isBalanced(exp);}
        else return false;
    }
}

void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    // TODO: write this function
    double y1 = size*sqrt(3)/2 + y;
    double x1 = size/2 + x;
    double y2 = y;
    double x2 = x + size;
    if(order==1){
        gw.drawLine(x,y,x1,y1);
        gw.drawLine(x,y,x2,y2);
        gw.drawLine(x1,y1,x2,y2);
    }
    else {
        drawSierpinskiTriangle(gw,x,y,size/2,order-1);
        drawSierpinskiTriangle(gw,(x+x1)/2,(y+y1)/2,size/2,order-1);
        drawSierpinskiTriangle(gw,(x+x2)/2,(y+y2)/2,size/2,order-1);
    }
}
