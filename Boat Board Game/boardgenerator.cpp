#include <array>
#include <string>
#include <fstream>
#include <cmath>


using namespace std;


const struct{
string black = " 0 0 0";
string white = " 255 255 255";
string grey = " 127 127 127";
string red = " 255 0 0";
string green = " 0 255 0";
string blue = " 0 0 255";
string yellow = " 255 255 0";
string magenta = " 255 0 255";
string cyan = " 0 255 255";
}pure;




struct{


string colorcode = " 0 0 0";


 int red {0};
 int green {0};
 int blue {0};


int * c1= &red, * c2 = &green, *c3 = &blue;


void set(int c, int s){ // red, green, blue, yellow, magenta, cyan, grayscale


if(c<3){
switch(c){
case 0:
c1 = &red, c2 = &green, c3 = &blue;
break;
case 1:
c1 = &green, c2 = &red, c3 = &blue;
break;
case 2:
c1 = &blue, c2 = &red, c3 = &green;
break;
}
if(s<256){
*c1 = s;
*c2 = 0;
*c3 = 0;
}
else{
*c1 = 255;
*c2 = s-256;
*c3 = s-256;
}
} //if(c<3)
else if(c<6){
switch(c){
case 3:
c1 = &red, c2 = &green, c3 = &blue;
break;
case 4:
c1 = &red, c2 = &blue, c3 = &green;
break;
case 5:
c1 = &green, c2 = &blue, c3 = &red;
break;
}
if(s<256){
*c1 = s;
*c2 = s;
*c3 = 0;
}
else{
*c1 = 255;
*c2 = 255;
*c3 = s-256;
}


} //else if(c<6)
else{
*c1 = c%256;
*c2 = c%256;
*c3 = c%256;
}


colorcode = ' ' + to_string(red) + ' ' + to_string(green) + ' ' + to_string(blue);


}        //set()


}shade;


int main(){
const  int boardsizex {23};        //original: 23
const  int boardsizey {15};        //original: 15




const  int squarewidth {256};
const  int imagesizex = boardsizex*squarewidth;
const  int imagesizey = boardsizey*squarewidth;
const  int borderwidth {10};


unsigned int i, i2;


//current drawing position, has to progress from top left to bottom right, in horizontal lines
int x = 0;
int y = 0;


ofstream image;
image.open("image.ppm");
image << "P3\n" << imagesizex << ' ' << imagesizey << "\n256\n";        //the first part of every .ppm file, defining type (P3), size, and color range (256 (0-255))


int draw;        //variable to select the final color to draw


int xyline, yxline;
int squarex, squarey;
int squarerelativex, squarerelativey;
int squarerelativesymmetricalx, squarerelativesymmetricaly;


array<array<unsigned char, 50>, 50> board {};


board[0][5] = 1;
board[0][6] = 1;
board[0][7] = 1;
board[0][8] = 1;
board[0][9] = 1;
board[0][10] = 1;
board[1][5] = 1;
board[1][6] = 1;
board[2][5] = 1;
board[2][6] = 1;
board[3][0] = 1;
board[3][1] = 1;
board[3][5] = 1;
board[4][0] = 1;
board[4][1] = 1;
board[4][5] = 1;
board[4][10] = 1;
board[4][11] = 1;
board[5][0] = 1;
board[5][9] = 1;
board[5][10] = 1;
board[5][11] = 1;
board[6][9] = 1;
board[6][10] = 1;
board[7][4] = 1;
board[8][4] = 1;
board[9][4] = 1;
board[9][5] = 1;
board[10][4] = 1;
board[10][5] = 1;
board[10][10] = 1;
board[11][0] = 1;
board[11][3] = 1;
board[11][4] = 1;
board[11][5] = 1;
board[11][9] = 1;
board[11][10] = 1;
board[11][11] = 1;
board[11][12] = 1;
board[12][0] = 1;
board[12][4] = 1;
board[12][5] = 1;
board[12][6] = 1;
board[12][10] = 1;
board[12][11] = 1;
board[12][12] = 1;
board[13][6] = 1;
board[13][11] = 1;
board[14][6] = 1;
board[15][14] = 1;
board[16][2] = 1;
board[16][3] = 1;
board[16][13] = 1;
board[16][14] = 1;
board[17][2] = 1;
board[17][3] = 1;
board[17][4] = 1;
board[17][8] = 1;
board[18][8] = 1;
board[18][9] = 1;
board[19][8] = 1;
board[19][9] = 1;
board[19][10] = 1;
board[21][3] = 1;
board[21][4] = 1;
board[22][3] = 1;
board[22][4] = 1;
board[22][5] = 1;
board[22][6] = 1;


board[10][3] = 2;
board[11][13] = 2;
board[12][7] = 2;
board[13][0] = 2;
board[13][9] = 2;


board[1][7] = 3;
board[22][7] = 3;


board[3][5] = 32;
board[17][9] = 33;


board[6][11] = 48;
board[18][3] = 49;




while(y < imagesizey){
draw = 0;
squarex = x/squarewidth;
squarey = y/squarewidth;
squarerelativex = x%squarewidth;
squarerelativey = y%squarewidth;
squarerelativesymmetricalx = squarerelativex - squarewidth/2;
squarerelativesymmetricaly = squarerelativey - squarewidth/2;
xyline = squarex * 100 + squarey;
yxline = squarey * 100 + squarex;


if(x%squarewidth < borderwidth|| x%squarewidth > (squarewidth-1)-borderwidth || y%squarewidth < borderwidth || y%squarewidth > (squarewidth-1)-borderwidth)
{ draw = 4; }


else if( board[squarex][squarey]==1 ) { draw = 5; }
else if( board[squarex][squarey]==2 ) { draw = 6; }
else if( board[squarex][squarey]==3) { draw = 7; }


else{ draw = 3; }












switch(draw){        //switch to select which color to draw
case 7:
shade.set(3, 200);
image << shade.colorcode;
break;
case 6:
image << pure.magenta;
break;
case 5:
shade.set(1, 220);
image << shade.colorcode;
break;
case 4:
image << pure.black;
break;
case 3:
image << pure.white;
break;
case 2:
image << pure.red;
break;
case 1:
image << pure.green;
break;
case 0:        
image << pure.blue;
break;
}


if(x<imagesizex-1) x++;
else { y++; x=0; }


}        //while(y < imagesizey)




}        //main