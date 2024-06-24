# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Archivos objeto
OBJS = nodo.o slip.o

# Regla principal para construir el ejecutable
nodo: $(OBJS)
	$(CXX) $(CXXFLAGS) -o nodo $(OBJS)

# Reglas para construir los archivos objeto
nodo.o: nodo.cpp slip.h
	$(CXX) $(CXXFLAGS) -c nodo.cpp

slip.o: slip.cpp slip.h
	$(CXX) $(CXXFLAGS) -c slip.cpp

# Limpieza de archivos generados
clean:
	rm -f $(OBJS) nodo

# Regla phony para evitar conflictos con archivos llamados clean
.PHONY: clean