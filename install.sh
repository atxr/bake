#!/bin/bash

# check if openssl is installed
if ! command -v openssl &> /dev/null
then
    echo "openssl could not be found"
    echo "please install it"
    exit
fi

# install thimble lib
cd tmp
git clone https://github.com/btams/thimble
cd thimble
make
sudo make install
cd ..

# install fjfx lib
git clone https://github.com/jerem/FingerJetFXOSE
cd FingerJetFXOSE/FingerJetFXOSE
./runCMake.sh x64
sudo mkdir /usr/local/include/fjfx/
sudo cp libFJFX/include/FJFX.h libFRFXLL/include/FRFXLL* /usr/local/include/fjfx/
cd build/Linux-x86_64/x64 
make
cd ../../../dist/Linux-x86_64/x64/
sudo cp libFRFXLL_static.a /usr/local/lib/libFRFXLL.a
sudo cp libFJFX_static.a /usr/local/lib/libFJFX.a
cd ../../../../../
sudo mv fjfx_all.h /usr/local/include/fjfx/all.h 

# clean installation
cd ..
sudo rm -r tmp 

# build the app
mkdir build
cd build
cmake ..
make
cd ..
