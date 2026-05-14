# Nome do programa
TARGET = main

# Pastas
SRC_DIR = src
INC_DIR = include

# Compilador e Flags
CXX = g++
# -I diz onde procurar os headers (.hpp)
# -L diz onde procurar as bibliotecas (.a / .lib)
CPPFLAGS = -I$(INC_DIR) -I"C:/msys64/ucrt64/include"
LDFLAGS = -L"C:/msys64/ucrt64/lib" -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CXX) $(SRC_DIR)/*.cpp -o $(TARGET) $(CPPFLAGS) $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm $(TARGET).exe
# Não esquecer que para compilar e mingw32-make