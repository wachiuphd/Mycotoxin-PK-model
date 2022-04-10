# Mycotoxin-PK-model
 
This repository demonstrates fitting a generic PK model for a mycotoxin. The model consists of three compartments: mycotoxin in GI tract, mycotoxin in body, mycotoxin metabolite in body. Elimination pathways for mycotoxin include fecal excretion, urinary excretion, and metabolism to the metabolite. The metabolite is eliminated in urine.  A graphical depiction of the model is in the "Mycotoxin-PK-model.pptx" Powerpoint file. Model is coded in Gnu MCSim (https://www.gnu.org/software/mcsim/) version 6.1.0 (files in the MCSim folder). 

Biomonitoring data are assumed to be collected at t=0.25, 0.5, 1, 2, 4, 6, 8, 12, 24, 36, and 48 h. Data include blood concentrations of mycotoxin and metabolite, cumulative urinary excretion of mycotoxin and metabolite, and cumulative fecal excretion of mycotoxin. Simulated data are generated using the "Generate_simulated_data.R" script:
* "Mycotoxin-MonteCarlo-run.in.R" is the simulation specification file for running a Monte Carlo simulation -- specifically it generates 8 random individual data. Outputs are in the "Mycotoxin-MonteCarlo-run.out" file.
* The outputs of the Monte Carlo simulation are used to generate "simulated" data, adding noise with CV=20%.  The simulated data are stored in "Mycotoxin-SimData.csv" -- the same file with ".xlsx" extension includes Excel code that generates text that can be directly copied into the "Mycotoxin-MCMC-calib.in.R" file. These would be replaced by “real” data from the biomonitoring study.

 The "Mycotoxin Example.Rmd" file demonstrates the running and fitting of the model. Key details:
1) "Mycotoxin-PK.model.R" is the model specification file, which includes default parameters and ODEs. These are converted to C in the "Mycotoxin-PK.model.r.c" file and executable (MacOS) in the "mcsim.Mycotoxin-PK.model.r.exe" file.
2) "Mycotoxin-default-run.in.R" is the simulation specification file for running the model deterministically using default parameters.  Outputs are in the "Mycotoxin-default-run.out" file.
3) "Mycotoxin-MCMC-test-calib.in.R" is the simulation specification file for testing Markov Chain Monte Carlo (MCMC) simulations to calibrate the model (i.e., fit model parameters) to the simulated data. For this test, 4 chains of 1000 iterations each are run. 
3) "Mycotoxin-MCMC-calib.in.R" is the simulation specification file for running the full MCMC simulations to calibrate the model to the simulated data. A hierarchical Bayesian population approach is utilized. In the example, 4 MCMC chains of length 50,000 iterations each are run. Results are stored in the two .Rdata files.
4) Convergence and other diagnostics are generated and plotted, and stored in the "DiagnosticPlots_model.calib.pdf" file.
5) Comparisons of predictions and simulated data stored in folder "Calibration Plots" as PDF files.

# Session info 
R version 4.1.1 (2021-08-10)
Platform: x86_64-apple-darwin17.0 (64-bit)
Running under: macOS Big Sur 11.5.2

Matrix products: default
LAPACK: /Library/Frameworks/R.framework/Versions/4.1/Resources/lib/libRlapack.dylib

locale:
en_US.UTF-8/en_US.UTF-8/en_US.UTF-8/C/en_US.UTF-8/en_US.UTF-8

attached base packages:
stats     graphics  grDevices utils     datasets  methods   base     

other attached packages:
psych_2.1.9     forcats_0.5.1   stringr_1.4.0   dplyr_1.0.8     purrr_0.3.4    
readr_2.1.2     tidyr_1.2.0     tibble_3.1.6    tidyverse_1.3.1 here_1.0.1     
ggplot2_3.3.5   coda_0.19-4    

loaded via a namespace (and not attached):
Rcpp_1.0.8        lubridate_1.8.0   lattice_0.20-44   assertthat_0.2.1  rprojroot_2.0.2  
digest_0.6.29     utf8_1.2.2        R6_2.5.1          cellranger_1.1.0  backports_1.4.1  
reprex_2.0.1      evaluate_0.15     httr_1.4.2        pillar_1.7.0      rlang_1.0.1      
readxl_1.3.1      rstudioapi_0.13   rmarkdown_2.11    munsell_0.5.0     broom_0.7.12     
compiler_4.1.1    modelr_0.1.8      xfun_0.29         pkgconfig_2.0.3   mnormt_2.0.2     
tmvnsim_1.0-2     htmltools_0.5.2   tidyselect_1.1.1  gridExtra_2.3     fansi_1.0.2      
viridisLite_0.4.0 crayon_1.5.0      tzdb_0.2.0        dbplyr_2.1.1      withr_2.4.3      
grid_4.1.1        nlme_3.1-152      jsonlite_1.8.0    gtable_0.3.0      lifecycle_1.0.1  
DBI_1.1.2         magrittr_2.0.2    scales_1.1.1      cli_3.2.0         stringi_1.7.6    
viridis_0.6.2     fs_1.5.2          xml2_1.3.3        ellipsis_0.3.2    generics_0.1.2   
vctrs_0.3.8       tools_4.1.1       glue_1.6.1        hms_1.1.1         parallel_4.1.1   
fastmap_1.1.0     yaml_2.3.5        colorspace_2.0-2  rvest_1.0.2       knitr_1.37       
haven_2.4.3     
