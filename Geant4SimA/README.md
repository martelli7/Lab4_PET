# Simulation A
## How to compile the Geant4 Simulation A
1. Create a build folder inside Geant4SimA folder:
   ```
   cd Geant4SimA
   mkdir build
   cd build
   ```
2. Launch first cmake and then make to generate the executable:
   ```
   cmake ..
   make
   ```
3. pet_simulation.exe has been created and it can be run with many macro files according to the user's purpose:
    - **Batch mode.** Fastest way to execute the simulation:
      ```
      ./pet_simulation run.mac
      ```
    - **Visual mode.** Slower way, it shows the Geant4 graphic interface (useful for checking the geometry or the particles tracks):
      ```
      ./pet_simulation vis.mac
      ```
    - **Loop mode.** It can be used to loop over source coordinates or spectrometer coordinates, in _batch_ only:
      ```
      ./pet_simulation det.mac
      ```
  
4. To visualize the spectra, open the 'output{runID}.root' files with root TBrowser and select fEdepGATE or fEdepSPCT:
   ```
   root output0.root
   new TBrowser
   ```
