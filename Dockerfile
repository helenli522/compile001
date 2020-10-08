FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc test.c -o test
RUN chmod +x test