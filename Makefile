TARGET = main
SRC = src
INC = include
BIN = bin

SOURCE = $(wildcard $(SRC)/*.cpp)
OBJECT = $(patsubst %,$(BIN)/%, $(notdir $(SOURCE:.cpp=.o)))

DEVICE = msp430f5529
DRIVER = tilib
CXX = msp430-gcc -mmcu=$(DEVICE)
CXXFLAGS = -I$(INC) 

$(BIN)/$(TARGET) : $(OBJECT)
	@echo "Linking..."
	$(CXX) -o $@ $^
	@echo "Finished!"

$(BIN)/%.o : $(SRC)/%.cpp
	@echo "Compiling..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

PHONY : run clean

flash : $(BIN)/$(TARGET)
	@echo "Flashing..."
	mspdebug $(DRIVER) "prog $(BIN)/$(TARGET)"

clean :
	rm -f $(OBJECT) $(BIN)/$(TARGET)




