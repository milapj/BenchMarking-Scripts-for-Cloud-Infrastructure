#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/pmbw1.out
./pmbw -M 1073741824 -p 1 -P 1 -s 1024 -S 10485760
