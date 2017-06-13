#ifndef UTILS_HPP_
#define UTILS_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>

////////////////////////////////////////////////////////////
/// \brief Retourne un entier saisi au clavier
///
/// \param message le message d'information
/// \note Boucle tant que un entier n'a pas été saisie
/// \return Un entier saisi au clavier
///
////////////////////////////////////////////////////////////
int getIntFromInput(const std::string& message);

////////////////////////////////////////////////////////////
/// \brief Retourne une chaîne de caractères saisie au clavier
///
/// \param message le message d'information
/// \note Boucle tant que une chaîne n'a pas été saisie
/// \return Une chaîne de caractères saisie au clavier
///
////////////////////////////////////////////////////////////
std::string getStringFromInput(const std::string& message);


#endif // UTILS_HPP_
