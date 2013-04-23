int *test;
int *test2;
int *test3;
int powerup_count = 0;
int powerup_count2 = 0;
int flip = 0;
int gun = 0;
int invincibility = 0;
int invincibility_count=0;
char *powerup_message ;
int gun_ammo_position[2]={0,0};
int gun_shot = 0;
int gun_ammo = 1;
int poweruprow=0;
int powerupcolumn=0;
int powerupcolumn1=0;
int poweruprow1=0;


void gunHitTopWall(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	if (gun_ammo_position[1] == SCREEN_HEIGHT_MIN_PIXEL + 1 + LEVEL_MIN_HEIGHT) {
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, gun_ammo_position[0],
				gun_ammo_position[1], gun_ammo_position[0] + 1,
				gun_ammo_position[1] + 1, 0, 1);
		gun_ammo_position[0] = 0;
		gun_ammo_position[1] = 0;
		gun_shot = 0;
		gun_ammo = 1;
	}
}

int checkPowerUps(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev *char_buffer, int *color, int * xpaddleCurrentPosition, int **levelBricksToDraw){
//New code for dropping power ups
	int valueToreturn = 0;
	int power;

						if (test3[0] == 1) {
							power = test2[0];
						}

						if (powerup_count2 > 0) {
							if (power == 1)
								alt_up_char_buffer_string(char_buffer,
										"GET A LIFE!      ", 35, 8);
							else if (power == 2)
								alt_up_char_buffer_string(char_buffer,
										"GUN!             ", 35, 8);
							else if (power == 3)
								alt_up_char_buffer_string(char_buffer,
										"DOUBLE LENGTH    ", 35, 8);
							else if (power == 4)
								alt_up_char_buffer_string(char_buffer,
										"FLIP             ", 35, 8);
							else if (power == 5)
								alt_up_char_buffer_string(char_buffer,
										"NEED FOR SPEED?  ", 35, 8);
							else if (power ==6)
								alt_up_char_buffer_string(char_buffer,
										"UNSTOPPABLE FORCE", 35, 8);
							powerup_count2--;
						} else {
							alt_up_char_buffer_string(char_buffer,
									"                                ", 35, 8);
							power = 0;
							test3[0] = 0;
						}
						if ((levelBricksToDraw[test[0]/8][powerupcolumn] < 5) && (levelBricksToDraw[test[0]/8][powerupcolumn] > 0)){
							draw_brick( pixel_buffer,  test[0]/8, powerupcolumn, levelBricksToDraw[test[0]/8][powerupcolumn]);
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, powerupcolumn
									* BRICK_SIZE_WIDTH + 1, test[0] + 1, powerupcolumn
									* BRICK_SIZE_WIDTH + BRICK_SIZE_WIDTH - 1,
									test[0] + BRICK_SIZE_HEIGHT - 1, 0x586EB8, 1);
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, powerupcolumn
									* BRICK_SIZE_WIDTH + 1, test[0] + 1, powerupcolumn
									* BRICK_SIZE_WIDTH + BRICK_SIZE_WIDTH - 1,
									test[0] + BRICK_SIZE_HEIGHT - 1, 0x586EB8, 0);
						}
						else{

						int drawcolor =
								color[levelBricksToDraw[test[0] / 8][powerupcolumn]];
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, (powerupcolumn
								* BRICK_SIZE_WIDTH), ((test[0] / 8)
								* BRICK_SIZE_HEIGHT), (powerupcolumn * BRICK_SIZE_WIDTH)
								+ BRICK_SIZE_WIDTH - 1, ((test[0] / 8)
								* BRICK_SIZE_HEIGHT) + BRICK_SIZE_HEIGHT - 1,
								drawcolor, 1);
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, (powerupcolumn
								* BRICK_SIZE_WIDTH), ((test[0] / 8)
								* BRICK_SIZE_HEIGHT), (powerupcolumn * BRICK_SIZE_WIDTH)
								+ BRICK_SIZE_WIDTH - 1, ((test[0] / 8)
								* BRICK_SIZE_HEIGHT) + BRICK_SIZE_HEIGHT - 1,
								drawcolor, 0);
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, powerupcolumn
								* BRICK_SIZE_WIDTH + 1, test[0] + 1, powerupcolumn
								* BRICK_SIZE_WIDTH + BRICK_SIZE_WIDTH - 1,
								test[0] + BRICK_SIZE_HEIGHT - 1, 0x586EB8, 1);
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, powerupcolumn
								* BRICK_SIZE_WIDTH + 1, test[0] + 1, powerupcolumn
								* BRICK_SIZE_WIDTH + BRICK_SIZE_WIDTH - 1,
								test[0] + BRICK_SIZE_HEIGHT - 1, 0x586EB8, 0);
						}

						if (test[0] <= PADDLE_Y_AXIS_POSITION + 6 && test[0]
								>= PADDLE_Y_AXIS_POSITION - BRICK_SIZE_HEIGHT)
							if ((powerupcolumn * BRICK_SIZE_WIDTH >= xpaddleCurrentPosition[0]
									&& powerupcolumn * BRICK_SIZE_WIDTH
											<= xpaddleCurrentPosition[0]
													+ LENGTH_OF_PADDLE) || (powerupcolumn
									* (BRICK_SIZE_WIDTH + 1)
									>= xpaddleCurrentPosition[0] && powerupcolumn
									* (BRICK_SIZE_WIDTH + 1)
									<= xpaddleCurrentPosition[0]
											+ LENGTH_OF_PADDLE)) {
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

								if (test2[0] == 1) {
									valueToreturn = 1;
									sprintf(powerup_message, "EXTRA LIFE   ");
								} else if (test2[0] == 2) {
									gun = 1;
									sprintf(powerup_message, "GUN          ");
								} else if (test2[0] == 3) {
									LENGTH_OF_PADDLE=76;
									sprintf(powerup_message, "DOUBLE LENGTH");
								} else if (test2[0] == 4) {
									if(flip==0)
										flip=1;
									else
										flip=0;
									sprintf(powerup_message, "FLIP         ");
								} else if (test2[0] == 5) {
									DEFAULT_SPEED_OF_PADDLE = 6;
									sprintf(powerup_message, "SPEED UPGRADE");
								} else if (test2[0] == 6){
									invincibility =1;
									invincibility_count=300;
									sprintf(powerup_message, "INVINCIBILITY");
								}

								test2[0] = 0;
								test[0] = 240;
								printf("powerup");
								powerup_count = 30;
							}
						if (test[0] < 240)
							test[0] = test[0] + 1;
						else
							test[0] = 240;

						if (powerup_count > 0) {
							alt_up_char_buffer_string(char_buffer,
									powerup_message, 35, 10);
							powerup_count--;
						} else
							alt_up_char_buffer_string(char_buffer,
									"             ", 35, 10);
						if(invincibility_count>0){
							invincibility_count--;
						}
						else
							invincibility=0;

					return valueToreturn;
}
