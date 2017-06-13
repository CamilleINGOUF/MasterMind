#include <CppUTest/CommandLineTestRunner.h>
#include "Mastermind.hpp"
#include "Combinaison.hpp"

TEST_GROUP(GroupMastermind) { };
TEST(GroupMastermind, test_mastermind_1) {
  
  Mastermind m;
  m.setNbManches(3);
  m.setCurrentNbManches(2);
  std::vector<Pion> vectP{jaune, orange, marron, noir};
  std::vector<Pion> vectP2{marron, noir,jaune, orange};
  Combinaison c(vectP);
  Combinaison c1(vectP2);
  
  std::vector<Combinaison> vectC{c,c1};
  Plateau p(vectC);
  m.setPlateau(p);

  m.setNomJoueurA("max");
  m.setNomJoueurB("mix");
  m.setScoreJoueurA(33);
  m.setScoreJoueurB(22);
  m.setGagnantNom("mix");
  m.setCodeSecret(vectP);
  
  CHECK(m.getNbManches()==3);
  CHECK(m.getCurrentNbManches()==2);

  std::vector<Combinaison> vectC2=m.getPlateau().getCombinaisons();
  
  CHECK(vectC2[0] == c);
  CHECK(vectC2[1] == c1);

  CHECK(m.getNomJoueurA() == "max");
  CHECK(m.getNomJoueurB() == "mix");
  CHECK(m.getScoreJoueurA() == 33);
  CHECK(m.getScoreJoueurB() == 22);
  CHECK(m.getCodeSecret() == vectP);
  
}
//test de la methode  ajoutPoints
TEST(GroupMastermind, test_mastermind_2) {

    Mastermind m;
    m.setScoreJoueurB(22);
    m.ajoutPoints(Joueur::B,2);

    CHECK(m.getScoreJoueurB() == 24);
}

//test de la methode partieTerminee
TEST(GroupMastermind, test_mastermind_3) {

    Mastermind m;
    m.setNbManches(0);
    CHECK(m.partieTerminee());
}

//test de la methode inverserRoles et getDecodeur
TEST(GroupMastermind, test_mastermind_4) {
    Mastermind m;
  
    CHECK(m.getDecodeur() == Joueur::B);
    m.inverserRoles();
    CHECK(m.getDecodeur() == Joueur::A);
}

//test de la methode plateauVide
TEST(GroupMastermind, test_mastermind_5)
{
    Mastermind m;
    CHECK(m.plateauVide());
}
