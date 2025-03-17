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

Environment Setup
------------------

#. Pre-conditions:

   * Install `Arduino IDE (2.0 or higher) <https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/>`_ 
   * Or Install `Arduino CLI (1.0.0 or higher) <https://arduino.github.io/arduino-cli/latest/installation/>`_
   * Python

#. Create a ``<SKETCHBOOK>/hardware/arduino-git`` folder. Where ``<SKETCHBOOK>`` is the location of your Arduino sketchbook. The ``<SKETCHBOOK>`` default is OS-dependent:
   
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
   
   This allows quick testing of local changes during development while keeping the released version.

#. You can check if the correct version is installed by running: 
   ::

      arduino-cli core list

   You should be able to see the ``arduino-git:xmc core``.

#. Update all submodule included in this project:
   ::

      git submodule update --init --recursive
   
   If you are not familiar with git submodules, check out `Git-Tools-Submodules <https://git-scm.com/book/en/v2/Git-Tools-Submodules>`_ 

#. Start developing |:tools:|!

|:bell:| 
If you encounter strange behavior with Arduino IDE during development, try cleaning up the Arduino IDE's cache:

   .. tabs::

      .. group-tab:: Windows

         .. code-block:: text
            
            %AppData%\arduino-ide

      .. group-tab:: Linux

         ::

            ~/.config/arduino-ide

      .. group-tab:: macOS

         ::
         
            ~/Library/Application Support/arduino-ide/


Automated Build Checks
-----------------------

Currently a GitHub Action workflow is used for automatic compilation checking and releasing. Workflows are defined [here](https://github.com/Infineon/XMC-for-Arduino/tree/master/.github/workflows).
Before opening a Pull Request for your contribution, please add a git tag in the format `Vx.y.z` (e.g. V3.3.0) to trigger the release process in your fork and pass the compilation tests.

Creating and Maintaining Third Party Libraries
------------------------------------------------
Basics
^^^^^^^^
The Arduino IDE allows for external libraries to be added to support specific devices and functions which are not part of the core setup. For details on creating libraries see the 
[Arduino library specification](https://arduino.github.io/arduino-cli/library-specification/). If you add additional libraries to this project, make sure to [document them](https://xmc-arduino.readthedocs.io/en/latest/builtin-libraries.html) accordingly.

XMC-for-Arduino Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
To ensure that a library specific to one architecture or board type is only compiled when a supporting board is set up, this specification includes a setting for *architecture* in the *library.properties* file.

When creating or maintaining third party or external libraries for XMC-for-Arduino please use this setting:

   .. code-block:: text
      
      architecture=xmc

If your library also supports other boards and architectures, add those in as well.

Validation Test
----------------
To validate the XMC-for-Arduino, we utilize Unity for testing various features of the Arduino core and built-in libraries.

Tests are located in ``tests/arduino-core-tests`` and included as submodule in this project. Run  ``git submodule update --init --recursive`` to update them.  

Code Checks
----------------
.. warning::

   Code Checks are still a work in progress in this project.

Refer to ``libraries\CAN\Makefile.codecheck``. 

Regarding formatting, we currently use `pre-commit <https://pre-commit.com/>`_ to automatically run clang-formatting to format all C/C++ code.
Please install this Python package, and follow the quick start (the pre-commit configuration file is already there). You should be able to format your code automatically on git commit!