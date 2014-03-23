#!/bin/sh

# Called twice due to the two passes needed for the table of contents.
pdflatex Guide.tex
pdflatex Guide.tex
mv Guide.pdf ..

