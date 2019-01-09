CC = gcc
CFLAGS = -Wall -lpthread -O2

clean:
	rm -rf *.o CPUFinal

run:
	sbatch cpu_QP_1.slurm
	sbatch cpu_QP_2.slurm
	sbatch cpu_QP_4.slurm
	sbatch cpu_HP_1.slurm
	sbatch cpu_HP_2.slurm
	sbatch cpu_HP_4.slurm
	sbatch cpu_SP_1.slurm
	sbatch cpu_SP_2.slurm
	sbatch cpu_SP_4.slurm
	sbatch cpu_DP_1.slurm
	sbatch cpu_DP_2.slurm
	sbatch cpu_DP_4.slurm
