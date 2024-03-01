# set path to directory of this script
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"
# create python virtual environment
python3 -m venv env
# activate python virtual environment
source env/bin/activate
# install required python packages
pip install mkdocs-material
pip install pillow cairosvg
pip install mkdocs_custom_fences
pip install markdown-include
pip install mkdoxy
pip install mkdocs_puml
