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
            dotnet-sdk_8
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
          ] ++ lib.optionals stdenv.isDarwin [
            darwin.ICU
          ];

          shellHook = ''
            export CC=${pkgs.clang_20}/bin/clang
            export CXX=${pkgs.clang_20}/bin/clang++
            export RUSTUP_TOOLCHAIN=nightly
            export BOOST_LIB_DIR=${staticBoost.out}/lib/

            export ICU_LIB_DIR=${pkgs.icu}/lib
            export LD_LIBRARY_PATH=$ICU_LIB_DIR:$LD_LIBRARY_PATH
            export DYLD_LIBRARY_PATH=$ICU_LIB_DIR:$DYLD_LIBRARY_PATH

            # Additional environment variables for macOS ICU support
            ${pkgs.lib.optionalString pkgs.stdenv.isDarwin ''
              export DYLD_FALLBACK_LIBRARY_PATH="${pkgs.icu}/lib:${pkgs.darwin.ICU}/lib"
              export ICU_ROOT="${pkgs.icu}"
            ''}

            echo "bitcoinfuzz dev environment ready."
          '';
        };
      });
}