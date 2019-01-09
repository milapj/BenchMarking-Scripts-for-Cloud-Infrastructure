#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/pmbw4.out
./pmbw -M 1073741824 -p 4 -P 4 -s 1024 -S 10485670
