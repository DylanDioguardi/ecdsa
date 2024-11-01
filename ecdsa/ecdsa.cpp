#include "ecdsa.h"
#include <cctype>
#include <iostream>

const ap_uint_t p = 17;
const ap_uint_t A = 15;

static ap_uint_t modp(const ap_uint_t &a){
    return a%p;
}

static ap_uint_t gyaku(const ap_uint_t &a){
    ap_uint_t b = 1;
    for(ap_uint_t i=1; i < p - 1; i++){
        b = b * a;
        b = modp(b);
    }
    return b;
    // #pragma HLS PIPELINE II=1
    // ap_uint_t x = 1;
    // ap_uint_t result = 0;
    
    // for (x = 1; x < p; x++) {
    //     ap_uint_t prod = modp(a * x);
    //     result = (prod == 1) ? x : result;
    // }
    // return result;
}

bool check_point(const Point& P1, const Point& P2){
    if(P1.x == P2.x && P1.y == P2.y){
        return true;
    }
    return false;
}

Point point_add(const Point& P1, const Point& P2){
    ap_uint_t a, b, x3, y3;
    ap_uint_t x1 = P1.x;
    ap_uint_t x2 = P2.x;
    ap_uint_t y1 = P1.y;
    ap_uint_t y2 = P2.y;

    if (check_point(P1, P2)){
        return Point{0, 0};
    }    

	a=(x1-x2+p);
	a=modp(a);
	a=gyaku(a);
	b=((y1-y2+p)*a);
	b=modp(b);
	
	x3=(b*b-x1-x2+2*p);
	x3=modp(x3);

    y3=(b*(x1-x3+p))-y1+p;
	y3=modp(y3);

    Point P3 = {x3, y3};
    return P3;
}

Point point_dbl(const Point& P1){
    ap_uint_t a,b,x3,y3;
    ap_uint_t x1 = P1.x;
    ap_uint_t y1 = P1.y;

    a=(y1+y1);
	a=modp(a);
	a=gyaku(a);
	b=((3*x1*x1+A)*a);
	b=modp(b);

	x3=(b*b-x1-x1+2*p);
	x3=modp(x3);

	y3=(b*(x1-x3+p))-y1+p;
	y3=modp(y3);

    Point P3 = {x3, y3};
    return P3;
}

Point point_mult(const Point &P, const ap_uint_t &n){
    Point R = P;
    int t=5-1;
    if(n == 0){
        printf("n was 0");
        return Point {0,0};
    }
    while (n[t] == 0){
        t--;
    }
    for (int i = t - 1; i >= 0; i--) {
    std::cout << n[i] << std::endl;
    R = point_dbl(R);
    if (n[i] == 1) {
        std::cout << "point add" << std::endl;
        R = point_add(R, P);
        }
    }            
    return R;
}

void ecdsa(Point P1, Point P2, bool is_add, Point &result) {
    #pragma HLS INTERFACE s_axilite port=P1
    #pragma HLS INTERFACE s_axilite port=P2
    #pragma HLS INTERFACE s_axilite port=is_add
    #pragma HLS INTERFACE s_axilite port=result
    #pragma HLS INTERFACE s_axilite port=return

    if (is_add) {
        // Point addition
        result = point_add(P1, P2);
    } else {
        // Point doubling (when P1 = P2)
        result = point_dbl(P1);
    }
}