# Onboard SDK Examples

This repository includes examples how to use the Blunux Onboard SDK.

Please find the documenataion here:
https://blueye-robotics.github.io/onboard_sdk_examples/


## Build using docker

Pull the cross-compilation tool chain
```
docker pull ghcr.io/blueye-robotics/blunux-onboard-sdk:blunux-3.3-x86_64
```

Start the container
```
docker run -it --name blunux-sdk --rm -v $(pwd):/root/workspace ghcr.io/blueye-robotics/blunux-onboard-sdk:blunux-3.3-x86_64
```

In the container, run
```
source /opt/poky/3.4.4/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi 
cd /root/workspace
mkdir build
cd build
cmake ..
make -j $(nproc)
```

Afterwards, the programs are found in the build folder and can be copied to the drone.
