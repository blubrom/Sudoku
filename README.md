# Sudoku
Solveur et générateur de grilles de Sudoku en C basé sur l'algorithme de backtracking
Le programme permet d'enregistrer la grille générée dans un fichier texte au nom choisi par l'utilisateur

# présentation du projet

<p allign ="justify">Le jeu de Sudoku n’est plus à présenter, avec une grille de 9*9 décomposée en 9 blocs de 3*3. De nombreuses personnes recherchent des solutions par eux même et j’ai eu l’envie de construire un programme permettant de résoudre n’importe quelle grille.</p> 

<p allign ="justify"> <br />Pour ce faire j’ai utilisé l’algorithme de <b>backtracking</b>, qui consiste en la recherche d’une solution par l’exploration des différents coups possibles en revenant sur un embranchement précédent pour suivre le chemin suivant jusqu’à atteindre une solution (ou avoir testé toutes les possibilités s’il n’en existe pas). Je n’ai pas créé d’interface graphique, je rentre la grille sous forme d’un tableau bi-dimensionnel et le programme m’affiche la grille complétée.</p>
<p allign ="justify"><b>Après avoir implémenté le solveur, je me suis intéressé à la génération de grilles de Sudoku valides</b> (c’est à dire, une grille avec une solution unique). Pour ce faire, j’ai  essayé une première méthode consistant, à partir d’une grille vide, à remplir case par case aléatoirement (dans le respect des règles) jusqu’à n’obtenir qu’une seule solution. Le problème de cette méthode est qu’elle ne garantit pas l’obtention d’une grille valide. En effet, il est possible de ne jouer que des coups valides à partir d’une grille vide et d’arriver à une grille n’ayant aucune solution. </p>
<p allign ="justify">C’est pourquoi je me suis tourné vers une seconde méthode : à partir d’une grille pleine valide, on enlève des cases  jusqu’à ce qu’il y ait plusieurs solutions. On annule alors la dernière action pour se retrouver avec une grille ayant une seule solution. On remarque que quand on effectue une permutation de  3 lignes ou 3 colonnes passant dans un bloc donné, on continue d’avoir une grille respectant les règles. Cette propriété est utilisée pour générer un maximum de grilles avec des solutions différentes. </p>

<p allign ="justify"> <br />Ce projet ne m’a demandé qu’une dizaine d’heures mais j’ai choisi de le présenter pour illustrer mon goût pour la logique.</p>
