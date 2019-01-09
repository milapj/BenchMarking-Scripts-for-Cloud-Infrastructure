#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RS-1000-4.out
./DISKFIN disk-RS-1000-4thread.dat
