@ECHO OFF
cd dist
7z.exe a -tzip ShadowOfTheWyrm-Win.zip * -r -x!*.pdb
cd ..
@ECHO dist\ShadowOfTheWyrm.zip created!
