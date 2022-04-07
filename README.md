# Mycotoxin-PK-model
 
This repository demonstrates fitting a generic PK model for a mycotoxin. The model consists of three compartments: mycotoxin in GI tract, mycotoxin in body, mycotoxin metabolite in body. Elimination pathways for mycotoxin include fecal excretion, urinary excretion, and metabolism to the metabolite. The metabolite is eliminated in urine.  A graphical depiction of the model is in the "Mycotoxin-PK-model.pptx" Powerpoint file.

Biomonitoring data are assumed to be collected at t=0.25, 0.5, 1, 2, 4, 6, 8, 12, 24, 36, and 48 h. Data include blood concentrations of mycotoxin and metabolite, cumulative urinary excretion of mycotoxin and metabolite, and cumulative fecal excretion of mycotoxin. 

Model is coded in Gnu MCSim (https://www.gnu.org/software/mcsim/) version 6.1.0.  The "Mycotoxin Example.Rmd" file demonstrates the running and fitting of the model. Key details:
1) "Mycotoxin-PK.model.r" is the model specification file, which includes default parameters and ODEs
2) "Mycotoxin-default-run.in.R" is the simulation specification file for running the model deterministically using default parameters.
3) "Mycotoxin-MonteCarlo-run.in.R" is the simulation specification file for running a Monte Carlo simulation -- specifically it generates 8 random individual data. 
4) The outputs of the Monte Carlo simulation are used to generate "simulated" data, adding noise with CV=20%.  The simulated data are stored in "Mycotoxin-SimData.csv" -- the same file with ".xlsx" extension includes
5) "Mycotoxin-MCMC-calib.in.R" is the simulation specification file for running a Markov Chain Monte Carlo (MCMC) simulations to calibrate the model (i.e., fit model parameters) to the simulated data. A hierarchical Bayesian population approach is utilized. In the example, 4 MCMC chains of length 50,000 iterations each are run. The code stores the resuls in Rdata files.
6) Convergence and other diagnostics are generated and plotted, and stored in the file "DiagnosticPlots_model.calib.pdf"
7) Comparisons of predictions and simulated data stored in folder "Calibration Plots" as PDF files.

