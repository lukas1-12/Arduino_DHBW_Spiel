# Set the directory to docs folder
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"/docs
# remove all files in docs
rm *