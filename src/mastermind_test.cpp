#include <CppUTest/CommandLineTestRunner.h>
#include "mastermind.hpp"

TEST_GROUP(GroupMastermind) { };
TEST(GroupMastermind, test_mastermind_1) { // premier test unitaire
  Mastermind* m=new Mastermind();
  CHECK_EQUAL(1, 1);
  delete m;
}
