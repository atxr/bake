# BAKE
## Biometrics-authenticated key exchange

This project aims to implement a biometrics-authenticated key exchange protocol designed at da-sec during my internship.

### Motivation

TODO

### Installation & Dependencies

Follow the following steps to install `BAKE`:

```bash
git clone https://github.com/atxr/bake
cd bake
./install.sh
```

You should have the following dependencies before installing `BAKE`:

- Openssl C library, which can be easily installed on Linux with:
```bash
sudo apt install openssl #Debian based distro
sudo pacman -S openssl #Archlinux based distro
brew install openssl #MacOS
```
- C++ build tools: CMake, make, GCC...

The installation script will setup the following libraries, which are requirements:
- [thimble library](https://github.com/btams/thimble), a Fuzzy Vault implementation
- [FingerJetFX library](https://github.com/FingerJetFXOSE/FingerJetFXOSE), a Minutiae Point extractor

The is working on x86-64 devices only. Feel free to open an issue if you want an installation script for another architecture. 

### Building

Move to the `build` directory and compile the app inside:
```bash
cd build
cmake ..
make
```

Then you will be able to execute the built applications in this directory. Check the (TODO coming soon) documentation to understand the apps.
The building has been tested on Archlinux x64 only, feel free to open an issue if you experience building issues with another architecture. 

### Documentation

TODO

FIXME permutation error
```bash
mv /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0001_2_5.pgm /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0001_2_5.err
cp /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0001_2_4.pgm /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0001_2_5.pgm
mv /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0004_8_1.pgm /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0004_8_1.err
cp /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0004_8_0.pgm /mnt/dasec/dataset/mcyt/mcyt330dp/pgm/dp_0004_8_1.pgm
```