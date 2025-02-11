Development Instructions
=========================

.. warning::

   This is a work in progress version of XMC4Arduino documentation. 
   While this warning notice is present, the documentation is NOT ready for public usage.

..
   TODOS:
   - Contribution guidelines (move here from Contributing.md)
   - Code conventions
   - ....
   - Tools installation:
      - uncrustify
      - python ?
      - pip ?
      - pre-commit hook?
      - spellchecker
      - ... 
   - Installation of the xmc Arduino core
   - Setting up the development environment

.. _env_dev_setup:

Environment setup
------------------

.. note::
   | The development environment setup is (currently) only supported on **Linux/WSL** |:penguin:|. 
   | As many tools and scripts are not cross-platform, some of them will not directly work on Windows |:abcd:| or macOS |:apple:|.


0. Obviously |:neutral_face:|, install `Arduino IDE (2.0 or higher) <https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/>`_ or `Arduino CLI (1.0.0 or higher) <https://arduino.github.io/arduino-cli/0.24/installation/>`_.

1. Create an ``<SKETCHBOOK>/hardware/arduino-git`` folder. Where ``<SKETCHBOOK>`` is the location of your Arduino sketchbook. 
You can run: 
   ::
      
      mkdir -p $sketchbook/hardware/arduino-git
   
2. Change directories: 
   ::
      
      cd <SKETCHBOOK>/hardware/arduino-git

3. Clone this repo: 
   ::
      
      git clone https://github.com/Infineon/XMC-for-Arduino.git xmc

4.  You can check if the correct version is installed by running

   .. tabs::

      .. group-tab:: Linux

         ::

              arduino-cli core list

      .. group-tab:: Windows/ WSL

         ::

             arduino-cli.exe core list

This allows quick testing of local changes during development, and keep released version.
4. From the root directory of the core, run the setup script :
   ::
      
       bash tools/dev-setup.sh

5. Start developing |:tools:|!

|:bell:| 
If you encounter strange behavior with Arduino IDE during development, try cleaning up the IDE cache:

   .. tabs::

      .. group-tab:: Windows

         ::
            
            C:\\User\\"username"\\AppData\\Roaming\\arduino-ide

      .. group-tab:: Linux

         ::

            ~/.config/arduino-ide

      .. group-tab::  macOS 
         ::
         
            ~/Library/Application Support/arduino-ide/
