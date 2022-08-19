# BAKE
## Biometrics-authenticated key exchange

This project aims to implement a biometrics-authenticated key exchange protocol designed at da-sec during my internship.

### Motivation

Biometric data are uniquely suited for connecting individuals to their digital identities. Deriving cryptographic key exchange from successful biometric authentication therefore gives an additional layer of trust compared to password-authenticated key exchange. However, biometric data differ from passwords in two crucial points: firstly, they are sensitive personal data that need to be protected on a long-term basis. Secondly, efficient feature extraction and comparison components resulting in high intra-subject tolerance and low inter-subject distinguishability, documented with good biometric performance, need to be applied in order to prevent zero-effort impersonation attacks.

In this work, we present a protocol for secure and efficient biometrics-authenticated key exchange that fulfills the above requirements of biometric information protection compliant with ISO/IEC 24745. The protocol is based on established fuzzy vault schemes and validated with good recognition performance. We build our protocol from established primitives for password-authenticated key exchange using oblivious pseudo-random functions. Our protocol is independent of the biometric modality and can be instantiated both based on the security of discrete logarithms as well as lattices. We provide an open-source implementation of our protocol instantiated with discrete logarithm security and a state-of-the-art unlinkable fingerprint fuzzy vault scheme that is practical with transaction times of less than one second from the image capture to the completed key exchange.

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
- [FingerJetFX library](https://github.com/FingerJetFXOSE/FingerJetFXOSE), a Minutiae Extractor

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
