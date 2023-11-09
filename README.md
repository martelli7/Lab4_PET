# Lab4_PET
## How to compile the Geant4 Simulation
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
  
4. To visualize the spectra, open the _output{runID}.root_ files with root TBrowser and select fEdepSPCT:
   ```
   root output0.root
   new TBrowser
   ```
## Credits
All the codes in this repository were created for the _Nuclear and Subnuclear Measurements Laboratory course_ of the Physics Master degree of the _University of Milano-Bicocca_, 2022/2023 Academic Year.

The geant4 simulation is based on the CERN guide, built-in examples, and on the [Youtube tutorials](https://youtube.com/playlist?list=PLLybgCU6QCGWgzNYOV0SKen9vqg4KXeVL&si=KvdO9rwtt9r4BO5_) of [Dr. Mustafa Schmidt](https://github.com/MustafaSchmidt).

All credits go to Alessandro Lazzaroni, [Mattia Martelli](https://github.com/martelli7), Francesco Merighi and Beatrice Scotti.

Special thanks to Dr. Daniele Guffanti for his help throughout the course.
