Spécifications :

- réseau :
 - Client / serveur
 - peer to peer ?
 
- jeu :
 - 2 joueurs :
        * Codeur 
        * Décodeur
 - pas IA
 - 4 trous
 - 8 couleurs
 - 12 essais
 - correcteur :
        * noir -> bien placé
        * blanc -> mal placé
        * vide -> couleur pas présente
 - calcule points
        * Nombre d'essais
        * temps pour finir ?
 - Interfaces graphiques :
        * cli
        * gui
    
    
    
    
- misc : 

- les regles du jeux:
    - Pour commencer, il faut décider le nombre maximum de manches a jouer.  
    - Un joueur (le codeur) commence par placer son choix de pions sans qu'ils soient vus de l'autre joueur (decodeur) à l'arrière d'un cache qui les masquera à la vue de celui-ci jusqu'à la fin de la manche.
    - Le decodeur doit trouver quels sont les quatre pions, c'est-à-dire leurs couleurs et positions.
    - Pour cela, à chaque tour, le decodeur doit se servir de pions pour remplir une rangée selon l'idée qu'il se fait des pions dissimulés.
    - Une fois les pions placés, le codeur indique : 
        * le nombre de pions de la bonne couleur bien placés en utilisant le même nombre de pions blanc.
        * le nombre de pions de la bonne couleur, mais mal placés, avec les pions noir.
    - Le decodeur continue ainsi en proposant sur la seconde ligne une autre proposition, en prenant bien entendu en compte les indications des languettes noir et blanches. Il a droit a 12 propositions pour déchiffrer le code.
    - Le decodeur aura un nombre de point ajouter un son score egale au nombre d'essai avant de trouver la combinaisant secrete ,si il ne trouve pas la combinaisant la valeur ajoute a son score  est +20 et le codeur aura -5 point ajouter a son score.
    - Les rôles sont alors inversés et le jeu recomence.
    - la seconde manche commence apres que les deux joueur passe par les deux role.
    - Le gagnant d’une partie de Mastermind est celui qui a le moins de point.
    