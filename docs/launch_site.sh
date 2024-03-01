# set path to directory of this script
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"
# copy docs
cd ..
./docs/copy_docs.sh
cd docs/
# activate python virtual environment
source env/bin/activate
# launch the site locally
mkdocs serve