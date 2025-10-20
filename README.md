Eli est un compilateur decompilateur pour la ti82 83 modifiable facilement pour les autres ti .
Il à ete conçu pour fonctionner avec 
 a : le black link a acheter d occase sur ebay avec un enfichable COM !
 b : telecharger le TICOnnect de chez TI

 Principe:
 passer le source pour compiler un module pour la ti82 ou 83 ce module se chargera avec le black link et TI connect
 a l inverse decomplier le code compilé venant de la ti par le black link en code ascii modifiable

 a noter les codes des sources ti ne sont pas en ascii (code controle differents) et certain caracteres d edition n existent pas
 dans les affichage ecran de la calto.

 Remarque: on m afait remarquer que des decompilo ou source src de compilo decompilo pululaient sur le net, un seul marche pour 82 et 83 
 c est le mien. a lediteur hex le fichier generé peu paraitre genetiquement modifié mais il fonctionne ses genes seront reconnus par le systeme TI.
 GoodLuck bon exams ...

/*
    +------------------------------------------------------------------------+
    +    Compil et decompil de .tib -> .83p a texas instrument calto system
    +    Debloquage de l octet de protection sur les codes decompiles. Chut!
    +     Prog/prj: BolosR    tokens lexer, compil, decompil for ti langage  +
    +    File Name: Main program. Corps du programme                         +
      ___
   __|___|__    +------------------------------------------------------------+
   c/ .-. \g    ¦  BolosR (Compil & Reverse) for Ti83/stat/.fr               ¦
  __\( c )/__   ¦  Version publiee sur CS le 18 mars 2016                    ¦
(_.-/     \-._) ¦  Version publiee sur gitHub le 18 mars 2016                ¦
    \     /     ¦                                                            ¦
  _.' ___ '._   ¦  .                                                         ¦
 (.-./   |.-.)  ¦                             (c) ccgousset@gmail.com 2015   ¦
  `-'     `-'   +-------- Bon on recolle cette table Alexis ? ---------------+
    +                                                                        +
    +------------------------------------------------------------------------+
*/
  
