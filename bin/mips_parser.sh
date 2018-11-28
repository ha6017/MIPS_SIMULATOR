#!/bin/bash

cd tests/bin
rm *.bin
cd ../..

FILES="tests/meta/*.meta"


for F in $FILES; do
  echo $F
  "bin/parser_linux" $F "tests/bin/#"
done

echo -e "Finished.\n"
