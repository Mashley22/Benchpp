module Benchpp;
import :priv.cli;

int main(int argc, char** argv) {
  benchpp::priv::parse_cli_input(argc, argv);
}
