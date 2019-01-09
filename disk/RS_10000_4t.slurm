#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RS-10000-4.out
./DISKFIN disk-RS-10000-4thread.dat
