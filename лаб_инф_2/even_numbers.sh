#!/bin/bash
for a in "$@"; do
  if [a % 2 == 0]; then
    echo "a"
  fi
done
