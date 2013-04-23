#include <system.h>
#include <stdio.h>
#include <stdlib.h>
#include <altera_up_sd_card_avalon_interface.h>

#define ASCII_VALUE_0 48
#define ASCII_VALUE_9 57
#define MAX_BLOCKS_PER_ROW 30
#define MAX_BLOCKS_PER_COLUMN 20
#define ROWS MAX_BLOCKS_PER_ROW
#define COLUMNS MAX_BLOCKS_PER_COLUMN
#define BRICK_SIZE_WIDTH 16  // Was 16
#define BRICK_SIZE_HEIGHT 8 // Was 8
#define NO_BRICK 0

//Colors
#define BLACK 0
#define RED 0xA83857
#define ORANGE 0xA74D31
#define YELLOW 0x00FF00
#define GREEN 0x6D8005
#define BLUE 31
#define VIOLET 0x4E48C4
#define PINK 0x00FEFF


int readLevelFromSDCARD (int levelToRead, int **levelBricksToDraw){
	// Create row an column variables for iteration
	int row, column, i, j = 0;

	// Variables needed for sdcard reading
	int fileHandle;
	char dataRead;

	// File name to be opened
	char *fileName = (int *)malloc(12*sizeof(int));

	// Array being saved to
	// int map[ROWS][COLUMNS];
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	if(device_reference == NULL){
		printf("Could not read from the SDcard.\n");
		return 0;
	}
	else {
		// If you are debugging, this will load
		// a minimalist map for testing
		if (DEBUG) {
			for (i=0; i<ROWS; i++){
				for (j=0; j<COLUMNS; j++){
					if (i > 2 && i < 9)
						levelBricksToDraw[i][j] = 6 - (i - 2);
					else
						levelBricksToDraw[i][j] = 0;
				}
				printf("\n");
			}
			return 1;
		}
		if (!alt_up_sd_card_is_Present()) {
			printf("The SDcard is not present!\n");
			return 0;
		}
		else {
			if (!alt_up_sd_card_is_FAT16()) {
				printf("The SDcard is not formatted to be FAT16 and could not be read.\n");
				return 0;
			}
			else {
				row = 0;
				// Get filename to open
				sprintf(fileName, "lev%d.txt", levelToRead);
				printf("%s\n\n\n",fileName);

				// Get file handle
				fileHandle = alt_up_sd_card_fopen(fileName, false);

				// Get first byte of file
				dataRead = alt_up_sd_card_read(fileHandle);

				// Keep reading till eof
				while (dataRead > -1){
					// If new line character then write data to next line
					// and (increment column)
					if (dataRead == 10) {
						dataRead = alt_up_sd_card_read(fileHandle);
						row++;
						column = 0;
						//printf("\n");
					}
					if ((dataRead >= ASCII_VALUE_0 && dataRead <= ASCII_VALUE_9) && column < MAX_BLOCKS_PER_COLUMN){
						//map[row][column]= atoi(&dataRead);
						levelBricksToDraw[row][column] = atoi(&dataRead);
						column++;
						//printf("%d", map[row][column]);

					}
					dataRead = alt_up_sd_card_read(fileHandle);
				}
				for(row = 0;row<3;row++){
													for(column=0; column < 20; column++){
														levelBricksToDraw[row][column]=0;
													}
												}


				//Close file
				alt_up_sd_card_fclose(fileHandle);

				return 1;
			}
		}
	}
	return 0;
}

void printmap(int **levelBricksToDraw){
	//print map to console
	int i,j = 0;
	for (i=0; i<ROWS; i++){
		for (j=0; j<COLUMNS; j++){
			printf("%d",levelBricksToDraw[i][j]);
		}
		printf("\n");
	}
}
