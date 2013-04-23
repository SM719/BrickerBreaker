unsigned short *bitmap;
unsigned int **bitMapBrickcolors;
unsigned int *bitMapPaddle;

void readBitMapBricks(){
	int bytes = readBitMap(bitmap, "brick_2.bmp");
	bitmapTo16BitRGB(bytes, 2);
	bytes = readBitMap(bitmap, "brick_4.bmp");
	bitmapTo16BitRGB(bytes, 1);
	bytes = readBitMap(bitmap, "brick_1.bmp");
	bitmapTo16BitRGB(bytes, 3);
	bytes = readBitMap(bitmap, "brick_3.bmp");
		bitmapTo16BitRGB(bytes, 4);
	//bytes = 	readBitMap( bitmap, "2_2.bmp");

}

void readBitMapPaddle(){
	int bytes = readBitMap(bitmap, "paddleb.bmp");
	printf("paddle bytes: %d\n",bytes);

	int max_i = (bytes-54)/3;
	printf("max_i: %d\n", max_i);
	int i,k = 54;
			for (i = 0; i < max_i; i++ ){
			 // bitmapcolors[i] = (((bitmapcolors[k] >> 3) << 11) | ((bitmapcolors[k+1] >> 2) << 6) | (bitmapcolors[k+2] >> 3) );
				bitMapPaddle[i] = (((bitmap[k+2] >> 4) << 11) + ((bitmap[k+1] >> 3) << 5) + (bitmap[k] >> 4));
				k = k+3;
			}
			for(i=0;i<max_i;i++){
				printf("%d\n",bitMapPaddle[i]);
			}
}
void bitmapTo16BitRGB(int bytes, int brick){
	int max_i = (bytes-54)/3;

		int i,k = 54;
		for (i = 0; i < max_i; i++ ){
		 // bitmapcolors[i] = (((bitmapcolors[k] >> 3) << 11) | ((bitmapcolors[k+1] >> 2) << 6) | (bitmapcolors[k+2] >> 3) );
			bitMapBrickcolors[brick][i] = (((bitmap[k+2] >> 4) << 11) + ((bitmap[k+1] >> 3) << 5) + (bitmap[k] >> 4));
			k = k+3;
		}
}
int readBitMap(unsigned short *bitmap, char *filename){
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	 short dataRead;
	int fileHandle;
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

				// Get first byte of file
				dataRead = alt_up_sd_card_read(fileHandle);
				printf("%s\n",filename);
				printf("first: %d\n",dataRead);
				int n = 0;
				// Keep reading till eof
				while (dataRead > -1){
					// If new line character then write data to next line
					// and (increment column)
					bitmap[n] = dataRead;
					dataRead = alt_up_sd_card_read(fileHandle);
					printf("%d ",dataRead);
					n++;
				}
				printf("\n");
				//Close file
				alt_up_sd_card_fclose(fileHandle);

				return n;
			}
		}
	}
	return 0;
}
void draw_paddle(alt_up_pixel_buffer_dma_dev* pixel_buffer, int *xpaddleCurrentPosition){
	int i=0,s,l;
	//printf("\n\n\n\n\n\n");
	for (l = 5 ; l>=0;l--){
			for(s = 0; s<38;s++){
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddleCurrentPosition[0]+s,
					l+PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition[0]
							+ s + 1, PADDLE_Y_AXIS_POSITION
							+ l + 1, bitMapPaddle[i], 1);
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddleCurrentPosition[0]+s,
									l+PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition[0]
											+ s + 1, PADDLE_Y_AXIS_POSITION
											+ l + 1, bitMapPaddle[i], 0);
		//		printf("%d ",bitMapPaddle[i]);
				i++;
			}
		//	printf("\n");
	}
}

void draw_brick(alt_up_pixel_buffer_dma_dev* pixel_buffer, int rowToAccess, int columnToAccess, int brick){

	int i = 0,l,s;
	//printf("columntoaccess: %d\n", columnToAccess);
	//printf("rowtoaccess: %d\n", rowToAccess);

	for (l = 6 ; l>=0;l--){
		for(s = 0; s<15;s++){
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
												(columnToAccess * BRICK_SIZE_WIDTH) + s,
												(rowToAccess * BRICK_SIZE_HEIGHT) + l,
												(columnToAccess * BRICK_SIZE_WIDTH)
												+ s + 1, (rowToAccess
														* BRICK_SIZE_HEIGHT)
												+ l + 1, bitMapBrickcolors[brick][i], 1);
										alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
												(columnToAccess * BRICK_SIZE_WIDTH) + s,
												(rowToAccess * BRICK_SIZE_HEIGHT) + l,
												(columnToAccess * BRICK_SIZE_WIDTH)
												+ s + 1, (rowToAccess
														* BRICK_SIZE_HEIGHT)
												+ l + 1, bitMapBrickcolors[brick][i], 0);
										i++;
			}
		  		//printf("\n");
	}
}
