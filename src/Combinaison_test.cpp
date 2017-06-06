#include <CppUTest/CommandLineTestRunner.h>
#include "Combinaison.hpp"

TEST_GROUP(GroupCombinaison) { };

TEST(GroupCombinaison, test_Combinaison_0) {
  Combinaison c;
  std::vector<Pion> vect=c.getPions();
  vect[0]==blanc;
  vect[1]==noir;
  vect[2]==bleu;
  vect[3]==rouge;
}

//test constricteur par defaut
TEST(GroupCombinaison, test_Combinaison_1) {
  Combinaison c;
  std::vector<Pion> vect=c.getPions();
  std::vector<Pion> vect1{blanc, noir, bleu, rouge};
  for(int i=0;i<4;i++){
    CHECK(vect[i]==vect1[i]);
  }
    
}
//test constricteur: Combinaison(std::vector<Pion> pions)
TEST(GroupCombinaison, test_Combinaison_2) {

  std::vector<Pion> vect1{blanc, noir, bleu, rouge};
  Combinaison c(vect1);
  std::vector<Pion> vect=c.getPions();
  for(int i=0;i<4;i++){
    CHECK(vect[i]==vect1[i]);
  }

 
}

//test de la methode :getPions()  setPion()
TEST(GroupCombinaison, test_Combinaison_3) {

  Combinaison c;
  c.setPions("jomn");
  std::vector<Pion> vect=c.getPions();
  std::vector<Pion> vect1{jaune, orange, marron, noir};
  for(int i=0;i<4;i++){
    CHECK(vect[i]==vect1[i]);
  }
}

//test operateur d'egalite
TEST(GroupCombinaison, test_Combinaison_4) {

  Combinaison c;
  Combinaison c1;
  CHECK(c==c1);
  
}

//test operateur d'affectation
TEST(GroupCombinaison, test_Combinaison_5) {

  
  std::vector<Pion> vect1{jaune, orange, marron, noir};
  Combinaison c1(vect1);
  Combinaison c=c1;

  CHECK(c==c1);
 
}

//test de la methode toString()
TEST(GroupCombinaison, test_Combinaison_6) {
  
  std::vector<Pion> vect1{jaune, orange, marron, noir};
  Combinaison c(vect1);
  std::string str=c.toString();
  CHECK(str=="jomn");
}

