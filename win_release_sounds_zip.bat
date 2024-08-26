@ECHO OFF
mkdir dist_sounds\effects
mkdir dist_sounds\music
copy assets\sound\effects\* dist_sounds\effects
copy assets\sound\music\* dist_sounds\music
copy license dist_sounds
cd dist_sounds
7z.exe a -tzip ShadowOfTheWyrm-Sounds.zip * -r
cd ..
@ECHO dist_sounds\ShadowOfTheWyrm-Sounds.zip created!
