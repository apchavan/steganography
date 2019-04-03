
# Declaration of necessary variables

HDIR := inc
ODIR := obj
CDIR := src
DESTDIR :=

SOURCES :=  MatImage.cc TextFile.cc util.cc Error.cc 
OBJECTS := $(SOURCES:%.cc=$(ODIR)/%.o)

# Change version of 'gtkmm-x.x' with the latest installed, since here's version (2.4) might be different.
LIBRARIES := gtkmm-2.4 opencv openssl
CC := g++
CFLAGS := -O `pkg-config --cflags $(LIBRARIES)` -I $(HDIR) -std=c++11
LFLAGS := -O `pkg-config --libs $(LIBRARIES)` -std=c++11

vpath %.h $(HDIR)
vpath %.cc $(CDIR)
vpath %.o $(ODIR)

# Commands to execute with their dependencies

all: cli

cli: steg unsteg

steg: $(OBJECTS) $(ODIR)/steg.o
	@echo " Making $@"
	@$(CC) $^ -o $@ $(LFLAGS)
	
unsteg: $(OBJECTS) $(ODIR)/unsteg.o
	@echo " Making $@"
	@$(CC) $^ -o $@ $(LFLAGS)
	
$(ODIR)/%.o: %.cc $(HDIR)/*.h
	@echo " Compiling $<"
	@mkdir -p $(ODIR)
	@$(CC) $(CFLAGS) $< -c -o $@
	
clean: clean-exe clean-obj

clean-exe: 
	@echo " Cleaning the executables "
	@rm -f steg unsteg
	
clean-obj: 
	@echo " Cleaning the object files "
	@rm -rf $(ODIR)
	
