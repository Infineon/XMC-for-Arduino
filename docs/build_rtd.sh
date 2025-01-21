#!/bin/bash

# Check if Python and pip are installed
if ! command -v python3 &> /dev/null
then
    echo "Python 3 could not be found. Please install Python 3."
    exit
fi

if ! command -v pip3 &> /dev/null
then
    echo "pip3 could not be found. Please install pip3."
    exit
fi

# Create a virtual environment
python3 -m venv myenv
source myenv/bin/activate

# Install Sphinx and Read the Docs theme
pip install sphinx sphinx_rtd_theme

# Install project dependencies (if requirements.txt file exists)
if [ -f "requirements.txt" ]; then
    pip install -r requirements.txt
fi

# Check if the Sphinx project folder exists
if [ ! -d "source" ]; then
    # Initialize Sphinx project
    sphinx-quickstart -q --project "My Project" --author "Author Name" --release "0.1" --extensions "sphinx_rtd_theme" --sep -v
fi

# Configure conf.py file
CONF_FILE="source/conf.py"
if ! grep -q "sphinx_rtd_theme" "$CONF_FILE"; then
    echo "Configuring conf.py to use Read the Docs theme..."
    echo "
import os
import sys
sys.path.insert(0, os.path.abspath('.'))
html_theme = 'sphinx_rtd_theme'
" >> "$CONF_FILE"
fi

# Build documentation
make html

# Open generated documentation
HTML_FILE="build/html/index.html"
if command -v explorer.exe &> /dev/null; then
    explorer.exe $(wslpath -w $HTML_FILE)
else
    echo "Please open build/html/index.html manually."
fi

echo "Documentation build complete."