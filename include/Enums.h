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
  FINI_DEPOSER_PLATEAU
};

#endif // ENUMS_H