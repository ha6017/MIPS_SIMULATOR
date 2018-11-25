#!/bin/bash

cd bin/tests/bin
rm *.bin
cd ../../..

cd bin/mips-parser
make parser
cd ../..

FILES="bin/tests/src/*.meta"


for F in $FILES; do
  echo $F
  "bin/mips-parser/bin/parser" $F "bin/tests/bin/#"
done

echo -e "Finished.\n"
