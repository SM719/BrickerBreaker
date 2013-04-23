#define FIRST_LEVEL_TO_READ 3 //needs to be 1 less than the actual level to start
#define BALL_DEFAULT_X_SPEED 1
#define BALL_DEFAULT_Y_SPEED 1
#define PADDLE_START_X_POSITION 89
#define XPADDLE_DO_NOT_MOVE 0
#define XPADDLE_MOVE_LEFT_1_PIXEL -1
#define XPADDLE_MOVE_RIGHT_1_PIXEL 1

#define PADDLE_2_START_X_POSITION 89
#define XPADDLE_2_DO_NOT_MOVE 0
#define XPADDLE_2_MOVE_LEFT_1_PIXEL -1
#define XPADDLE_2_MOVE_RIGHT_1_PIXEL 1
#define PADDLE_2_Y_AXIS_POSITION 28
#define LENGTH_OF_PADDLE_2 38
#define HEIGHT_OF_PADDLE_2 6

#define SCREEN_WIDTH_MIN_PIXEL 0
#define SCREEN_WIDTH_MAX_PIXEL 319
#define SCREEN_HEIGHT_MIN_PIXEL 0
#define SCREEN_HEIGHT_MAX_PIXEL 239
#define PADDLE_Y_AXIS_POSITION 230
//#define LENGTH_OF_PADDLE 38
#define HEIGHT_OF_PADDLE 6
#define KEY_2_PRESSED 0x04
#define KEY_1_PRESSED 0x02
#define KEY_0_PRESSED 0x01
#define KEY_3_PRESSED 0x08
//#define DEFAULT_SPEED_OF_PADDLE 3
#define BALL_WIDTH 1
#define BALL_HEIGHT 1
#define LEVEL_MIN_HEIGHT 23
#define BALL_START_X_POSITION PADDLE_START_X_POSITION+12
#define BALL_START_Y_POSITION PADDLE_Y_AXIS_POSITION - HEIGHT_OF_PADDLE - 5

int flag_inner_paddle = 0;
int count = 0;


int LENGTH_OF_PADDLE = 38;
int DEFAULT_SPEED_OF_PADDLE = 3;

#define DEBUG 0

#include <system.h>
#include <stdio.h>
#include <stdlib.h>
#include "levelread.h"
#include "joystick.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include <altera_up_sd_card_avalon_interface.h>
#include "read_bitmap.h"
#include "io.h"
#include "sound.h"
#include "powerups.h"
#include "print.h"
#include "gamebrain.h"
#include "highscore.h"

//SOUND
#include <altera_up_sd_card_avalon_interface.h>
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_and_video_config.h"

//int file_size = 0;
//int number_bytes=0;
void configure_audio();
unsigned int * read_wav(char *name);
void play_wav(unsigned int * temp_array);
void reset_variables();
//END OF SOUND


int main() {
	tempString = (char *) malloc(sizeof(char) * 20);
	int rowToAccess = 0, columnToAccess = 0, y = 0;

	int *positionOfBall = (int *) malloc(sizeof(int) * 2);
	positionOfBall[0] = BALL_START_X_POSITION;
	positionOfBall[1] = BALL_START_Y_POSITION;

	int *speedOfBall = (int *) malloc(sizeof(int) * 2);
	speedOfBall[0] = BALL_DEFAULT_X_SPEED;
	speedOfBall[1] = BALL_DEFAULT_Y_SPEED;

	int *xpaddleCurrentPosition = (int *) malloc(sizeof(int));

	xpaddleCurrentPosition[0] = PADDLE_START_X_POSITION;
	int *xpaddleSpeed = (int *) malloc(sizeof(int));
	xpaddleSpeed[0] = XPADDLE_DO_NOT_MOVE;
	int scorePlayer1, scorePlayer2;
	int livesPlayer1, livesPlayer2;
	char *intLivesToCharPlayer1;
	char *intLivesToCharPlayer2;
	char *intScoreToCharPlayer1;
	char *intScoreToCharPlayer2;
	int *levelTotalBrickCount = (int *) malloc(sizeof(int));
	levelTotalBrickCount[0] = 0;
	char *levelToPlay = (char *) malloc(sizeof(char));
	levelToPlay[0] = 3;
	intLivesToCharPlayer1 = (char *) malloc(5 * sizeof(char));
	intLivesToCharPlayer2 = (char *) malloc(5 * sizeof(char));
	intScoreToCharPlayer1 = (char *) malloc(5 * sizeof(char));
	intScoreToCharPlayer2 = (char *) malloc(5 * sizeof(char));
	int gameMode = 1;
	int i;
	int sukhi = 0;
	int high_score_values[] = { 30, 25, 22, 20, 18, 15, 14, 10, 8, 5 };
	int temp[] = { 30, 25, 22, 20, 18, 15, 14, 10, 8, 5 };
	char **high_score_names = (char *) malloc(10 * sizeof(char *));
	for (i = 0; i < 10; i++) {
		high_score_names[i] = (char *) malloc(7 * sizeof(char));
	}
	int *high_scores = (int *) malloc(10 * sizeof(int));
	//	char high_score_names[10][7] = { { "SKM 30" }, { "DND 25" }, { "GEE 22" },
	//			{ "MOE 20" }, { "NIK 18" }, { "NBL 15" }, { "SKM 14" },
	//			{ "DND 10" }, { "NBL 8 " }, { "MOE 5" } };i
	char temp2[10][7] = { { "SKM 30" }, { "DND 25" }, { "GEE 22" },
			{ "MOE 20" }, { "NIK 18" }, { "NBL 15" }, { "SKM 14" },
			{ "DND 10" }, { "NBL 8 " }, { "MOE 5" } };

	char name[4] = "    ";
	powerup_message = (char *) malloc(15 * sizeof(char));

	int x;
	int m;
	int j;
	int n;
	int b;
	char letter;

	int *xpaddle2CurrentPosition = (int *) malloc(sizeof(int));
	xpaddle2CurrentPosition[0] = PADDLE_2_START_X_POSITION;
	int *xpaddle2Speed = (int *) malloc(sizeof(int));
	xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;

	int levelReadSuccess;
	int color[8] = { BLACK, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET };

	int who_won = 0;
	int option = 0;

	// DIRECTION Variables
	char direction;

	test = (int *) malloc(sizeof(int));
	test2 = (int *) malloc(sizeof(int));
	test3 = (int *) malloc(sizeof(int));

	test[0] = 240;
	test2[0] = 0;
	test3[0] = 0;
	int bytes;
	bitmap = (short *) malloc(sizeof(short) * 1000);
	bitMapPaddle = (int *) malloc(sizeof(int) * 40 * 8);
	bitMapBrickcolors = (int *) malloc(sizeof(int *) * 10);
	for (i = 0; i < 10; i++) {
		bitMapBrickcolors[i] = (int *) malloc(sizeof(int) * 150);
	}
	readBitMapPaddle();
	readBitMapBricks();


	//INITIALIZE 2D ARRAY (20x30) TO STORE LEVEL
	int **levelBricksToDraw;
	levelBricksToDraw = (int **) malloc(MAX_BLOCKS_PER_ROW * sizeof(int*));
	for (rowToAccess = 0; rowToAccess < MAX_BLOCKS_PER_ROW; rowToAccess++) {
		levelBricksToDraw[rowToAccess] = (int *) malloc(sizeof(int)
				* MAX_BLOCKS_PER_COLUMN);
		for (columnToAccess = 0; columnToAccess < MAX_BLOCKS_PER_COLUMN; columnToAccess++) {
			levelBricksToDraw[columnToAccess][rowToAccess] = 0;
		}
	}

	// Sound stuff
	// Sound stuff
	configure_audio(); //new1
	init_button_pio();

	unsigned int * temp_array;
	temp_array = (int *) malloc((number_bytes / 2) * sizeof(int));

	temp_array_play = (int *) malloc((100000) * sizeof(int));

	temp_array = read_wav("boing_m.wav");
	laser = size_wav;

	unsigned int * temp_array2;
	temp_array2 = (int *) malloc((number_bytes / 2) * sizeof(int));

	temp_array2 = read_wav("boing_m.wav");
	miss = size_wav;

	//chunk to copy to play laser
	temp_array_play = temp_array;
	size = laser;
	alt_up_audio_enable_write_interrupt(audio_dev);

	//

	//chunk to copy to play miss
	temp_array_play = temp_array2;
	size = miss;
	alt_up_audio_enable_write_interrupt(audio_dev);

	// play_wav(temp_array, audio_dev);
	//play_wav(temp_array, audio_dev);
	//play_wav(temp_array, audio_dev);
	//play_wav(temp_array, audio_dev);
	//play_wav(temp_array, audio_dev);
	init_button_pio(temp_array);
	alt_up_audio_enable_write_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);

	// End sound stuff


	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev(
			"/dev/video_pixel_buffer_dma_0");
	unsigned int pixel_buffer_addr1 = SRAM_0_BASE + (320 * 240 * 2);
	unsigned int pixel_buffer_addr2 = SRAM_0_BASE + (320 * 240 * 4);

	// Set the 1st buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			pixel_buffer_addr1);
	// Swap buffers “ we have to swap because there is only an API function
	// to set the address of the background buffer.
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	// Set the 2nd buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			pixel_buffer_addr2);
	// Clear both buffers (this makes all pixels black)
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);

	printf("test\n");

	//Initialize character buffer
	alt_up_char_buffer_dev *char_buffer;
	char_buffer = alt_up_char_buffer_open_dev(
			"/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_init(char_buffer);
	alt_up_char_buffer_clear(char_buffer);

	int choose = 1;
	while (1) {
		int i = 0;
		for (i = 0; i < 90000; i++)
			;
		//char *gameMessage = (char *)malloc(15*sizeof(char));
		//sprintf(gameMessage, "Player %d Won", who_won);
		if (option == 0) {
			printMenu(char_buffer, pixel_buffer);
			draw_paddle(pixel_buffer, xpaddleCurrentPosition);
			option = 9;
		}

		if (choose == 1) {
			printMenuOptionSelected(1, pixel_buffer);
		}
		if (choose == 2) {
			printMenuOptionSelected(2, pixel_buffer);
		}
		if (choose == 3) {
			printMenuOptionSelected(3, pixel_buffer);
		}
		if (choose == 4) {
			printMenuOptionSelected(4, pixel_buffer);
		}

		direction = getmovement(1);
		if ((direction == DIRECTION_DOWN || direction == DIRECTION_RIGHT) && choose < 4)
			choose++;
		else if ((direction == DIRECTION_UP || direction == DIRECTION_LEFT)
				&& choose > 1)
			choose--;

		if (is_shooting(1))
			option = choose;

		if (option == 2) {
			printHowTo(char_buffer, pixel_buffer);
			option = 0;
		}

		if (option == 3) {
			gameMode = printChooseGamePlayers(char_buffer, pixel_buffer);
			printf("%d", gameMode);
			option = 0;
		}
		if (option == 4) {
			printHighScoreMenu(char_buffer, pixel_buffer, high_score_names);
			option = 0;
		}

		if (option == 1) {

			scorePlayer1 = 0;
			scorePlayer2 = 0;
			livesPlayer1 = 3;
			livesPlayer2 = 3;
			int *whoHitBallLast = (int *) malloc(sizeof(int));
			whoHitBallLast[0] = 0;
			i = 0;
			levelToPlay[0] = 0;
			levelTotalBrickCount[0] = 0;
			rowToAccess = 0;
			columnToAccess = 0;
			y = 0;
			//positionOfBall[0] = BALL_START_X_POSITION;
			//positionOfBall[1] = BALL_START_Y_POSITION;
			positionOfBall[0] = 0;
			positionOfBall[1] = 0;
			speedOfBall[0] = BALL_DEFAULT_X_SPEED;
			speedOfBall[1] = BALL_DEFAULT_Y_SPEED;
			xpaddleCurrentPosition[0] = PADDLE_START_X_POSITION;
			xpaddleSpeed[0] = XPADDLE_DO_NOT_MOVE;
			xpaddle2CurrentPosition[0] = PADDLE_2_START_X_POSITION;
			xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;

			alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
			alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
			alt_up_char_buffer_clear(char_buffer);
			who_won = 0;

			//DRAW LEVEL BOX
			printLevelBox(pixel_buffer);

			//Print Player info
			if (gameMode == 2) {
				printTwoPlayerInfo(char_buffer, livesPlayer1, scorePlayer1,
						livesPlayer2, scorePlayer2);
			} else if (gameMode == 1) {
				printOnePlayerInfo(char_buffer, 3, 0);
			}

			//Pause Game
			while (!(IORD_8DIRECT(SWITCHES_BASE, 0) & 0x01)) {
				//Delay
				//for (i = 0; i<280000;i++);
				option = 0;

				if (gameIfLevelOver(levelTotalBrickCount, levelToPlay,
						levelBricksToDraw, positionOfBall, speedOfBall,
						whoHitBallLast, char_buffer, color, pixel_buffer,
						xpaddleCurrentPosition, xpaddle2CurrentPosition,
						xpaddleSpeed, xpaddle2Speed) == -1) {
					break;
				}

				//while ((IORD_8DIRECT(SWITCHES_BASE, 0) & 0x04));

				//Read level from file


				if (gameMode == 2) {
					//Erase the ball at current location

					gameEraseBallPosition(positionOfBall, speedOfBall,
							pixel_buffer);

					gameErasePaddle1(xpaddleSpeed, xpaddleCurrentPosition,
							pixel_buffer);
					gameErasePaddle2(xpaddle2Speed, xpaddle2CurrentPosition,
							pixel_buffer);

					//Erase the paddle at current location
					//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddleCurrentPosition, PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition + LENGTH_OF_PADDLE, PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE, 0, 1);


					//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 319, 239, 0, 1);


					//Check if ball will hit the side, if so change directions
					if (ballHitSideWalls(positionOfBall, speedOfBall) == 1) {
						temp_array_play = temp_array;
						size = laser;
						alt_up_audio_enable_write_interrupt(audio_dev);
					}

					//Check if ball will hit top and change directions
					//if(positionOfBall[1] == SCREEN_HEIGHT_MIN_PIXEL + BALL_HEIGHT ) {
					//speedOfBall[1] = speedOfBall[1] * -1;
					//}

					//Go through all bricks in the 2D array and check if the ball will hit any of the brick

					cycleBallSpeedX(positionOfBall, speedOfBall);
					cycleBallSpeedY(positionOfBall, speedOfBall);

					//hit detection
					if (gameCheckIfBallHitBrick(levelBricksToDraw,
							positionOfBall, speedOfBall, color,
							levelTotalBrickCount, pixel_buffer) == 1) {
						if (whoHitBallLast[0] == 1) {
							scorePlayer1 += 1;
						} else if (whoHitBallLast[0] == 2) {
							scorePlayer2 += 1;
						}
					}

					//}

					//If ball is about to hit the paddle then change direction


					if (gameBallHItPaddle1(positionOfBall,
							xpaddleCurrentPosition, speedOfBall) == 1) {
						whoHitBallLast[0] = 1;
					}

					if (gameBallHItPaddle2(positionOfBall,
							xpaddle2CurrentPosition, speedOfBall) == 1) {
						whoHitBallLast[0] = 2;
					}

					//gameSetPaddle1Speed(xpaddleCurrentPosition,xpaddleSpeed);
					//if the paddle is at the edge then do not let the user go in that direction anymore


					//if the paddle is at the edge then do not let the user go in that direction anymore
					//gameSetPaddle2Speed(xpaddle2CurrentPosition,xpaddle2Speed);


					//Set new location of ball
					positionOfBall[0] += speedOfBall[0];
					positionOfBall[1] += speedOfBall[1];

					gamePaddle1NewPosition(xpaddleSpeed, xpaddleCurrentPosition);
					gamePaddle2NewPosition(xpaddle2Speed,
							xpaddle2CurrentPosition);
					//Check if the user wants to go left or right


					//If the ball goes out of screen then quit
					if (positionOfBall[1] > SCREEN_HEIGHT_MAX_PIXEL) {
						if (livesPlayer1 == 1) {
							who_won = 2;
							break;
						} else {
							gameEraseBallPosition(positionOfBall, speedOfBall,
									pixel_buffer);
							livesPlayer1--;
							positionOfBall[0] = xpaddleCurrentPosition[0]
									+ (LENGTH_OF_PADDLE / 2);
							positionOfBall[1] = PADDLE_Y_AXIS_POSITION - 2;
							speedOfBall[1] = -speedOfBall[1];

							speedOfBall[0] = 1;
							printTwoPlayerInfo(char_buffer, livesPlayer1,
									scorePlayer1, livesPlayer2, scorePlayer2), usleep(
									2000000);
						}
					} else if (positionOfBall[1] < SCREEN_HEIGHT_MIN_PIXEL
							- LEVEL_MIN_HEIGHT) {
						if (livesPlayer2 == 1) {
							who_won = 1;
							break;
						} else {
							gameEraseBallPosition(positionOfBall, speedOfBall,
									pixel_buffer);
							livesPlayer2--;
							positionOfBall[0] = xpaddle2CurrentPosition[0]
									+ (LENGTH_OF_PADDLE / 2);
							positionOfBall[1] = PADDLE_2_Y_AXIS_POSITION + 2;
							speedOfBall[1] = -speedOfBall[1];

							speedOfBall[0] = 1;
							printTwoPlayerInfo(char_buffer, livesPlayer1,
									scorePlayer1, livesPlayer2, scorePlayer2), usleep(
									2000000);

						}

					}

					//Draw the new ball and paddle

					printTwoPlayerInfo(char_buffer, livesPlayer1, scorePlayer1,
							livesPlayer2, scorePlayer2);
					gameDrawNewBallAndPaddle2Player(pixel_buffer,
							xpaddleCurrentPosition, positionOfBall,
							xpaddle2CurrentPosition);

				} else if (gameMode == 1) {
					//Erase the ball at current location
					gameEraseBallPosition(positionOfBall, speedOfBall,
							pixel_buffer);

					gameErasePaddle1(xpaddleSpeed, xpaddleCurrentPosition,
							pixel_buffer);

					alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
							gun_ammo_position[0], gun_ammo_position[1] + 1,
							gun_ammo_position[0] + 1, gun_ammo_position[1] + 2,
							0, 1);
					//Erase the paddle at current location
					//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddleCurrentPosition, PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition + LENGTH_OF_PADDLE, PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE, 0, 1);

					while ((IORD_8DIRECT(SWITCHES_BASE, 0) & 0x04))
						;

					//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 319, 239, 0, 1);


					//Check if ball will hit the side, if so change directions

					if (ballHitSideWalls(positionOfBall, speedOfBall) == 1) {
						temp_array_play = temp_array;
						size = laser;
						alt_up_audio_enable_write_interrupt(audio_dev);
					}

					//Check if ball will hit top and change directions
					if (ballHitsTopWall(positionOfBall, speedOfBall) == 1) {
						temp_array_play = temp_array;
						size = laser;
						alt_up_audio_enable_write_interrupt(audio_dev);
					}

					//Go through all bricks in the 2D array and check if the ball will hit any of the brick


					cycleBallSpeedX(positionOfBall, speedOfBall);
					cycleBallSpeedY(positionOfBall, speedOfBall);

					//Go through all bricks in the 2D array and check if the ball will hit any of the brick
					//hit detection
					int check = gameCheckIfBallHitBrick(levelBricksToDraw,
							positionOfBall, speedOfBall, color,
							levelTotalBrickCount, pixel_buffer);
					if (check == 1) {
						scorePlayer1 += 1;
						if ((scorePlayer1 % 10 == 0) && (scorePlayer1 > 0)
								&& test[0] == 240) {
							poweruprow = poweruprow1;
							test[0] = poweruprow * BRICK_SIZE_HEIGHT;
							test2[0] = (rand() % 6 + 1);
							test3[0] = 1;
							powerup_count2 = 300;
							powerupcolumn = powerupcolumn1;
						}
					} else if (check > 1) {
						scorePlayer1 += check;
						if ((scorePlayer1 % 10 == 0) && (scorePlayer1 > 0)
								&& test[0] == 240) {
							poweruprow = poweruprow1;
							test[0] = poweruprow * BRICK_SIZE_HEIGHT;
							test2[0] = (rand() % 6 + 1);
							test3[0] = 1;
							powerup_count2 = 300;
							powerupcolumn = powerupcolumn1;
						}
					}

					//Check for if you catch a power up
					if (checkPowerUps(pixel_buffer, char_buffer, color,
							xpaddleCurrentPosition, levelBricksToDraw) == 1)
						livesPlayer1++;
					//}

					if (gameBallHItPaddle1(positionOfBall,
							xpaddleCurrentPosition, speedOfBall) == 1) {
						temp_array_play = temp_array;
						size = laser;
						alt_up_audio_enable_write_interrupt(audio_dev);
					}

					//if(flag_inner_paddle == 0)
					//{

					//}


					//cycleBallSpeed(positionOfBall, speedOfBall);
					//Set new location of ball for the y-coordinate
					positionOfBall[1] += speedOfBall[1];

					//Set the new location of the x-coordinate
					positionOfBall[0] += speedOfBall[0];

					//Check if the user wants to go left or right
					gamePaddle1NewPosition(xpaddleSpeed, xpaddleCurrentPosition);


					//If the ball goes out of screen then quit
					if (positionOfBall[1] > SCREEN_HEIGHT_MAX_PIXEL) {
						if (livesPlayer1 == 1) {
							who_won = 2;
							break;
						} else {
							gameEraseBallPosition(positionOfBall, speedOfBall,
									pixel_buffer);
							livesPlayer1--;
							gun = 0;
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
									gun_ammo_position[0], gun_ammo_position[1],
									gun_ammo_position[0] + 1, gun_ammo_position[1]
											+ 1, 0, 1);
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
									gun_ammo_position[0], gun_ammo_position[1],
									gun_ammo_position[0] + 1, gun_ammo_position[1]
											+ 1, 0, 0);
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
									gun_ammo_position[0], gun_ammo_position[1] + 1,
									gun_ammo_position[0] + 1, gun_ammo_position[1] + 2,
									0, 1);
							gun_ammo_position[0] = 0;
							gun_ammo_position[1] = 0;
							gun_shot=0;
							gun_ammo=1;
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
									powerupcolumn * BRICK_SIZE_WIDTH + 1, test[0] + 1,
									powerupcolumn * BRICK_SIZE_WIDTH + BRICK_SIZE_WIDTH
											- 1, test[0]
											+ BRICK_SIZE_HEIGHT - 1, 0, 1);
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
									powerupcolumn * BRICK_SIZE_WIDTH + 1, test[0] + 1,
									powerupcolumn * BRICK_SIZE_WIDTH + BRICK_SIZE_WIDTH
											- 1, test[0]
											+ BRICK_SIZE_HEIGHT - 1, 0, 0);
							test[0] = 240;
							test2[0] = 0;
							test3[0] = 0;
							flip = 0;
							invincibility = 0;
							powerup_count=0;
							powerup_count2=0;
							alt_up_char_buffer_string(char_buffer,
									"                                ", 35, 8);
							alt_up_char_buffer_string(char_buffer,
									"             ", 35, 10);


							DEFAULT_SPEED_OF_PADDLE = 3;
							LENGTH_OF_PADDLE = 38;
							positionOfBall[0] = xpaddleCurrentPosition[0]
									+ (LENGTH_OF_PADDLE / 2);
							positionOfBall[1] = PADDLE_Y_AXIS_POSITION - 2;
							speedOfBall[1] = -speedOfBall[1];
							speedOfBall[0] = 1;
							printOnePlayerInfo(char_buffer, livesPlayer1,
									scorePlayer1), usleep(2000000);
						}
					}

					//gameSetPaddle1Speed(xpaddleCurrentPosition,xpaddleSpeed);

					printOnePlayerInfo(char_buffer, livesPlayer1, scorePlayer1);
					gameDrawNewBallAndPaddle1Player(pixel_buffer,
							xpaddleCurrentPosition, positionOfBall);
					//Check if the ammo hits the top of the screen

					gunHitTopWall(pixel_buffer);

					if (gun == 1) {
						alt_up_pixel_buffer_dma_draw_box(
								pixel_buffer,
								xpaddleCurrentPosition[0] + (LENGTH_OF_PADDLE / 2),
								PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition[0]
										+ (LENGTH_OF_PADDLE / 2) + 1,
								PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE,
								0xFFFFFF, 1);
						alt_up_pixel_buffer_dma_draw_box(
								pixel_buffer,
								xpaddleCurrentPosition[0] + (LENGTH_OF_PADDLE / 2),
								PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition[0]
										+ (LENGTH_OF_PADDLE / 2) + 1,
								PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE,
								0xffffff, 0);
						//Firing the gun
						if (gun_ammo == 1 && is_shooting(1)) {
							gun_shot = 1;
							gun_ammo = 0;
							gun_ammo_position[0] = xpaddleCurrentPosition[0]
									+ (LENGTH_OF_PADDLE / 2);
							gun_ammo_position[1] = PADDLE_Y_AXIS_POSITION;
						}
					}
					//Advancing the bullet
					if (gun_shot == 1) {
						gun_ammo_position[1]--;
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
								gun_ammo_position[0], gun_ammo_position[1],
								gun_ammo_position[0] + 1, gun_ammo_position[1]
										+ 1, 0x586EB8, 1);
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
								gun_ammo_position[0], gun_ammo_position[1],
								gun_ammo_position[0] + 1, gun_ammo_position[1]
										+ 1, 0x586EB8, 0);
					}

					//Checking if the bullet hits a brick
					if (levelBricksToDraw[gun_ammo_position[1]/BRICK_SIZE_HEIGHT][gun_ammo_position[0]/BRICK_SIZE_WIDTH]
							!= 0) {
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
								gun_ammo_position[0], gun_ammo_position[1],
								gun_ammo_position[0] + 1, gun_ammo_position[1]
										+ 1, 0, 1);
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
								gun_ammo_position[0], gun_ammo_position[1],
								gun_ammo_position[0] + 1, gun_ammo_position[1]
										+ 1, 0, 0);
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
								gun_ammo_position[0], gun_ammo_position[1] + 1,
								gun_ammo_position[0] + 1, gun_ammo_position[1] + 2,
								0, 1);
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
								gun_ammo_position[0], gun_ammo_position[1] + 1,
								gun_ammo_position[0] + 1, gun_ammo_position[1] + 2,
								0, 0);

						levelBricksToDraw[gun_ammo_position[1]/BRICK_SIZE_HEIGHT][gun_ammo_position[0]/BRICK_SIZE_WIDTH]
								= levelBricksToDraw[gun_ammo_position[1]/BRICK_SIZE_HEIGHT][gun_ammo_position[0]/BRICK_SIZE_WIDTH]
										- 1;
						levelTotalBrickCount[0] -= 1;

						//Redrawing the brick
						if ((levelBricksToDraw[gun_ammo_position[1]/BRICK_SIZE_HEIGHT][gun_ammo_position[0]/BRICK_SIZE_WIDTH] < 5)
								&& (levelBricksToDraw[gun_ammo_position[1]/BRICK_SIZE_HEIGHT][gun_ammo_position[0]/BRICK_SIZE_WIDTH]
										> 0)) {
							draw_brick(
									pixel_buffer,
									gun_ammo_position[1]/8,
									gun_ammo_position[0]/16,
									levelBricksToDraw[gun_ammo_position[1]/BRICK_SIZE_HEIGHT][gun_ammo_position[0]/BRICK_SIZE_WIDTH]);

						} else {
							int
									drawcolor =
											color[levelBricksToDraw[gun_ammo_position[1]/BRICK_SIZE_HEIGHT][gun_ammo_position[0]/BRICK_SIZE_WIDTH]];
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
									(gun_ammo_position[0]/BRICK_SIZE_WIDTH) * BRICK_SIZE_WIDTH,
									(gun_ammo_position[1]/BRICK_SIZE_HEIGHT) * BRICK_SIZE_HEIGHT,
									((gun_ammo_position[0]/BRICK_SIZE_WIDTH) * BRICK_SIZE_WIDTH)
											+ BRICK_SIZE_WIDTH - 1,
									((gun_ammo_position[1]/BRICK_SIZE_HEIGHT) * BRICK_SIZE_HEIGHT)
											+ BRICK_SIZE_HEIGHT - 1, drawcolor,
									1);
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
									(gun_ammo_position[0]/BRICK_SIZE_WIDTH) * BRICK_SIZE_WIDTH,
									(gun_ammo_position[1]/BRICK_SIZE_HEIGHT) * BRICK_SIZE_HEIGHT,
									((gun_ammo_position[0]/BRICK_SIZE_WIDTH) * BRICK_SIZE_WIDTH)
											+ BRICK_SIZE_WIDTH - 1,
									((gun_ammo_position[1]/BRICK_SIZE_HEIGHT) * BRICK_SIZE_HEIGHT)
											+ BRICK_SIZE_HEIGHT - 1, drawcolor,
									0);
						}
						gun_ammo_position[0] = 0;
						gun_ammo_position[1] = 0;
						gun_shot = 0;
						gun_ammo = 1;
					}

				} else if (gameMode == 3) {
					//Erase the ball at current location

					gameEraseBallPosition(positionOfBall, speedOfBall,
							pixel_buffer);

					gameErasePaddle1(xpaddleSpeed, xpaddleCurrentPosition,
							pixel_buffer);
					gameErasePaddle2(xpaddle2Speed, xpaddle2CurrentPosition,
							pixel_buffer);

					//Erase the paddle at current location
					//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddleCurrentPosition, PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition + LENGTH_OF_PADDLE, PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE, 0, 1);


					//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 319, 239, 0, 1);


					cycleBallSpeed(positionOfBall, speedOfBall);

					//Go through all bricks in the 2D array and check if the ball will hit any of the brick
					//hit detection
					if (gameCheckIfBallHitBrick(levelBricksToDraw,
							positionOfBall, speedOfBall, color,
							levelTotalBrickCount, pixel_buffer) == 1) {
						if (whoHitBallLast[0] == 1) {
							scorePlayer1 += 1;
						} else if (whoHitBallLast[0] == 2) {
							scorePlayer2 += 1;
						}
					}

					//Check if ball will hit the side, if so change directions
					if (ballHitSideWalls(positionOfBall, speedOfBall) == 1) {
						temp_array_play = temp_array;
						size = laser;
						alt_up_audio_enable_write_interrupt(audio_dev);
					}

					//Check if ball will hit top and change directions
					//if(positionOfBall[1] == SCREEN_HEIGHT_MIN_PIXEL + BALL_HEIGHT ) {
					//speedOfBall[1] = speedOfBall[1] * -1;
					//}

									cycleBallSpeedX(positionOfBall, speedOfBall);
									cycleBallSpeedY(positionOfBall, speedOfBall);


									//Go through all bricks in the 2D array and check if the ball will hit any of the brick
									//hit detection
									if (gameCheckIfBallHitBrick(levelBricksToDraw, positionOfBall, speedOfBall, color, levelTotalBrickCount, pixel_buffer) == 1){
										if (whoHitBallLast[0] == 1) {
											scorePlayer1 += 1;
										}
										else if (whoHitBallLast[0] == 2) {
											scorePlayer2 += 1;
										}
									}

					if (gameBallHItPaddle1(positionOfBall,
							xpaddleCurrentPosition, speedOfBall) == 1) {
						whoHitBallLast[0] = 1;
					}

					//hit detection
					if (gameCheckIfBallHitBrick(levelBricksToDraw,
							positionOfBall, speedOfBall, color,
							levelTotalBrickCount, pixel_buffer) == 1) {
						if (whoHitBallLast[0] == 1) {
							scorePlayer1 += 1;
						} else if (whoHitBallLast[0] == 2) {
							scorePlayer2 += 1;
						}
					}

					//}

					//If ball is about to hit the paddle then change direction

					if (gameBallHItPaddle1(positionOfBall,
							xpaddleCurrentPosition, speedOfBall) == 1) {
						whoHitBallLast[0] = 1;
					}

					if (gameBallHItPaddle2(positionOfBall,
							xpaddle2CurrentPosition, speedOfBall) == 1) {
						whoHitBallLast[0] = 2;
					}

					//gameSetPaddle1Speed(xpaddleCurrentPosition,xpaddleSpeed);
					//if the paddle is at the edge then do not let the user go in that direction anymore


					//if the paddle is at the edge then do not let the user go in that direction anymore
					//gameSetPaddle2Speed(xpaddle2CurrentPosition,xpaddle2Speed);

					gamePaddle1NewPosition(xpaddleSpeed, xpaddleCurrentPosition);
					//if(sukhi == 3) {
					gamePaddle2NewPosition_AI(xpaddle2Speed,
							xpaddle2CurrentPosition, positionOfBall,
							speedOfBall);
					//sukhi = 0;
					//}

					//else { sukhi++; }
					//Check if the user wants to go left or right


					//Set new location of ball
					positionOfBall[0] += speedOfBall[0];
					positionOfBall[1] += speedOfBall[1];

					gamePaddle1NewPosition(xpaddleSpeed, xpaddleCurrentPosition);

					gamePaddle2NewPosition_AI(xpaddle2Speed,
							xpaddle2CurrentPosition, positionOfBall,
							speedOfBall);

					//If the ball goes out of screen then quit
					if (positionOfBall[1] > SCREEN_HEIGHT_MAX_PIXEL) {
						if (livesPlayer1 == 1) {
							who_won = 2;
							break;
						} else {
							gameEraseBallPosition(positionOfBall, speedOfBall,
									pixel_buffer);
							livesPlayer1--;
							positionOfBall[0] = xpaddleCurrentPosition[0]
									+ (LENGTH_OF_PADDLE / 2);
							positionOfBall[1] = PADDLE_Y_AXIS_POSITION - 2;
							speedOfBall[1] = -speedOfBall[1];
							speedOfBall[0] = 1;
							printTwoPlayerInfo(char_buffer, livesPlayer1,
									scorePlayer1, livesPlayer2, scorePlayer2), usleep(
									2000000);
						}
					} else if (positionOfBall[1] < SCREEN_HEIGHT_MIN_PIXEL
							- LEVEL_MIN_HEIGHT) {
						if (livesPlayer2 == 1) {
							who_won = 1;
							break;
						} else {
							gameEraseBallPosition(positionOfBall, speedOfBall,
									pixel_buffer);
							livesPlayer2--;
							positionOfBall[0] = xpaddle2CurrentPosition[0]
									+ (LENGTH_OF_PADDLE / 2);
							positionOfBall[1] = PADDLE_2_Y_AXIS_POSITION + 2;
							speedOfBall[1] = -speedOfBall[1];
							speedOfBall[0] = 1;
							printTwoPlayerInfo(char_buffer, livesPlayer1,
									scorePlayer1, livesPlayer2, scorePlayer2), usleep(
									2000000);
						}
					}

					//Check if the user wants to go left or right


					//Draw the new ball and paddle

					printTwoPlayerInfo(char_buffer, livesPlayer1, scorePlayer1,
							livesPlayer2, scorePlayer2);
					gameDrawNewBallAndPaddle2Player(pixel_buffer,
							xpaddleCurrentPosition, positionOfBall,
							xpaddle2CurrentPosition);

				}

			}

		}
		if (who_won != 0) {

			alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
			alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
			int score;
			alt_up_char_buffer_clear(char_buffer);
			if (gameMode == 2 || gameMode == 3) {

				twoPlayerScore(scorePlayer1, scorePlayer2, livesPlayer1,
						livesPlayer2, char_buffer, pixel_buffer);
				who_won = 0;

			} else {
				score = scorePlayer1;
				who_won = 0;
				for (x = 0; x <= 9; x++) {
					if (score > high_scores[x]) {
						alt_up_char_buffer_string(char_buffer,
								"ENTER A 3 LETTER NAME", 29, 26);
						for (n = 0; n < 3; n++) {
							letter = 65;
							for (i = 0; i < 90000; i++)
								;
							for (i = 0; i < 90000; i++)
								;

							while (!(is_shooting(1))) {
								for (i = 0; i < 90000; i++)
									;
								for (i = 0; i < 90000; i++)
									;
								direction = getmovement(1);
								if (((direction == DIRECTION_DOWN) || (direction
										== DIRECTION_LEFT)) && letter < 90)
									letter++;
								if (((direction == DIRECTION_UP) || (direction
										== DIRECTION_RIGHT)) && letter > 65)
									letter--;
								char *temp;
								sprintf(temp, "%c", letter);
								alt_up_char_buffer_string(char_buffer, temp, 34
										+ 2 * n, 30);
								char temp2;
								temp2 = (char) letter;

								name[n] = temp2;
							}
						}
						name[3] = '\0';
						high_scores[x] = score;
						char *temp3 = (char *)malloc(sizeof(char)*11);

						sprintf(temp3, "%s %d", name, score);
						char *temp2 = (char *)malloc(sizeof(char *));
						for (m = 9; m > x; m--) {
							temp2 = high_score_names[m];
							high_score_names[m] = high_score_names[m-1];
							high_score_names[m-1] = temp2;
						}
						high_score_names[x] = temp3;
						saveNewHighScore(high_score_names, "hScore.txt");
						score = -1;
						for (i = 0; i < 10; i++) {
							printf("%s\n", high_score_names[i]);
						}
					}
				}
			}
		}
	}
	return 0;
}

