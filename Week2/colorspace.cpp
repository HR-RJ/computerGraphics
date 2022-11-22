// compileren met 
// -std=c++11 
// of hogere standaard

#include <iostream>
#include <string>

using namespace std;
float r,g,b,c,m,y,h,s,l;

float *RGBtoCMY(float r, float g, float b) {
    // to do
    return new float[3] {c, m, y};
}

float *CMYtoRGB(float c, float m, float y) {
    // to do
    return new float[3] {r, g, b};
}

float *RGBtoHSL(float r, float g, float b) {
    // to do
    return new float[3] {h, s, l};
}

float *HSLtoRGB(float h, float s, float l) {
    // to do
    return new float[3] {r, g, b};
}

float *transparency(float r1, float g1, float b1, float alpha, float r2, float g2, float b2) {
    // to do
    return new float[3] {r, g, b};
}

string to_string(float *f) {
    return "(" + to_string(f[0]) + ", " + to_string(f[1]) + ", " + to_string(f[2]) + ")"; 
}

int main() {
    // testcode
    // let op: de beoordeling wordt gedaan op basis van andere waarden
    cout << to_string(RGBtoCMY(0.4, 0.5, 0.6)) << endl; // (0.6, 0.5, 0.4)
    cout << to_string(CMYtoRGB(0.4, 0.5, 0.6)) << endl; // (0.6, 0.5, 0.4)
    cout << to_string(RGBtoHSL(0.4, 0.5, 0.6)) << endl; // (210.0, 0.2, 0.5)
    cout << to_string(HSLtoRGB(100, 0.5, 0.6)) << endl; // (0.533, 0.8, 0.4)
    cout << to_string(transparency(0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0)) << endl; // (0.52, 0.62, 0.72)
    return 0;
}
