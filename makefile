

ndsphere: ndsphere.cpp
	g++ -std=c++11 -g -Wall -Wextra -pedantic ndsphere.cpp -o ndsphere -fopenmp

test: ndsphere
	OMP_NUM_THREADS=4 ./ndsphere

t1: ndsphere
	OMP_NUM_THREADS=1 ./ndsphere


tn: ndsphere
	OMP_NUM_THREADS=$(t) ./ndsphere


clean:
	rm -f ndsphere seg length

gdb:
	OMP_NUM_THREADS=4 gdb ndsphere



seg: seg.cpp
	g++ -std=c++17 -g -Wall -Wextra -pedantic -mavx seg.cpp -o seg

s: seg
	./seg

length: length.cpp
	g++ -std=c++17 -g -Wall -Wextra -pedantic -mavx length.cpp -o length

plot:
	python3 plot.py
