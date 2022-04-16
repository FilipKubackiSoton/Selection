docker run --rm -v "$PWD":/usr/src/myapp gcc:test g++ -Wall -I /bin/gsl/include -L /bin/gsl/lib -O3 *.cpp -lgsl -lgslcblas -lm -o sr
