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
    # Adicionar .NET SDK
    wget \
    apt-transport-https \
    && rm -rf /var/lib/apt/lists/*

# Instalar .NET SDK 8.0
RUN wget https://packages.microsoft.com/config/debian/12/packages-microsoft-prod.deb -O packages-microsoft-prod.deb \
    && dpkg -i packages-microsoft-prod.deb \
    && rm packages-microsoft-prod.deb \
    && apt-get update \
    && apt-get install -y dotnet-sdk-8.0 \
    && rm -rf /var/lib/apt/lists/*

# Definir diretório de trabalho
WORKDIR /app

# Copiar o código do projeto para o container
COPY . .

ENV CC=clang CXX=clang++

# Verificar a estrutura de diretórios e compilar o projeto .NET
RUN mkdir -p modules/nlightning/nlightning_lib/bin/Release/net8.0/linux-x64/publish/ || true
RUN cd modules/nlightning/nlightning_lib && \
    dotnet publish -c Release -r linux-x64 --self-contained true && \
    ls -la bin/Release/net8.0/linux-x64/publish/

# Compilar os módulos necessários
# RUN cd modules/rustbitcoin/rust_bitcoin_lib && cargo build --release
# RUN cd modules/rustbitcoin && make
# RUN cd modules/rustminiscript/rust_miniscript_lib && cargo build --release
# RUN cd modules/rustminiscript && make
# RUN cd modules/btcd && make
RUN cd modules/ldk/ldk_lib && cargo build --release
RUN cd modules/nlightning && make
# RUN cd modules/bitcoin && make

# Construir o bitcoinfuzz
RUN make

# Definir comando padrão
CMD ["sh", "-c", "$FUZZ ./bitcoinfuzz "]