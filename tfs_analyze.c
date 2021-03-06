#include "ll.h"

int main(int argc, char *argv[]) {

	if(argc==1){
		printf("No arguments \n");
	}

	char* nameFile;
	if (argc == 2) {
		nameFile = argv[1];
	} else {
		nameFile = "disk.tfs";
	}
	printf("%s\n",nameFile);

	error er;


	disk_id *disk = malloc(sizeof(disk));
	if (disk == NULL) {
		er.val = 1;
		er.message = "ERROR MALLOC DISK in TFS_ANALYSE";
		testerror(er);
	}


	er = start_disk(nameFile, disk);

	testerror(er);
	int * array=NULL;

	array = getInfo(*disk);
	if (array[0] == 0) {
		er.val = 1;
		er.message ="\nthe file selected is 0 size or not yet initialised with tfs_create\n";
		testerror(er);
	}
	printf("TAILLE DISQUE : %d\n", array[0]);

	int nbPartitions = array[1];
	printf("NOMBRE DE PARTITIONS : %d\n", nbPartitions);

	int i;
	for (i = 0; i < array[1] ; i++) {
		printf("PARTITION : %d  | TAILLE : %d\n", i, array[i + 2]);
	}

	printf("TAILLE OCCUPE AU TOTAL PAR PARTITIONS : %d\n",
			array[nbPartitions + 2]);
	printf("BLOCK DISPONIBLE : %d\n", array[nbPartitions + 3]);
	printf("NOMBRE MAX DE PARTITION ENCORE CREABLE : %d\n",
			array[nbPartitions + 4]);
	free(array);
	er = stop_disk(*disk);
	testerror(er);
	freeDisk(disk);
	return 0;
}
