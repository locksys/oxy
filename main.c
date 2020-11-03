//
//  main.c
//  Language C Isen
//
//  Created by SOULABAIL on 28/02/2020.
//  Copyright © 2020 SOULABAIL. All rights reserved.
//

#include "main.h"



int main(){
    absorp myAbsorp;
    oxy myOxy;
    myOxy.pouls=0;
    myOxy.spo2=0;
    
/*----------------------------Test pour Affichage------------------------------------------*/
    
//    affichage(myOxy);
    
/*------------------------------Test pour IIR----------------------------------------------*/
   
 //   myAbsorp=iirTest("record1_fir.dat");
    
 //   printf(" ACR : %f ACIR: %f DCR: %f DCIR : %f\n",myAbsorp.acr,myAbsorp.acir,myAbsorp.dcr,myAbsorp.dcir);
    
/*-----------------------------Test pour FIR----------------------------------------------*/
    
  //  myAbsorp=firTest("record1.dat");
    
   // printf(" ACR : %f ACIR: %f DCR: %f DCIR : %f\n",myAbsorp.acr,myAbsorp.acir,myAbsorp.dcr,myAbsorp.dcir);
    
/*-----------------------------Test pour mesure-------------------------------------------*/
    
   // myOxy=mesureTest("record1_iir.dat");
    
   // printf("Pouls : %d Spo2: %d\n",myOxy.pouls,myOxy.spo2);
    
/*----------------------------Test pour integration---------------------------------------*/
    integrationTest("record1.dat");
    
    
    
    
}
