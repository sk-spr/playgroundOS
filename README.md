# playgroundOS - an experimental operating system for learning
This is my first operating system. It is a personal projects to learn the practice of OSdev by doing.

## build
To build playgroundOS to a bootable .iso, you must set up the build environment.
### Linux
```
sudo chmod +x ./setup.sh && ./setup.sh
```

To build the operating system, enter the docker build environment
```
sudo chmod +x ./run.sh && ./run.sh
```
Then, execute the build command
```
make build-x86_64
```

Finally, to run your ISO in QEMU, run the following command:
```
qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso
```
