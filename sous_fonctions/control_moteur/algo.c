#include "algo.h"
#include "constantes.h"
#include <math.h>
//#include "simulateur.h"
#include <stdbool.h>

#define ALGO_DISTANCE_MAX 8000.0f
#define ANGLE_DE_BRAQUAGE_MAX 1 / 4.0f


//extern voiture car;


liste_couples liste;


DistancesZones ALGO_analyser_zones(const LidarScan *scan)
{


    DistancesZones zones = {
        LIDAR_RANGE_MAX,
        LIDAR_RANGE_MAX,
        LIDAR_RANGE_MAX,
        LIDAR_RANGE_MAX,
        LIDAR_RANGE_MAX,
        LIDAR_RANGE_MAX


    };


    for (int i = 0; i < (int)scan->nb_mesures; i++)
    {
        float distance = scan->distances[i];


        if (distance == 0)
        {
            continue;
        }


        float angle_deg = (float)i / scan->nb_mesures * 360;
        if (angle_deg >= 330.0f || angle_deg < 30.0f)
        {
            if (distance < zones.devant)
                zones.devant = distance;
        }


        else if (angle_deg >= 30.0f && angle_deg < 90.0f)
        {
            if (distance < zones.avant_droit)
                zones.avant_droit = distance;
        }
        else if (angle_deg >= 90.0f && angle_deg < 150.0f)
        {
            if (distance < zones.arriere_droit)
                zones.arriere_droit = distance;
        }
        else if (angle_deg >= 150.0f && angle_deg < 210.0f)
        {
            if (distance < zones.arriere)
                zones.arriere = distance;
        }
        else if (angle_deg >= 210.0f && angle_deg < 270.0f)
        {
            if (distance < zones.arriere_gauche)
                zones.arriere_gauche = distance;
        }
        else if (angle_deg >= 270.0f && angle_deg < 330.0f)
        {
            if (distance < zones.avant_gauche)
                zones.avant_gauche = distance;
        }
    }
    return zones;
}


DistancesZones ALGO_analyser_zones_moyenne(const LidarScan *scan)
{


    moyenneZones calcule_moyenne = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    DistancesZones result;


    for (int i = 0; i < (int)scan->nb_mesures; i++)
    {


        float distance = scan->distances[i];


        if (distance == 0)
        {
            continue;
        }


        float angle_deg = (float)i / scan->nb_mesures * 360;
        if (angle_deg >= 330.0f || angle_deg < 30.0f)
        {
            calcule_moyenne.devant.moyenne += distance;
            calcule_moyenne.devant.nb_mesure++;
        }


        else if (angle_deg >= 30.0f && angle_deg < 90.0f)
        {
            calcule_moyenne.avant_droit.moyenne += distance;
            calcule_moyenne.avant_droit.nb_mesure++;
        }
        else if (angle_deg >= 90.0f && angle_deg < 150.0f)
        {
            calcule_moyenne.arriere_droit.moyenne += distance;
            calcule_moyenne.arriere_droit.nb_mesure++;
        }
        else if (angle_deg >= 150.0f && angle_deg < 210.0f)
        {
            calcule_moyenne.arriere.moyenne += distance;
            calcule_moyenne.arriere.nb_mesure++;
        }
        else if (angle_deg >= 210.0f && angle_deg < 270.0f)
        {
            calcule_moyenne.arriere_gauche.moyenne += distance;
            calcule_moyenne.arriere_gauche.nb_mesure++;
        }
        else if (angle_deg >= 270.0f && angle_deg < 330.0f)
        {
            calcule_moyenne.avant_gauche.moyenne += distance;
            calcule_moyenne.avant_gauche.nb_mesure++;
        }
    }


    result.arriere = calcule_moyenne.arriere.moyenne / calcule_moyenne.arriere.nb_mesure;
    result.arriere_gauche = calcule_moyenne.arriere_gauche.moyenne / calcule_moyenne.arriere_gauche.nb_mesure;
    result.arriere_droit = calcule_moyenne.arriere_droit.moyenne / calcule_moyenne.arriere_droit.nb_mesure;
    result.devant = calcule_moyenne.devant.moyenne / calcule_moyenne.devant.nb_mesure;
    result.avant_droit = calcule_moyenne.avant_droit.moyenne / calcule_moyenne.avant_droit.nb_mesure;
    result.avant_gauche = calcule_moyenne.avant_gauche.moyenne / calcule_moyenne.avant_gauche.nb_mesure;


    return result;
}


void ALGO_decision_V1(DistancesZones *zones, commande_voiture *commandes)
{


    if (zones->devant > DISTANCE_FREINAGE) // pas de mur devant
    {
        commandes->vitesse = 0.5f;
    }
    else if (zones->devant < DISTANCE_ARRET)
    { // mur juste devant
        commandes->vitesse = 0.05f;
    }
    else
    { // mur encore un peu loin
        commandes->vitesse = 0.3f;
    }


    float difference = zones->avant_droit - zones->avant_gauche;


    if (difference > -20.0f && difference < 20.0f)
    {
        // Les distances sont presque égales, on va TOUT DROIT
        commandes->angle_roue = 0.0f;
    }
    else if (zones->avant_droit > zones->avant_gauche)
    {
        // Vraiment plus de place à DROITE, on braque à droite (fixe)
        commandes->angle_roue = 0.5f;
    }
    else
    {
        // Vraiment plus de place à GAUCHE, on braque à gauche (fixe)
        commandes->angle_roue = -0.5f;
    }


    if (commandes->angle_roue > 1)
    {
        commandes->angle_roue = 1;
    }
    else if (commandes->angle_roue < -1)
    {
        commandes->angle_roue = -1;
    }
    if (commandes->vitesse > 1)
    {
        commandes->vitesse = 1;
    }
    else if (commandes->vitesse < 0)
    {
        commandes->vitesse = 0;
    }
}


void ALGO_decision_V2(DistancesZones *zones, commande_voiture *commandes)
{
    static float erreur_angle;
    static float previous_error_angle;
    float KP_angle = 0.01, KD_angle = 0.01;///////////////// a modifier kp stabilsation kd virage rapide
    previous_error_angle = erreur_angle;


    erreur_angle = zones->avant_droit - zones->avant_gauche;


    commandes->angle_roue = erreur_angle * KP_angle + (erreur_angle - previous_error_angle) * KD_angle;


    commandes->vitesse = expf(-zones->devant / 500);///////////////////modifier valeur si trop rapide
}


int meilleur_score_index;
trajectoire traj;
void ALGO_decision_V3(LidarScan *scan, commande_voiture *commandes)
{
    couple_V_A meilleur_score = {0, 0, 0};
    meilleur_score.score = (float)0xFFFFFFFF;


    meilleur_score_index = 0;


    float Kdist = 0.05, Kvit = 10.0, Kcap = 2.0, Kbraquage = 3.0;//////////////////// cap | vit si il s'arrete


    float coordonee_cartesien[LIDAR_NB_RAYON][2];
    int nb_coordone_cart = 0;
    float angle_cible;
    float distance_max = 0;
    for (int i = 0; i < (int)scan->nb_mesures; i++)
    {
        float angle;
        float distance = scan->distances[i];
        angle = ((float)i / scan->nb_mesures) * 2 * M_PI;
        if (distance <= LIDAR_RANGE_MAX && distance >= 1.0f)
        {


            coordonee_cartesien[nb_coordone_cart][0] = distance * cosf(angle);
            coordonee_cartesien[nb_coordone_cart][1] = distance * sinf(angle);
            nb_coordone_cart++;
        }


        if (distance > distance_max)
        {
            distance_max = distance;
            angle_cible = angle;
        }
    }


    float dist_min = (float)0x7FFFFFFF;;


    for (int i = 0; i < NB_ANGLE_DWA * NB_VITESSE_DWA; i++)
    {
        float x_cible = 300.0f, y_cible = 0.0f;
        float x_sim = 0, y_sim = 0;


        float dist_min_tout = (float)0x7FFFFFFF;;


        float vitesse_sim = liste.liste[i].vitesse;
        float angle_sim = 0;
        float braquage_sim = liste.liste[i].angle * M_PI / 4.0f;
        float score_sim = (float)0x7FFFFFFF;;


        for (int t = 0; t < NB_SAMPLE_DWA; t++)
        {
            x_sim += vitesse_sim * cosf(angle_sim) * PERIODE_ECHANTILLONAGE;
            y_sim += vitesse_sim * sinf(angle_sim) * PERIODE_ECHANTILLONAGE;
            angle_sim += vitesse_sim / 30 * tanf(braquage_sim) * PERIODE_ECHANTILLONAGE;


            dist_min = recherche_point_plus_proche(x_sim, y_sim, coordonee_cartesien, nb_coordone_cart);


            if (dist_min < 10.0f)////////////////////////////////////////////dist min pour collision donc pt modif
            {
                break;
            }
            else if (dist_min < dist_min_tout)
            {
                dist_min_tout = dist_min;
            }


            traj.point[i][t][0] = x_sim;
            traj.point[i][t][1] = y_sim;
        }


        // 5. ASTUCE DWA : Plafonner la distance pour que la voiture n'ait pas peur des murs lointains
        if (dist_min_tout > 70.0f)
        {
            dist_min_tout = 70.0f;
        }


        float score_cap = cosf(angle_cible - angle_sim);


        if (dist_min < 10.0f)
        {
            score_sim = (float)0xFFFFFFFF;;
        }
        else
        {
            score_sim = dist_min_tout * Kdist + Kvit * vitesse_sim + Kcap * score_cap;
            score_sim -= Kbraquage * fabsf(liste.liste[i].angle);
        }


        if (meilleur_score.score < score_sim)
        {
            meilleur_score.angle = liste.liste[i].angle;
            meilleur_score.vitesse = vitesse_sim;
            meilleur_score.score = score_sim;
            meilleur_score_index = i;
        }
    }
    commandes->angle_roue = meilleur_score.angle;
    commandes->vitesse = meilleur_score.vitesse;


    //SIMULATEUR_dessiner_trajectoire(traj.point, &car, meilleur_score_index);
}


float recherche_point_plus_proche(float x_sim, float y_sim, float coord[][2], int nb_elements)
{
    int result = 0;
    float min = (float)0x7FFFFFFF;
    for (int i = 0; i < nb_elements; i++)
    {
        float delta_x = x_sim - coord[i][0];
        float delta_y = y_sim - coord[i][1];
        float dist = sqrtf(delta_x * delta_x + delta_y * delta_y);
        if (dist < min)
        {
            min = dist;
            result = i;
        }
    }
    return min;
}


void ALGO_decision_V3_optimiser(LidarScan *scan, commande_voiture *commandes)
{


    couple_V_A meilleur_score = {0, 0, 0};
    meilleur_score.score = (float)0xFFFFFFFF;


    meilleur_score_index = 0;


    float Kdist = 0.1f, Kvit = 1.0f, Kcap = 2.0f, Kbraquage = 0.15f;


    int coordonee_cartesien[LIDAR_NB_RAYON][2];
    int nb_coordone_cart = 0;
    float angle_cible;
    float distance_max = 0;
    for (int i = 0; i < (int)scan->nb_mesures; i++)
    {
        float angle;
        int distance = scan->distances[i];
        angle = ((float)i / scan->nb_mesures) * 2 * M_PI;
        if (distance <= LIDAR_RANGE_MAX && distance >= LIDAR_RANGE_MIN)
        {


            coordonee_cartesien[nb_coordone_cart][0] = distance * cosf(angle);
            coordonee_cartesien[nb_coordone_cart][1] = distance * sinf(angle);
            nb_coordone_cart++;
        }


        if (distance > distance_max)
        {
            distance_max = distance;
            angle_cible = angle;
        }
    }


    uint32_t dist_min = 0xFFFFFFFF; // max


    for (int i = 0; i < NB_ANGLE_DWA * NB_VITESSE_DWA; i++)
    {
        float x_cible = 300, y_cible = 0;
        float x_sim = 0, y_sim = 0;


        // 4. CORRIGER LA LOGIQUE : Initialiser à INFINITY
        uint32_t dist_min_tout = 0xFFFFFFFF;


        float vitesse_sim = liste.liste[i].vitesse * 5;
        float angle_sim = 0;
        float braquage_sim = liste.liste[i].angle * M_PI / 4;
        float score_sim = (float)0x7FFFFFFF;
        bool colision = false;
        for (int t = 0; t < NB_SAMPLE_DWA; t++)
        {
            x_sim += vitesse_sim * cosf(angle_sim) * PERIODE_ECHANTILLONAGE;
            y_sim += vitesse_sim * sinf(angle_sim) * PERIODE_ECHANTILLONAGE;
            angle_sim += vitesse_sim / 30 * tanf(braquage_sim) * PERIODE_ECHANTILLONAGE;


            dist_min = recherche_point_plus_proche_optimiser(x_sim, y_sim, coordonee_cartesien, nb_coordone_cart);


            if (dist_min < 225)
            {
                colision = true;
                break;
            }
            else if (dist_min < dist_min_tout)
            {
                dist_min_tout = dist_min;
            }


            traj.point[i][t][0] = x_sim;
            traj.point[i][t][1] = y_sim;
        }


        float distance_final_lineaire = sqrtf((float)dist_min_tout);


        // 5. ASTUCE DWA : Plafonner la distance pour que la voiture n'ait pas peur des murs lointains
        if (distance_final_lineaire > 70.0f)
        {
            distance_final_lineaire = 70.0f;
        }


        float score_cap = cosf(angle_cible - angle_sim);


        if (colision)
        {
            score_sim = (float)0xFFFFFFFF;
        }
        else
        {
            score_sim = distance_final_lineaire * Kdist + Kvit * vitesse_sim + Kcap * score_cap;
            score_sim -= Kbraquage * fabsf(liste.liste[i].angle);
            if (meilleur_score.score < score_sim)
            {
                meilleur_score.angle = liste.liste[i].angle;
                meilleur_score.vitesse = liste.liste[i].vitesse;
                meilleur_score.score = score_sim;
                meilleur_score_index = i;
            }
        }
    }
    commandes->angle_roue = meilleur_score.angle;
    commandes->vitesse = meilleur_score.vitesse;


    // SIMULATEUR_dessiner_trajectoire(traj.point, &car, meilleur_score_index);
}


int recherche_point_plus_proche_optimiser(int x_sim, int y_sim, int coord[][2], int nb_elements)
{


    int result = 0;
    uint32_t min = 0XFFFFFFFF;
    for (int i = 0; i < nb_elements; i++)
    {
        int delta_x = x_sim - coord[i][0];
        int delta_y = y_sim - coord[i][1];
        int dist = delta_x * delta_x + delta_y * delta_y;
        if (dist < min)
        {
            min = dist;
            result = i;
        }
    }
    return min;
}


void remplir_liste_couple(int nb_vitesse, int nb_angle)
{


    for (int i = 0; i < nb_vitesse; i++) // remplissage des couples
    {
        for (int j = 0; j < nb_angle; j++)
        {
            liste.liste[i * nb_angle + j].angle = (2.0f / (nb_angle - 1)) * j - 1; // plage de -1 a 1
            liste.liste[i * nb_angle + j].vitesse = (1.0f / (nb_vitesse - 1)) * i;
            liste.liste[i * nb_angle + j].score = 0;
            liste.liste[i * nb_angle + j].tangeante = tanf(liste.liste[i * nb_angle + j].angle) * ANGLE_DE_BRAQUAGE_MAX * 1800.0f;
        }
    }
}


void ALGO_decision_V3_optimiser_LUT(LidarScan *scan, commande_voiture *commandes)
{
    couple_V_A meilleur_score = {0, 0, 0};
    meilleur_score.score = (float)0xFFFFFFFF;
    meilleur_score_index = 0;


    // Nouveaux coefficients équilibrés
    float Kdist = 0.12f;     // La distance aux murs compte beaucoup
    float Kvit = 9.0f;       // Récompense pour avancer vite
    float Kcap = 10.0f;      // Forte récompense pour rester aligné sur le cap
    float Kbraquage = 0.37f; // Pénalité stricte contre les coups de volant inutiles


    int coordonee_cartesien[LIDAR_NB_RAYON][2];
    int nb_coordone_cart = 0;
    short angle_cible_dixiemes = 0;
    int distance_max = 0;


    for (int i = 0; i < (int)scan->nb_mesures; i++)
    {
        int distance = scan->distances[i];


        short angle_dixiemes = (short)(((uint32_t)i * 3600) / scan->nb_mesures);


        if (distance <= LIDAR_RANGE_MAX && distance >= LIDAR_RANGE_MIN)
        {
            coordonee_cartesien[nb_coordone_cart][0] = (distance * trigo_LUT_int(cosinus, angle_dixiemes)) >> 15;
            coordonee_cartesien[nb_coordone_cart][1] = (distance * trigo_LUT_int(sinus, angle_dixiemes)) >> 15;
            nb_coordone_cart++;
        }


        if (distance > distance_max && (angle_dixiemes > 3000 || angle_dixiemes < 600))
        {
            distance_max = distance;
            angle_cible_dixiemes = angle_dixiemes;
        }
    }






    // --- 2. LA BOUCLE HAUTE PERFORMANCE DWA ---
    for (int i = 0; i < NB_ANGLE_DWA * NB_VITESSE_DWA; i++)
    {
        int32_t x_sim_q15 = 0;
        int32_t y_sim_q15 = 0;


        uint32_t dist_min_tout_carre = 0xFFFFFFFF;


        float vitesse_reelle = liste.liste[i].vitesse;
        float vitesse_sim = vitesse_reelle * 5.0f;


        short angle_sim_dixiemes = 0;
        float score_sim = (float)0x7FFFFFFF;
        bool colision = false;
        short delta_angle = (vitesse_sim / 30 * liste.liste[i].tangeante * PERIODE_ECHANTILLONAGE);


        for (int t = 0; t < NB_SAMPLE_DWA; t++)
        {
            x_sim_q15 += (int32_t)(vitesse_sim * trigo_LUT_int(cosinus, angle_sim_dixiemes) * PERIODE_ECHANTILLONAGE);
            y_sim_q15 += (int32_t)(vitesse_sim * trigo_LUT_int(sinus, angle_sim_dixiemes) * PERIODE_ECHANTILLONAGE);


            int x_sim_reel = x_sim_q15 >> 15;
            int y_sim_reel = y_sim_q15 >> 15;


            angle_sim_dixiemes += delta_angle;


            uint32_t dist_min_carre = recherche_point_plus_proche_optimiser(x_sim_reel, y_sim_reel, coordonee_cartesien, nb_coordone_cart);


            if (dist_min_carre < 800) // 225 = 15^2
            {
                colision = true;
                break;
            }
            else if (dist_min_carre < dist_min_tout_carre)
            {
                dist_min_tout_carre = dist_min_carre;
            }


            // On transmet les coordonnées réelles pour le simulateur Raylib
            traj.point[i][t][0] = (float)x_sim_reel;
            traj.point[i][t][1] = (float)y_sim_reel;
        }


        // --- 3. LE CALCUL DU SCORE (Ici on s'autorise les floats pour l'équilibre final) ---
        if (colision)
        {
            score_sim = (float)0xFFFFFFFF;
        }
        else
        {
            uint16_t distance_final_lineaire = isqrt(dist_min_tout_carre);


            if (distance_final_lineaire > 150)
                distance_final_lineaire = 150;


            // valeur Q15 en un float compris entre -1.0 et 1.0
            float score_cap_float = (float)trigo_LUT_int(cosinus, angle_cible_dixiemes - angle_sim_dixiemes) / 32767.0f;
            // Calcul du score global
            score_sim = distance_final_lineaire * Kdist + Kvit * vitesse_reelle + Kcap * score_cap_float;
            score_sim -= Kbraquage * fabsf(liste.liste[i].angle);


            if (meilleur_score.score < score_sim)
            {
                meilleur_score.angle = liste.liste[i].angle;
                meilleur_score.vitesse = vitesse_reelle;
                meilleur_score.score = score_sim;
                meilleur_score_index = i;
            }
        }
    }


    commandes->angle_roue = meilleur_score.angle;
    commandes->vitesse = meilleur_score.vitesse;
}


int16_t trigo_LUT_int(enum fonction_trigo fonction, short angle)
{
    extern int16_t LUT_TRIGO_INT[NB_LUT];


    switch (fonction)
    {
    case sinus:
        angle -= 900;
    case cosinus:
        // Normalisation de l'angle
        while (angle < -1800)
            angle += 3600;
        while (angle > 1800)
            angle -= 3600;


        // Aiguillage des quadrants avec la mise à l'échelle pour 450 valeurs
        if (angle < -900)
            return -LUT_TRIGO_INT[(uint32_t)(1800 + angle) * (NB_LUT - 1) / 900];
        else if (angle < 0)
            return LUT_TRIGO_INT[(uint32_t)(-angle) * (NB_LUT - 1) / 900];
        else if (angle > 900)
            return -LUT_TRIGO_INT[(uint32_t)(1800 - angle) * (NB_LUT - 1) / 900];
        else
            return LUT_TRIGO_INT[(uint32_t)angle * (NB_LUT - 1) / 900];


    default:
        return 0;
    }
}


uint16_t isqrt(uint32_t X)
{


    uint16_t result = 0;


    for (int i = 0; i < 16; i++)
    {
        uint32_t test = result | (1 << (15 - i));
        if ((test * test) <= X)
        {
            result |= (1 << (15 - i));
        }
    }
    return result;
}

