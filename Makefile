OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include/eigen3 -I./

BIN=rt
SRCS1=rt.cpp scene.cpp object.cpp material.cpp camera.cpp light.cpp 
SRCS2=color.cpp ray.cpp transform.cpp image.cpp sphere.cpp integrator.cpp tinyxml2.cpp
INCLUDES1=rt.hpp scene.hpp object.hpp material.hpp camera.hpp light.hpp 
INCLUDES2=color.hpp utils.hpp ray.hpp image.hpp sphere.hpp transform.hpp integrator.hpp tinyxml2.h

SRCS=$(SRCS1) $(SRCS2)
INCLUDES=$(INCLUDES1) $(INCLUDES2)

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
