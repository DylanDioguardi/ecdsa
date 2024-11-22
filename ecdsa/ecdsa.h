#ifndef ECDSA_H
#define ECDSA_H

#include <ap_int.h>
#include <cstdint>
#include <utility>
#include <hls_stream.h>

#define BIT_NUM 1024
typedef ap_uint<BIT_NUM> ap_uint_t;

extern const ap_uint_t p;
extern const ap_uint_t A;

struct Point {
    ap_uint_t x;
    ap_uint_t y;
};

static ap_uint_t modp(const ap_uint_t& a);

ap_uint_t gyaku(const ap_uint_t& a);
// ap_uint_t gyaku_old(const ap_uint_t& a);

bool check_point(const Point& P1, const Point& P2);
Point point_add(const Point& P1, const Point& P2);
Point point_dbl(const Point& P1);
Point point_mult(const Point& P, const ap_uint_t& n);

struct EcdsaData {
    ap_uint_t x;
    ap_uint_t y;
    ap_uint_t scalar;
};


extern "C" {
           void ecdsa(hls::stream<Point> &point_in, hls::stream<int> &scalar_in, hls::stream<Point> &point_out);
        }
#endif // ECDSA_H