# set path to directory of this script
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"
# remove all files in docs
./remove_docs.sh
# copy all DOC*.md files and PIC* files to docs
cd ..
cp */DOC*.md docs/docs
cp */*/DOC*.md docs/docs
cp */*/*/DOC*.md docs/docs
cp */PIC* docs/docs | true
cp */*/PIC* docs/docs | true
cp */*/*/PIC* docs/docs | true
# set index page
mv docs/docs/DOC_DED_PD_Project_Description.md docs/docs/index.md
