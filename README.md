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

- Les rêgles du jeu:
    - Pour commencer, il faut décider du nombre maximum de manches à jouer.  
    - Un joueur (le codeur) commence par placer ses pions. Ceux-ci ne doivent pas être vus de l'autre joueur (le décodeur).
    - Le decodeur doit trouver la combinaison du codeur.
    - Il est interdit de placer deux fois le même pion dans une combinaison.
    - Pour cela, à chaque tour, le decodeur a 1 minute pour créer une combinaison.
    - Une fois les pions placés, la correction sera automatiquement faite avec : 
        * un pion blanc pour indiquer que la couleur est bien placée.
        * un pion noir pour indiquer que la couleur n'est pas bien placée.
        * rien si la couleur ne fait pas partie de la combinaison cachée.
    - Le decodeur continue ainsi en proposant sur la seconde ligne une autre combinaison, en prenant en compte les indications des languettes noires et blanches. Il a le droit à 12 essais pour déchiffrer le code.
    - Le nombre d'essais est ajouté au score du décodeur courant. Si le décodeur n'a pas réussi à trouver le code, celui-ci se voit ajouter 20 points au lieu de douze, et le codeur se voir retirer 5 points.
    - Les rôles sont alors inversés et le jeu recommence.
    - La seconde manche commence après que les deux joueurs soient passés par les deux rôles.
    - Le gagnant d’une partie de Mastermind est celui qui a le moins de points à la fin de toutes les manches.
    
