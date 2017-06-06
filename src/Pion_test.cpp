#include <CppUTest/CommandLineTestRunner.h>
#include "Pion.hpp"

TEST_GROUP(GroupPion) { };
TEST(GroupPion, test_Pion_1) { // premier test unitaire
  CHECK_EQUAL(1, 1);
}
