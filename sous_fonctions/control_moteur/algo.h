#ifndef ALGO_H
#define ALGO_H


#include <stdint.h>
#include <stddef.h>


#define DISTANCE_FREINAGE 150
#define DISTANCE_ARRET 40


#define NB_ANGLE_DWA 9/////////// tjrs odd
#define NB_VITESSE_DWA 7
#define NB_SAMPLE_DWA 10
#define PERIODE_ECHANTILLONAGE 4


#define NB_LUT 450


enum fonction_trigo{cosinus,sinus,tangeante};


// Ce que le simulateur/RPLidar envoie au cerveau
typedef struct
{
    float *distances;
    size_t nb_mesures; // Normalement 360
} LidarScan;


// Ce que le simulateur/RPLidar envoie au cerveau
typedef struct
{
    int *distances; //en mm (une precision au milieme est largement suffisnte)
    size_t nb_mesures; // Normalement 360
} LidarScan_opti;




// La nouvelle structure d'analyse : la distance de l'obstacle le plus proche par zone
typedef struct
{
    float devant;
    float avant_droit;
    float arriere_droit;
    float arriere;
    float arriere_gauche;
    float avant_gauche;
} DistancesZones;


typedef struct
{
    float moyenne;
    short nb_mesure;
} calcul_moyenne;


typedef struct
{
    calcul_moyenne devant;
    calcul_moyenne avant_droit;
    calcul_moyenne avant_gauche;
    calcul_moyenne arriere;
    calcul_moyenne arriere_droit;
    calcul_moyenne arriere_gauche;
} moyenneZones;


typedef struct
{
    float angle_roue; // entre -1 et 1
    float vitesse; // entre 0 et 1
} commande_voiture;


typedef struct
{
    float angle;
    float vitesse;
    float score;
    int tangeante;
} couple_V_A;


typedef struct
{
    couple_V_A liste[NB_ANGLE_DWA*NB_VITESSE_DWA];
} liste_couples;


typedef struct
{
    float point[NB_ANGLE_DWA*NB_VITESSE_DWA][NB_SAMPLE_DWA][2];
}trajectoire;






// Prototypes
DistancesZones ALGO_analyser_zones(const LidarScan *scan);
DistancesZones ALGO_analyser_zones_moyenne(const LidarScan *scan);
void ALGO_decision_V1(DistancesZones *zones, commande_voiture *commandes);
void ALGO_decision_V2(DistancesZones *zones, commande_voiture *commandes);
void ALGO_decision_V3(LidarScan *scan, commande_voiture *commandes);
void ALGO_decision_V3(LidarScan *scan, commande_voiture *commandes);
float recherche_point_plus_proche(float x_sim, float y_sim, float coord [][2], int nb_elements);
void ALGO_decision_V3_optimiser(LidarScan *scan, commande_voiture *commandes);
int recherche_point_plus_proche_optimiser(int x_sim, int y_sim, int coord [][2], int nb_elements);


void ALGO_decision_V3_optimiser_LUT(LidarScan *scan, commande_voiture *commandes);


void remplir_liste_couple(int nb_vitesse,int nb_angle);
float trigo_LUTf(enum fonction_trigo,short angle);
int16_t trigo_LUT_int(enum fonction_trigo fonction, short angle);


uint16_t isqrt(uint32_t X);


void ALGO_decision_V4(LidarScan *scan, commande_voiture *commandes);


#endif // ALGO_H

