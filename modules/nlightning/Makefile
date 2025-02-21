# CXX = /opt/homebrew/opt/llvm/bin/clang++
# CXXFLAGS += -Wall -Wextra -std=c++20 -I. -I ../../include

# The RID (Runtime Identifier) for which you want to publish.
#   linux-x64   (Linux 64-bit)
#   osx-x64     (macOS 64-bit, Intel)
#   osx-arm64   (macOS Apple Silicon)
#   win-x64     (Windows 64-bit)
RUNTIME_ID     := osx-arm64
# Output directory for "dotnet publish"
DOTNET_OUT_DIR := src/bin

all: module.a

module.a: dotnet module.o
	ar rcs module.a module.o
	/opt/homebrew/opt/llvm/bin/llvm-ranlib module.a

dotnet:
	dotnet publish src \
		-c Release \
		-r $(RUNTIME_ID) \
		-o $(DOTNET_OUT_DIR)

module.o: module.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c module.cpp -o module.o

clean:
	rm -rf *.o *.a $(DOTNET_OUT_DIR)