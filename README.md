# Lab4_PET
## How to compile Geant4 Simulation
1. Create a build folder inside Geant4Sim folder:
   ```
   cd Geant4Sim
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
  
4. To visualize the spectra, open the _output{runID}.root_ files with root TBrowser and select fEdepSPCT:
   ```
   root output0.root
   new TBrowser
   ```
