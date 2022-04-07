#Example run with default parameters
Integrate (Lsodes, 1e-4, 1e-6, 1);
MonteCarlo ("Mycotoxin-MonteCarlo-run.out", 8, 3.14159);

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

Distrib(lnFgutabs, Normal, 0, 1);
Distrib(lnkgutelim , Normal, 0, 1);
Distrib(lnktot, Normal, 0, 1);
Distrib(lnkufrac, Normal, 0, 1);
Distrib(lnkumet, Normal, 0, 1);
Distrib(lnVdist, Normal, 0, 1);
Distrib(lnVdistmet, Normal, 0, 1);

Simulation {
  InitDose    = 100;    # ingested dose (mmol)
  BW         = 70;      # body weight (kg)
  
  Print(Ccpt_out, Cmet_out, Qu_out, Q_fec_out, Qu_met_out, 0.25,0.5,1,2,4,6,8,12,24,36,48);
}

End.
