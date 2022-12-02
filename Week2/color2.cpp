// compileren met 
// -std=c++11 
// of hogere standaard

#include <iostream>
#include <string>

using namespace std;
float r,g,b,c,m,y,h,s,l;
float chroma;
float colorout;
float hue;
//this function is used to calculate the rgb values
float *hueconvert(float color, float temp1, float temp2){
       if (6.0*color <=1.0){
        colorout = temp2 + (temp1 - temp2) * 6 * color;
    } else if (2.0*color <=1.0){

        colorout = temp1;
    } else if (3.0*color <2.0){

        colorout = temp2 + (temp1 - temp2) * (0.666 - color) * 6;
    } else {
        colorout = temp2;
    }
    return new float {colorout};
}

float *RGBtoCMY(float r, float g, float b) {
    //CMY can be calculated by doing 1 minus the RGB value.
    //(This would be 1-(rgb/255) if the RGB value was in the standard format.)
    return new float[3] {c = 1-r , m = 1-g, y=1-b};
}

float *CMYtoRGB(float c, float m, float y) {
    //Here the same calculation can be done the only thing that changes is that its now 1-cmy.
    //If you want RGB to be in the 0-255 format you have to multiply the result by 255.
    return new float[3] {r = 1-c, g = 1-m, b = 1-y};
}

float *RGBtoHSL(float r, float g, float b) {
    /*
    You can calculate the h by finding the smallest and the biggest values from rgb.
    Then you create a temporary h by doing R - G divided by the result of the biggest value - smallest value + 4
    then you can calculate h by doing the result of the temph times 60 degrees

    you can calculate l by doing the smallest value + the largest value divided by 2

    you can calculate s by checking if l is smaller then or equal to 0.5 if that is the case you:
    get s by doing (Max-Min)/(Max + Min)
    else you need to change the second component of the formula to (2.0 - Max - Min)
    */
    float Max = max(max(r,g),b);
    float Min = min(min(r,g),b);
    chroma = Max - Min;
    float h1 = (r-g) / chroma + 4;
    h = h1 * 60; //calculate h

    l = (Min + Max) / 2; //calculate l

    if (l <= 0.5){
        s = (Max - Min)/(Max + Min);
    } else if (l <=1.0 && l > 0.5) {
        s = (Max - Min)/(2.0 - Max - Min);
    }//calculate s
    return new float[3] {h, s, l};
}

float *HSLtoRGB(float h, float s, float l) {
    /*
        In this function we calculate RGB by using the given HSL values
        First we need to make 5 temporary variables (temp1 and temp2 and a temp value for R, G and B).
        then we use these values to calculate the actual RGB colors.
    */
    float temp1;
    float temp2;
    float hue;
    float tempR, tempG, tempB;
    if (l <= 0.5){
        temp1 = l * (1.0+s);
    } else if (l > 0.5 && l <= 1.0) {
        temp1 = (l + s) - (l * s);
    }
    temp2 = 2 * l - temp1;
    hue = h / 360.0;
    tempR = hue + 0.333;
    tempG = hue;
    tempB = hue - 0.333;

    //the hue values must be between 0 and 1
    if (tempR > 1){
        tempR -= 1;
    }
    if (tempB < 1) {
        tempB += 1;
    }

    r = *hueconvert(tempR, temp1, temp2);
    g = *hueconvert(tempG, temp1, temp2);
    b = *hueconvert(tempB, temp1, temp2);

    return new float[3] {r, g, b};
}

float *transparency(float r1, float g1, float b1, float alpha, float r2, float g2, float b2) {
    /*
    Transparency can be calculated by taking the alpha * r1 +(1-alpha) * r2
    you repeat this formula for g1,g2 and b1,b2
    */
    r = alpha * r1 + (1-alpha) * r2;
    g = alpha * g1 + (1-alpha) * g2;
    b = alpha * b1 + (1-alpha) * b2;
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