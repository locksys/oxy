#include "fir.h"
#include "fichiers.h"




absorp firTest(char* filename){
    
/*-----------------------Déclaration des variables-----------------------------------------*/
	absorp  myAbsorp, test;
     int i,etat=0,compteur=0,compteurbis=0;
     float* mem_acr_fir=malloc(51*sizeof(float));
    //initialisation du pointeur mem_acr qui pointe sur un tableau de 50 cases mémoires
     float* mem_acir_fir=malloc(51*sizeof(float));
    //initialisation du pointeur mem_acr qui pointe sur un tableau de 50 cases mémoires
     
    
    
/*-----Boucle For qui va permettre d'initialiser les valeurs des tableaux mem_acr et mem_acir
            On initialise toutes les valeurs à 0 car pour appliquer la formule dans le iir on a besoin des valeurs précedentes. Dans le cas du première appel de la fonction on n'aura pas de valeurs précedente stocké donc nous les initialisons à 0 par défault.----------------------------------------------*/
     for(i=0;i<50;i++){
         mem_acr_fir[i]=0;
         mem_acir_fir[i]=0;
     }
     
/*------On parcourt une première fois le fichier afin de connaitre le nombre de valeurs----*/
    
     FILE* fichier=initFichier(filename);
    // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
     
     // On fait une boucle while afin de connaître combien de boucle on doit réaliser dans notre do while afin de s'arrêter à la derniere ligne du fichier
     while(etat!=EOF){
         test=lireFichier(fichier,&etat);
         compteur++;
     }
     
     finFichier(fichier);// on ferme le fichier
    
    
/*----------Parcours du fichier "record1_fir.dat" en modifiant les valeurs des variables acr et acir présentent dans la structure absorp.-------------------------------------------*/
    
     FILE* fichier1=initFichier(filename);
    // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
     
     do{
         myAbsorp=lireFichier(fichier1,&etat);
         // Appel de la fonction lire Fichier qui va retourner une structure de la forme absorp contenant 4 valeurs lu dans le fichier
         
         
         fir(&myAbsorp,mem_acr_fir,mem_acir_fir);//Appel de la fonction fir
         
         // printf("valeur suivante :\nacr : %f\nacir : %f dcir: %f dcr :%f \n\n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcir, myAbsorp.dcr);
         
         compteurbis++;
         //on incrémente le compteur2
         
     }while(compteur!=(compteurbis+1));
    // On sort de la boucle while lorsque compteur1==compteur2+1 autrement dit lorsque l'on a parcouru l'ensemble du fichier
        
        
/*---------On libère la mémoire de nos 2 pointeurs sur les tableaux mem_acir et mem_acr----*/
    
    
     free(mem_acir_fir);// on libère la mémoire du pointeur sur le tableau mem_acir
     free(mem_acr_fir);// on libère la mémoire du pointeur sur le tableau mem_acr
    
     finFichier(fichier1);// on ferme le fichier1 "record1_fir.dat"
    
     return myAbsorp;

}



void fir(absorp* myAbsorp,float* mem_acr_fir,float* mem_acir_fir){
    
/*----------------------------Déclaration des variables------------------------------------*/
    int i=0;
    //Tableau des valeurs des coefficient K
    float FIR_TABLEAU[51]=
    { 1.4774946e-019,
      1.6465231e-004,
      3.8503956e-004,
      7.0848037e-004,
      1.1840522e-003,
      1.8598621e-003,
      2.7802151e-003,
      3.9828263e-003,
      5.4962252e-003,
      7.3374938e-003,
      9.5104679e-003,
      1.2004510e-002,
      1.4793934e-002,
      1.7838135e-002,
      2.1082435e-002,
      2.4459630e-002,
      2.7892178e-002,
      3.1294938e-002,
      3.4578348e-002,
      3.7651889e-002,
      4.0427695e-002,
      4.2824111e-002,
      4.4769071e-002,
      4.6203098e-002,
      4.7081811e-002,
      4.7377805e-002,
      4.7081811e-002,
      4.6203098e-002,
      4.4769071e-002,
      4.2824111e-002,
      4.0427695e-002,
      3.7651889e-002,
      3.4578348e-002,
      3.1294938e-002,
      2.7892178e-002,
      2.4459630e-002,
      2.1082435e-002,
      1.7838135e-002,
      1.4793934e-002,
      1.2004510e-002,
      9.5104679e-003,
      7.3374938e-003,
      5.4962252e-003,
      3.9828263e-003,
      2.7802151e-003,
      1.8598621e-003,
      1.1840522e-003,
      7.0848037e-004,
      3.8503956e-004,
      1.6465231e-004,
      1.4774946e-019};
    
    float sortie_acr = 0;
    float sortie_acir = 0;
    
/*------------Affectation des valeurs acr acir lues dans le fichier record1.dat aux tableaux mem_acr et mem_acir à l'adresse 50---------------------------------------------------*/
    
    mem_acr_fir[50] = myAbsorp->acr;
    mem_acir_fir[50] = myAbsorp->acir;
    
    
/*-----Boucle For afin de réaliser la même fonction qu'une somme présente dans la formule--*/
    
    for(i=0;i<51;i++){
        
        sortie_acr = sortie_acr + FIR_TABLEAU[i] * mem_acr_fir[50-i];
        // calcul de la nouvelle variable ACR en sortie du filtre pour chaque i
        sortie_acir = sortie_acir + FIR_TABLEAU[i] * mem_acir_fir[50-i];
        // calcul de la nouvelle variable ACIR en sortie du filtre pour chaque i
    }
    
    
    
/*-------Boucle For afin de réaliser un décalage dans les tableaux mem_acr et mem_acir----*/
    
    for (i=0; i<50; i++){
      mem_acr_fir[i]=mem_acr_fir[i+1];                    // decalage de la memoire de acr
      mem_acir_fir[i]=mem_acir_fir[i+1];                  // decalage de la memoire de acir
    }
    
    //on affecte la valeur de la place 0 dans le tableau a la place 50 dans le tableau
    mem_acr_fir[50]=mem_acr_fir[0];
    mem_acir_fir[50]=mem_acir_fir[0];
    
/*----------------On modifie les valeurs de la structure myAbsorp a l'aide d'un pointeur qui pointe sur la structure---------------------------------------------------------------*/
    
    myAbsorp->acr = sortie_acr;                                                       // affectation des nouvelles valeurs de Acr dans la structure
    myAbsorp->acir = sortie_acir;                                                     // affectation des nouvelles valeurs de Acir dans la structure
    
}
