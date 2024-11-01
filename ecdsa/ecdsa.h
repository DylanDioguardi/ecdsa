#ifndef ECDSA_H
#define ECDSA_H

#include <ap_int.h>
#include <cstdint>
#include <utility>

#define BIT_NUM 1024
typedef ap_uint<BIT_NUM> ap_uint_t;
extern const ap_uint_t p;
extern const ap_uint_t A;

struct Point {
    ap_uint_t x;
    ap_uint_t y;
};

static ap_uint_t modp(const ap_uint_t& a);
static ap_uint_t gyaku(const ap_uint_t& a);

bool check_point(const Point& P1, const Point& P2);
Point point_add(const Point& P1, const Point& P2);
Point point_dbl(const Point& P1);
Point point_mult(const Point& P, const ap_uint_t& n);

void ecdsa(Point P1, Point P2, bool is_add, Point &result);

#endif // ECDSA_H