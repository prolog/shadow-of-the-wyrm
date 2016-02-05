@ECHO OFF
cd dist_xp
7z.exe a -tzip ShadowOfTheWyrm-WinXP.zip * -r -x!*.pdb
cd ..
@ECHO dist_xp\ShadowOfTheWyrm.zip created!
