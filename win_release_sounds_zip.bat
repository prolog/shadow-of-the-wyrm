@ECHO OFF
mkdir dist_sounds
copy assets\sound\effects\* dist_sounds
copy license dist_sounds
cd dist_sounds
7z.exe a -tzip ShadowOfTheWyrm-Sounds.zip * -r
cd ..
@ECHO dist_sounds\ShadowOfTheWyrm-Sounds.zip created!
