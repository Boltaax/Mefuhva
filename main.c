#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <wchar.h>

void Color(int couleurDuTexte,int couleurDeFond);       // Cette fonction permet d'initialiser l'utilisation des couleurs pour le dans la console

int main(int argc, char *argv[])                        // fonction principale permettant de boucler les tours des joueurs tant que la partie n'est pas finie
{
    int Plateau1[6][2], Plateau2[6][2], ligne, colonne, *test1, *test2, *tour=1 , *mode=0;

    for (ligne=0; ligne<2; ligne++){
        for (colonne=0; colonne<6; colonne++){          // Ici on définit deux tableau 6 par 2 rempli de 2
            Plateau1[colonne][ligne] = 2;
            Plateau2[colonne][ligne] = 2;
        }
    }
    Plateau1[5][1] = 0;                                 // Ici on change les quelques cases spécifiques dans les tableaux qui serviront de plateaux de jeu aux Joueurs 1 et 2
    Plateau1[4][1] = 1;
    Plateau2[0][0] = 0;
    Plateau2[1][0] = 1;

    Menu_Principal(Plateau1, Plateau2, &tour, &mode);


    return 0;                                           // Fin du programme
}

void jcj(int Plateau1[6][2], int Plateau2[6][2], int *tour, int *mode){     //Si on décide de jouer contre un autre joueur

    int ligne, colonne, *test1, *test2;
    system("cls");
    mode = 0;
    tour = *tour;
    do {                                                                    // Les joueurs jouent chacun leur tour
        if (tour == 1){                                                     // On test la variable tour au cas où on l'on a chargé une ancienne partie
        tour = 1;                                                           // On réinitialise le tour du joueur à chaque fois pour la sauvegarde
        Sauvegarder(Plateau1, Plateau2, &tour, &mode);                      //Chaque tour on sauvegarde les deux plateaux
        Tour_J1(Plateau1, Plateau2);                                        //On lanxe le système pour que le joueur joue
        verif_end(Plateau1, Plateau2, &test1, &test2);                      //On test si l'un des deux plateaux et vide pour finir ou non la partie
        system("cls");
        tour = 2;
        }                                                                   //Même chose ensuite mais pour le joueur 2
        if (tour == 2){
        tour = 2;
        Sauvegarder(Plateau1, Plateau2, &tour, &mode);
        Tour_J2(Plateau1, Plateau2);
        verif_end(Plateau1, Plateau2, &test1, &test2);
        system("cls");
        tour = 1;
        }
    }
    while (test1 != 0 && test2 != 0);                                       // Tant que l'un des deux plateaux n'est pas vide de graine on continue la boucle des tours

}

void jvIA(int Plateau1[6][2],int Plateau2[6][2],int *tour, int *mode){      //Si on décide de jouer contre l'IA de niveau 1 (aléatoire)

    int ligne, colonne, *test1, *test2;
    system("cls");
    mode = 1;
    tour = *tour;


    do {                                                // Les joueur joue puis c'est à l'IA
        if (tour == 1){
        tour = 1;
        Sauvegarder(Plateau1, Plateau2, &tour, &mode);  //On sauvegarde à chaque tour le plateau pour pouvoir reprendre la partie
        Tour_J1(Plateau1, Plateau2);
        verif_end(Plateau1, Plateau2, &test1, &test2);  //Vérification de si la partie est finie
        system("cls");
        tour = 2;
        }
        if (tour == 2){
        tour = 2;
        Sauvegarder(Plateau1, Plateau2, &tour, &mode);
        IA_1(Plateau1, Plateau2);                       //On va lancer le tour de l'IA
        verif_end(Plateau1, Plateau2, &test1, &test2);
        system("cls");
        tour = 1;
        }
    }
    while (test1 != 0 && test2 != 0);                   // Tant que l'un des deux plateaux n'est pas vide de graine on continue la boucle des tours
    printf("\n\n%d     %d",test1, test2);
}

void jvIA2(int Plateau1[6][2],int Plateau2[6][2],int *tour, int *mode){     //Si on décide de jouer contre l'IA de niveau 2 (meilleur coup)

    int ligne, colonne, *test1, *test2;
    system("cls");
    mode = 2;
    tour = *tour;


    do {                                                // Le joueur joue puis c'est à l'IA
        if (tour == 1){
        tour = 1;
        Sauvegarder(Plateau1, Plateau2, &tour, &mode);  //On sauvegarde à chaque tour le plateau pour pouvoir reprendre la partie
        Tour_J1(Plateau1, Plateau2);
        verif_end(Plateau1, Plateau2, &test1, &test2);
        system("cls");
        tour = 2;
        }
        if (tour == 2){
        tour = 2;
        Sauvegarder(Plateau1, Plateau2, &tour, &mode);
        IA_2(Plateau1, Plateau2);
        verif_end(Plateau1, Plateau2, &test1, &test2);
        system("cls");
        tour = 1;
        }
    }
    while (test1 != 0 && test2 != 0);                   // Tant que l'un des deux plateaux n'est pas vide de graine on continue la boucle des tours
    printf("\n\n%d     %d",test1, test2);
}

void Regles(int Plateau1[6][2], int Plateau2[6][2]){                        //Affichage des règles du jeu

    int touch;

    printf("\n\n\n   ");
    wprintf(L"                          Les r%lcgles du Mefuhva sont les suivantes :\n\n",138);
    printf("  Le but est de prendre toutes les graines de l'adversaire\n");
    wprintf(L"  Le camp de chaque joueur est constitu%lc par les 2 rang%lces de 6 trous, situ%lces\n",130,130,130);
    wprintf(L"  imm%lcdiatement devant lui. Les graines sont dispos%lces comme indiqu%lc dans le tableau ci-apr%lcs.",130,130,130,138);

    affichage(Plateau1,Plateau2);

    wprintf(L"  A son tour, le joueur ramasse toutes les graines d'un trou de son camp. Il s%lcme ensuite ses graines,\n",138);
    printf("  une par une, en tournant dans son propre camp dans le sens inverse des aiguilles d'une montre,\n");
    wprintf(L"  %lc partir du trou suivant et sans sauter de trous.\n",133);
    wprintf(L"  Lorsque la derni%lcre graine sem%lce tombe dans un trou contenant au moins une graine, il reprend\n",138,130);
    wprintf(L"  l'ensemble des graines de ce trou et il recommence %lc semer. Il continue de la sorte jusqu'%lc ce que la\n",133,133);
    wprintf(L"  derni%lcre graine soit pos%lce dans un trou vide.\n",138,130);
    Color(14,0);
    printf("                                                                                                 Toucher pour continuer");
    Color(15,0);
    touch = getch();
    system("cls");
    printf("\n\n\n");

    wprintf(L"  Lorsque la derni%lcre graine tombe dans un trou vide, deux cas de figure sont possibles.\n",138);
    wprintf(L"  Si le trou d'arriv%lce est situ%lc sur la rang%lce ext%lcrieure (la plus proche du joueur), aucune r%lccolte n'est\n",130,130,130,130,130);
    wprintf(L"  possible. C'est %lc l'autre joueur de semer.\n",133);
    wprintf(L"  Si le trou d'arriv%lce est situ%lc sur la rang%lce int%lcrieure du jeu (celle qui est en contact avec le camp\n",130,130,130,130);
    wprintf(L"  adverse), le joueur r%lccolte dans le camp de l'adversaire les graines situ%lces en face de la derni%lcre graine\n",130,130,138);
    wprintf(L"  qu'il vient de poser. Cette prise lui permet %lcgalement de capturer les graines juste derri%lcre le premier trou r%lccolt%lc\n",130,138,130,130);
    wprintf(L"  Attention ! Si la premi%lcre case adverse est vide, le joueur ne peut pas prendre les graines contenues\n",138);
    wprintf(L"  dans la case de la deuxi%lcme rang%lce.",138,130);
    touch = getch();
    system("cls");
    Menu_Principal(Plateau1, Plateau2);

}

void Menu_2(int Plateau1[6][2], int Plateau2[6][2],int *tour, int *mode)    //Menu de sélection du type de partie
{
    int variable = 0, i=0, font, bg;
    char touche;

    tour = *tour;
    mode = *mode;

    printf("\n\n\n\n\n\n\n\n");
    printf("                                      ");
    Color(3,0);
    wprintf(L"Appuyez sur x pour s%lclectionner",130);
    Color(15,0);
    printf("\n\n\n");
    printf("                                           ");
    printf("   Nouvelle Partie\n\n");
    printf("                                           ");
    printf("____________________\n\n");
    printf("                                           ");
    printf("---> Mode Joueur contre Joueur\n");
    printf("                                           ");
    printf("     Mode contre Ordinateur : niveau 1\n");
    printf("                                           ");
    printf("     Mode contre Ordinateur : niveau 2\n");
    Color(11,0);
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("                                                                  ");
    wprintf(L"Appuyer sur B pour retourner en arri%lcre",138);
    Color(15,0);

    do{
        touche = getch();

        system("cls");

        switch(touche) /* On baisse ou augmente le score de variable en fonction de la flèche touchée */
        {
            case 72 : /* fleche du haut détectée (valeur ASCII) */
            variable -= 1;
            break;

            //     [ mémo ]     touche flèche gauche : 75     touche flèche droite : 77

            case 80: /* fleche du bas détectée */
            variable += 1;
            break;

            case 'b':
            Menu_Principal(Plateau1, Plateau2, &tour, &mode);
            break;
        }

        if (variable > 2){
            variable = 0;
        }
        if (variable < 0){
            variable = 2;
        }

        system("cls");
        switch(variable)        //On affiche le défilement de la flèche grâce aux flèches directrices
        {

            case 1:
                printf("\n\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Nouvelle Partie\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("     Mode Joueur contre Joueur\n");
                printf("                                           ");
                printf("---> Mode contre Ordinateur : niveau 1\n");
                printf("                                           ");
                printf("     Mode contre Ordinateur : niveau 2\n");
                Color(11,0);
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                printf("                                                                  ");
                wprintf(L"Appuyer sur B pour retourner en arri%lcre",138);
                Color(15,0);
                break;

            case 2:
                printf("\n\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Nouvelle Partie\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("     Mode Joueur contre Joueur\n");
                printf("                                           ");
                printf("     Mode contre Ordinateur : niveau 1\n");
                printf("                                           ");
                printf("---> Mode contre Ordinateur : niveau 2\n");
                Color(11,0);
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                printf("                                                                  ");
                wprintf(L"Appuyer sur B pour retourner en arri%lcre",138);
                Color(15,0);
                break;

             case 0:
                printf("\n\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Nouvelle Partie\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("---> Mode Joueur contre Joueur\n");
                printf("                                           ");
                printf("     Mode contre Ordinateur : niveau 1\n");
                printf("                                           ");
                printf("     Mode contre Ordinateur : niveau 2\n");
                Color(11,0);
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                printf("                                                                  ");
                wprintf(L"Appuyer sur B pour retourner en arri%lcre",138);
                Color(15,0);
                break;
        }
    }while(touche!= 'x');

    system("cls");

    switch(variable){       //En fonction du défilement de la flèche, on va lancer la fonction correspondante

        case 0:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("                                       ");
            Color(11,0);
            printf(" Lancement d'une nouvelle partie ! \n\n");
            Color(15,0);
            printf("                                    ");
            for (i=0; i<21; i++)
            {
                bg = 2*(i%2)+1;
                font = 4-bg;
                Color(font,bg);
                wprintf(L"%lc",219);
                usleep(50000);
                wprintf(L"%lc",219);
                usleep(50000);
            }
            Color(15,0);

            jcj(Plateau1, Plateau2, &tour, &mode);
            break;

        case 1:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("                                       ");
            Color(11,0);
            printf(" Lancement d'une nouvelle partie ! \n\n");
            Color(15,0);
            printf("                                    ");
            for (i=0; i<21; i++)
            {
                bg = 2*(i%2)+1;
                font = 4-bg;
                Color(font,bg);
                wprintf(L"%lc",219);
                usleep(50000);
                wprintf(L"%lc",219);
                usleep(50000);
            }
            Color(15,0);

            jvIA(Plateau1, Plateau2, &tour, &mode);
            break;

        case 2:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("                                       ");
            Color(11,0);
            printf(" Lancement d'une nouvelle partie ! \n\n");
            Color(15,0);
            printf("                                    ");
            for (i=0; i<21; i++)
            {
                bg = 2*(i%2)+1;
                font = 4-bg;
                Color(font,bg);
                wprintf(L"%lc",219);
                usleep(50000);
                wprintf(L"%lc",219);
                usleep(50000);
            }
            Color(15,0);

            jvIA2(Plateau1, Plateau2, &tour, &mode);
            break;

    }
    sleep(1);
    system("cls");
}

void Menu_Principal(int Plateau1[6][2], int Plateau2[6][2], int *tour, int *mode)   //Premier Menu
{
    int variable = 0, i=0, font, bg, touch;
    char touche;

    tour = *tour;
    mode = *mode;

    printf("\n\n\n\n\n\n\n");
    printf("                                      ");
    Color(3,0);
    wprintf(L"Appuyez sur x pour s%lclectionner",130);
    Color(6,0);
    printf("\n                                      ");
    wprintf(L"Utilisez les fl%lcches pour se d%lcplacer",138,130);
    Color(15,0);
    printf("\n\n\n");
    printf("                                           ");
    printf("   Menu Principal\n\n");
    printf("                                           ");
    printf("____________________\n\n");
    printf("                                           ");
    printf("---> Nouvelle Partie\n");
    printf("                                           ");
    printf("     Charger Partie\n");
    printf("                                           ");
    wprintf(L"     Cr%lcdits\n",130);
    printf("                                           ");
    wprintf(L"     R%lcgles\n",138);
    printf("                                           ");
    printf("     Quitter");

    do{
        touche = getch();

        system("cls");

        switch(touche) /* On baisse ou augmente le score de variable en fonction de la flèche touchée */
        {
            case 72 : /* fleche du haut détectée (valeur ASCII) */
            variable -= 1;
            break;

            //     [ mémo ]     touche flèche gauche : 75     touche flèche droite : 77

            case 80: /* fleche du bas détectée */
            variable += 1;
            break;
        }

        if (variable > 4){
            variable = 0;
        }
        if (variable < 0){
            variable = 4;
        }

        system("cls");
        switch(variable)
        {

            case 1:
                printf("\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(6,0);
                printf("\n                                      ");
                wprintf(L"Utilisez les fl%lcches pour se d%lcplacer",138,130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Menu Principal\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("     Nouvelle Partie\n");
                printf("                                           ");
                printf("---> Charger Partie\n");
                printf("                                           ");
                wprintf(L"     Cr%lcdits\n",130);
                printf("                                           ");
                wprintf(L"     R%lcgles\n",138);
                printf("                                           ");
                printf("     Quitter");
                break;

            case 2:
                printf("\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(6,0);
                printf("\n                                      ");
                wprintf(L"Utilisez les fl%lcches pour se d%lcplacer",138,130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Menu Principal\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("     Nouvelle Partie\n");
                printf("                                           ");
                printf("     Charger Partie\n");
                printf("                                           ");
                wprintf(L"---> Cr%lcdits\n",130);
                printf("                                           ");
                wprintf(L"     R%lcgles\n",138);
                printf("                                           ");
                printf("     Quitter");
                break;

             case 3:
                printf("\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(6,0);
                printf("\n                                      ");
                wprintf(L"Utilisez les fl%lcches pour se d%lcplacer",138,130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Menu Principal\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("     Nouvelle Partie\n");
                printf("                                           ");
                printf("     Charger Partie\n");
                printf("                                           ");
                wprintf(L"     Cr%lcdits\n",130);
                printf("                                           ");
                wprintf(L"---> R%lcgles\n",138);
                printf("                                           ");
                printf("     Quitter");
                break;

            case 4:
                printf("\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(6,0);
                printf("\n                                      ");
                wprintf(L"Utilisez les fl%lcches pour se d%lcplacer",138,130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Menu Principal\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("     Nouvelle Partie\n");
                printf("                                           ");
                printf("     Charger Partie\n");
                printf("                                           ");
                wprintf(L"     Cr%lcdits\n",130);
                printf("                                           ");
                wprintf(L"     R%lcgles\n",138);
                printf("                                           ");
                printf("---> Quitter");
                break;


             case 0:
                printf("\n\n\n\n\n\n\n");
                printf("                                      ");
                Color(3,0);
                wprintf(L"Appuyez sur x pour s%lclectionner",130);
                Color(6,0);
                printf("\n                                      ");
                wprintf(L"Utilisez les fl%lcches pour se d%lcplacer",138,130);
                Color(15,0);
                printf("\n\n\n");
                printf("                                           ");
                printf("   Menu Principal\n\n");
                printf("                                           ");
                printf("____________________\n\n");
                printf("                                           ");
                printf("---> Nouvelle Partie\n");
                printf("                                           ");
                printf("     Charger Partie\n");
                printf("                                           ");
                wprintf(L"     Cr%lcdits\n",130);
                printf("                                           ");
                wprintf(L"     R%lcgles\n",138);
                printf("                                           ");
                printf("     Quitter");
                break;
        }
    }while(touche!= 'x');

    system("cls");

    switch(variable){

        case 0:
            Menu_2(Plateau1, Plateau2, &tour, &mode);
            break;

        case 1:
            RecupSauvegarde(Plateau1, Plateau2, &tour, &mode);
            system("cls");
            Menu_Principal(Plateau1, Plateau2, &tour, &mode);
            break;

        case 2:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            Color(11,0);
            wprintf(L"                                             Cr%lcateur du jeu :\n\n",130);
            Color(6,0);
            wprintf(L"                                        Thibault Foss%lc a.k.a Ptik",130);
            Color(11,0);
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("                                                      ");
            wprintf(L"Appuyer sur n'importe quelle touche pour retourner en arri%lcre",138);
            Color(15,0);
            touch = getch();
            system("cls");
            Menu_Principal(Plateau1, Plateau2, &tour, &mode);
            break;

        case 3:
            Regles(Plateau1, Plateau2);
            system("cls");
            break;

        case 4:
            system("exit");
            break;
    }
    sleep(1);
    system("cls");
}

void affichage(int Plateau1[6][2],int Plateau2[6][2])   // fonction qui vas permettre l'affichage du plateau de jeu entier (comprenant le plateau du Joueur 1 et celui du Joueur 2)
{
    int colonne, ligne;
    printf("\n\n");
    printf("          A          B          C          D          E          F\n");         // Affichage des coordonées correspodant aux colonnes
    printf("         _________________________________________________________    \n\n");
    Color(10, 0);
    printf("         ___________________Plateau du Joueur 1___________________    \n\n");
    Color(15, 0);
    for (ligne=0; ligne<2; ligne++){
        Color(15, 0);
        printf("%d -->",ligne+1);                                                           // Affichage des coordonées correspondant aux lignes du Joueur 1
        for (colonne=0; colonne<6; colonne++){
            Color(15, 8);
            if (Plateau1[colonne][ligne] == 0)
            {
                Color(4, 7);
            }
            printf("     %d     ",Plateau1[colonne][ligne]);
            Color(15, 8);
        }
        Color(15, 0);
        printf("\n\n");
    }
    Color(15, 0);
    printf("         _________________________________________________________    \n\n");     // Séparation entre le plateau du Joueur 1 au dessus et celui du Joueur 2 en dessous
    Color(12,0);
    printf("         ___________________Plateau du Joueur 2___________________    \n\n");
    Color(15, 0);
    for (ligne=0; ligne<2; ligne++){
        Color(15, 0);
        printf("%d -->",ligne+1);                                                           // Affichage des coordonées correspondant aux lignes du Joueur 2
        for (colonne=0; colonne<6; colonne++){
            Color(15, 8);
            if (Plateau2[colonne][ligne] == 0)
            {
                Color(4, 7);
            }
            printf("     %d     ",Plateau2[colonne][ligne]);
            Color(15, 8);
        }
        Color(15, 0);
        printf("\n\n");
    }
    Color(15,0);
}

void Tour_J1(int Plateau1[6][2], int Plateau2[6][2])    // fonction rappelée à chaque fois que c'est au tour du Joueur 1 qui vas lancer les actions que le joueur doit faire automatiquement.
{
    int *colonne, *ligne, graines;

    affichage(Plateau1,Plateau2);
    printf("\n\n C'est au ");
    Color(10,0);
    printf("Joueur 1");
    Color(15,0);
    printf(" : ");
    ramasser(&colonne, &ligne, Plateau1, Plateau2);

    verif_J1(colonne, ligne, Plateau1, Plateau2);
}

void Tour_J2(int Plateau1[6][2], int Plateau2[6][2])    // même chose que semer_J1 mais pour le Joueur 2
{
    int *colonne, *ligne, graines;

    affichage(Plateau1,Plateau2);
    printf("\n\n C'est au ");
    Color(12,0);
    printf("Joueur 2");
    Color(15,0);
    printf(" : ");
    ramasser(&colonne, &ligne, Plateau1, Plateau2);

    verif_J2(colonne, ligne, Plateau1, Plateau2);
}

void IA_1(int Plateau1[6][2], int Plateau2[6][2])       // IA qui joue de manière aléatoire
{
    int colonne, ligne, graines=0, y, touch;
    char x;

    srand(time(NULL));
    affichage(Plateau1,Plateau2);
    wprintf(L"\n\n C'est %lc ",133);
    Color(11,0);
    printf("l'Ordinateur");
    Color(15,0);
    printf(" : ");
    while(graines == 0)
    {
        colonne = rand()%6;
        ligne = rand()%2;
        graines = Plateau2[colonne][ligne];
    }
    switch (colonne){       //On transforme notre coordonées avec un caractère et un entier en deux pointeurs entiers servant de coordonnées que l'on vas réutiliser dans la suite du programme.
    case 0:
        x = 'A';
        break;
    case 1:
        x = 'B';
        break;
    case 2:
        x = 'C';
        break;
    case 3:
        x = 'D';
        break;
    case 4:
        x = 'E';
        break;
    case 5:
        x = 'F';
        break;
    }
    y = ligne + 1;
    verif_J2(colonne, ligne, Plateau1, Plateau2);
    wprintf(L"\n\n L'ordinateur a jou%lc en ",130);
    Color(3,0);
    printf("%c%d", x, y);
    Color(15,0);
    printf("\n\n Toucher n'importe quelle touche pour continuer.");
    touch = getch();
}

void IA_2(int Plateau1[6][2], int Plateau2[6][2])       // IA de meilleur niveau
{
    int colonne, ligne, graines=0, y, touch, *test=0, test2=0, test3, col, lin;
    char x;

    affichage(Plateau1,Plateau2);
    wprintf(L"\n\n C'est %lc ",133);
    Color(11,0);
    printf("l'Ordinateur");
    Color(15,0);
    printf(" : ");

    for (ligne=0; ligne<2; ligne++){
        for (colonne=0; colonne<6; colonne++){
            graines = Plateau2[colonne][ligne];
            if (graines != 0){
                verif_IA2(colonne, ligne, Plateau1, Plateau2, &test);
                test3 = test;
                if (test3 > test2){
                    col = colonne;
                    lin = ligne;
                    test2 = test3;
                }
            }
        }
    }

    switch (col){       //On transforme notre coordonées avec un caractère et un entier en deux pointeurs entiers servant de coordonnées que l'on vas réutiliser dans la suite du programme.
    case 0:
        x = 'A';
        break;
    case 1:
        x = 'B';
        break;
    case 2:
        x = 'C';
        break;
    case 3:
        x = 'D';
        break;
    case 4:
        x = 'E';
        break;
    case 5:
        x = 'F';
        break;
    }
    y = lin + 1;
    verif_J2(col, lin, Plateau1, Plateau2);
    wprintf(L"\n\n L'ordinateur a jou%lc en ",130);
    Color(3,0);
    printf("%c%d", x, y);
    Color(15,0);
    printf("\n\n Toucher n'importe quelle touche pour continuer.");
    touch = getch();
}

void ramasser(int *x,int *y, int Plateau1[6][2], int Plateau2[6][2])            // fonction qui vas permettre au joueur de choisir depuis quelle case il veut commencer son tour
{
    int lig;
    char colo;
    printf("Quelle case voulez vous ramasser ?\n\n (Exemple : B1)"); // Le joueur entre une coordonnée avec une lettre pour la colonne et un chiffre pour la ligne pour éclaircir la compréhension
    Color(8,0);
    printf("                    Q1 pour Quitter\n\n");
    Color(15,0);
    scanf("%c",&colo);
    printf("");
    scanf("%d",&lig);

    while(((lig != 1) && (lig != 2)) || ((colo != 'A') && (colo != 'B') && (colo != 'C') && (colo != 'D') && (colo != 'E') && (colo != 'F') && (colo!= 'Q') && (colo  != 'I')))       //On vérifie que la coordonée entrée par le joueur existe
    {
        Color(4,0);
        wprintf(L"\n\n\n\n\n\n\n\n\n\n\n                     Ces coordon%lces n'existent pas.\n                Veuillez choisir des coordonn%lces valides!\n\n\n",130 ,130);
        Color(15,0);
        affichage(Plateau1,Plateau2);
        printf("\n\n\n Quelle case voulez vous ramasser ?\n\n (Exemple : B1)\n\n ");        //Dans le cas contraire le programme boucle jusqu'à ce que les coordonées données soient bonnes. (Avec message d'erreur)
        scanf("%c",&colo);
        printf("");
        scanf("%d",&lig);
    }


    switch (colo){       //On transforme notre coordonées avec un caractère et un entier en deux pointeurs entiers servant de coordonnées que l'on vas réutiliser dans la suite du programme.
    case 'A':
        *x = 0;
        break;
    case 'B':
        *x = 1;
        break;
    case 'C':
        *x = 2;
        break;
    case 'D':
        *x = 3;
        break;
    case 'E':
        *x = 4;
        break;
    case 'F':
        *x = 5;
        break;
    case 'Q':                                           //système pour quitter en pleine partie
        system("cls");
        Color(6,0);
        wprintf(L"\n\n\n\n\n\n\n\n\n\n\n\n                                          Vous avez quitt%lc avec succ%lcs",130, 138);
        Color(15,0);
        system("exit");                     //Il avait du mal à quitter avec un seul
        exit(0);
        return 0;
        break;
    case 'I':       //Petit Easter Egg
        if( lig == 2 ){
            srand(time(NULL));
            egg_b();
            Color(15,0);
            system("cls");
            printf("\n\n\n\n                                                EGG Boom !\n\n\n\n\n");
            sleep(2);
            wprintf(L"\n\n\n\n                                                SI vous avez trouv%lc ceci vous me devez un 20/20!\n\n\n\n\n",130);
            system("exit");                     //Il avait du mal à quitter avec un seul
            exit(0);
            return 0;
            break;
        }
    }
    *y = lig - 1;
}

void verif_J1(int x,int y,int Plateau1[6][2],int Plateau2[6][2])                // fonction permettant de vérifier que la case sélectionnée contient bien au moins 1 graine
{
    int graines, *col, *lin;
     //Prendre les graines dans Plateau1[x][y] et distribuer dans :
     //si ligne == 0 alors colonne - 1, si colonne == 0 alors ligne = 1 si ligne == 1 alors colonne + 1, si colonne = 5 alors ligne = 0
     //Tant que la dernière graine n'est pas posée dans une box Plateau1[x][y] = 0, on recommence en prenant les graines de la dernière case remplie

     graines = Plateau1[x][y];

     if (graines == 0)
     {
        wprintf(L"\n\n\n Il n'y a aucune graine dans la case s%lclectionn%lce.\n\n Veuillez choisir des coordonn%lces valides.\n\n", 130, 130, 130 );
        Tour_J1(Plateau1, Plateau2);
     }


     col = x;
     lin = y;


     semer_J1(&col, &lin, Plateau1, Plateau2, graines);
}

void semer_J1(int *x,int *y,int Plateau1[6][2],int Plateau2[6][2], int graines) // fonction qui vas effectuer le déplacement des graines ainsi que la capture des graines du Joueur 2
{
     int i;

     do
     {
         graines = Plateau1[*x][*y];
         Plateau1[*x][*y] = 0;      // On Enlève toutes les graines de la case sélectionnée

         for (i = graines; i > 0; i-- )      // déplacement des graines sur le plateau du Joueur 1 dans le sens inverse des aiguilles d'une montre
        {

            if (*y == 0)
            {
                if (*x != 0)
                {
                    *x = *x - 1;
                    Plateau1[*x][*y] = Plateau1[*x][*y] + 1;
                    graines--;
                }
                else
                {
                    *y = 1;
                    Plateau1[*x][*y] = Plateau1[*x][*y] + 1;
                    graines--;
                }
            }
            else
            {
                if (*x != 5)
                {
                    *x = *x + 1;
                    Plateau1[*x][*y] = Plateau1[*x][*y] + 1;
                    graines--;
                }
                else
                {
                    *y = 0;
                    Plateau1[*x][*y] = Plateau1[*x][*y] + 1;
                    graines--;
                }
            }
        }
     }
     while (Plateau1[*x][*y] != 1);  // On répète le mouvement en reprenant toutes les graines prises dans la dernière case si elle n'est pas vide


     //Si la graine tombe dans une case vide alors :
     //Si c'est sur Plateau1[x][0] il ne se passe rien c'est au Joueur 2 de jouer
     //Si c'est sur Plateau1[x][1], les graines sur Plateau2[x][0] et Plateau2[x][1] sont volées
     // /!\ Si Plateau2[x][0] est vide il ne se passe rien et c'est au Joueur2 de jouer

     if (*y == 1){
        if (Plateau2[*x][0] != 0){
            Plateau2[*x][0] = 0;
            Plateau2[*x][1] = 0;
        }
     }
}

void verif_J2(int x,int y,int Plateau1[6][2],int Plateau2[6][2]) // même chose que verif_J1 mais pour le Joueur 2
{
    int graines, *col, *lin;
     //Prendre les graines dans Plateau2[x][y] et distribuer dans :
     //si ligne == 0 alors colonne - 1, si colonne == 0 alors ligne = 1 si ligne == 1 alors colonne + 1, si colonne = 5 alors ligne = 0
     //Tant que la dernière graine n'est pas posée dans une box Plateau1[x][y] = 0, on recommence en prenant les graines de la dernière case remplie


     graines = Plateau2[x][y];

     //printf("\n\n x = %d y = %d Il y a %d graines dans la case\n\n",x , y, graines);

     if (graines == 0)
     {
        wprintf(L"\n\n\n Il n'y a aucune graine dans la case s%lclectionn%lce.\n\n Veuillez choisir des coordonn%lces valides.", 130, 130, 130 );
        Tour_J2(Plateau1, Plateau2);
     }


     col = x;
     lin = y;


     semer_J2(&col, &lin, Plateau1, Plateau2, graines);
}

void semer_J2(int *x,int *y,int Plateau1[6][2],int Plateau2[6][2], int graines) // même chose que semer_J1 mais pour le Joueur 2
{
     int i;

     do
     {
         graines = Plateau2[*x][*y];
         Plateau2[*x][*y] = 0;

         for (i = graines; i > 0; i-- )
        {
            if (*y == 0)
            {
                if (*x != 0)
                {
                    *x = *x - 1;
                    Plateau2[*x][*y] = Plateau2[*x][*y] + 1;
                    graines--;
                }
                else
                {
                    *y = 1;
                    Plateau2[*x][*y] = Plateau2[*x][*y] + 1;
                    graines--;
                }
            }
            else
            {
                if (*x != 5)
                {
                    *x = *x + 1;
                    Plateau2[*x][*y] = Plateau2[*x][*y] + 1;
                    graines--;
                }
                else
                {
                    *y = 0;
                    Plateau2[*x][*y] = Plateau2[*x][*y] + 1;
                    graines--;
                }
            }
        }
     }
     while (Plateau2[*x][*y] != 1);
     //Si la graine tombe dans une case vide alors :
     //Si c'est sur Plateau2[x][1] il ne se passe rien c'est à joueur 1 de jouer
     //Si c'est sur Plateau2[x][0], les graines sur Plateau1[x][0] et Plateau1[x][1] sont volées
     // /!\ Si Plateau1[x][1] est vide il ne se passe rien et c'est à Joueur2 de jouer

     if (*y == 0){
        if (Plateau1[*x][1] != 0){
            Plateau1[*x][0] = 0;
            Plateau1[*x][1] = 0;
        }
     }
}

void verif_IA2(int x,int y,int Plateau1[6][2],int Plateau2[6][2],int *test) // même chose que verif_J1 mais pour le Joueur 2
{
    int graines, Plateau3[6][2], Plateau4[6][2], a, b, i, test2;
     //Prendre les graines dans Plateau2[x][y] et distribuer dans :
     //si ligne == 0 alors colonne - 1, si colonne == 0 alors ligne = 1 si ligne == 1 alors colonne + 1, si colonne = 5 alors ligne = 0
     //Tant que la dernière graine n'est pas posée dans une box Plateau1[x][y] = 0, on recommence en prenant les graines de la dernière case remplie


    for (a=0; a<2; a++){
        for (b=0; b<6; b++){
            Plateau3[b][a] = Plateau1[b][a];
            Plateau4[b][a] = Plateau2[b][a];
        }
    }

    graines = Plateau4[x][y];


    do
    {
         graines = Plateau4[x][y];
         Plateau4[x][y] = 0;

         for (i = graines; i > 0; i-- )
        {
            if (y == 0)
            {
                if (x != 0)
                {
                    x = x - 1;
                    Plateau4[x][y] = Plateau4[x][y] + 1;
                    graines--;
                }
                else
                {
                    y = 1;
                    Plateau4[x][y] = Plateau4[x][y] + 1;
                    graines--;
                }
            }
            else
            {
                if (x != 5)
                {
                    x = x + 1;
                    Plateau4[x][y] = Plateau4[x][y] + 1;
                    graines--;
                }
                else
                {
                    y = 0;
                    Plateau4[x][y] = Plateau4[x][y] + 1;
                    graines--;
                }
            }

        }
    }
    while (Plateau4[x][y] != 1);

     //Si la graine tombe dans une case vide alors :
     //Si c'est sur Plateau2[x][1] il ne se passe rien c'est à joueur 1 de jouer
     //Si c'est sur Plateau2[x][0], les graines sur Plateau1[x][0] et Plateau1[x][1] sont volées
     // /!\ Si Plateau1[x][1] est vide il ne se passe rien et c'est à Joueur2 de jouer

    if (y == 0){
        if (Plateau3[x][1] != 0){
            test2 = Plateau3[x][0];
            test2 = test2 + Plateau3[x][1];
            *test = test2;
        }
    }
}

void verif_end(int Plateau1[6][2],int Plateau2[6][2], int *test1, int *test2) // fonction permettant de vérifier si toutes les cases du Plateau1 ou Plateau2 sont vides
{
    int colonne, ligne, i, j, egg;
    srand(time(NULL));
    for (ligne=0; ligne<2; ligne++){
        for (colonne=0; colonne<6; colonne++){
            test1 = test1 + Plateau1[colonne][ligne];
        }
    }
    for (ligne=0; ligne<2; ligne++){
        for (colonne=0; colonne<6; colonne++){
            test2 = test2 + Plateau2[colonne][ligne];
        }
    }

    if (test1 == 0){
        system("cls");
        egg_b();
        sleep(1);
        wprintf(L"\n\n      F%lclicitations au joueur 2 d'avoir remport%lc la partie\n\n", 130, 130);
        sleep(3);
    }

    if (test2 == 0){
        system("cls");
        egg_b();
        sleep(1);
        wprintf(L"\n\n      F%lclicitations au joueur 1 d'avoir remport%lc la partie\n\n", 130, 130);
        sleep(3);
    }

                        //Ici on a une petite célébration si le jeu est en effet fini
    return 0;
}


void Sauvegarder(int Plateau1[6][2], int Plateau2[6][2],int *tour, int *mode)
{
    int colonne, ligne;
    FILE* f = fopen("sauvegarde.txt", "w+");    //On supprime l'ancienne sauvegarde pour réécrire la nouvelle


    if(f != NULL)       //On enregistre les deux plateaux, puis le tour du joueur et enfin le mode de jeu choisi
    {
        for (ligne=0; ligne<2; ligne++){
            for (colonne=0; colonne<6; colonne++){
                fprintf(f,"%d ",Plateau1[colonne][ligne]);
            }
        }
        for (ligne=0; ligne<2; ligne++){
            for (colonne=0; colonne<6; colonne++){
                fprintf(f,"%d ",Plateau2[colonne][ligne]);
            }
        }
        fprintf(f,"%d ",*tour);
        fprintf(f,"%d", *mode);
    }
    fclose(f);                      //On ferme le fichier de sauvegarde
    Color(8,0);
    wprintf(L"\n\nLe fichier a bien %lct%lc sauvegard%lc", 130, 130, 130);
    Color(15,0);
}

void RecupSauvegarde(int Plateau1[6][2],int Plateau2[6][2], int *tour, int *mode){
    char rep;
    int ligne, colonne, taille, rPlateau1[6], rPlateau2[6];

    FILE* f = fopen("sauvegarde.txt","r");          //On lit la sauvegarde sans pouvoir la modifier
    tour = *tour;
    mode = *mode;

    system("cls");

    if(f != NULL)
    {
        while (rep != 'O' && rep!= 'N')         //On demande si l'on veut récupérer la sauvegarde grâce à un caractère O ou N sinon on boucle jusqu'à une réponse correcte
        {
            system("cls");

            wprintf(L" Voulez-vous reprendre votre partie sauvegard%lce ? (O / N) ?",130);
            Color(7,0);
            wprintf(L"\n Attention une fois refus%lce, la sauvegarde est perdue a tout jamais.\n\n",130);
            Color(15,0);
            scanf("%c",&rep);

        }
        switch (rep){
        case 'O':

            if (fgetc(f) == EOF){                           //On test si le tableau est vide et si oui on retourne au menu principal.
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
                Color(4,0);
                printf("                                        Il n'y a pas de sauvegarde sur ce PC !\n\n");
                Color(15,0);
                sleep(3);
                system("cls");
                Menu_Principal(Plateau1, Plateau2, &tour, &mode);
            }

            for (ligne=0; ligne<2; ligne++){                  //On lit les 6 valeurs suivantes que l'on enregistre dans la ligne 1 puis 2 du Plateau 1 en utilisant un deuxième tableau comme intermédiaire
                fscanf(f, "%d %d %d %d %d %d", &rPlateau1[0], &rPlateau1[1], &rPlateau1[2], &rPlateau1[3], &rPlateau1[4], &rPlateau1[5]);
                for (colonne=0; colonne<6; colonne++){
                    Plateau1[colonne][ligne] = rPlateau1[colonne];
                }
            }
            for (ligne=0; ligne<2; ligne++){        //même chose pour le plateau 2
                fscanf(f, "%d %d %d %d %d %d", &rPlateau2[0], &rPlateau2[1], &rPlateau2[2], &rPlateau2[3], &rPlateau2[4], &rPlateau2[5]);
                for (colonne=0; colonne<6; colonne++){
                    Plateau2[colonne][ligne] = rPlateau2[colonne];
                }
            }

            fscanf(f, "%d %d", &rPlateau1[0], &rPlateau1[1]);       //On récupère enfin les deux dernières valeurs correspodantes à :
            tour = rPlateau1[0];    //Le tour du joueur
            mode = rPlateau1[1];    //Le mode de jeu

            fclose(f);

            switch (rPlateau1[1])                           //En fonction du mode de jeu choisi on lance le bon mode, au tour quitté et avec le plateau d'origine.
            {
            case 0:
                jcj(Plateau1, Plateau2, &tour, &mode);
                break;
            case 1:
                jvIA(Plateau1, Plateau2, &tour, &mode);
                break;
            case 2:
                jvIA2(Plateau1, Plateau2, &tour, &mode);
                break;
            }


            break;
        case 'N':       //En cas de refus, on supprime les données de sauvegarde et on retourne au Menu Principal
            fopen("sauvegarde.txt","w+");
            fclose(f);
            printf("\n Retour au Menu Principal !");
            break;
        }

    }
    else        //En cas d'erreur dans la lecture du fichier de sauvegarde ou si il est vide, on affiche le problème et on reviens au menu
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Color(4,0);
        printf("                                        Il n'y a pas de sauvegarde sur ce PC !\n\n");
        Color(15,0);
        sleep(3);
        system("cls");
    }
    fclose(f);
}

void egg_b()
{
    int i, j, egg;
    for (i=0; i<5000; i++)
    {
        egg = rand()%15+1;
        for (j=0; j<15; j++)
            {
                Color(15,0);
                printf(" ");
;                    }
        Color(0,egg);
        printf(" ");
        for (j=15; j>0; j--)
            {
                Color(15,0);
                printf(" ");
            }
    }
}

void Color(int couleurDuTexte,int couleurDeFond)        // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}



