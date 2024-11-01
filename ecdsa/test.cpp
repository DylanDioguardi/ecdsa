#include "ecdsa.h"
#include <iostream>
#include <stdio.h>



int main(void){
    ap_uint<5> n ("18", 10) ;
    printf("n[0]:");
    std::cout << n[0]<< std::endl;
    printf("n[0]:");
    std::cout << n[0]<< std::endl;
    printf("n[1]:");
    std::cout << n[1]<< std::endl;
    printf("n[2]:");
    std::cout << n[2]<< std::endl;
    printf("n[3]:");
    std::cout << n[3]<< std::endl;
    printf("n[4]:");
    std::cout << n[4]<< std::endl;
    std::cout << n << std::endl;

    if(n[0] == true){
        printf("abc");
    }

	ap_uint_t X[18];
	ap_uint_t Y[18];
	ap_uint_t x1,x2,x3,x4,x4_1,x5;
	ap_uint_t y1,y2,y3,y4,y5;
	ap_uint_t r1,r2,r3;
	ap_uint_t A=15;
	ap_uint_t B=8;
	
	//P4=(P1+P2)+P3;
	//P5=P1+)P2+P3);
	
	srand(18);
	
	X[0]=0;
	X[1]=0;
	X[2]=4;
	X[3]=4;
	X[4]=5;
	X[5]=5;
	X[6]=6;
	X[7]=6;
	X[8]=10;
	X[9]=10;
	X[10]=11;
	X[11]=11;
	X[12]=14;
	X[13]=14;
	X[14]=15;
	X[15]=15;
	X[16]=16;
	X[17]=16;
	Y[0]=5;
	Y[1]=12;
	Y[2]=8;
	Y[3]=9;
	Y[4]=2;
	Y[5]=15;
	Y[6]=5;
	Y[7]=12;
	Y[8]=16;
	Y[9]=11;
	Y[10]=5;
	Y[11]=12;
	Y[12]=2;
	Y[13]=15;
	Y[14]=2;
	Y[15]=15;
	Y[16]=3;
	Y[17]=14;
	
	// r1=rand()%18;
	// r2=rand()%18;
	// r3=rand()%18;
	r1=5;
    r2=11;
    r3=13;
    std::cout << "r1=" << r1 << ", r2=" << r2 << ", r3=" << r3 << std::endl;

	x1=X[r1];
	x2=X[r2];
	x3=X[r3];
	y1=Y[r1];
	y2=Y[r2];
	y3=Y[r3];
	
    std::cout << "P1=(" << x1 << ", " << y1 << ")" << std::endl;
    std::cout << "P2=(" << x2 << ", " << y2 << ")" << std::endl;  
    std::cout << "P3=(" << x3 << ", " << y3 << ")" << std::endl;


	// x4=point_dblx(x1,y1,A);
    // y4=point_dbly(x1,y1,A);
    Point P1 = {x1, y1};
    Point P2 = {x2, y2};
    Point P3 = {x3, y3};
    Point P4, P4_1, P5, P5_1;

    P4 = point_add(P1, P2);
    P4_1 = point_add(P3, P4);
    P5 = point_add(P2, P3);
    P5_1 = point_add(P1, P5);

    std::cout << "P4=(" << P4.x << ", " << P4.y << ")" << std::endl;
    std::cout << "P4_1=(" << P4_1.x << ", " << P4_1.y << ")" << std::endl;
    std::cout << "P5=(" << P5.x << ", " << P5.y << ")" << std::endl;
    std::cout << "P5_1=(" << P5_1.x << ", " << P5_1.y << ")" << std::endl;
	// x4_1=point_addx(x3,y3,x4,y4);
	// y4=point_addy(x3,y3,x4,y4);
	// printf("P4=(%d, %d)\n",x4_1,y4);
	
    // unsigned int x5_1;
	// x5=point_addx(x2,y2,x3,y3);
	// y5=point_addy(x2,y2,x3,y3);
	// printf("P5'=(%d, %d)\n",x5,y5);
	// x5_1=point_addx(x1,y1,x5,y5);
	// y5=point_addy(x1,y1,x5,y5);
	// printf("P5=(%d, %d)\n",x5_1,y5);

    Point nP;
    nP = point_mult(P1, 6);
    std::cout << "nP=(" << nP.x << ", " << nP.y << ")" << std::endl;

	return 0;
}
