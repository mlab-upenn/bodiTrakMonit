#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsa.h"
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
static bool volatile keepRunning =true;
float *values;
FILE *outFP;
FILE *dbOutFP;
void intHandler(int dummy){
	keepRunning=false;
	//check if file is open, close otherwise
	if(outFP){
		fclose(outFP);
	}
	if(dbOutFP){
		fclose(dbOutFP);
	}
}

void main(int argc, char *argv[]) {
	//Check command line arguments
	if(argc<=1){
		printf("Usage: sudo ./fsaMonitor outputFilename\n");
		exit(0);
	}
	//get command line arguments and print outputfilename (Note: better way to do this by allocating based on argument length)
	char outputFilename[255];
	char outputPathname[255];
	char dropboxPathname[255];

	outputFilename[0]='\0';
	outputPathname[0]='\0';
	dropboxPathname[0]='\0';
	strcat(outputFilename, argv[1]);
	strcat(outputFilename, ".txt");
	printf("Output Filename : %s\n",outputFilename);
	//check directory, create if exists
	char outputDirectory[]="rawdata";
	strcat(outputPathname, outputDirectory);
	strcat(outputPathname, "/");
	strcat(outputPathname, outputFilename);
	printf("Output Pathname : %s\n",outputPathname);
	//assumes dropbox folder is created
	strcat(dropboxPathname, "/home/mlab-user/Dropbox/bodiTrakMonitorRawdata/");
	strcat(dropboxPathname, outputFilename);
	printf("Dropbox Pathname : %s\n",dropboxPathname);
	struct stat st = {0}; //Note: there could be other ways to do this, possible race conditions if done this way (better to try to use filesystem resource and handle errors
	if(stat(outputDirectory,&st)==-1){
		mkdir(outputDirectory,0777);
		printf("Creating output directory .. \n");
	}
	//open file with filename, rewrite if exist,
	outFP= fopen(outputPathname, "w");
	if(outFP==NULL){
		printf("Unable to open file for writing\n");
		exit(1);
	}
//	fclose(outFP);
	dbOutFP=fopen(dropboxPathname,"w");
	if(dbOutFP==NULL){
		printf("Unable to open dropbox file for writing\n");
		exit(1);
	}
//	fclose(dbOutFP);

	FSAT7 t7;
	fsat7Initialize();
	t7 = fsat7Create(0, 0);
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = intHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags=0;
	sigaction(SIGINT, &sigIntHandler,NULL);
	//signal(SIGINT, intHandler); (Note: sigaction is better ..)
	bool fsaConnected=false;
	/*TODO
	//add blocking interrupt while writing to file
	//Get current calendar time
	//print calendar time
	//write header until dimensions and units
	//header format (on separate lines): name;date_and_time;trial; row column;
	//
	 */

	if (t7) {
		fsaConnected=true;
		int c, columns = fsat7GetColumnCount(t7);
		int r, rows = fsat7GetRowCount(t7);
		values = malloc(columns * rows * sizeof(float));
		while(keepRunning){
			if (values) {
				float minimum, maximum;
				char units[32];
				if (fsat7LoadCalibration(t7)) {
					minimum = fsat7GetMinimum(t7);
					maximum = fsat7GetMaximum(t7);
					fsat7GetUnits(t7, units);
				}
				else {
					minimum = 0;
					maximum = fsat7GetConductance(t7);
					strcpy(units, "uSiemens");
				}
				printf("%dx%d  %f-%f %s\r\n", columns, rows, minimum, maximum, units);

				if (fsat7Scan(t7, values, NULL)) {
					//block INT during this period
					//open file with filename, rewrite if exist,
					/*outFP= fopen(outputPathname, "a");
					if(outFP==NULL){
						printf("Unable to open file for writing\n");
						exit(1);
					}
					dbOutFP=fopen(dropboxPathname,"a");
					if(dbOutFP==NULL){
						printf("Unable to open dropbox file for writing\n");
						exit(1);
					}
					*/
					sigset_t oldMask, toBlock;
					sigemptyset(&toBlock);
					sigaddset(&toBlock, SIGINT);
					sigprocmask(SIG_BLOCK,&toBlock,&oldMask);
					float* value = values;
					for (r = 0; r < rows; ++r) {
						for (c = 0; c < columns; ++c, ++value){
							printf("%4d", (int)(*value));
							fprintf(outFP,"%4d\t",(int)(*value));
							fprintf(dbOutFP,"%4d\t",(int)(*value));
						}
						puts("");
					}
					fprintf(outFP,"\n");
					fprintf(dbOutFP,"\n");
					/*fclose(outFP);
					fclose(dbOutFP);
					outFP=0;
					dbOutFP=0;*/
					sigprocmask(SIG_SETMASK, &oldMask, NULL);
				}
				else puts("Failed to scan sensor array.");
			}
			else puts("Failed to allocate value buffer.");
		}
	}
	else puts("Failed to connect to a sensor array.");
	if(fsaConnected==true){
		printf("Process interrupted\n");
		free(values);
		fsat7Destroy(t7);
	}
	fsat7Uninitialize();
	if(outFP){
		fclose(outFP);
	}
	if(dbOutFP){
		fclose(dbOutFP);
	}
}
