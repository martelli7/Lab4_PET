# Simulation B
## How to compile the Geant4 Simulation B
1. Create a build folder inside Geant4SimB folder:
   ```
   cd Geant4SimB
   mkdir build
   cd build
   ```
2. Launch first cmake and then make to generate the executable:
   ```
   cmake ..
   make
   ```
3. exampleB3a.exe has been created and it can be run with many macro files according to the user's purpose:
    - **Batch mode.** Fastest way to execute the simulation:
      ```
      ./exampleB3a run.mac
      ```
    - **Visual mode.** Slower way, it shows the Geant4 graphic interface by running initial_vis.mac file (useful for checking the geometry or the particles tracks):
      ```
      ./exampleB3a
      ```
      It is possibile to use 'run1.mac' and 'run2.mac' files written by CERN, however these were not used.
   - **Loop mode.** It can be used to loop over source coordinates or spectrometer coordinates, in _batch_ only:
      ```
      ./exampleB3a det.mac
      ```
  
4. To visualize the spectra, open the 'output{runID}.root' files with root TBrowser and select fEdepCoincidence or crystal_edep_score:
   ```
   root output0.root
   new TBrowser
   ```
