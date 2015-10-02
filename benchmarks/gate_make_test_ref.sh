#!/bin/bash

if [ "$#" -ne 3 ]
then
    echo "Usage (example): `basename $0` benchRT gamma Linux"
    exit 1
fi

echo "The reference will be built from the first_parameter/'output' folder content, based on the list of files provided in the reference/second_parameter.txt file. Third parameter is the architecture (not mandatory)."
echo "This script should be launched from a git repository."

echo "Current directory:"
pwd
echo

echo "Printing the three parameters for debugging:"
echo $1
echo $2
echo $3


# This script should be launched locally, from its containing folder
# Note : ${BASH_SOURCE[0]} contains this script name
# Tests -ge instead of -eq to include the case of there are backup versions of the script in the current folder.
if [ `ls | grep ${BASH_SOURCE[0]} | wc -l` -ge 1 ]; then
    echo "This script is launched locally, from its containing folder."
    BENCHMARKS_DIRECTORY=`pwd`
# exit otherwise
else
    echo "You are launching gate_make_test_ref.sh from an improper location. Please launch this script locally, from its containing folder."
    exit 1
fi

echo
echo "Benchmarks directory:"
echo $BENCHMARKS_DIRECTORY
echo
cd $BENCHMARKS_DIRECTORY/$1/

echo "Working directory:"
pwd

echo
echo

echo "----------------------------------------------------"
echo "Reference archive creation:"
mkdir test_ref

# Each line of the $2.txt file is splitted (separator is space) and stored in an array 'WORD'
while read -a WORD
do
    echo "${WORD[@]}"

    cp output/${WORD[1]} test_ref

done <reference/$2.txt

cp reference/$2.txt test_ref
git add reference/$2.txt test_ref

echo "This reference was created by launching a Gate simulation on" >reference/$2_ref.txt
echo $(date) >>reference/$2_ref.txt
echo "with the configuration file benchmarks/$1/mac/$2.mac" >>reference/$2_ref.txt
echo "from the commit" >>reference/$2_ref.txt
echo $(git log |head -1) >>reference/$2_ref.txt
echo "with the version of gcc" >>reference/$2_ref.txt
echo $(gcc --version |head -1) >>reference/$2_ref.txt
echo "on the architecture" >>reference/$2_ref.txt
echo $(uname --all) >>reference/$2_ref.txt

cp reference/$2_ref.txt test_ref
git add reference/$2_ref.txt test_ref

tar cvzf $1-reference.tgz test_ref/*
mv $1-reference.tgz reference
rm -rf test_ref
echo "----------------------------------------------------"

cd reference

echo "md5sum creation."
echo $(md5sum $1-reference.tgz | cut -f 1-1 -d ' ') >$1-reference.tgz.md5
git add $1-reference.tgz.md5

echo "$1-reference.tgz" >> .gitignore
echo "$1-reference.tgz.md5-stamp" >> .gitignore
git add .gitignore

cd ../..

echo "GateAddBenchmarkData(\"DATA{$1/reference/$1-reference.tgz}\")" >> CMakeLists.txt
git add CMakeLists.txt

echo
echo "----------------------------------------------------"
echo "Here is a 'git status':"
git status
echo "Don't forget to commit and push the local modifications, especially the new files."
echo
echo "Don't forget to upload your data $1-reference.tgz (from $1/reference folder) in http://midas3.kitware.com/midas/community/28"

exit 0
