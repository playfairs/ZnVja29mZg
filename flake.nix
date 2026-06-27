{
  description = "ZnVja29mZg SDL3 procedural visuals";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-26.05";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "znvja29mzg";
          version = "0.1";
          src = ./.;
          buildInputs = with pkgs; [ meson ninja  python3 ];
          nativeBuildInputs = with pkgs; [ sdl3  pkg-config ];
        };
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            meson
            ninja
            pkg-config
            sdl3
          ];
          shellHook = ''
            echo "fuckoff"
          '';
        };
      });
}
