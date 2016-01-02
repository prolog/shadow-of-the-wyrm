#!/bin/bash
if [ -z "$1" ]; then
    echo "No version tag supplied!"
else
    echo "Creating version $1..."
    hg tag "$1"
    hg update stable
    hg merge default
    hg commit -m "Merge default to stable for release $1"
    hg push
    echo "Done!"
fi
