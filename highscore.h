void twoPlayerScore(int scorePlayer1, int scorePlayer2, int livesPlayer1, int livesPlayer2, alt_up_char_buffer_dev *char_buffer, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	scorePlayer2 = scorePlayer2 + (10*livesPlayer2);
	scorePlayer1 = scorePlayer1 + (10*livesPlayer1);
	int who_won;
	if (scorePlayer2 > scorePlayer1) {
						who_won = 2;
					} else
						who_won = 1;
	char *gameMessage = (char *) malloc(15 * sizeof(char));
	sprintf(gameMessage, "Player %d Won", who_won);
	alt_up_char_buffer_string(char_buffer, gameMessage, 32, 30);
	while (!(IORD_8DIRECT(SWITCHES_BASE, 0) & 0x01))
		;
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}
int readHighScoreFromFile(char **high_score_names, int *high_scores, char *filename){
	int i;
	alt_up_sd_card_dev *device_reference = NULL;
			device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
			 short dataRead;
			int fileHandle;
			//int bitmap[1000];
			if(device_reference == NULL){
				printf("Could not read from the SDcard.\n");
				return 0;
			}
			else {
				// If you are debugging, this will load
				// a minimalist map for testing
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

						// Get file handle
						fileHandle = alt_up_sd_card_fopen(filename, false);
						printf("fileHandle: %d\n",alt_up_sd_card_get_attributes(fileHandle));
						// Get first byte of file
						dataRead = alt_up_sd_card_read(fileHandle);
						printf("%s\n",filename);
						printf("first: %d\n",dataRead);
						int n = 0;
						int rank = 0;
						// Keep reading till eof
						while (dataRead > -1){
							// If new line character then write data to next line
							// and (increment column)
							if (dataRead == 10){
								high_score_names[rank][n] = '\0';
								dataRead = alt_up_sd_card_read(fileHandle);
								n = 0;
								rank++;
							}
							high_score_names[rank][n] = dataRead;
							dataRead = alt_up_sd_card_read(fileHandle);
							printf("%d ",dataRead);
							n++;
						}
						high_score_names[rank][n] = '\0';
						printf("\n");
						//Close file
						int k;
						alt_up_sd_card_fclose(fileHandle);
						for (i = 0;i < 10; i++){
							//for (k=0;k<10;k++){
								printf("%s",high_score_names[i]);
							//}
							printf("\n");
						}
						int z=3;
						int q=0;
						for (i=0;i<10;i++){
							char test[6];
							while (high_score_names[i][z] != '\0'){
								test[q] = high_score_names[i][z];
								z++;
								q++;
							}
							test[q] = '\0';
							high_scores[i] = atoi(test);
							q = 0;
							z = 3;
						}
						return 1;
					}
				}
			}

			//high_score_names[0] = "SUK 1000";


}

int saveNewHighScore(char **high_score_names, char *filename){
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	short dataRead;
	int fileHandle;
	int i;
	//int bitmap[1000];
	if (device_reference == NULL) {
		printf("Could not read from the SDcard.\n");
		return 0;
	} else {
		// If you are debugging, this will load
		// a minimalist map for testing
		if (!alt_up_sd_card_is_Present()) {
			printf("The SDcard is not present!\n");
			return 0;
		} else {
			if (!alt_up_sd_card_is_FAT16()) {
				printf(
						"The SDcard is not formatted to be FAT16 and could not be read.\n");
				return 0;
			} else {

				fileHandle = alt_up_sd_card_fopen(filename, false);
				if (fileHandle == -1) {
					fileHandle = alt_up_sd_card_fopen(filename, true);
					alt_up_sd_card_set_attributes(fileHandle, 32);
				}
				for (i = 0; i < 10; i++) {
					int k = 0;
					while (high_score_names[i][k] != '\0') {
						char c = high_score_names[i][k];
						alt_up_sd_card_write(fileHandle, c);
						k++;
					}
					//printf("\n");
					alt_up_sd_card_write(fileHandle, 10);
				}
				alt_up_sd_card_fclose(fileHandle);
				return 1;
			}
		}
}}
