# CAS739 Project
### Andrew Mitchell
### 001225727

This repository is forked from https://github.com/gegelati/gegelati, and modified to receive the top 3 actions instead of the top 1.

The main project can be found at https://github.com/myrithok/cas739_project_001225727.

This project needs to be built and installed using cmake in order for the main project to work. This installation cannot coexist with a regular GEGELATI install.

To install this project, execute these commands:
```
$ git clone https://github.com/gegelati/gegelati.git
$ cd gegelati/bin
$ cmake ..
$ cmake --build . --target INSTALL # On Windows
$ cmake --build . --target install # On Linux
```
If you encounter any installation issues, please see the original repository.