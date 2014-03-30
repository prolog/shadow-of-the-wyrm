#!/bin/sh

# Called twice due to the two passes needed for the table of contents.
echo 'Generating the Guidebook.'
pdflatex Guide.tex
pdflatex Guide.tex
mv Guide.pdf ..

echo 'Generating the Command Reference.'
pdflatex Commands.tex
mv Commands.pdf ..

