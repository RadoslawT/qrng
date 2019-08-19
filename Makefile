#This makefile should be used with a Gnu Make compatible
#make program.
#
#When the Gnu Make is not available,simply comment out
#the lines defining the test of OS:
#   ifeq ($(OS),Darwin)
#      LDFLAGS += -L/opt/local/lib -lusb-1.0
#   endif
#
#When running on Mac OS X system, please define the variable
#"OS" with the value "Darwin" by running the command
#"make OS=Darwin"
LIB_AND_APPS_PATH = /home/radek/Desktop/quantis3/Libs-Apps/
QUANTIS_LIB_PATH = $(LIB_AND_APPS_PATH)build/Quantis
QUANTIS_EXT_LIB_PATH = $(LIB_AND_APPS_PATH)build/QuantisExtensions
QUANTIS_INC_PATH = $(LIB_AND_APPS_PATH)Quantis
QUANTIS_EXT_INC_PATH = $(LIB_AND_APPS_PATH)QuantisExtensions

CFLAGS += -I$(QUANTIS_INC_PATH)
CFLAGS += -I$(QUANTIS_EXT_INC_PATH)
CXXFLAGS += -I$(QUANTIS_INC_PATH)
CXXFLAGS += -I$(QUANTIS_EXT_INC_PATH)

LDFLAGS = -lusb-1.0 -L$(QUANTIS_LIB_PATH) -lQuantis `simple2d --libs`

ifeq ($(OS),Darwin)
  LDFLAGS += -L/opt/local/lib -lusb-1.0
endif

qrng-sources := \
	src/main.cpp \
	src/models/qrng_logger.cpp \
	src/models/random_image_renderer.cpp \
	src/models/quantum_measurements_set.cpp \
	src/models/quantum_measurement.cpp \
	src/helpers/probability_helper.cpp \
	src/helpers/qrng.cpp \
	src/helpers/cast_helper.cpp

qrng-objects := $(qrng-sources:.c=.c.o)
qrng-objects := $(qrng-objects:.cpp=.cpp.o)

all: qrng

qrng: $(qrng-objects)
	@echo "-->  Linking executable $@"
	@$(CXX) -o bin/$@ $(qrng-objects) $(LDFLAGS)

clean:
	@rm -rf *.o *~ bin/qrng


%.cpp.o: %.cpp
	@echo "->  Building CXX object $@"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

%.c.o: %.c
	@echo "->  Building C object $@"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

