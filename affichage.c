#include "affichage.h"




void affichage(oxy myOxy){
    
/*--------------------------Déclaration des variables-------------------------------------*/
    char Verrou[]=".verrouData";
    char pszFichier[]="Data.txt";
    FILE *P_FICHIER=NULL;
    FILE *pf=NULL;
    
    sleep(0.5);

/*-------Condition if..else afin de déterminer si le fichier .verrouData existe ou non-----*/
    

    if( access( ".verrouData", F_OK ) != -1 ) {
        // Si le .verrouData existe alors on sort du programme
       
        printf("Verrou Activé");
        
    }
    
    
    else{
        // dans le cas ou le fichier n'est pas crée on va pouvoir écrire dans le fichier
        
        P_FICHIER = fopen(Verrou,"w+");// on crée un fichier .verrouData
        
        pf =fopen(pszFichier,"w+");// On ouvre le fichier Data.txt
        
        fprintf(pf,"%d\n%d",myOxy.spo2,myOxy.pouls);
            // on écrit dans le fichier "Data.txt" les valeurs des variables spo2 et pouls qui étaient dans la structure myOxy
        
        fclose(pf);// on ferme le fichier Data.txt
        
        remove(".verrouData");// on supprime le .verrouData
        fclose(P_FICHIER);
    }
}

