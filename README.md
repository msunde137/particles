# particles

Implements particle systems using openGL

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake -G "Visual Studio 16 2019" ..
particles/build $ start CS312-Particles.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
particles/build $ ../bin/Debug/billboard
particles/build $ ../bin/Debug/confetti
particles/build $ ../bin/Debug/demo
```

*macOS*

Open terminal to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake ..
particles/build $ make
```

To run each program from build, you would type

```
particles/build $ ../bin/billboard
particles/build $ ../bin/confetti
particles/build $ ../bin/demo
```

## Results

Implemented a confeti particle system with gravity.

I<img width="376" alt="Particles1" src="https://user-images.githubusercontent.com/54864515/116822128-0b92d080-ab4b-11eb-943f-ff8a53331fd1.PNG">

Implemented a fireworks particle system with drag and gravity.

<img width="387" alt="Particles2" src="https://user-images.githubusercontent.com/54864515/116822129-0b92d080-ab4b-11eb-9b32-bc1dbea45dda.PNG">
