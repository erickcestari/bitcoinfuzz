{
  description = "Development environment for bitcoinfuzz";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
        staticBoost = pkgs.boost.override {
          enableStatic = true;
          enableShared = false;
        };
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            rustup
            go
            dotnet-sdk_9
            clang_20
            libcxx
            cmake
            (python3.withPackages (ps: with ps; [ pip setuptools distutils mako ]))
            staticBoost
            libevent
            openssl
            pkg-config
            zlib
            protobuf
            libsodium
            autoconf
            automake
            libtool
            gettext
            jq
            sqlite
          ];

          shellHook = ''
            export CC=${pkgs.clang_20}/bin/clang
            export CXX=${pkgs.clang_20}/bin/clang++
            export RUSTUP_TOOLCHAIN=nightly
            export BOOST_LIB_DIR=${staticBoost.out}/lib/
            echo "bitcoinfuzz dev environment ready."
          '';
        };
      });
}
