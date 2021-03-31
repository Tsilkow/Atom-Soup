#!/bin/bash

#rm -rf build/
#mkdir build/
#cp Sicretmono.ttf build/Sicretmono.ttf
#cp station.png build/station.png
#cp scores.json build/scores.json
cp -r data/ build/
clear
cd build/
cmake ..
if eval cmake --build .; then
    if [ "$#" -ge 1 ]; then
	exec "./AtomSoup" "$1"
    else
	exec "./AtomSoup"
    fi
    cd ..
else
    cd ..
fi
    
