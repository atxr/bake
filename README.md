# BAKE
## Biometrics-authenticated key exchange

In this repository, we provide our code corresponding to our submission "Improved Biometrics-Authenticated Key Exchange Based on Fuzzy Vaults" at S&P 2023 (second cycle).
### Installation & Dependencies

After downloading the repository, follow these steps to install `BAKE`:

```bash
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

Then you will be able to execute the built applications in this directory. Check the documentation to understand the apps.
The building has been tested on Archlinux x64 only, feel free to open an issue if you experience building issues with another architecture. 
