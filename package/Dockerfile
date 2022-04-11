FROM gcc:9.4.0-buster

RUN cd /home \
    && wget ftp://ftp.gnu.org/gnu/gsl/gsl-2.7.tar.gz \
    && tar -zxvf gsl-2.7.tar.gz \
    && cd gsl-2.7 \
    && mkdir /bin/gsl \
    && ./configure --prefix=/bin/gsl \
    && make \
    && make check \
    && make install
 
WORKDIR /usr/src/myapp

RUN export LD_LIBRARY_PATH=/bin/gsl/lib 
