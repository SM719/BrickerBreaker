char *tempString;

void printOnePlayerInfo(alt_up_char_buffer_dev *char_buffer, int lives, int score){

	alt_up_char_buffer_string(char_buffer, "Player 1", 15, 1);
	alt_up_char_buffer_string(char_buffer, "Lives: ", 3, 3);
	alt_up_char_buffer_string(char_buffer, "Score: ", 18, 3);
	sprintf(tempString, "%d", lives);
	alt_up_char_buffer_string(char_buffer, tempString, 10, 3);
	sprintf(tempString, "%d", score);
	alt_up_char_buffer_string(char_buffer, tempString, 25, 3);
}

void printTwoPlayerInfo(alt_up_char_buffer_dev *char_buffer, int livesPlayer1, int scorePlayer1, int livesPlayer2, int scorePlayer2){
	alt_up_char_buffer_string(char_buffer, "Player 1", 15, 1);
	alt_up_char_buffer_string(char_buffer, "Player 2", 67, 1);
	alt_up_char_buffer_string(char_buffer, "Lives: ", 3, 3);
	alt_up_char_buffer_string(char_buffer, "Score: ", 18, 3);
	alt_up_char_buffer_string(char_buffer, "Lives: ", 50, 3);
	alt_up_char_buffer_string(char_buffer, "Score: ", 70, 3);
	sprintf(tempString, "%d", livesPlayer1);
	alt_up_char_buffer_string(char_buffer, tempString, 10, 3);
	sprintf(tempString, "%d", livesPlayer2);
	alt_up_char_buffer_string(char_buffer, tempString, 57, 3);
	sprintf(tempString, "%d", scorePlayer1);
	alt_up_char_buffer_string(char_buffer, tempString, 25, 3);
	sprintf(tempString, "%d", scorePlayer2);
	alt_up_char_buffer_string(char_buffer, tempString, 77, 3);
}

void printMenu(alt_up_char_buffer_dev *char_buffer, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_char_buffer_clear(char_buffer);
	alt_up_char_buffer_string(char_buffer, "PLAY", 35, 25);
	alt_up_char_buffer_string(char_buffer, "HOW TO", 35, 30);
	alt_up_char_buffer_string(char_buffer, "OPTIONS", 35, 35);
	alt_up_char_buffer_string(char_buffer, "HIGH SCORES", 35, 40);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 100, 139, 101, YELLOW, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 120, 139, 121, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 140, 139, 141, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 160, 139, 161, BLACK, 0);
}

void printMenuOptionSelected (int optionSelected, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	if (optionSelected == 1){
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 100, 139, 101, YELLOW, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 120, 139, 121, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 140, 139, 141, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 160, 139, 161, BLACK, 0);
	}
	else if(optionSelected == 2){
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 100, 139, 101, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 120, 139, 121, YELLOW, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 140, 139, 141, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 160, 139, 161, BLACK, 0);
	}
	else if (optionSelected == 3){
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 100, 139, 101, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 120, 139, 121, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 140, 139, 141, YELLOW, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 160, 139, 161, BLACK, 0);
	}
	else if(optionSelected == 4){
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 100, 139, 101, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 120, 139, 121, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 140, 139, 141, BLACK, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 138, 160, 139, 161, YELLOW, 0);
	}
}

void printHowTo(alt_up_char_buffer_dev *char_buffer, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_char_buffer_clear(char_buffer);
	while (!(IORD_8DIRECT(SWITCHES_BASE, 0) & 0x01)) {
		alt_up_char_buffer_string(char_buffer, "The objective of this game, Breakout, is to bounce the ball", 5, 25);
		alt_up_char_buffer_string(char_buffer, "off the paddle and keep it in play to break as many bricks", 5, 30);
		alt_up_char_buffer_string(char_buffer, "as possible", 5, 35);
	}
}

int printChooseGamePlayers (alt_up_char_buffer_dev *char_buffer, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	int playerChoose = 0;
	int gameMode = 1;
	int i;
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_char_buffer_clear(char_buffer);
	alt_up_char_buffer_string(char_buffer, "1 Player", 35, 25);
	alt_up_char_buffer_string(char_buffer, "2 Player", 35, 30);
	alt_up_char_buffer_string(char_buffer, "VS Computer", 35, 35);

	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 100, 138, 101,
			YELLOW, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 120, 138, 121,
			BLACK, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 140, 138, 141,
			BLACK, 0);

	while ((!(IORD_8DIRECT(SWITCHES_BASE, 0) & 0x01))) {
		for (i = 0; i < 90000; i++)
			;
		if ((getmovement(1) == DIRECTION_DOWN) && playerChoose < 3)
			playerChoose++;

		else if ((getmovement(1) == DIRECTION_UP) && playerChoose > 1)
			playerChoose--;

		if (playerChoose == 1) {
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 100,
					138, 101, YELLOW, 0);
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 120,
					138, 121, BLACK, 0);
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 140, 138, 141,
						BLACK, 0);
			gameMode = 1;
		} else if (playerChoose == 2) {
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 100,
					138, 101, BLACK, 0);
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 120,
					138, 121, YELLOW, 0);
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 140, 138, 141,
						BLACK, 0);
			gameMode = 2;
		}
		else if (playerChoose == 3) {
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 100, 138, 101,
					BLACK, 0);
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 120, 138, 121,
					BLACK, 0);
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 137, 140, 138, 141,
					YELLOW, 0);
			gameMode = 3;
		}
	}
	return gameMode;
}

void printHighScoreMenu (alt_up_char_buffer_dev *char_buffer, alt_up_pixel_buffer_dma_dev* pixel_buffer, char *high_score_names[]){
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_char_buffer_clear(char_buffer);
	while (!(IORD_8DIRECT(SWITCHES_BASE, 0) & 0x01)) {
		alt_up_char_buffer_string(char_buffer, high_score_names[0], 35,	5);
		alt_up_char_buffer_string(char_buffer, high_score_names[1], 35,	10);
		alt_up_char_buffer_string(char_buffer, high_score_names[2], 35,	15);
		alt_up_char_buffer_string(char_buffer, high_score_names[3], 35,	20);
		alt_up_char_buffer_string(char_buffer, high_score_names[4], 35,	25);
		alt_up_char_buffer_string(char_buffer, high_score_names[5], 35,	30);
		alt_up_char_buffer_string(char_buffer, high_score_names[6], 35, 35);
		alt_up_char_buffer_string(char_buffer, high_score_names[7], 35,	40);
		alt_up_char_buffer_string(char_buffer, high_score_names[8], 35,	45);
		alt_up_char_buffer_string(char_buffer, high_score_names[9], 35, 50);
	}
}

void printLevelBox(alt_up_pixel_buffer_dma_dev* pixel_buffer){
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, SCREEN_WIDTH_MIN_PIXEL, SCREEN_WIDTH_MAX_PIXEL, SCREEN_HEIGHT_MIN_PIXEL + LEVEL_MIN_HEIGHT, 0x586EB8, 1);
	alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MIN_PIXEL, SCREEN_HEIGHT_MIN_PIXEL + LEVEL_MIN_HEIGHT, SCREEN_HEIGHT_MAX_PIXEL, 0x586EB8, 1);
	alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, SCREEN_HEIGHT_MIN_PIXEL + LEVEL_MIN_HEIGHT, SCREEN_HEIGHT_MAX_PIXEL, 0x586EB8, 1);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, SCREEN_WIDTH_MIN_PIXEL, SCREEN_WIDTH_MAX_PIXEL, SCREEN_HEIGHT_MIN_PIXEL + LEVEL_MIN_HEIGHT, 0x586EB8, 0);
	alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MIN_PIXEL, SCREEN_HEIGHT_MIN_PIXEL + LEVEL_MIN_HEIGHT, SCREEN_HEIGHT_MAX_PIXEL, 0x586EB8, 0);
	alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, SCREEN_HEIGHT_MIN_PIXEL + LEVEL_MIN_HEIGHT, SCREEN_HEIGHT_MAX_PIXEL, 0x586EB8, 0);
}

