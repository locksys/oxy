#include "iir.h"
#include "fichiers.h"




absorp iirTest(char* filename){
    
    
/*---------------------------Déclaration des variables------------------------------------*/
    
    absorp	myAbsorp, test;
    int i,etat=0,compteur=0,compteurbis=0;
   
    float* mem_acr_iir=malloc(2*sizeof(float));
    //initialisation du pointeur mem_acr qui pointe sur un tableau de 2 cases mémoires
    float* mem_acir_iir=malloc(2*sizeof(float));
    //initialisation du pointeur mem_acir qui pointe sur un tableau de 2 cases mémoires
    
    
    
    
/*-----Boucle For qui va permettre d'initialiser les valeurs des tableaux mem_acr et mem_acir
        On initialise toutes les valeurs à 0 car pour appliquer la formule dans le iir on a besoin des valeurs précedentes. Dans le cas du première appel de la fonction on n'aura pas de valeurs précedente stocké donc nous les initialisons à 0 par défault.----------------------------------------------------------------------*/
    
    for(i=0;i<2;i++){
        mem_acr_iir[i]=0;
        mem_acir_iir[i]=0;
    }
    
    
/*------On parcourt une première fois le fichier afin de connaitre le nombre de valeurs----*/
    
    FILE* fichier=initFichier(filename);
    // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
    
    // On fait une boucle while afin de connaître combien de boucle on doit réaliser dans notre do while afin de s'arrêter à la derniere ligne du fichier
    while(etat!=EOF){
        test=lireFichier(fichier,&etat);
        compteur++;
        //On caclul le nombre de tour de boucle en incrementant compteur1
    }
    
    finFichier(fichier);// on ferme le fichier
    
    
    
    
/*------------Parcours du fichier "record1_fir.dat" en modifiant les valeurs des variables acr et acir présentent dans la structure absorp.--------------------------------------*/
    
    FILE* fichier1=initFichier(filename);
    // appel de la fonction initFichier qui va ouvrir le fichier et nous retourner le pointeur sur le fichier
    
    
    do{
        myAbsorp=lireFichier(fichier1,&etat);
        // Appel de la fonction lire Fichier qui va retourner une structure de la forme absorp contenant 4 valeurs lu dans le fichier
        
        
        //printf("valeur suivante :\nacr : %f\nacir : %f dcir: %f dcr :%f \n\n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcir, myAbsorp.dcr);
        
        iir(&myAbsorp,mem_acr_iir,mem_acir_iir);
        // on appelle la fonction iir
        
        // getchar();// permet de faire tour par tour
        compteurbis++;
        //on incrémente le compteur2
        
    }while(compteur!=(compteurbis+1));
    // On sort de la boucle while lorsque compteur1==compteur2+1 autrement dit lorsque l'on a parcouru l'ensemble du fichier
    
    
/*-------On libère la mémoire de nos 2 pointeurs sur les tableaux mem_acir et mem_acr------*/
    
    free(mem_acir_iir);
    free(mem_acr_iir);
    
    finFichier(fichier1);// on ferme le fichier1
	return myAbsorp;

}

void iir(absorp* myAbsorp,float* mem_acr_iir,float* mem_acir_iir){
    
    
/*--------------------------Déclaration des variables-------------------------------------*/
    float alpha = 0.992;
    float sortie_acr,sortie_acir;
    
/*--------------On applique la formule du Filtre pour la variable acr---------------------*/
    
    
    sortie_acr= myAbsorp->acr - mem_acr_iir[0] + alpha * mem_acr_iir[1];
    
/*------on met la valeur precedente de acr et de sortie_acr dans le tableau mem_acr[0] et mem_acr[1]---------------------------------------------------------------------------*/
   
    mem_acr_iir[0] = myAbsorp->acr;
    mem_acr_iir[1] = sortie_acr;
    
    
/*------------On applique la formule du Filtre pour la variable acir-----------------------*/
    sortie_acir= myAbsorp->acir - mem_acir_iir[0] + alpha * mem_acir_iir[1];
    
    
    
/*---------on met la valeur precedente de acir et de sortie_acir dans le tableau mem_acir[0] et mem_acir[1]-----------------------------------------------------------------------*/
    mem_acir_iir[0] = myAbsorp->acir;
    mem_acir_iir[1] = sortie_acir;
    
/*-On modifie la structure myAbsorp par le biais d'un pointeur qui pointe sur la structure-*/
   
    myAbsorp->acr = sortie_acr;// On place la nouvelle valeurs calculer par la formule dans la structure
    myAbsorp->acir = sortie_acir;
    
    
}



