#!/bin/bash

rootDirectory="$(dirname "$(readlink -n "$0")")";
binPath="bin/tests";
simPath=$1
cd "$binPath"
rm output.csv
$cat > output.csv
cd ../..
files="./$binPath/*.meta"
outputFile="./$binPath/output.csv"
text="Test ID, Instruction name, Expected Output, Author, Additional Information"
echo "$text" >> "$outputFile";

for testFile in ${files}; do
  echo "$testFile"

  testName=$(basename "$testFile");
  testName="${testName%%.*}";
  echo "$testName"
  metadata=()
  #for each line, extract the important information
  while read -r line || [[ -n "$line" ]];
  do
    metadata+=("${line//#}");
  done < "$testFile"

  #instruction ID
  instID="$testName";
  #inst being tested
  instruction="${metadata[1]}";
  #correct output
  expectedOutput="${metadata[2]}";
  #author
  author="${metadata[3]}";
  #additional Information
  notes="${metadata[4]}";

  binFile="${testName}.bin";
  echo "$binFile"

  #simulator_run "$binFile";
  echo "${simPath} ${binPath}/$binFile"
  ${simPath} ${binPath}/$binFile
  output=$?
  echo "$output"

  if [ $output -eq $expectedOutput ]; then
    success="Success";
  else
    success="Fail";
  fi
  text=""$instID", "$instruction", "$success", "$author", "$notes"";
  echo "$text" >> "$outputFile";
  echo "$text"
    #echo $success
    #text=""
    #successful output
    #expectedOutput=metadata[1];
    #echo expcted output $expectedOutput
    #execute testbench
    #compare results
    #output success or failure
done
