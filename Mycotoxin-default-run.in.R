#Example run with default parameters
Integrate (Lsodes, 1e-4, 1e-6, 1);
OutputFile("Mycotoxin-default-run.out");

  Simulation {
    InitDose    = 100;    # ingested dose (mmol)
    BW         = 70;      # body weight (kg)

    PrintStep(Ccpt_out, Cmet_out, Qu_out, Q_fec_out, Qu_met_out, 0, 48, 0.1);
  }

End.
