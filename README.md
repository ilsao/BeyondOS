# Introduction

This project is extended from OS in 1000 lines. 

# Getting Started

## Installation

1. Clone the repository

``` bash
git clone https://github.com/ilsao/BeyondOS.git
cd BeyondOS
```

2. Install dependencies

``` bash
sudo apt update && sudo apt install -y clang llvm lld qemu-system-riscv32 curl
curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin
```

## Running

- If you are Ubuntu users (or other linux systems)

``` bash
./run.sh
```
