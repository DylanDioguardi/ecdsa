#include "ecdsa.h"
#include <cctype>
#include <iostream>

const ap_uint_t p = ap_uint_t("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f",16);
const ap_uint_t A = 15;

static ap_uint_t modp(const ap_uint_t &a) { return a % p; }

ap_uint_t gyaku(const ap_uint_t &a) {
#pragma HLS INLINE
  ap_uint_t u = a;
  ap_uint_t v = p;
  ap_uint_t x1 = 1;
  ap_uint_t x2 = 0;

BINARY_GCD_LOOP:
  while (u != 1 && v != 1) {
#pragma HLS PIPELINE II = 1

    while ((u & 1) == 0) {
      u >>= 1;
      if (x1 & 1)
        x1 += p;
      x1 >>= 1;
    }

    while ((v & 1) == 0) {
      v >>= 1;
      if (x2 & 1)
        x2 += p;
      x2 >>= 1;
    }

    if (u >= v) {
      u -= v;
      if (x1 >= x2)
        x1 -= x2;
      else
        x1 = p - (x2 - x1);
    } else {
      v -= u;
      if (x2 >= x1)
        x2 -= x1;
      else
        x2 = p - (x1 - x2);
    }
  }

  return (u == 1) ? x1 : x2;
}

// ap_uint_t gyaku_old(const ap_uint_t &a) {
//   ap_uint_t b = 1;
//   for (ap_uint_t i = 1; i < p - 1; i++) {
//     b = b * a;
//     b = modp(b);
//   }
//   return b;
//   // #pragma HLS PIPELINE II=1
//   // ap_uint_t x = 1;
//   // ap_uint_t result = 0;

//   // for (x = 1; x < p; x++) {
//   //     ap_uint_t prod = modp(a * x);
//   //     result = (prod == 1) ? x : result;
//   // }
//   // return result;
// }

bool check_point(const Point &P1, const Point &P2) {
  if (P1.x == P2.x && P1.y == P2.y) {
    return true;
  }
  return false;
}

Point point_add(const Point &P1, const Point &P2) {
  ap_uint_t a, b, x3, y3;
  ap_uint_t x1 = P1.x;
  ap_uint_t x2 = P2.x;
  ap_uint_t y1 = P1.y;
  ap_uint_t y2 = P2.y;

  if (check_point(P1, P2)) {
    return Point{0, 0};
  }

  a = (x1 - x2 + p);
  a = modp(a);
  a = gyaku(a);
  b = ((y1 - y2 + p) * a);
  b = modp(b);

  x3 = (b * b - x1 - x2 + 2 * p);
  x3 = modp(x3);

  y3 = (b * (x1 - x3 + p)) - y1 + p;
  y3 = modp(y3);

  Point P3 = {x3, y3};
  return P3;
}

Point point_dbl(const Point &P1) {
  ap_uint_t a, b, x3, y3;
  ap_uint_t x1 = P1.x;
  ap_uint_t y1 = P1.y;

  a = (y1 + y1);
  a = modp(a);
  a = gyaku(a);
  b = ((3 * x1 * x1 + A) * a);
  b = modp(b);

  x3 = (b * b - x1 - x1 + 2 * p);
  x3 = modp(x3);

  y3 = (b * (x1 - x3 + p)) - y1 + p;
  y3 = modp(y3);

  Point P3 = {x3, y3};
  return P3;
}

Point point_mult(const Point &P, const ap_uint_t &n) {
  Point R = P;
  int t = BIT_NUM - 1;
  if (n == 0) {
    printf("n was 0");
    return Point{0, 0};
  }
  while (n[t] == 0) {
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

void ecdsa(volatile EcdsaData* input, volatile EcdsaData* output) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // Read input data
    Point P1_in;
    P1_in.x = input->x;
    P1_in.y = input->y;
    ap_uint_t scalar = input->scalar;
    
    // Perform point multiplication
    Point result = point_mult(P1_in, scalar);
    
    // Write output data
    output->x = result.x;
    output->y = result.y;
}

