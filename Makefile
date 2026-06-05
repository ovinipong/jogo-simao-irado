# Nome do programa
TARGET = main

# Pastas
SRC_DIR = src
INC_DIR = include

# Compilador e Flags
CXX = g++
# -I diz onde procurar os headers (.hpp)
# -L diz onde procurar as bibliotecas (.a / .lib)
CPPFLAGS = -I$(INC_DIR) \
           -I$(INC_DIR)/Entidades \
           -I$(INC_DIR)/Entidades/Obstaculos \
           -I$(INC_DIR)/Entidades/Personagens \
           -I$(INC_DIR)/Fases \
           -I$(INC_DIR)/Gerenciadores \
           -I$(INC_DIR)/Listas \
           -I"C:/msys64/ucrt64/include"
LDFLAGS = -L"C:/msys64/ucrt64/lib" -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CXX) $(SRC_DIR)/*.cpp \
	       $(SRC_DIR)/Entidades/*.cpp \
	       $(SRC_DIR)/Entidades/Obstaculos/*.cpp \
	       $(SRC_DIR)/Entidades/Personagens/*.cpp \
	       $(SRC_DIR)/Fases/*.cpp \
	       $(SRC_DIR)/Gerenciadores/*.cpp \
	       $(SRC_DIR)/Listas/*.cpp \
	       -o $(TARGET) $(CPPFLAGS) $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm $(TARGET).exe
# Não esquecer que para compilar e mingw32-make