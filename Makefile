compile_run:
	g++ -o build/debug/QuizMaker -L lib -I include src/*.cpp
	./build/debug/QuizMaker

compile:
	g++ -o build/debug/QuizMaker -L lib -I include src/*.cpp

run:
	./build/debug/QuizMaker