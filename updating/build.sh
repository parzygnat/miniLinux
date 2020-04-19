#!/bin/bash
set -e
BR_NAME=buildroot-2020.02
BR_FILE=${BR_NAME}.tar.bz2
BR_DL=../${BR_FILE}
set -e
if [ ! -f ${BR_DL} ] || ! ( bzip2 -q -t ${BR_DL}); then
  (  
     cd ..
     rm -f ${BR_FILE}
     wget https://buildroot.org/downloads/${BR_FILE}
  )
fi
tar -xjf ${BR_DL}
cp BR_CONFIG ${BR_NAME}/.config
cp kernel.conf ${BR_NAME}/kernel.conf
cp -r my_overlay ${BR_NAME}
cd ${BR_NAME}
make

