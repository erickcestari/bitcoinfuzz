# Use uma imagem oficial do Rust como base
FROM debian:bullseye-slim as builder

# Instalar dependências necessárias
RUN apt-get update && apt-get install -y \
    clang \
    llvm \
    make \
    cmake \
    g++ \
    libboost-all-dev \
    autoconf \
    automake \
    libtool \
    pkg-config \
    libgmp-dev \
    libevent-dev \
    libsqlite3-dev \
    curl \
    git \
    jq \
    && rm -rf /var/lib/apt/lists/*

# Instalar a versão 1.85.0 do Rust
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs/ | sh -s -- --default-toolchain 1.85.0 -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Instalar a versão mais recente do Go
RUN GO_LATEST=$(curl -fsSL https://go.dev/dl/?mode=json | jq -r 'map(select(.stable == true)) | first | .files[] | select(.os == "linux" and .arch == "amd64") | .filename') \
    && curl -fsSL "https://go.dev/dl/$GO_LATEST" -o go.tar.gz \
    && rm -rf /usr/local/go \
    && tar -C /usr/local -xzf go.tar.gz \
    && rm go.tar.gz \
    && ln -s /usr/local/go/bin/go /usr/local/bin/go \
    && go version

# Definir diretório de trabalho
WORKDIR /app

# Copiar o código do projeto para o container
COPY . .

ENV RUST_TARGET=x86_64-unknown-linux-gnu
# ENV CXXFLAGS="-DLND -DLDK"
ENV CXXFLAGS="-DLND"
ENV CC=clang CXX=clang++

# Compilar os módulos necessários
RUN cd modules/lnd && make
RUN cd modules/ldk/ldk_lib && cargo build --release --target=$RUST_TARGET
RUN cd modules/ldk && make

# Construir o bitcoinfuzz
RUN make

# Definir comando padrãos
CMD ["sh", "-c", "$FUZZ ./bitcoinfuzz "]
