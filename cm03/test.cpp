#include "OTP.hpp"
#include <chrono>
#include <gtest/gtest.h>
#include <thread>

using namespace std;

TEST(TOTP, TOTP_get) {
  auto t = unique_ptr<TOTP>(new TOTP("secret", 10));
  auto v1 = t->get();
  cerr << v1 << endl;
  this_thread::sleep_for(chrono::seconds(5));
  EXPECT_EQ(v1, t->get());
  cerr << v1 << endl;
  this_thread::sleep_for(chrono::seconds(6));
  auto v2 = t->get();
  EXPECT_NE(v1, v2);
  cerr << v2 << endl;
}

