#!/bin/bash

echo Checking TRUST root ...
[ -d "$TRUST_ROOT" ] || exit -1
echo Checking mini root ...
[ -d "$MINI_ROOT" ] || exit -1

cd $MINI_ROOT

for f in `find src \( -name "*.cpp" -or -name "*.tpp" -or -name "*.h" \) -not -name "medcoupling++.*" -not -name "ICoCoExceptions.*" -not -name "petsc_for_kernel.*"`
do
  if [ -f $f ]; then
     dirn=`dirname $f` 
     echo "copy file $f to $dirn"
     cp $TRUST_ROOT/$f $dirn
  else
     echo "removing file $f"
     rm $f
  fi
done 

