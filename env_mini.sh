#!/bin/bash

DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)
MINI_ROOT=$DIR
export MINI_ROOT

export exec=$MINI_ROOT/build/miniTRUST

alias mini=$exec

export PATH=$MINI_ROOT/llvm/llvm-project/build/bin:$MINI_ROOT/llvm/llvm-project/clang-tools-extra/clang-tidy/tool:$PATH
