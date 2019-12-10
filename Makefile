compile: coordinator.c function.c function.h
		 gcc -o coordinator coordinator.c function.c function.h -lpthread
clean:
		 rm coordinator
