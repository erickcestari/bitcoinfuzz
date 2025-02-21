# Use uma imagem oficial do Rust como base
FROM rust:1.74 as builder

# Instalar dependências necessárias
RUN apt-get update && apt-get install -y \
    clang \
    llvm \
    make \
    cmake \
    g++ \
    libboost-all-dev \
    golang \
    autoconf \
    automake \
    libtool \
    pkg-config \
    libgmp-dev \
    libevent-dev \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Definir diretório de trabalho
WORKDIR /app

# Copiar o código do projeto para o container
COPY . .

ENV CC=clang CXX=clang++

# Compilar os módulos necessários
RUN cd modules/rustbitcoin/rust_bitcoin_lib && cargo build --release
RUN cd modules/rustbitcoin && make
RUN cd modules/rustminiscript/rust_miniscript_lib && cargo build --release
RUN cd modules/rustminiscript && make
RUN cd modules/btcd && make
RUN cd modules/ldk/ldk_lib && cargo build --release
# RUN cd modules/bitcoin && make

# Construir o bitcoinfuzz
RUN make


# Definir comando padrão
CMD ["sh", "-c", "$FUZZ ./bitcoinfuzz "]
