Development Instructions
=========================

..
   TODOS:
   - Contribution guidelines (move here from Contributing.md)
   - Code conventions
   - ....
   - Tools installation:
      - pre-commit hook?
      - spellchecker
      - ... 

.. _env_dev_setup:

Environment setup
------------------

#. Pre-conditions:

   * Install `Arduino IDE (2.0 or higher) <https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/>`_ 
   * Or Install `Arduino CLI (1.0.0 or higher) <https://arduino.github.io/arduino-cli/latest/installation/>`_
   * Python (you need this for upload/ flash XMC board anyways)

#. Create an ``<SKETCHBOOK>/hardware/arduino-git`` folder. Where ``<SKETCHBOOK>`` is the location of your Arduino sketchbook. The ``<SKETCHBOOK>`` default is OS-dependent:
   
   .. tabs::

      .. group-tab:: Linux

         ::

              {HOME}/Arduino

      .. group-tab:: Windows

         ::

              {DOCUMENTS}/Arduino

      .. group-tab:: MacOS

         ::

              {HOME}/Documents/Arduino


#. Clone this repo in ``<SKETCHBOOK>/hardware/arduino-git``: 
   :: 
         
      git clone https://github.com/Infineon/XMC-for-Arduino.git xmc
   
   This allows quick testing of local changes during development, and keep released version.

#. You can check if the correct version is installed by running: 
   ::

      arduino-cli core list

   you should be able to see the ``arduino-git:xmc core``.

#. Update all submodule included in this project:
   ::

      git submodule update --init --recursive
   
   If you are not familiar with submodules, check out `Git-Tools-Submodules <https://git-scm.com/book/en/v2/Git-Tools-Submodules>`_ 

#. Start developing |:tools:|!

|:bell:| 
If you encounter strange behavior with Arduino IDE during development, try cleaning up the IDE cache:

   .. tabs::

      .. group-tab:: Windows

         .. code-block:: text
            
            C:\User\"username"\AppData\Roaming\arduino-ide

      .. group-tab:: Linux

         ::

            ~/.config/arduino-ide

      .. group-tab::  macOS

         ::
         
            ~/Library/Application Support/arduino-ide/


Automated Build Checks
-----------------------

Currently a Github workflow is used for automatic compilation checking and releasing. Workflows are defined [here](https://github.com/Infineon/XMC-for-Arduino/tree/master/.github/workflows).
Before opening a Pull Request for your contribution, please add a git tag in the format `Vx.y.z` (e.g. V3.3.0) to trigger the release process in your fork and pass the compilation tests.

Creating and Maintaining Third Party Libraries
------------------------------------------------
Basics
^^^^^^^^
The Arduino IDE allows for external libraries to be added to support specific devices and functions which are not part of the core setup. For details on creating libraries see the 
[Arduino library specifications](https://arduino.github.io/arduino-cli/library-specification/). If you add additional libraries to this project, make sure to [document them](https://xmc-arduino.readthedocs.io/en/latest/builtin-libraries.html) accordingly.

XMC-for-Arduino Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
To ensure that a library specific to one architecture or board type is only compiled when a supporting board is set up, this specification includes a setting for *architecture* in the *library.properties* file.

When creating or maintaining third party or external libraries for XMC-for-Arduino please use this setting:

   .. code-block:: text
      
      architecture=xmc

If your library also supports other boards and architectures, add those in as well.

Validation test
----------------
To test the XMC4arduino, we used unity to test some of the features of the arduino core & builtin library. 

Tests are located in tests/arduino-core-tests and included as submodule in this project. Run  ``git submodule update --init --recursive`` to update them.  

Code checks (WIP)
----------------------
Refer to ``libraries\CAN\Makefile.codecheck``. 

Regarding formatting, we currently use `pre-commit <https://pre-commit.com/>`_ to automatically run clang-formatting to format all c/c++ code. Please install this python package, and follow the quick start (the pre-commit configuration file is already there). You should be able to format your code automatically on git commit!