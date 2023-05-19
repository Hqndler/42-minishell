# Minishell (101 %)

L’objectif de ce projet est de créer un shell minimaliste.

# Préambule
Minishell est à mon sens un projet qui est au antipodes de la définition du mot "fun", vous allez le détester, devenir fou et peut-être même backhole dessus...<br>
Ce projet ne vous apprendra pas grand chose si vous avez déjà fait pipex avant, avis à tout ceux qui ont fait minitalk : dommage vous avez choisi le mauvais projet pour préparer minishell.<br>
### Le comportement de minishell doit être le même que sur bash, ça ne veut pas pour autant dire qu'il doit respecter la norme POSIX. Si vous voulez faire un minishell POSIX c'est 42sh qu'il faudra faire.
# Comment bien commencer le projet ?
Le plus dur dans minishell c'est de bien commencer et de savoir comment faire. Si vous voulez trouver par vous même fermez la fenetre tout de suite !<br>
Minishell est globalement un projet de parsing, execve() sera votre meilleure amie sur la partie de l'execution donc no stress là dessus.<br>
Il faudra par contre découper la chaine de charactère comme il se doit pour pouvoir la passer à execve, et c'est là que ça devient compliqué...
# Les tokens
Pour chaques lignes de commandes envoyée à votre programme, plein de choses seront faite mais la plus important des choses à faire est de se créer une liste chainée de token pour chaques éléments de la ligne de commande.<br>
La liste chainée aura une str et un int pour chaque maillon, la str sera le "mot" et l'int le token.
Prenons l'exemple de la pire ligne de commande possible : `cat|ls` (on remarquera qu'il n'y a pas d'espace et c'est normal)
- le premier token aura comme str "cat" avec CMD comme type (6).
- le deuxieme token aura comme str "|" avec PIPE comme type (5).
- le dernier token aura comme str "ls" avec CMD comme type (6).

(se referer à [minishell.h](https://github.com/Hqndler/42-minishell/blob/main/include/minishell.h))

Les règles sont simple :
- Si on croise une redirection (`<`, `>`, `<<` ou `>>`) alors le token sera soit INPUT (1), soit TRUNC (3), soit HEREDOC (2) ou soit APPEND (4) respectivement.
- Le premier token sera CMD (6) si pas de redirection.
- Les tokens après un CMD ou une redirection seront ARG (7).
- Si "|" est la str avec il aura le type PIPE (5).
- Après un pipe le prochain token sera soit une redirection soit CMD.

Les tokens ne sont pas la première étape du parsing mais ils sont la clé d'un minishell simple à faire.

# Comment on s'y est pris ?
Premièrement plein de choses ne sont pas à gerer : les quotes ouvertes, les backslash, les points virgules ne sont pas à gerer.<br>
Le dérouler est simple : 
- check des quotes histoire de ne pas avoir de problème par la suite, message d'erreur si quote ouverte.
- remplacement des variables d'environments s'il y en a.
- création des tokens, check du dernier token, si c'est un pipe message d'erreur
- création des différentes commandes (t_cmd).

## Sur les quotes
L'interprétation des quotes n'est pas forcément celle que pous pensez avoir. Quand une quote est ouverte, elle sera fermer au moment où le charactère d'ouverture sera trouver dans la str.<br>
Dans `echo ""hello""` les doubles quotes sont ouvertes et fermées instantanément et il y a hello qui n'est pas entre quotes.<br>
`echo $USER` et `echo "$USER"` affichera la valeur de USER tandis que `echo '$USER'` affichera `$USER`.
### Tout ce qui est entre single quote ne doit pas être interprété.
Donc `echo ''$USER''` affichera... La valeur de USER, vous suivez ?<br>
Le meilleur moyen est de tester avec bash et avec des variables d'environements.<br>
Au niveau des tokens, s'il y a des quotes alors la string sera l'entièreté du contenu de ce qu'il y a dans la quote, exemple :<br>
- `echo "cat | ls" lol` -> le deuxième token aura pour str `"cat | ls"` et ARG (7) comme type.
- `echo "une phrase très longue avec l'arrivée d'une apostrophe" ''$?''` cette commande n'a pas de quote ouverte. Le deuxième token aura pour str `"une phrase très longue avec l'arrivée d'une apostrophe"` et le type ARG (7), le dernier token aura pour str itoa(exit->code) de la dernière commande puisque $? n'est pas entre quote.

Pour faire simple, une fois les quotes ouvertes la str du token continue tant que la quote n'est pas fermée. Tout char dans les quotes à ce niveau là ne doit pas être interpreter que ça soit un pipe, une redirection, un point virgule ou que sais-je.

## Les t_cmd

Un t_cmd est une liste chainée avec un fd d'infile, d'outfile et un tableau de chaine de charactères. Ce tableau sera le deuxième paramètres qu'on passera à execve().<br>
Nous avons decider de ne pas faire les bonus donc les t_cmd seront simple : il aura autant de maillon dans la liste chainée qu'il y a de commande dans la ligne de commandes.<br>
`echo lol` aura un seul maillon alors que `echo lol | cat -e` aura deux maillons.<br>
Les fd d'infile et d'outfile sont là pour les redirections. C'est à la création des t_cmd que les redirections sont ouvertes.<br>
C'est pour l'ouverture des redirections et la création du tableau de chaine de charactères que les tokens sont très important. Le token pipe servant de limiteur pour le tableau de char * et de création d'un nouveau maillon de t_cmd.<br>

## L'execution

Le sujet demande d'avoir des builtins, dans l'éventualité qu'on lance minishell avec `env -i` ou qu'on unset PATH il est impératif de les recoder entièrement et ne pas utiliser execve() pour ces builtins.
#### Execve
Pour toute les autres commandes execve sera la fonction qui fera le café. Execve prend trois paramètres : 
- le premier un char * path qui sera le chemin complet vers la commande demandée -> ls aura comme chemin /bin/ls
- le deuxième un tableau de chaine de charactères se finisant par NULL, l'équivalent d'un ft_split("ls -ls", ' ')
- le troisième un tableau de chaine de charactères **env, littéralement le char **env qu'on a dans le main, je vous conseille quand même de recréer un char **env si des modifications ont été apportées aux variables d'environments.

#### Pourquoi recréer un env ?
Prenons l'exemple d'un .sh, avant de vouloir le lancer dans notre minishell on aura export une nouvelle variable d'environment `export LOL=lolilol`, dans ce .sh on écrira $LOL. Si on venait à lancer execve sans avoir recréer un env, la variable d'environment LOL n'existe pas et ne sera pas affichée...<br>
Chose simple à savoir : vous n'êtes pas obliger de dup tout les str de votre env de minishell pour créer un char ** env pour execve, un char * est un pointeur vers le premier char de la chaine de charactère. Un char ** est un tableau de pointeur, il suffit de malloc ce tablau et d'y ajouter tout les pointeurs. Attention à ne pas free ce qu'il y a dans ce tableau : toutes les str de l'env du minishell seront free aussi.

## Les builtins

Expérimentez un maximum tout les commandes des builtins pour comprendre leur comportements.
- cd permet de changer de dossier, il update pwd et oldpwd en conséquence.
- echo avec l'option -n affiche tout les arg qui suivent, avec ou sans retour à la ligne. (echo -nn -nnn -nnnn oui -> oui$)
- env affiche les variables d'environments qui ont des valeurs associées.
- exit permet de quitter avec le code erreur donner en argument (à tester en long en large et en travers)
- export sans argument affiche l'env dans l'ordre ascii (testez `export a` puis faites export, `export a=` puis re export... tient c'est drôle), export avec argument permet d'export autant de fois qu'il faut.
- pwd affiche le dossier dans le lequel le proccess se trouve.
- unset permet de retirer une variable d'environment.

Les exit code de ces builtins sont important, testez les de votre côté (`echo $?` pour rappel)

## Les signaux

Pas grand chose à dire dessus, regardez comment utiliser la fonction signal() et les SIG code. De notre côté le ctrl + \ n'est pas parfaitement gerer, le message d'erreur est manquant, et le ctrl + C dans un heredoc est possible à faire mais on ne l'a pas fait. Le moyen de faire le ctrl + C dans un heredoc qu'on a trouvé était de mettre tout la partie écriture du heredoc dans le child d'un fork() pour exit et retourner au main ensuite.
Petit rappel de ce que doivent faire les signaux :
- ctrl + C redonne un prompt que la ligne soit vide ou pleine ou qu'on soit dans une commande bloquante comme `cat`
- ctrl + D exit si la ligne est vide et redonne un prompt dans un commande bloquante comme `grep ""`
- ctrl + \ ne fait rien sauf dans une commande bloquante, il permet de kill le process avec un message d'erreur.

## Les messages d'erreur et le projet en général

Les messages ne sont pas demandé, vous pouvez ne pas les mettre, si vous voulez en mettre les tokens sont important pour ça aussi.<br>
Le plus dur dans ce projet se passe à la correction, si votre projet est solide et qu'on vous met faux sur une commande obscure, retentez avec le même code. Si segfault ou réel problème dans le code, le code devra être changer avant de retry, sinon vous êtes tomber sur un casse couille / minishell breaker.

## Disclaimer

Notre projet n'est pas parfait mais on a réussi à le valider : $$ créer une boucle infinie, unset peut retirer la mauvaise variable, cd - / cd ~ n'est pas supporter. Les quotes imbriquée sont toute fois gérées ce qui permet d'avoir le dernier bonus pour la note de 101% WOW !

## La bible

[Cliquez c'est bien](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0)

## Aperçu de la correction
![Correction Minishell](https://github.com/Hqndler/42-minishell/assets/69089935/e63ad3c7-67f8-4260-8e60-c79b60b2a303)
