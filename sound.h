#include <system.h>
#include <stdio.h>
#include <stdlib.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "io.h"
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_and_video_config.h"
#include "assert.h"


int k = 0;
alt_up_audio_dev * audio_dev=NULL;

int number_bytes=0;
int readWavFromSDCARD(char *name, char *levelBricksToDraw);
void configure_audio();
unsigned int * read_wav(char *name);
void play_wav();
void reset_variables();
int size=0;
int size_wav=0;
unsigned int * temp_array_play=NULL;
int ding;
		 int miss;
		 int laser;
		 int boing;

static void init_button_pio()
{
    alt_irq_register( AUDIO_0_IRQ, NULL, play_wav );
    printf("4\n");
}


//int main() {
//
//	 int ding;
//	 int miss;
//	 int laser;
//	 int boing;
//	 configure_audio(); //new1
//	 init_button_pio();
//
//	 unsigned int * temp_array;
//	 temp_array = (int *) malloc((number_bytes / 2) * sizeof(int));
//
//	 temp_array_play =(int *) malloc((100000) * sizeof(int));
//
//	 temp_array=read_wav("dingding.wav");
//	 ding=size_wav;
//
//
//	 temp_array_play=temp_array;
//	 size=ding;
//	 alt_up_audio_enable_write_interrupt(audio_dev);
//
////////////////////////////
//	 usleep(500000);
//	 unsigned int * temp_array2;
//	 temp_array2 = (int *) malloc((100000) * sizeof(int));
//	 temp_array2=read_wav("boing.wav");
//	 boing=size_wav;
//
//	 temp_array_play=temp_array2;
//	 size=boing;
//	 alt_up_audio_enable_write_interrupt(audio_dev);
//
//
///////////////////////////////
//
//	 temp_array_play=temp_array2;
//	 size=boing;
//	 alt_up_audio_enable_write_interrupt(audio_dev);
//
//
//
//}

void play_wav() {



	//whil
		//while (alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_RIGHT)
		//		< 100);

		alt_up_audio_write_fifo(audio_dev, &(temp_array_play[k]), 100,
				ALT_UP_AUDIO_RIGHT);
		alt_up_audio_write_fifo(audio_dev, &(temp_array_play[k]), 100,
				ALT_UP_AUDIO_LEFT);

		if (k >= size) {
			k = 0;
			alt_up_audio_disable_write_interrupt(audio_dev);
			alt_up_audio_reset_audio_core(audio_dev);
		} else
			k += 100;


}

unsigned int * read_wav(char *name)
{
	unsigned char *levelBricksToDraw;
	levelBricksToDraw = (unsigned char *) malloc(100000 * sizeof(unsigned char));

	int fileopen;
	fileopen = readWavFromSDCARD(name, levelBricksToDraw);

	unsigned int * temp_array;
	temp_array = (int *) malloc((number_bytes / 2) * sizeof(int));
	int x;
	int y = 0;
	for (x = 0; x < number_bytes; x += 2) {
		unsigned int sample = (levelBricksToDraw[x + 1] << 8
				| levelBricksToDraw[x]) << 8; //original
		//int sample = (levelBricksToDraw[x + 1] <<8 | levelBricksToDraw[x])<<8;
		temp_array[y] = sample;
		y++;
	}
	size_wav=y;
	return temp_array;
}

/////////////////////////////////////////*******?//////////////////////////////////////////////
int readWavFromSDCARD(char * name, char *levelBricksToDraw) {
	// Create row an column variables for iteration
	int row, column, i, j = 0;

	// Variables needed for sdcard reading
	int fileHandle;
	int dataRead;
	//int number_bytes = 0;

	// File name to be opened
	char *fileName = (int *) malloc(12 * sizeof(int));

	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(
			"/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	if (device_reference == NULL) {
		printf("Could not read from the SDcard.\n");
		return 0;
	} else {
		if (!alt_up_sd_card_is_Present()) {
			printf("The SDcard is not present!\n");
			return 0;
		}

		else {
			if (!alt_up_sd_card_is_FAT16()) {
				printf(
						"The SDcard is not formatted to be FAT16 and could not be read.\n");
				return 0;
			}
		}
	}

	// Get file handle
	fileHandle = alt_up_sd_card_fopen("README.txt", false);
	while (1) {
		dataRead = alt_up_sd_card_read(fileHandle);
		if (dataRead < 0) {
			break;
		} else {
			printf("%c", dataRead);
		}
	}
	alt_up_sd_card_fclose(fileHandle);

	fileHandle = alt_up_sd_card_fopen(name, false);

	// Get first byte of file
	dataRead = alt_up_sd_card_read(fileHandle);

	// Keep reading till eof
	while (dataRead > -1) {
		number_bytes++;
		// If new line character then write data to next line
		// and (increment column)

		//map[row][column]= atoi(&dataRead);
		levelBricksToDraw[j] = dataRead;
		j++;
		//printf("%d", map[row][column]);
		dataRead = alt_up_sd_card_read(fileHandle);
		//printf("Dataread: %02x\n", dataRead );

	}

	printf("number of reads: %d\n", number_bytes);

	alt_up_sd_card_fclose(fileHandle);
	return number_bytes;

}
//////////////////////////////////////////////////******/////////////////////////////////////////
void configure_audio()
{
	alt_up_av_config_dev* audio_config;
	//alt_up_av_config_dev * config=alt_up_av_config_open_dev(ON_BOARD_AUDIO_ONLY_CONFIG);
	//alt_up_av_config_open_dev(ON_BOARD_AUDIO_ONLY_CONFIG); //open the audio device.
	audio_config = alt_up_av_config_open_dev(AUDIO_AND_VIDEO_CONFIG_0_NAME);

	assert(audio_config);
	alt_up_av_config_reset(audio_config);


	while (!alt_up_av_config_read_ready(audio_config)) {
	}


	// open the Audio port
	audio_dev = alt_up_audio_open_dev("/dev/audio_0");
	if (audio_dev == NULL)
		alt_printf("Error: could not open audio device \n");
	else
		alt_printf("Opened audio device \n");

	alt_up_audio_reset_audio_core(audio_dev);
}

