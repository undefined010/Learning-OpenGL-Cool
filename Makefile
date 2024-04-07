
all:
	clang -Wno-deprecated -Wall -Wextra src/*.c -lglfw3 -lGLEW -framework OpenGL -framework IOKit -framework CoreFoundation -framework Cocoa -framework CoreVideo -o bin/game