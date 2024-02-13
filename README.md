# The rt Raytracing Framework


![rt logo](https://github.com/paragchaudhuri/rt/blob/master/doc/rt-logo-small.jpg?raw=true)

rt is a simple ray tracer framework written in C++. 

### Downloading rt

- rt can be downloaded by cloning the git repository using

  `git clone https://github.com/paragchaudhuri/rt.git`

### Dependencies

- The only external dependency required for rt depends is Eigen.
- Install `libeigen3-dev` on Ubuntu/Debian to get it. Use `brew` on MacOS.  
- Install this and update the path to the library in the `Makefile`.

### Compiling and using rt

- Run `make` to compile rt. 

  - You may have to change paths in the makefile to make it match your system.

- Then test it out with the provided scene file by running

  `./rt scenes/myscene.xml`

- For the scenefile format checkout the provided xml scenefile.


### Generating Documentation
- Documentation can be found in the `docs/html` folder. 
- look at `doc/html/namespaces.html` to begin.
- To generate the documentation from scratch, first install `doxygen` and `graphviz` and then run
  `make doc`


