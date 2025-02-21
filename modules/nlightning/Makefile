all: module.a

CXXFLAGS += -Wall -Wextra -std=c++20 -I ../../include
NLIGTHING_LIB_PATH := ./nlightning_lib/bin/Release/net8.0/linux-x64/publish/nlightning_lib.so
NLIGTHING_LIB_NAME := nlightning_lib.so

# Adicione uma regra para construir a biblioteca .NET, se ela não existir
$(NLIGTHING_LIB_PATH):
	cd ./nlightning_lib && dotnet publish -c Release -r linux-x64 --self-contained true

module.a: module.o $(NLIGTHING_LIB_PATH)
	bash ../../merge.sh module.a $(NLIGTHING_LIB_PATH) module.o
	ranlib module.a

module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c module.cpp -o module.o

clean:
	rm -rf *.o module.a