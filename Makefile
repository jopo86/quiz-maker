compile_run:
	g++ -o build/debug/a -L lib -I include src/*.cpp && ./build/debug/a
compile:
	g++ -o build/debug/a -L lib -I include src/*.cpp
run:
	./build/debug/a