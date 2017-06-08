#include <CppUTest/CommandLineTestRunner.h>
#include "Pion.hpp"

TEST_GROUP(GroupPion) { };
TEST(GroupPion, test_Pion_1) { 

  Pion p;
  CHECK(p.getCouleur() == blanc);
}

TEST(GroupPion, test_Pion_2) {

  Pion p(noir);
  CHECK(p.getCouleur() == noir);
}

TEST(GroupPion, test_Pion_3) {

  Pion p;
  p.setCouleur(noir);
  CHECK(p.getCouleur() == noir);
  Pion p1(noir);
  CHECK(p == p1);
}

