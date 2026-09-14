# Compilador y Banderas
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# Carpetas
SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

# Archivos
OBJS   = $(OBJ_DIR)/murmur3.o $(OBJ_DIR)/hyperloglog.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_hll

.PHONY: all clean run

# Regla principal
all: $(TARGET)

# Enlazado
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilacion de modulos
$(OBJ_DIR)/murmur3.o: $(SRC_DIR)/murmur3.cpp include/murmur3.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/hyperloglog.o: $(SRC_DIR)/hyperloglog.cpp include/hyperloglog.h include/murmur3.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/hyperloglog.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpetas si no existen
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Ejecutar el binario
run: all
	./$(TARGET)

# Limpiar
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
