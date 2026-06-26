{
  description = "ZnVja29mZg SDL3 procedural visuals";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "znvja29mzg";
          version = "0.1";
          src = ./.;
          nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config ];
          buildInputs = [ pkgs.clang pkgs.sdl3 ];
          buildPhase = ''
            cmake -S $SRC -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
            cmake --build build -- -j${pkgs.stdenv.hostPlatform.buildParallel}
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp build/ZnVja29mZg $out/bin/
          '';
        };
        devShell = pkgs.mkShell {
          buildInputs = [ pkgs.cmake pkgs.clang pkgs.pkg-config pkgs.sdl3 ];
          shellHook = ''
            echo "fuckoff"
          '';
        };
      });
}
