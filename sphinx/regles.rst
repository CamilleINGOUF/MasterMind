========================
Les règles du MasterMind 
========================


#. Un joueur (le codeur) commence par choisir sa combinaison secrète.
#. Le décodeur doit trouver la combinaison du codeur.
#. Il est interdit de placer deux fois le même pion dans une combinaison.
#. Pour cela, à chaque tour, le décodeur crée une combinaison.
#. Une fois les pions placés, la correction sera automatiquement faite avec :
    * un pion blanc pour indiquer que la couleur est bien placée.
    * un pion noir pour indiquer que la couleur n'est pas bien placée.
    * rien si la couleur ne fait pas partie de la combinaison cachée.
#. Le décodeur continue ainsi en proposant sur la seconde ligne une autre combinaison, en prenant en compte les indications des languettes noires et blanches. Il a le droit à 12 essais pour déchiffrer le code.
#. Le nombre d'essais est ajouté au score du décodeur courant. Si le décodeur n'a pas réussi à trouver le code, celui-ci se voit ajouter 20 points au lieu de douze.
#. Les rôles sont alors inversés et le jeu recommence.
#. La seconde manche commence après que les deux joueurs soient passés par les deux rôles.
#. Le gagnant d’une partie de Mastermind est celui qui a le moins de points à la fin de toutes les manches.
