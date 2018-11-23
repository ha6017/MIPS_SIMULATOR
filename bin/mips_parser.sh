#!/bin/bash

cd bin/tests
rm *.bin
cd ../..

FILES="bin/tests/*.meta"

for F in ${FILES}; do
  bin/mips-parser-master/bin/parser $F "bin/tests/#"
done

echo -e "Finished.\n"
