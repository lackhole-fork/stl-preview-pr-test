#include "preview/utility.h"

#include <complex>

#include "gtest.h"

using namespace std::literals;

struct empty {};
struct not_empty {
  int x;
};

TEST(VERSIONED(Utility), compressed_pair) {
  {
    EXPECT_EQ(sizeof(preview::compressed_pair<int      , int  >), sizeof(int) * 2);
    EXPECT_EQ(sizeof(preview::compressed_pair<empty    , int  >), sizeof(int)    );
    EXPECT_EQ(sizeof(preview::compressed_pair<int      , empty>), sizeof(int)    );
    EXPECT_EQ(sizeof(preview::compressed_pair<not_empty, int  >), sizeof(int) * 2);
    EXPECT_EQ(sizeof(preview::compressed_pair<empty    , empty>), 1);
  }

  { // ctor
    preview::compressed_pair<int, float> p1;
    EXPECT_EQ(p1.first(), 0);
    EXPECT_EQ(p1.second(), 0.f);

    preview::compressed_pair<int, double> p2{42, 3.1415};
    EXPECT_EQ(p2.first(), 42);
    EXPECT_EQ(p2.second(), 3.1415);

    preview::compressed_pair<char, int> p4{p2};
    EXPECT_EQ(p4.first(), '*');
    EXPECT_EQ(p4.second(), 3);

    preview::compressed_pair<std::complex<double>, std::string> p6
        { std::piecewise_construct, std::forward_as_tuple(0.123, 7.7), std::forward_as_tuple(10, 'a') };
    EXPECT_EQ(p6.first().real(), 0.123);
    EXPECT_EQ(p6.first().imag(), 7.7);
    EXPECT_EQ(p6.second(), "aaaaaaaaaa"s);

  }
}
