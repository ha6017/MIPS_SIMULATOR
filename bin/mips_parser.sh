#!/bin/bash

cd bin/tests/bin
rm *.bin
cd ../../..

FILES="bin/tests/src/*.meta"


for F in $FILES; do
  echo $F
  "bin/parser_mac" $F "bin/tests/bin/#"
done

echo -e "Finished.\n"
