// Début du fichier main.cpp

/**
 *  \file main.cpp
 *  \brief Contient la fonction main
 *
 *  Ce fichier contient la fonction :
 *  int main(int argc, char** argv)
 *  qui est le point d'entrée d'un programme C++
 *  (cf documentation de la fonction en question).
 */

#include "MainWindow.hpp" // Inclut le header MainWindow.hpp
/**
 * Inclut la classe QApplication qui gère le contôle de flux
 * et les paramètres principaux de l'interface graphique utilisateur.
 * cf : https://doc.qt.io/qt-5/qapplication.html#details
 */
#include <QApplication>
#include <iostream> // Inclut la bibliothèque de gestion de flux d'entrée-sortie standards

/**
 * \fn main
 * \brief Point d'entrée du programme C++
 * \param argc Nombre d'arguments de la commande de lancement du programme
 * \param argv Tableau de chaînes de caractères
 * \return Entier qui correspond à un code de statut
 *
 *  L'argument 0 de argv contient la commande qui correspond à l'appel du programme.
 *
 *  Pour la valeur de retour, un 0 correspond à une terminaison sans erreur ; une autre valeur
 *  indique que le programme s'est arrêté anormalement.
 *  Pour plus d'information sur cette fonction, le lecteur est invité à consulter les spécifications du
 *  standard C++.
 *  Nous en donnons une version de travail ici, la version finale étant inaccessible publiquement :
 *  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4640.pdf#page=77
 */
int main(int argc, char** argv) {
    // Début de la fonction main

    QApplication app(argc, argv); // Création de l'application

    MainWindow window; // Création de la fenêtre principale
    window.show(); // Affichage de la fenêtre principale

    return QApplication::exec(); // Exécution de l'application

    // Fin de la fonction main
}

// Fin du programme C++

// Fin du fichier main.cpp