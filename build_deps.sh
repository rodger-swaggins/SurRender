#!/bin/bash
git submodule update --init --recursive
cd radix
make
cd ../
make
