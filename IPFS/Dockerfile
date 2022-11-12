FROM ubuntu:latest
RUN apt-get update
COPY kubo_v0.16.0_linux-amd64.tar.gz ./
RUN tar -vzxf kubo_v0.16.0_linux-amd64.tar.gz
WORKDIR /kubo
RUN mv ipfs /usr/local/bin/ipfs
RUN ipfs init
RUN mkdir Luisa
WORKDIR /Luisa
COPY Luisa.txt ./



