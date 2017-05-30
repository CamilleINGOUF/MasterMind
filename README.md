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

- les regles du jeu:
    - Pour commencer, il faut décider du nombre maximum de manches à jouer.  
    - Un joueur (le codeur) commence par placer son choix de pions sans qu'ils soient vus de l'autre joueur (decodeur) à l'arrière d'un cache qui les masquera de la vue de celui-ci jusqu'à la fin de la manche.
    - Le decodeur doit trouver quels sont les quatre pions, c'est-à-dire leurs couleurs et positions.
    - Pour cela, à chaque tour, le decodeur a 1 minute pour se servir des pions et remplir une rangée selon l'idée qu'il se fait des pions dissimulés.
    - Une fois les pions placés, la correction sera automatiquement faite avec : 
        * un pion blanc pour indiquer que la couleur est bien placée.
        * un pion noir pour indiquer que la couleur n'est pas bien placée.
        * rien si la couleur ne fait pas partie de la combinaison cachée.
    - Le decodeur continue ainsi en proposant sur la seconde ligne une autre combinaison, en prenant en compte les indications des languettes noires et blanches. Il a droit à 12 propositions pour déchiffrer le code.
    - Le decodeur aura un nombre de point ajouter, à son score, égale au nombre d'essais pour trouver la combinaisant secrete ,s'il ne trouve pas la combinaisont, la valeur ajoutée à son score  est de 20 point et le codeur aura -5 point à son score.
    - Les rôles sont alors inversés et le jeu recommence.
    - la seconde manche commence après que les deux joueurs passent par les deux rôles.
    - Le gagnant d’une partie de Mastermind est celui qui a le moins de points à la fin de toutes les manches.
    
