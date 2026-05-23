REM Remember to notify Larzid so he can update the checksums!
@ECHO OFF
mkdir dist_assets
cd dist_assets
7z.exe a -tzip ShadowOfTheWyrm-assets.zip ..\assets -r
cd ..
@ECHO dist_assets\ShadowOfTheWyrm-assets.zip created!
