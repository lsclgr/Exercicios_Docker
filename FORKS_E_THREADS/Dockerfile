FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y vim
RUN mkdir Luisa
WORKDIR /Luisa
COPY Luisa.txt ./
COPY forks.c ./
COPY threads.c ./
