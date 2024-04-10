/* Mycotoxin-PK.model.r.c
   ___________________________________________________

   Model File:  Mycotoxin-PK.model.r

   Date:  Wed Apr 10 11:53:16 2024

   Created by:  "./MCSim/mod.exe v6.1.0"
    -- a model preprocessor by Don Maszle
   ___________________________________________________

   Copyright (c) 1993-2019 Free Software Foundation, Inc.

   Model calculations for compartmental model:

   7 States:
     Q_GI -> 0.0;
     Q_fec -> 0.0;
     Qcpt -> 0.0;
     Qu -> 0.0;
     Qmet -> 0.0;
     Qu_met -> 0.0;
     AUC -> 0.0;

   7 Outputs:
     Ccpt -> 0.0;
     Cmet -> 0.0;
     Ccpt_out -> 0.0;
     Cmet_out -> 0.0;
     Qu_out -> 0.0;
     Q_fec_out -> 0.0;
     Qu_met_out -> 0.0;

   0 Inputs:

   40 Parameters:
     M_lnFgutabs = -0.70;
     M_lnkgutelim = -1.05;
     M_lnktot = -1.20;
     M_lnkufrac = -1.20;
     M_lnkumet = -0.50;
     M_lnVdist = 0;
     M_lnVdistmet = 0;
     SD_lnFgutabs = 0.2;
     SD_lnkgutelim = 0.2;
     SD_lnktot = 0.2;
     SD_lnkufrac = 0.2;
     SD_lnkumet = 0.2;
     SD_lnVdist = 0.2;
     SD_lnVdistmet = 0.2;
     lnFgutabs = 0;
     lnkgutelim = 0;
     lnktot = 0;
     lnkufrac = 0;
     lnkumet = 0;
     lnVdist = 0;
     lnVdistmet = 0;
     InitDose = 100;
     ConstDoseRate = 0;
     Fgutabs = 0.5;
     Fgutabs_tmp = 0.5;
     kgutabs = 0.35;
     Vdist = 1.0;
     Vdistmet = 1.0;
     BW = 70;
     ktot = 0.30;
     ku = 0.1;
     ku_tmp = 0.1;
     kmet = 0.2;
     kumet = 1.0;
     kgutelim = 0.35;
     GSD_Ccpt = 1.1;
     GSD_Cmet = 1.1;
     GSD_Qu = 1.1;
     GSD_Q_fec = 1.1;
     GSD_Qu_met = 1.1;
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "modelu.h"
#include "random.h"
#include "yourcode.h"


/*----- Indices to Global Variables */

/* Model variables: States and other outputs */
#define ID_Q_GI 0x00000
#define ID_Q_fec 0x00001
#define ID_Qcpt 0x00002
#define ID_Qu 0x00003
#define ID_Qmet 0x00004
#define ID_Qu_met 0x00005
#define ID_AUC 0x00006
#define ID_Ccpt 0x00007
#define ID_Cmet 0x00008
#define ID_Ccpt_out 0x00009
#define ID_Cmet_out 0x0000a
#define ID_Qu_out 0x0000b
#define ID_Q_fec_out 0x0000c
#define ID_Qu_met_out 0x0000d

/* Inputs */

/* Parameters */
#define ID_M_lnFgutabs 0x0000e
#define ID_M_lnkgutelim 0x0000f
#define ID_M_lnktot 0x00010
#define ID_M_lnkufrac 0x00011
#define ID_M_lnkumet 0x00012
#define ID_M_lnVdist 0x00013
#define ID_M_lnVdistmet 0x00014
#define ID_SD_lnFgutabs 0x00015
#define ID_SD_lnkgutelim 0x00016
#define ID_SD_lnktot 0x00017
#define ID_SD_lnkufrac 0x00018
#define ID_SD_lnkumet 0x00019
#define ID_SD_lnVdist 0x0001a
#define ID_SD_lnVdistmet 0x0001b
#define ID_lnFgutabs 0x0001c
#define ID_lnkgutelim 0x0001d
#define ID_lnktot 0x0001e
#define ID_lnkufrac 0x0001f
#define ID_lnkumet 0x00020
#define ID_lnVdist 0x00021
#define ID_lnVdistmet 0x00022
#define ID_InitDose 0x00023
#define ID_ConstDoseRate 0x00024
#define ID_Fgutabs 0x00025
#define ID_Fgutabs_tmp 0x00026
#define ID_kgutabs 0x00027
#define ID_Vdist 0x00028
#define ID_Vdistmet 0x00029
#define ID_BW 0x0002a
#define ID_ktot 0x0002b
#define ID_ku 0x0002c
#define ID_ku_tmp 0x0002d
#define ID_kmet 0x0002e
#define ID_kumet 0x0002f
#define ID_kgutelim 0x00030
#define ID_GSD_Ccpt 0x00031
#define ID_GSD_Cmet 0x00032
#define ID_GSD_Qu 0x00033
#define ID_GSD_Q_fec 0x00034
#define ID_GSD_Qu_met 0x00035


/*----- Global Variables */

/* For export. Keep track of who we are. */
char szModelDescFilename[] = "Mycotoxin-PK.model.r";
char szModelSourceFilename[] = __FILE__;
char szModelGenAndVersion[] = "./MCSim/mod.exe v6.1.0";

/* Externs */
extern BOOL vbModelReinitd;

/* Model Dimensions */
int vnStates = 7;
int vnOutputs = 7;
int vnModelVars = 14;
int vnInputs = 0;
int vnParms = 40;

/* States and Outputs*/
double vrgModelVars[14];

/* Inputs */
IFN vrgInputs[1];

/* Parameters */
double M_lnFgutabs;
double M_lnkgutelim;
double M_lnktot;
double M_lnkufrac;
double M_lnkumet;
double M_lnVdist;
double M_lnVdistmet;
double SD_lnFgutabs;
double SD_lnkgutelim;
double SD_lnktot;
double SD_lnkufrac;
double SD_lnkumet;
double SD_lnVdist;
double SD_lnVdistmet;
double lnFgutabs;
double lnkgutelim;
double lnktot;
double lnkufrac;
double lnkumet;
double lnVdist;
double lnVdistmet;
double InitDose;
double ConstDoseRate;
double Fgutabs;
double Fgutabs_tmp;
double kgutabs;
double Vdist;
double Vdistmet;
double BW;
double ktot;
double ku;
double ku_tmp;
double kmet;
double kumet;
double kgutelim;
double GSD_Ccpt;
double GSD_Cmet;
double GSD_Qu;
double GSD_Q_fec;
double GSD_Qu_met;

BOOL bDelays = 0;


/*----- Global Variable Map */

VMMAPSTRCT vrgvmGlo[] = {
  {"Q_GI", (PVOID) &vrgModelVars[ID_Q_GI], ID_STATE | ID_Q_GI},
  {"Q_fec", (PVOID) &vrgModelVars[ID_Q_fec], ID_STATE | ID_Q_fec},
  {"Qcpt", (PVOID) &vrgModelVars[ID_Qcpt], ID_STATE | ID_Qcpt},
  {"Qu", (PVOID) &vrgModelVars[ID_Qu], ID_STATE | ID_Qu},
  {"Qmet", (PVOID) &vrgModelVars[ID_Qmet], ID_STATE | ID_Qmet},
  {"Qu_met", (PVOID) &vrgModelVars[ID_Qu_met], ID_STATE | ID_Qu_met},
  {"AUC", (PVOID) &vrgModelVars[ID_AUC], ID_STATE | ID_AUC},
  {"Ccpt", (PVOID) &vrgModelVars[ID_Ccpt], ID_OUTPUT | ID_Ccpt},
  {"Cmet", (PVOID) &vrgModelVars[ID_Cmet], ID_OUTPUT | ID_Cmet},
  {"Ccpt_out", (PVOID) &vrgModelVars[ID_Ccpt_out], ID_OUTPUT | ID_Ccpt_out},
  {"Cmet_out", (PVOID) &vrgModelVars[ID_Cmet_out], ID_OUTPUT | ID_Cmet_out},
  {"Qu_out", (PVOID) &vrgModelVars[ID_Qu_out], ID_OUTPUT | ID_Qu_out},
  {"Q_fec_out", (PVOID) &vrgModelVars[ID_Q_fec_out], ID_OUTPUT | ID_Q_fec_out},
  {"Qu_met_out", (PVOID) &vrgModelVars[ID_Qu_met_out], ID_OUTPUT | ID_Qu_met_out},
  {"M_lnFgutabs", (PVOID) &M_lnFgutabs, ID_PARM | ID_M_lnFgutabs},
  {"M_lnkgutelim", (PVOID) &M_lnkgutelim, ID_PARM | ID_M_lnkgutelim},
  {"M_lnktot", (PVOID) &M_lnktot, ID_PARM | ID_M_lnktot},
  {"M_lnkufrac", (PVOID) &M_lnkufrac, ID_PARM | ID_M_lnkufrac},
  {"M_lnkumet", (PVOID) &M_lnkumet, ID_PARM | ID_M_lnkumet},
  {"M_lnVdist", (PVOID) &M_lnVdist, ID_PARM | ID_M_lnVdist},
  {"M_lnVdistmet", (PVOID) &M_lnVdistmet, ID_PARM | ID_M_lnVdistmet},
  {"SD_lnFgutabs", (PVOID) &SD_lnFgutabs, ID_PARM | ID_SD_lnFgutabs},
  {"SD_lnkgutelim", (PVOID) &SD_lnkgutelim, ID_PARM | ID_SD_lnkgutelim},
  {"SD_lnktot", (PVOID) &SD_lnktot, ID_PARM | ID_SD_lnktot},
  {"SD_lnkufrac", (PVOID) &SD_lnkufrac, ID_PARM | ID_SD_lnkufrac},
  {"SD_lnkumet", (PVOID) &SD_lnkumet, ID_PARM | ID_SD_lnkumet},
  {"SD_lnVdist", (PVOID) &SD_lnVdist, ID_PARM | ID_SD_lnVdist},
  {"SD_lnVdistmet", (PVOID) &SD_lnVdistmet, ID_PARM | ID_SD_lnVdistmet},
  {"lnFgutabs", (PVOID) &lnFgutabs, ID_PARM | ID_lnFgutabs},
  {"lnkgutelim", (PVOID) &lnkgutelim, ID_PARM | ID_lnkgutelim},
  {"lnktot", (PVOID) &lnktot, ID_PARM | ID_lnktot},
  {"lnkufrac", (PVOID) &lnkufrac, ID_PARM | ID_lnkufrac},
  {"lnkumet", (PVOID) &lnkumet, ID_PARM | ID_lnkumet},
  {"lnVdist", (PVOID) &lnVdist, ID_PARM | ID_lnVdist},
  {"lnVdistmet", (PVOID) &lnVdistmet, ID_PARM | ID_lnVdistmet},
  {"InitDose", (PVOID) &InitDose, ID_PARM | ID_InitDose},
  {"ConstDoseRate", (PVOID) &ConstDoseRate, ID_PARM | ID_ConstDoseRate},
  {"Fgutabs", (PVOID) &Fgutabs, ID_PARM | ID_Fgutabs},
  {"Fgutabs_tmp", (PVOID) &Fgutabs_tmp, ID_PARM | ID_Fgutabs_tmp},
  {"kgutabs", (PVOID) &kgutabs, ID_PARM | ID_kgutabs},
  {"Vdist", (PVOID) &Vdist, ID_PARM | ID_Vdist},
  {"Vdistmet", (PVOID) &Vdistmet, ID_PARM | ID_Vdistmet},
  {"BW", (PVOID) &BW, ID_PARM | ID_BW},
  {"ktot", (PVOID) &ktot, ID_PARM | ID_ktot},
  {"ku", (PVOID) &ku, ID_PARM | ID_ku},
  {"ku_tmp", (PVOID) &ku_tmp, ID_PARM | ID_ku_tmp},
  {"kmet", (PVOID) &kmet, ID_PARM | ID_kmet},
  {"kumet", (PVOID) &kumet, ID_PARM | ID_kumet},
  {"kgutelim", (PVOID) &kgutelim, ID_PARM | ID_kgutelim},
  {"GSD_Ccpt", (PVOID) &GSD_Ccpt, ID_PARM | ID_GSD_Ccpt},
  {"GSD_Cmet", (PVOID) &GSD_Cmet, ID_PARM | ID_GSD_Cmet},
  {"GSD_Qu", (PVOID) &GSD_Qu, ID_PARM | ID_GSD_Qu},
  {"GSD_Q_fec", (PVOID) &GSD_Q_fec, ID_PARM | ID_GSD_Q_fec},
  {"GSD_Qu_met", (PVOID) &GSD_Qu_met, ID_PARM | ID_GSD_Qu_met},
  {"", NULL, 0} /* End flag */
};  /* vrgpvmGlo[] */


/*----- InitModel
   Should be called to initialize model variables at
   the beginning of experiment before reading
   variants from the simulation spec file.
*/

void InitModel(void)
{
  /* Initialize things in the order that they appear in
     model definition file so that dependencies are
     handled correctly. */

  vrgModelVars[ID_Q_GI] = 0.0;
  vrgModelVars[ID_Q_fec] = 0.0;
  vrgModelVars[ID_Qcpt] = 0.0;
  vrgModelVars[ID_Qu] = 0.0;
  vrgModelVars[ID_Qmet] = 0.0;
  vrgModelVars[ID_Qu_met] = 0.0;
  vrgModelVars[ID_AUC] = 0.0;
  vrgModelVars[ID_Ccpt] = 0.0;
  vrgModelVars[ID_Cmet] = 0.0;
  vrgModelVars[ID_Ccpt_out] = 0.0;
  vrgModelVars[ID_Cmet_out] = 0.0;
  vrgModelVars[ID_Qu_out] = 0.0;
  vrgModelVars[ID_Q_fec_out] = 0.0;
  vrgModelVars[ID_Qu_met_out] = 0.0;
  M_lnFgutabs = -0.70;
  M_lnkgutelim = -1.05;
  M_lnktot = -1.20;
  M_lnkufrac = -1.20;
  M_lnkumet = -0.50;
  M_lnVdist = 0;
  M_lnVdistmet = 0;
  SD_lnFgutabs = 0.2;
  SD_lnkgutelim = 0.2;
  SD_lnktot = 0.2;
  SD_lnkufrac = 0.2;
  SD_lnkumet = 0.2;
  SD_lnVdist = 0.2;
  SD_lnVdistmet = 0.2;
  lnFgutabs = 0;
  lnkgutelim = 0;
  lnktot = 0;
  lnkufrac = 0;
  lnkumet = 0;
  lnVdist = 0;
  lnVdistmet = 0;
  InitDose = 100;
  ConstDoseRate = 0;
  Fgutabs = 0.5;
  Fgutabs_tmp = 0.5;
  kgutabs = 0.35;
  Vdist = 1.0;
  Vdistmet = 1.0;
  BW = 70;
  ktot = 0.30;
  ku = 0.1;
  ku_tmp = 0.1;
  kmet = 0.2;
  kumet = 1.0;
  kgutelim = 0.35;
  GSD_Ccpt = 1.1;
  GSD_Cmet = 1.1;
  GSD_Qu = 1.1;
  GSD_Q_fec = 1.1;
  GSD_Qu_met = 1.1;

  vbModelReinitd = TRUE;

} /* InitModel */


/*----- Dynamics section */

void CalcDeriv (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  CalcInputs (pdTime); /* Get new input vals */


  rgDerivs[ID_Q_GI] = ConstDoseRate - rgModelVars[ID_Q_GI] * ( kgutabs + kgutelim ) ;

  rgDerivs[ID_Q_fec] = rgModelVars[ID_Q_GI] * kgutelim ;

  rgDerivs[ID_Qcpt] = rgModelVars[ID_Q_GI] * kgutabs - rgModelVars[ID_Qcpt] * ( ku + kmet ) ;

  rgDerivs[ID_Qu] = rgModelVars[ID_Qcpt] * ku ;

  rgDerivs[ID_Qmet] = rgModelVars[ID_Qcpt] * kmet - rgModelVars[ID_Qmet] * kumet ;

  rgDerivs[ID_Qu_met] = rgModelVars[ID_Qmet] * kumet ;

  rgDerivs[ID_AUC] = rgModelVars[ID_Qcpt] / ( Vdist * BW ) ;

} /* CalcDeriv */


/*----- Model scaling */

void ScaleModel (PDOUBLE pdTime)
{

  vrgModelVars[ID_Q_GI] = InitDose ;
  Fgutabs_tmp = exp ( M_lnFgutabs + SD_lnFgutabs * lnFgutabs ) ;
  Fgutabs = ( Fgutabs_tmp > 1 ) ? 1 : Fgutabs_tmp ;
  kgutelim = exp ( M_lnkgutelim + SD_lnkgutelim * lnkgutelim ) ;
  kgutabs = kgutelim * Fgutabs / ( 1 - Fgutabs ) ;
  ktot = exp ( M_lnktot + SD_lnktot * lnktot ) ;
  ku_tmp = ktot * exp ( M_lnkufrac + SD_lnkufrac * lnkufrac ) ;
  ku = ( ku_tmp > ( 0.99 * ktot ) ) ? ( 0.99 * ktot ) : ku_tmp ;
  kmet = ( ktot - ku ) ;
  kumet = exp ( M_lnkumet + SD_lnkumet * lnkumet ) ;
  Vdist = exp ( M_lnVdist + SD_lnVdist * lnVdist ) ;
  Vdistmet = exp ( M_lnVdistmet + SD_lnVdistmet * lnVdistmet ) ;

} /* ScaleModel */


/*----- Jacobian calculations */

void CalcJacob (PDOUBLE pdTime, double rgModelVars[],
                long column, double rgdJac[])
{

} /* CalcJacob */


/*----- Outputs calculations */

void CalcOutputs (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  rgModelVars[ID_Ccpt] = rgModelVars[ID_Qcpt] / ( Vdist * BW ) ;
  rgModelVars[ID_Cmet] = rgModelVars[ID_Qmet] / ( Vdistmet * BW ) ;
  rgModelVars[ID_Ccpt_out] = ( rgModelVars[ID_Ccpt] < 1e-15 ? 1e-15 : rgModelVars[ID_Ccpt] ) ;
  rgModelVars[ID_Cmet_out] = ( rgModelVars[ID_Cmet] < 1e-15 ? 1e-15 : rgModelVars[ID_Cmet] ) ;
  rgModelVars[ID_Qu_out] = ( rgModelVars[ID_Qu] < 1e-15 ? 1e-15 : rgModelVars[ID_Qu] ) ;
  rgModelVars[ID_Q_fec_out] = ( rgModelVars[ID_Q_fec] < 1e-15 ? 1e-15 : rgModelVars[ID_Q_fec] ) ;
  rgModelVars[ID_Qu_met_out] = ( rgModelVars[ID_Qu_met] < 1e-15 ? 1e-15 : rgModelVars[ID_Qu_met] ) ;

}  /* CalcOutputs */


