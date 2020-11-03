#include "integration.h"
#include "fichiers.h"
#include "iir.h"
#include "fir.h"
#include "mesure.h"
#include "affichage.h"
#include "define.h"






void integrationTest(char* filename)
{
    int i,etat=0,compteur=0,compteurbis=0;
    oxy myOxyFinal;
    myOxyFinal.pouls=0;
    myOxyFinal.spo2=0;
/*----------------------------Initialisation de fir---------------------------------------*/
    
    
    float* mem_acr_fir=malloc(51*sizeof(float));
       //initialisation du pointeur mem_acr qui pointe sur un tableau de 50 cases mémoires
    float* mem_acir_fir=malloc(51*sizeof(float));
       //initialisation du pointeur mem_acr qui pointe sur un tableau de 50 cases mémoires
        
       
       
         /*  Boucle For qui va permettre d'initialiser les valeurs des tableaux mem_acr et mem_acir
               On initialise toutes les valeurs à 0 car pour appliquer la formule dans le iir on a besoin des valeurs précedentes. Dans le cas du première appel de la fonction on n'aura pas de valeurs précedente stocké donc nous les initialisons à 0 par défault.   */
        for(i=0;i<50;i++){
            mem_acr_fir[i]=0;
            mem_acir_fir[i]=0;
        }
        
    
    
    
    
    
/*----------------------------Initialisation de iir----------------------------------------*/
    
    
        float* mem_acr_iir=malloc(2*sizeof(float));
           //initialisation du pointeur mem_acr qui pointe sur un tableau de 2 cases mémoires
        float* mem_acir_iir=malloc(2*sizeof(float));
           //initialisation du pointeur mem_acir qui pointe sur un tableau de 2 cases mémoires
           
           
        for(i=0;i<2;i++){
               mem_acr_iir[i]=0;
               mem_acir_iir[i]=0;
           }
           
    
/*----------------------------Initialisation de mesure-------------------------------------*/
    
    int *mem_acr_max=malloc(1*sizeof(float));
    mem_acr_max[0]=0;
    
    int *mem_acr_min=malloc(1*sizeof(float));
    mem_acr_min[0]=0;
    
    int *mem_acr_precedent=malloc(1*sizeof(float));
    mem_acr_precedent[0]=0;
    
    float *mem_acr_ptp=malloc(1*sizeof(float));
    mem_acr_ptp[0]=0;
    
    //Initialisation des mémoires extérieures lié à la variable acir
    int *mem_acir_max=malloc(1*sizeof(float));
    mem_acir_max[0]=0;
    
    int *mem_acir_min=malloc(1*sizeof(float));
    mem_acir_min[0]=0;
    
    int *mem_acir_precedent=malloc(1*sizeof(float));
       mem_acir_precedent[0]=0;
    
    float *mem_acir_ptp=malloc(1*sizeof(float));
       mem_acir_ptp[0]=0;
    
    //Initialisation des compteurs
    int* compteur1 = malloc(1*sizeof(float));
    compteur1[0]=0;
    int* compteur2 = malloc(1*sizeof(float));
    compteur2[0]=0;
    int* compteur3 = malloc(1*sizeof(float));
    compteur3[0]=0;
    int* compteur4 = malloc(1*sizeof(float));
    compteur4[0]=0;
    
    
/*-----On parcourt une première fois le fichier afin de connaitre le nombre de valeurs----*/
       
        absorp test, myAbsorp;
        FILE* fichier=initFichier(filename);
       // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
    
        // On fait une boucle while afin de connaître combien de boucle on doit réaliser dans notre do while afin de s'arrêter à la derniere ligne du fichier
        while(etat!=EOF){
            test=lireFichier(fichier,&etat);
            compteur++;
            
        }
   
        finFichier(fichier);// on ferme le fichier
       
       
/*---------------Parcours du fichier "record1_fir.dat" en modifiant les valeurs des variables acr et acir présentent dans la structure absorp.----------------------------*/

        FILE* fichier1=initFichier(filename);
       // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
    
        do{
            myAbsorp=lireFichier(fichier1,&etat);
            // Appel de la fonction lire Fichier qui va retourner une structure de la forme absorp contenant 4 valeurs lu dans le fichier
            
            
            fir(&myAbsorp, mem_acr_fir, mem_acir_fir);
            iir(&myAbsorp,mem_acr_iir,mem_acir_iir);
            //printf("acr : %f acir : %f",myAbsorp.acr, myAbsorp.acir);
            
          myOxyFinal=mesure(compteur1,compteur2,compteur3,compteur4,mem_acr_max,mem_acir_max, mem_acr_min,mem_acir_min, mem_acr_precedent,mem_acir_precedent, mem_acr_ptp,mem_acir_ptp,myAbsorp);
            
            printf("sortie de mesure : pouls : %d spo2 :%d\n",myOxyFinal.pouls,myOxyFinal.spo2 );
           affichage(myOxyFinal);
           // printf("sortie de affichage : pouls : %d spo2 :%d\n",myOxyFinal.pouls,myOxyFinal.spo2 );
            // printf("valeur suivante :\nacr : %f\nacir : %f dcir: %f dcr :%f \n\n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcir, myAbsorp.dcr);
            
            compteurbis++;
            
        }while(compteur!=(compteurbis+1));
       // On sort de la boucle while lorsque compteur1==compteur2+1 autrement dit lorsque l'on a parcouru l'ensemble du fichier
         
    
    
/*----------------libération des pointeurs de tous les fichiers---------------------------*/
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
       free(mem_acir_fir);// on libère la mémoire du pointeur sur le tableau mem_acir
       free(mem_acr_fir);// on libère la mémoire du pointeur sur le tableau mem_acr
       free(mem_acir_iir);
       free(mem_acr_iir);
       finFichier(fichier1);
               
}




