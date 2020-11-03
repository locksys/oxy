#include "mesure.h"
#include "fichiers.h"





oxy mesureTest(char* filename){
	
    
    /* Déclaration des mémoires des variables (acr, acir, dcr,dcir) issue de la structure absorp
     Les initialiser en temps que pointeur permet de pouvoir modifier leur valeur dans la fonction "mesure" et pouvoir les stocker en mémoire pour chaque tour de boucle   */
    
    //Initialisation des mémoires extérieures lié à la variable acr
    int *mem_acr_max=malloc(1*sizeof(int));
    mem_acr_max[0]=0;
    
    int *mem_acr_min=malloc(1*sizeof(int));
    mem_acr_min[0]=0;
    
    int *mem_acr_precedent=malloc(1*sizeof(int));
    mem_acr_precedent[0]=0;
    
    float *mem_acr_ptp=malloc(1*sizeof(float));
    mem_acr_ptp[0]=0;
    
    //Initialisation des mémoires extérieures lié à la variable acir
    int *mem_acir_max=malloc(1*sizeof(int));
    mem_acir_max[0]=0;
    
    int *mem_acir_min=malloc(1*sizeof(int));
    mem_acir_min[0]=0;
    
    int *mem_acir_precedent=malloc(1*sizeof(int));
       mem_acir_precedent[0]=0;
    
    float *mem_acir_ptp=malloc(1*sizeof(float));
       mem_acir_ptp[0]=0;
    
    //Initialisation des pointeurs sur les compteurs
    int* compteur1 = malloc(1*sizeof(int));
    compteur1[0]=0;
    int* compteur2 = malloc(1*sizeof(int));
    compteur2[0]=0;
    int* compteur3 = malloc(1*sizeof(int));
    compteur3[0]=0;
    int* compteur4 = malloc(1*sizeof(int));
    compteur4[0]=0;
    
    //Initialisation des variables et des structures
    int etat=0,compteur=0, compteurbis=0;
    absorp test,myAbsorp;
    oxy myOxy;
    
    /*On parcourt une première fois le fichier afin de connaitre le nombre de valeurs*/
    
     FILE* fichier=initFichier(filename);
    // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
     
     // On fait une boucle while afin de connaître combien de boucle on doit réaliser dans notre do while afin de s'arrêter à la derniere ligne du fichier
     while(etat!=EOF){
         test=lireFichier(fichier,&etat);
         compteur++;
     }
     
     finFichier(fichier);// on ferme le fichier
    
    
    /*  Parcours du fichier "record1_fir.dat" en modifiant les valeurs des variables acr et acir présentent dans la structure absorp.   */
    
     FILE* fichier1=initFichier(filename);
    // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
     
     do{
         myAbsorp=lireFichier(fichier1,&etat);
         // Appel de la fonction lire Fichier qui va retourner une structure de la forme absorp contenant 4 valeurs lues dans le fichier
         
         
         myOxy=mesure(compteur1,compteur2,compteur3,compteur4,mem_acr_max,mem_acir_max,mem_acr_min,mem_acir_min,mem_acr_precedent,mem_acir_precedent, mem_acr_ptp,mem_acir_ptp,myAbsorp);
         // printf("valeur suivante :\nacr : %f\nacir : %f dcir: %f dcr :%f \n\n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcir, myAbsorp.dcr);
         
         compteurbis++;
         //on incrémente le compteurbis
         
     }while(compteur!=(compteurbis+1));
    // On sort de la boucle while lorsque compteur==compteurbis+1 autrement dit lorsque l'on a parcouru l'ensemble du fichier
        
/*-------------------------Liberation des mémoires---------------------------------------*/

    free(compteur1);
    free(compteur2);
    free(compteur3);
    free(compteur4);
    free(mem_acr_max);
    free(mem_acr_min);
    free(mem_acir_max);
    free(mem_acir_min);
    free(mem_acr_precedent);
    free(mem_acir_precedent);
    free(mem_acr_ptp);
    free(mem_acir_ptp);
    finFichier(fichier1);
	return myOxy;

}



oxy mesure(int* compteur1,int* compteur2,int* compteur3,int* compteur4,int* mem_acr_max,int* mem_acir_max,int* mem_acr_min,int* mem_acir_min,int* mem_acr_precedent,int* mem_acir_precedent,float* mem_acr_ptp,float* mem_acir_ptp,absorp myAbsorp)
{
    
    /*Déclaration de la structure myOxy et initialisation des variables de pouls et spo2*/
    
    oxy myOxy;
    myOxy.pouls=0;
    myOxy.spo2=0;
    
    /*Déclarations variables*/
    float ratio=0;
    
    /*-------------------------------CALCUL DU POULS--------------------------------------*/
    
    
    /*Remise à 0 des valeurs maximums et minimums */
    
    //Passage à 0 dans le sens décroissant-> Remise à 0 du minimum dans le cas d'un front descendant
    if(*mem_acr_precedent>=0 && myAbsorp.acr<0){
        *mem_acr_min=0;
    }
    
    //Passage à 0 dans le sens croissant -> Remise à 0 du maximum dans le cas d'un front montant et on on donne la valeur de compteur 1 dans le compteur 2
    if(myAbsorp.acr>=0 && *mem_acr_precedent<0){
        *mem_acr_max=0;
        *compteur2=(*compteur1);//Le compteur2 corresponds au nombre de point sur une période
        *compteur1=0;// on remet le compteur 1 à 0 pour pouvoir re calculer le nombre de point ACR qu'on a par période ( car période change au début)
    }
    
   // On incrémente le compteur1 pour signifier que l'on passe à une nouvelle valeur de acr
    *compteur1=(*compteur1)+1;
    
    
    
    /*Calcul période pour ACIR*/
    
    //Passage à 0 dans le sens décroissant
       if(*mem_acir_precedent>=0 && myAbsorp.acir<0){
           *mem_acir_min=0;
       }
       
       //Passage à 0 dans le sens croissant
       if(myAbsorp.acir>=0 && *mem_acir_precedent<0){
           *mem_acir_max=0;
           *compteur3=(*compteur4);//compteur3 correspond au nombre de point d'acir dans une période
           *compteur4=0;
       }
       
        *compteur4=(*compteur4)+1;
    // On incrémente le compteur1 pour signifier que l'on passe à une nouvelle valeur de acir

    
    /*On affecte les valeurs lues dans le fichier pour acr et acir au pointeur qui stocke la valeur précedente*/
    
    *mem_acr_precedent=myAbsorp.acr;
    *mem_acir_precedent=myAbsorp.acir;
    
    
    /*----------------------------Calcul du pouls---------------------------------------- */
    
    
    //On vérifie seulement le cas  *compteur2 ==*compteur1 lors du premier tour de boucle car compteur2=compteur1=compteur3=compteur4=0 -> on aurait une valeur infinie
     if (*compteur2 != *compteur1 || *compteur4 != *compteur3) {
         
         myOxy.pouls = 60 / ((*compteur2 + *compteur3) * 0.001);
         // Calcul du pouls (*compteur2+*compteur3 représentent une moyenne du nombre de point d'acr et de acir sur une période)
         //printf("Le pouls vaut : %d\n", myOxy.pouls);
       }
    
    
    
    /*---------------------CALCUL SPO2----------------------------------------------------*/
    
    /*Pour ACR*/
    //Calcul du maximum sur 1 période
    if(*mem_acr_max<myAbsorp.acr){
        *mem_acr_max=myAbsorp.acr;
    }
    //Calcul du minimum sur 1 période
    if(*mem_acr_min>myAbsorp.acr){
        *mem_acr_min=myAbsorp.acr;
    }
    
    /*Pour ACIR*/
    
    //Calcul du maximum sur 1 période
    if (*mem_acir_max<myAbsorp.acir){
        
        *mem_acir_max=myAbsorp.acir;// on mémorise le maximum piur acr
    }
    
    //Calcul du minimum sur 1 période
    if(*mem_acir_min>myAbsorp.acir){
        
        *mem_acir_min=myAbsorp.acir;//on mémorise le minimum pour acir
    }
    
    /*---------------------Calcul des valeurs peak to peak--------------------------------*/
    
    *mem_acr_ptp=(*mem_acr_max - *mem_acr_min);
    *mem_acir_ptp=(*mem_acir_max - *mem_acir_min);
    
    
    
    /*-------------------------Calcul du ratio---------------------------------------------*/
    
    ratio=((*mem_acr_ptp/myAbsorp.dcr)/(*mem_acir_ptp/myAbsorp.dcir));
    
    if(ratio<=1){
        myOxy.spo2=((-25 *ratio)+110);//pente de la droite calculer sur le graphique
    }
    if(ratio>1){
        myOxy.spo2=((-35 * ratio) + 120);//pente de la droite calculer sur le graphique
    }
   //printf("Spo2:%d  Pouls: %d\n",myOxy.spo2,myOxy.pouls);
    return myOxy;
    
}
