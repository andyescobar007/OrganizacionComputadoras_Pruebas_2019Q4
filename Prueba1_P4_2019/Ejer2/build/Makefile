TARGET=libEjer2.so
BUILD_DIR=build_comp
VLOG_DIR=..
VLOG_SOURCES=../Ejer2.v
LIB_FILES=$(BUILD_DIR)/VEjer2__ALL.a
CPP_SOURCES=Ejer2.cpp Ejer2_upc.cpp
VERILATOR_ROOT=/opt/verilator
VERILATOR=$(VERILATOR_ROOT)/bin/verilator
LDFLAGS=-shared -lm -lstdc++ -static-libgcc -static-libstdc++
CFLAGS=-O2 -fPIC 

.PHONY: $(BUILD_DIR) clean

all: $(TARGET)
$(TARGET): $(BUILD_DIR) $(CPP_SOURCES:.cpp=.o) verilated.o
	g++ -o $@ $(CPP_SOURCES:.cpp=.o) verilated.o $(LIB_FILES) $(LDFLAGS)

verilated.o: $(VERILATOR_ROOT)/share/verilator/include/verilated.cpp
	g++ -c $(CFLAGS) -I./$(BUILD_DIR) -I$(VERILATOR_ROOT)/share/verilator/include -o $@ $<

%.o: %.cpp
	g++ -c $(CFLAGS) -I./$(BUILD_DIR) -I$(VERILATOR_ROOT)/share/verilator/include -o $@ $<

$(BUILD_DIR): $(VERILOG_SOURCES)
	$(VERILATOR) -DDIGITAL=1 -Wall -I../ \
		--cc ../Ejer2.v -Mdir $(@) -CFLAGS "$(CFLAGS)"
	make -C $(@) -f VEjer2.mk

clean::
	rm -rf *.o $(TARGET) $(BUILD_DIR)

