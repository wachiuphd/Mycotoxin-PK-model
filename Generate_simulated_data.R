knitr::opts_chunk$set(echo = TRUE)
library(coda)
library(ggplot2)
library(here)
library(tidyverse)
library(psych)
mdir <- "MCSim"
source(here::here(mdir,"setup_MCSim.R"))
#set_PATH() # For Windows
# Make mod.exe (used to create mcsim executable from model file)
makemod()
model_file<- "Mycotoxin-PK.model.r"
makemcsim(model_file)
calibplotfolder <- "Calibration Plots"

## Monte Carlo Simulation Run

```{r Monte Carlo run}
set.seed(3.14159)
tvec <- c(0.25,0.5,1,2,4,6,8,12,24,36,48)

in_file_montecarlo <- "Mycotoxin-MonteCarlo-run.in.R" 
out_file_montecarlo <- "Mycotoxin-MonteCarlo-run.out"
out_montecarlo <- mcsim(model_file=model_file, in_file = in_file_montecarlo,
                        out_file = out_file_montecarlo)
out_montecarlo_df <- pivot_longer(out_montecarlo[,-(2:8)],cols=2:56)
out_montecarlo_df$ID <- factor(out_montecarlo_df$Iter)
# Split by variable and time
namesplit <- str_split(out_montecarlo_df$name,"_1.",simplify = T)
out_montecarlo_df$variable <- namesplit[,1]
out_montecarlo_df$Time <- tvec[as.numeric(namesplit[,2])]

# Generate simulated data with noise 
out_montecarlo_df$simdata <- 0
## Noise in blood data
indx <- out_montecarlo_df$variable%in% c("Ccpt_out","Cmet_out")
out_montecarlo_df$simdata[indx] <- 
  out_montecarlo_df$value[indx] * 
  1.2^rnorm(sum(indx))
## Noise in urine data (noise applied to intervals)
for (Iter in unique(out_montecarlo_df$Iter)) {
  for (Qname in c("Qu_out","Q_fec_out","Qu_met_out")) {
    indx <- out_montecarlo_df$Iter==Iter &
      out_montecarlo_df$variable==Qname
    Qu <- out_montecarlo_df$value[indx]
    dQu <- diff(Qu) * 1.2^rnorm(length(Qu)-1)
    Qusim <- Qu[1]+c(0,cumsum(dQu))
    out_montecarlo_df$simdata[indx] <- Qusim
  }
}
out_montecarlo_df$simdata <- signif(out_montecarlo_df$simdata,3)
# Plot
ggplot(out_montecarlo_df)+geom_line(aes(x=Time,y=value,color=ID))+
  geom_point(aes(x=Time,y=simdata,color=ID))+
  facet_wrap(~variable,scales="free_y")

# Save simulated data
out_montecarlo_mat<-pivot_wider(out_montecarlo_df,
                                names_from = "Time",values_from = "simdata",
                                id_cols = c("ID","variable"))
write.csv(out_montecarlo_mat,"Mycotoxin-SimData.csv",row.names = FALSE)
