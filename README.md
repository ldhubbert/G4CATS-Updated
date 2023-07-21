# G4CATS-Updated
An even better version of G4CATS. Modified from G4CATS repository.

To run the G4CATS simulation:
        - Go into the G4CATS folder
        - ./build/exampleB4c -m run1.mac

run1.mac can be replaced with any macro that you want to run.
If it is not located as soon as you open the G4CATS folder, you will have to specify a place.
For example, if the macro was located in the build folder, you would write "~/G4CATS/build/<your_macro>".

NOTE: When an output file is produced, it either has to be moved to another folder or renamed.
This is because when the simulation is run the next time, those results will be replaced with the information from the most recent run.

File Directory

Note: For my histograms and smeared histograms, I used 100 bins for every delta-10-x (every 10 steps in the x-direction.)

G4CATS DIRECTORY
These are files included in the G4CATS folder in my home directory.

Run1.mac
This is the macro used when running the G4CATS simulation.
Here, you can control the number of particles thrown at the detector, the type of particle used, the gun direction, and the particle energy.
Any such information included here overrides the particle information stated in the “B4PrimaryGeneratorAction.cc” file in the src folder.

t_graph_og_equation.C
This file plots the variable t against theta.
Its answers should be identical to those of “t_graph.C”.
The speed of light is considered to have a value of 1.

t_graph.C
This file plots the variable t against theta.
It contains a simplified version of the equation used in “t_graph_og_equation.C”.
Its answers should be identical to those of “t_graph_og_equation.C”.
The speed of light is considered to have a value of 1.

t_graph_vs_energy.C
This file plot the variable t against energy.

B_Error.C
This file estimates the error on the parameter B in the equation e^(-Bx).
B was set equal to 1 here.
The values of the function e^(-Bx) are smeared to simulate real-world results you would get in an experiment, and the function is then fit with a computer-generated curve.
The error in B is then printed out on-screen.

plotHisto.C
This file creates plots. When you open a new TBrowser in root, you can click on the .root output files and see histograms.

plotNtuple.C
I think this file is similar to “plotHisto.C”. I’m pretty sure it has something to do with the plots created for the .root files.

exampleB4c.cc
I'm not sure what this file does, but if I had to guess, I would say that it pulls all the src and include files together to make the simulation.
It was leftover from the G4CATS simulation found in the “Vincent” folder, and it looked important, so I kept it.

GNUmakefile
I think this has something to do with compiling the simulation.

CMakeLists.txt
This file helps compile the simulation.
I commented out a bit of code in this file, so that files aren’t duplicated whenever I compile a simulation.
Vincent had a lot of files in his G4CATS repository that I didn’t want, so I deleted them.
The CMakeLists.txt file, however, wanted to copy them from the directory to the build folder.
Since I had deleted them already, the simulation didn’t compile.
I commented out this part of the code, and now you don’t need those specific files to update the simulation.

HISTOGRAMS FOLDER

H100MeV.C
This file produces a histogram from the .root output file with results from a 100MeV photon beam fired into G4CATS.

H200MeV.C
This file produces a histogram from the .root output file with results from a 200MeV photon beam fired into G4CATS.

H300MeV.C
This file produces a histogram from the .root output file with results from a 300MeV photon beam fired into G4CATS.

H400MeV.C
This file produces a histogram from the .root output file with results from a 400MeV photon beam fired into G4CATS.

H500MeV.C
This file produces a histogram from the .root output file with results from a 500MeV photon beam fired into G4CATS.

skew.C
This file has code copied from the H200MeV.C file, as well as additional code.
It fits a skewed Gaussian curve to the 200MeV histogram, but the fit isn’t great. The tall spike at 200MeV throws off the fit.

SMEARING FOLDER

H100MeVsmear.C
This file smears the histogram produced by “H100MeV.C” and plots the original H100MeV.C above it.
It uses an addition strategy to smear.
It also fits a skewed Gaussian to the smeared histogram results.

H200MeVsmear.C
This file smears the histogram produced by “H200MeV.C” and plots the original H200MeV.C above it.
It uses an addition strategy to smear.

H300MeVsmear.C
This file smears the histogram produced by “H300MeV.C” and plots the original H300MeV.C above it.
It uses an addition strategy to smear.

H400MeVsmear.C
This file smears the histogram produced by “H400MeV.C” and plots the original H400MeV.C above it.
It uses an addition strategy to smear.

H500MeVsmear.C
This file smears the histogram produced by “H500MeV.C” and plots the original H500MeV.C above it.
It uses an addition strategy to smear.

LinearGraph.C
This file plots the smearing percentages used in the five previous files against energy and FWHM.
It represents the linear correlation between the smearing percentages used in the Gaussian standard deviations in “H100MeVsmear.C”, “H200MeVsmear.C”, “H300MeVsmear.C”, “H400MeVsmear.C,” and “H500MeVsmear.C”.

MULTIPLICATION FOLDER IN SMEARING FOLDER

H100MeVsmearM.C
This file smears the histogram produced by “H100MeV.C” and plots the original H100MeV.C above it.
It uses a multiplication strategy to smear.
It also fits a skewed Gaussian to the smeared histogram results.

H200MeVsmearM.C
This file smears the histogram produced by “H200MeV.C” and plots the original H200MeV.C above it.
It uses a multiplication strategy to smear.

H300MeVsmearM.C
This file smears the histogram produced by “H300MeV.C” and plots the original H300MeV.C above it.
It uses a multiplication strategy to smear.

H400MeVsmearM.C
This file smears the histogram produced by “H400MeV.C” and plots the original H400MeV.C above it.
It uses a multiplication strategy to smear.

H500MeVsmearM.C
This file smears the histogram produced by “H500MeV.C” and plots the original H500MeV.C above it.
It uses a multiplication strategy to smear.

OUT FOLDER

B4_100MeV.root
This contains the simulation results when 100MeV photons are thrown at G4CATS.

B4_200MeV.root
This contains the simulation results when 200MeV photons are thrown at G4CATS.

B4_300MeV.root
This contains the simulation results when 300MeV photons are thrown at G4CATS.

B4_400MeV.root
This contains the simulation results when 400MeV photons are thrown at G4CATS.

B4_500MeV.root
This contains the simulation results when 500MeV photons are thrown at G4CATS.\

SRC AND INCLUDE FOLDERS

Theses folders describe the mechanics of the G4CATS simulation detector.
