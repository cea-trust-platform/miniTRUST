#!/bin/bash -e

# 
# This script builds a primary version of miniTRUST with just the necessary stuff from
# Kernel and VEF. It stops at the first error.
# 
# Some extra steps are taken (creation of dummy files, patching of CMake files, ...) so that
# the mini app can be simply compiled.
#

echo Checking TRUST root ...
[ -d "$TRUST_ROOT" ] || exit -1
echo TRUST_ROOT is $TRUST_ROOT

echo Checking mini root ...
[ -d "$MINI_ROOT" ] || exit -1

cd $MINI_ROOT

rm -rf src
mkdir src

### Main copy **and** creating src/CMakeLists.txt
MAIN_DIRS="Kernel MAIN ThHyd ThSol VEF"
for d in $MAIN_DIRS; do
    echo "Copying $d ..."
    cp -a $TRUST_ROOT/src/$d src
done

# Remove ICoCo
echo "Removing ICoCo (but keep exceptions) ..."
rm -rf src/Kernel/ICoCo
rm src/Kernel/Champs/*nput*  # Champ input
rm src/Kernel/Champs_dis/*nput*  # Champ input
rm src/Kernel/Champs/Champs_Don/Ch_input_*
cp $TRUST_ROOT/lib/src/LIBICOCOAPI/include/ICoCoExceptions.* src/Kernel/Utilitaires
cp $TRUST_ROOT/ThirdPart/src/LIBICOCOAPI/src/ICoCoExceptions.cpp src/Kernel/Utilitaires

# Remove various bits
echo "Removing bits of VDF, PolyMAC and multiphase ..."
rm -rf src/ThHyd/Chimie

### Creating src/CMakeLists.txt
for d in $MAIN_DIRS; do
    for dd in `find src/$d -name 'CMakeLists.txt'`; do
        dr=`echo $dd |sed 's@src/\(.*\)/CMakeLists.txt@\1@' `
        echo "add_subdirectory(\"$dr\")" >> src/CMakeLists.txt
    done
done

### Removing un-necessary files
echo "Removing non cpp/h/tpp files and instancie files ..."
find src -not \( -name "*.cpp" -or -name "*.tpp" -or -name "*.h*" -or -name "CMakeLists.txt" \) -type f | xargs rm

### Remove instancie files
echo "Removing instancie files ..."
find src -name "instancie*" |  xargs rm
#   to avoid no source in dir:
touch src/VEF/toto.cpp
touch src/VEF/Operateurs/toto.cpp

### Dummy headers
echo "Creating dummy headers (medcoupling++, med++, petsc_for_kernel, etc...)"
echo "" > src/Kernel/Utilitaires/medcoupling++.h
echo "" > src/Kernel/Utilitaires/petsc_for_kernel.h
echo "" > src/Kernel/Utilitaires/parmetis++.h
echo "" > src/Kernel/Utilitaires/ptscotch++.h
echo "" > src/Kernel/Utilitaires/coolprop++.h
echo "" > src/Kernel/Utilitaires/eos++.h
echo "" > src/Kernel/Utilitaires/rocalution_for_kernel.h
echo "" > src/Kernel/MEDimpl/med++.h
echo "" > src/Kernel/Utilitaires/med.h  # this one because of FichierHDF.h - probably sth wrong in TRUST ...

### Patching CMake
echo "Patching CMake files ..."
find src -name CMakeLists.txt | xargs sed -i "s/add_DEPENDENCIES/#add_DEPENDENCIES/g"

### Creating CMake object list:
echo "Adding sub-targets to CMakeFile ..."
echo 'set(sub_parts ' > src/obj_lst.cmake
find src -name "CMakeLists.txt" | xargs grep 'add_library(obj_' | cut -d '(' -f 2 | cut -d ' ' -f 1 >> src/obj_lst.cmake
echo ' ) ' >> src/obj_lst.cmake

###
### Various fixes 
###
echo "Various fixes ..."
#   Rather than patching those, I exclude them - they do not compile
rm src/Kernel/Geometrie/Decoupeur/Decouper_multi.*
rm src/Kernel/MEDimpl/Champ_Fonc_MED_Table*
rm src/Kernel/Champs/Champs_Don/Champ_Fonc_Tabule_Morceaux*
rm src/Kernel/Champs/Champ_front_xyz_debit.*
rm src/Kernel/Champs/Champ_front_debit*
rm src/Kernel/MEDimpl/Integrer_champ_med*
rm src/Kernel/MEDimpl/LataToMED.*
rm src/Kernel/MEDimpl/Pb_MED.*

# Those ones do not link, most often because they use FORTRAN calls
rm src/Kernel/Geometrie/Decoupeur/Partitionneur_Metis.*
rm src/Kernel/Geometrie/ExtrudeParoi.*
rm src/Kernel/Geometrie/Lire_Ideas.*
rm src/Kernel/Math/SolvSys/ILU_SP.*
rm src/Kernel/Math/SolvSys/SolvElem_BiCGStab*
rm src/Kernel/Math/SolvSys/SolvElem_Gmres.*
rm src/Kernel/Math/SolvSys/Solv_Cholesky.*
rm src/Kernel/Math/Matrices/Matrice_Dense*
rm src/Kernel/Math/Matrices/Sparskit.*
rm src/Kernel/Math/SolvSys/Solv_Gen.*

echo "Applyting patches ..."
for f in patches/*.patch; do
    echo "  Patch $f ..."
    patch -p1 < $f
done

