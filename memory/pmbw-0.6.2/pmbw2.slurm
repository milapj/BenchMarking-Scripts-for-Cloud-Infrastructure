#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/pmbw2.out
./pmbw -M 1073741824 -p 2 -P 2 -s 1024 -S 10485760
