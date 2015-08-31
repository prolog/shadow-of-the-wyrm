@ECHO OFF
cd dist
7z.exe a -tzip SavageLands.zip * -r -x!*.pdb
cd ..
@ECHO dist\SavageLands.zip created!
