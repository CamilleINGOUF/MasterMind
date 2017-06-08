#include <CppUTest/CommandLineTestRunner.h>
#include "Plateau.hpp"
#include "Combinaison.hpp"
#include <sstream>
TEST_GROUP(GroupPlateau) { };
TEST(GroupPlateau, test_Plateau_1) { // premier test unitaire

  std::vector<Pion> vectP{jaune, orange, marron, noir};
  std::vector<Pion> vectP2{marron, noir,jaune, orange};
  Combinaison c(vectP);
  Combinaison c1(vectP2);
  
  std::vector<Combinaison> vectC{c,c1};
  Plateau p(vectC);
  
  CHECK(vectC[0]==c);
  CHECK(vectC[1]==c1);
}
TEST(GroupPlateau, test_Plateau_2) {

  std::vector<Pion> vectP{jaune, orange, marron, noir};
  std::vector<Pion> vectP2{marron, noir,jaune, orange};
  Combinaison c(vectP);
  Combinaison c1(vectP2);
  
  std::vector<Combinaison> vectC{c,c1};
  Plateau p(vectC);
  
  std::vector<Combinaison> vectC1=p.getCombinaisons();

  CHECK(vectC1[0]==vectC[0]);
  CHECK(vectC1[1]==vectC[1]);
}
TEST(GroupPlateau, test_Plateau_3) {

  Plateau p;
  std::vector<Pion> vectP{jaune, orange, marron, noir};
  std::vector<Pion> vectP2{marron, noir,jaune, orange};
  Combinaison c(vectP);
  Combinaison c1(vectP2);
  
  std::vector<Combinaison> vectC{c,c1};
  p.setCombinaisons(vectC);

  CHECK(vectC[0]==c);
  CHECK(vectC[1]==c1);
}
//test get an set Correction
TEST(GroupPlateau, test_Plateau_4) {

  std::vector<Pion> vectP{jaune, orange, marron, noir};
  std::vector<Pion> vectP2{marron, noir,jaune, orange};
  Combinaison c(vectP);
  Combinaison c1(vectP2);
  
  std::vector<Combinaison> vectC{c,c1};
  Plateau p(vectC);

  std::vector<Pion> Corec1{blanc, blanc, blanc, noir};
  std::vector<Pion> Corec2{noir, noir,blanc,blanc};
  Combinaison c2(Corec1);
  Combinaison c3(Corec2);
  std::vector<Combinaison> corection{c2,c3};

  p.setCorrection(corection);

  std::vector<Combinaison> check_corec=p.getCorrections();

  CHECK(corection[0]==check_corec[0]);
  CHECK(corection[1]==check_corec[1]);

}

//test addCombinaison  et getLastCombinaison
TEST(GroupPlateau, test_Plateau_5) {

  Plateau p;
  std::vector<Pion> vectP2{marron, noir,jaune, orange};
  Combinaison c1(vectP2);
  
  p.addCombinaison(c1);


  CHECK(p.getLastCombinaison()==c1);
  
}
TEST(GroupPlateau, test_Plateau_6) {
  
  std::stringstream sstream;
  for(int i=0;i<12;i++){
    sstream << ".... ....\n";
  }
  Plateau p;
  std::string strr =p.toString();

  CHECK(strr==sstream.str());

}
