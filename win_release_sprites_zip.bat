@ECHO OFF
mkdir dist_sprites
copy assets\sprites\* dist_sprites
copy license dist_sprites
cd dist_sprites
7z.exe a -tzip ShadowOfTheWyrm-Sprites.zip * -r
cd ..
@ECHO assets\sprites\ShadowOfTheWyrm-Sprites.zip created!
