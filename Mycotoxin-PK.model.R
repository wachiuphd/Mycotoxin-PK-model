# Generic mycotoxin model

States  = { 
  Q_GI,       # Quantity of mycotoxin in the GI compartment (nmol)
  Q_fec,  # Quantity of mycotoxin in feces (nmol)
  Qcpt,       # Quantity in central compartment (nmol)
  Qu,     # Quantity of mycotoxin in urine (nmol)
  Qmet,   # Quantity of metabolite central compartment (nmol)
  Qu_met,     # Quantity of metabolite in urine (nmol)
  AUC,         # AUC of central compartment (nmol-hr/L)
};  

Outputs = {
  Ccpt, # Central compartment concentration
  Cmet, # Central compartment metabolite concentration
  Ccpt_out, # Central compartment concentration (truncated at 1e-15)
  Cmet_out, # Central compartment metabolite concentration (truncated at 1e-15)
  Qu_out, # Amount excreted in urine (truncated at 1e-15)
  Q_fec_out, # Amount excreted in feces (truncated at 1e-15)
  Qu_met_out # Amount of metabolite excreted in urine (truncated at 1e-15)
};

#population mean
M_lnFgutabs = -0.70; # Fraction absorbed
M_lnkgutelim = -1.05; # Gut elimination
M_lnktot = -1.20; # Total elimination
M_lnkufrac = -1.20; # Fraction of elimination that is urine
M_lnkumet = -0.50; # Urinary excretion of metabolite
M_lnVdist = 0; # Volume of distribution (L/kg)
M_lnVdistmet = 0; # Volume of distribution for metabolite (L/kg)

#population variance
SD_lnFgutabs = 0.2;
SD_lnkgutelim = 0.2;
SD_lnktot = 0.2;
SD_lnkufrac = 0.2;
SD_lnkumet = 0.2;
SD_lnVdist = 0.2; 
SD_lnVdistmet = 0.2; 

#individual log transformed, z-score
lnFgutabs = 0;
lnkgutelim = 0;
lnktot = 0;
lnkufrac = 0;
lnkumet = 0;
lnVdist = 0; 
lnVdistmet = 0; 

#individual parameters
# Oral input modeling
InitDose    = 100; # ingested input at t=0 (nmol)
ConstDoseRate = 0; # Constant dose rate per hour (nmol/h) 
Fgutabs    = 0.5; #fraction of gut absorption
Fgutabs_tmp = 0.5; #set it to avoid the value larger than 1
kgutabs    = 0.35; # Intestinal absorption rate (/h); kgutelim * Fgutabs/(1-Fgutabs)

# Distribution volumes (L/kg)
Vdist = 1.0;
Vdistmet = 1.0;

# Body weight (kg)
BW = 70;

# Elimination rate constants (/h)
ktot      = 0.30;   # total elimination rate constant
ku       = 0.1;     # Urinary excretion rate constant 
ku_tmp   = 0.1;     # Set it to avoid the value geq ktot
kmet       = 0.2;   # Metabolism rate constant 
kumet    = 1.0;     # Urinary excretion rate constant for metabolite
kgutelim   = 0.35;     #gut elimination rate

#GSD - Mesidual errors
GSD_Ccpt = 1.1; # Central compartment concentration
GSD_Cmet = 1.1; # Central compartment metabolite concentration
GSD_Qu = 1.1;  # Amount excreted in urine
GSD_Q_fec = 1.1;  # Amount excreted in feces
GSD_Qu_met = 1.1; # Amount of metabolite excreted in urine

Initialize {
  Q_GI = InitDose;
  Fgutabs_tmp = exp(M_lnFgutabs + SD_lnFgutabs * lnFgutabs);
  Fgutabs = (Fgutabs_tmp > 1) ? 1 : Fgutabs_tmp;
  kgutelim = exp(M_lnkgutelim + SD_lnkgutelim * lnkgutelim);
  kgutabs = kgutelim * Fgutabs / (1 - Fgutabs);
  ktot = exp(M_lnktot + SD_lnktot * lnktot);
  ku_tmp = ktot * exp(M_lnkufrac + SD_lnkufrac * lnkufrac);
  ku = (ku_tmp > (0.99*ktot)) ? (0.99*ktot) : ku_tmp;
  kmet = (ktot - ku);
  kumet = exp(M_lnkumet + SD_lnkumet * lnkumet);
  Vdist = exp(M_lnVdist + SD_lnVdist * lnVdist);
  Vdistmet = exp(M_lnVdistmet + SD_lnVdistmet * lnVdistmet);
}

Dynamics { 
  dt (Q_GI)  = ConstDoseRate - Q_GI * (kgutabs + kgutelim);
  dt (Q_fec) = Q_GI * kgutelim;
  dt (Qcpt) = Q_GI * kgutabs - Qcpt * (ku + kmet);
  dt (Qu) = Qcpt * ku;
  dt (Qmet) = Qcpt * kmet - Qmet * kumet;
  dt (Qu_met) = Qmet * kumet;
  dt (AUC) = Qcpt/(Vdist*BW);
}

CalcOutputs { # truncate at Q values of 1e-15
  Ccpt = Qcpt / (Vdist*BW);
  Cmet = Qmet / (Vdistmet*BW);
  Ccpt_out = (Ccpt < 1e-15 ? 1e-15 : Ccpt);
  Cmet_out = (Cmet < 1e-15 ? 1e-15 : Cmet);
  Qu_out = (Qu < 1e-15 ? 1e-15 : Qu);
  Q_fec_out = (Q_fec < 1e-15 ? 1e-15 : Q_fec);
  Qu_met_out = (Qu_met < 1e-15 ? 1e-15 : Qu_met);
}

End.