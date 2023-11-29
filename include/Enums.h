#ifndef ENUMS_H
#define ENUMS_H

enum Etat {
  // Etats initiaux
  DEPART,

  // Lever le plateau
  PRET_LEVER_PLATEAU,
  LEVER_PLATEAU,
  FINI_LEVER_PLATEAU,

  // Deposer le plateau
  PRET_DEPOSER_PLATEAU,
  DEPOSER_PLATEAU,
  FINI_DEPOSER_PLATEAU,

  // Chercher commande
  ATTENDRE_PROCHAINE_COMMANDE,
  TOURNER_VERS_COTE_TABLE_CUISINE,
  SUIVRE_LIGNE_VERS_COLONNE_CUISINE,
  TOURNER_VERS_TABLE_CUISINE,
  SUIVRE_LIGNE_VERS_TABLE_CUISINE,
  SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU_CUISINE,

  // Porter nourriture
  INITIER_DEPART_LIVRAISON,
  SUIVRE_LIGNE_VERS_RANGEE,
  TOURNER_VERS_TABLE_CLIENT,
  SUIVRE_LIGNE_VERS_TABLE,
  SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT,

  // Retour au point de base
  TOURNER_VERS_LIGNE_CENTRALE,
  SUIVRE_LIGNE_VERS_LIGNE_CENTRALE,
  TOURNER_VERS_CUISINE,
  SUIVRE_LIGNE_VERS_CUISINE
};

enum Action {
  CHERCHER_COMMANDE,
  LIVRAISON
};

#endif // ENUMS_H
