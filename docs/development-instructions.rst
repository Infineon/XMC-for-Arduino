Development Instructions
=========================

..
   TODOS:
   - Code conventions
   - Tools installation:
      - test
      - doc
      - code check
      - ... 

.. _env_dev_setup:

Environment Setup
------------------

#. Pre-conditions:

   * Install `Arduino IDE (2.0 or higher) <https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/>`_ 
   * Or Install `Arduino CLI (1.0.0 or higher) <https://arduino.github.io/arduino-cli/latest/installation/>`_
   * Python
   * Follow the :doc:`installation-instructions`

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

Code Check and Tests
----------------------

Pre-commit Hooks
^^^^^^^^^^^^^^^^^^
For the C/C++ code format and commit message format, we add git hooks to check it automatically.

For ease of use, we currently use `pre-commit <https://pre-commit.com/>`_ to automatically run clang-formatting to format all C/C++ code.
Please install this Python package, and follow the quick start (the pre-commit configuration file is already there). You should be able to format your code automatically on git commit.

We also have workflow to for auto-checking, so please refer to code convention before committing your code.

Code Check
^^^^^^^^^^^^
.. warning::

   Code Checks are still a work in progress in this project.

If you are developing a new built-in library, please refer to ``libraries\CAN\Makefile.codecheck`` using cppcheck for static code analysis to ensure code quality.

Automated Build Checks
^^^^^^^^^^^^^^^^^^^^^^^^
Currently a GitHub Action workflow is used for automatic compilation checking.
Workflows are defined `here <https://github.com/Infineon/XMC-for-Arduino/blob/master/.github/workflows/compile-examples.yml>`_.

Validation Test
^^^^^^^^^^^^^^^^
To validate the XMC-for-Arduino, we utilize Unity for testing various features of the Arduino core and built-in libraries.

Tests are located in ``tests/arduino-core-tests`` and included as submodule in this project. Run  ``git submodule update --init --recursive`` to update them.  

If you need to run these tests locally, you'll also need to download `GNU Make <https://www.gnu.org/software/make/#download>`_ .

Debugging (VS Code)
^^^^^^^^^^^^^^^^^^^^
Debugging support described here is for Visual Studio Code. The Arduino IDE already provides a built-in debugger for supported boards.

#. Install the `Cortex-Debug` extension in VS Code.
#. Copy the `task_xmc.json` file from `tools/vscode-profile` to the `.vscode` directory and rename to `tasks.json` in your project root.
#. In VS Code, run the task: **Generate launch.json for debug (XMC)**.
#. Required parameters for this task:
   * **fqbn**: Fully Qualified Board Name (e.g., `arduino-git:xmc:kit_xmc47_relax`)
   * **build path**: Directory where the `.elf` file will be placed
   * **example path**: Path to the sketch (`.ino` file) to debug (for arduino-core-tests make sure it has been built at least once to generate the required build.ino)
#. Optional parameters:
   * **boards.txt path**: Path to a custom `boards.txt` file
   * **gdb path**: Path to a custom GDB executable

Refer to the documentation of your chosen debugger and scripts in the `tools/` folder for more details.

.. note::
   If you encounter an error indicating that ``libncurses.so.5`` or a similar library cannot be found, please search online and install the appropriate package for your environment.

Release
---------
Add a git tag in the format `x.y.z` (e.g. 3.3.0) to trigger the release process.

For detailed steps on how to release the package, refer to the 
`Release Process Documentation <https://ifx-arduino-devops.readthedocs.io/en/latest/release/index.html>`_.


Creating and Maintaining Third Party Libraries
------------------------------------------------
Basics
^^^^^^^^
The Arduino IDE allows for external libraries to be added to support specific devices and functions which are not part of the core setup. For details on creating libraries see the 
`Arduino library specification <https://arduino.github.io/arduino-cli/library-specification/>`_.

If you add additional libraries to this project, make sure to `document them <https://xmc-arduino.readthedocs.io/en/latest/builtin-libraries.html>`_ accordingly.

XMC-for-Arduino Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
To ensure that a library specific to one architecture or board type is only compiled when a supporting board is set up, this specification includes a setting for *architecture* in the *library.properties* file.

When creating or maintaining third party or external libraries for XMC-for-Arduino please use this setting:

   .. code-block:: text
      
      architecture=xmc

If your library also supports other boards and architectures, add those in as well.
