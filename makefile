main:main.o CIFIndex.o
	g++ -o main main.o CIFIndex.o
main.o:main.cpp 
	g++ -c main.cpp
CIFIndex.o:CIFIndex.cpp
	g++ -c CIFIndex.cpp
rm:
	rm main main.o
