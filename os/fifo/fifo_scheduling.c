#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "plist.dat"

void printResult(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	int i, sum_tt=0, sum_wt=0;

	printf("%15s %15s %15s %15s %15s\n", "Process id", "Arrive time", "Burst time", "Turnaround time", "Waiting time");
	for(i=0; i<pnum; ++i) {
		printf("%15d %15d %15d %15d %15d\n", pid[i], at[i], bt[i], tt[i], wt[i]);
		sum_tt+=tt[i];
		sum_wt+=wt[i];
	}

	printf("  avg. of TT: %.2f\n", (float)sum_tt/pnum);
	printf("  avg. of WT: %.2f\n", (float)sum_wt/pnum);
}

void FIFO(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	printf("  Scheme: First-In-First-Out\n");
	tt[0]=3;
	wt[0]=0;

	for(int i=1; i<=pid[i]; i++) {
		wt[i] = at[i-1] + bt[i-1] + wt[i-1] - at[i];
		tt[i] = bt[i] + wt[i];

		if(wt[i]<0) {
		wt[i] = 0;
		tt[i] = bt[i] + wt[i];
		}
	}
}

int main(void) {
	FILE *fp;
	int pnum, i, exit=0;
	int *pid, *at, *bt, *tt, *wt;

	fp = fopen(INPUT_FILE, "r");
	//read the number of processes 
	fscanf(fp, "%d", &pnum);

	pid = (int*)calloc(pnum, sizeof(int));
	at = (int*)calloc(pnum, sizeof(int));
	bt = (int*)calloc(pnum, sizeof(int));
	tt = (int*)calloc(pnum, sizeof(int));
	wt = (int*)calloc(pnum, sizeof(int));

	for(i=0; i<pnum; ++i) {
		fscanf(fp, "%d %d %d", &pid[i], &at[i], &bt[i]);
	}

	fclose(fp);
		
	FIFO(pnum, pid, at, bt, tt, wt);
		

	printResult(pnum, pid, at, bt, tt, wt);
	memset(tt, 0, sizeof(int)*pnum);
	memset(wt, 0, sizeof(int)*pnum);
	
	return 0;
}

