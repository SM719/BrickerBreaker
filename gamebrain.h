int gameIfLevelOver(int *levelTotalBrickCount, char *levelToPlay, int **levelBricksToDraw, int *positionOfBall, int *speedOfBall, int *whoHitBallLast, alt_up_char_buffer_dev *char_buffer, int *color, alt_up_pixel_buffer_dma_dev* pixel_buffer, int *xpaddleCurrentPosition, int *xpaddle2CurrentPosition, int *xpaddleSpeed, int *xpaddle2Speed){
	if (levelTotalBrickCount[0] == 0){
		int levelReadSuccess;
		printf("leveltoread: %d\n",levelToPlay[0]);
		levelToPlay[0] = levelToPlay[0] + 1;
		printf("leveltoread: %d\n",levelToPlay[0]);
		int k = (int)levelToPlay[0];
		levelReadSuccess = readLevelFromSDCARD(k, levelBricksToDraw);
		printmap(levelBricksToDraw);
		if(levelReadSuccess == 0){
			printf("enetered here\n");
			levelToPlay[0] = 1;
			levelReadSuccess = readLevelFromSDCARD(k, levelBricksToDraw);
			if (levelReadSuccess == 0){
				printf("testing");
				return -1;
			}
		}
		int rowToAccess;
		int columnToAccess;
		char *levelStartMessage = (char *)malloc(10*sizeof(char));
		sprintf(levelStartMessage, "Level: %d", levelToPlay[0]);
		alt_up_char_buffer_string(char_buffer, levelStartMessage, 36, 30);
		usleep(2500000);
		alt_up_char_buffer_string(char_buffer, "          ", 36, 30);
		alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
		alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
		positionOfBall[0] = BALL_START_X_POSITION;
		positionOfBall[1] = BALL_START_Y_POSITION;
		speedOfBall[0] = BALL_DEFAULT_X_SPEED;
		speedOfBall[1] = BALL_DEFAULT_Y_SPEED;
		xpaddleCurrentPosition[0] = PADDLE_START_X_POSITION;
		xpaddleSpeed[0] = XPADDLE_DO_NOT_MOVE;
		xpaddle2CurrentPosition[0] = PADDLE_2_START_X_POSITION;
		xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;
		whoHitBallLast[0] = 0;
		//if read level successful then draw it out
		if (levelReadSuccess) {
			for (rowToAccess = 0; rowToAccess < MAX_BLOCKS_PER_ROW; rowToAccess++) {
				for (columnToAccess = 0; columnToAccess < MAX_BLOCKS_PER_COLUMN; columnToAccess++) {
					int drawcolor =	color[levelBricksToDraw[rowToAccess][columnToAccess]];
					if ((levelBricksToDraw[rowToAccess][columnToAccess] == 0)){

					}
					else if (levelBricksToDraw[rowToAccess][columnToAccess] < 5){
						draw_brick(pixel_buffer, rowToAccess, columnToAccess, levelBricksToDraw[rowToAccess][columnToAccess]);
					}
					else{
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, (columnToAccess * BRICK_SIZE_WIDTH), (rowToAccess * BRICK_SIZE_HEIGHT), (columnToAccess * BRICK_SIZE_WIDTH)+ BRICK_SIZE_WIDTH - 1, (rowToAccess * BRICK_SIZE_HEIGHT) + BRICK_SIZE_HEIGHT - 1, drawcolor, 1);
												alt_up_pixel_buffer_dma_draw_box(pixel_buffer, (columnToAccess * BRICK_SIZE_WIDTH), (rowToAccess * BRICK_SIZE_HEIGHT), (columnToAccess * BRICK_SIZE_WIDTH) + BRICK_SIZE_WIDTH - 1, (rowToAccess * BRICK_SIZE_HEIGHT) + BRICK_SIZE_HEIGHT - 1, drawcolor, 0);

					}
					levelTotalBrickCount[0] += levelBricksToDraw[rowToAccess][columnToAccess];
				}
			}
		}
		printLevelBox(pixel_buffer);

		//printLevelBox(pixel_buffer);
		printf("levelReadSuccess: %d\n", levelTotalBrickCount[0]);
		return 1;
	}
	return 0;
}

void gameEraseBallPosition(int *positionOfBall, int *speedOfBall, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	if (speedOfBall[0] > 0 && speedOfBall[1] > 0) {
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
			positionOfBall[0] - speedOfBall[0],
			positionOfBall[1] - speedOfBall[1],
			positionOfBall[0], positionOfBall[1], 0, 1);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
				positionOfBall[0] - speedOfBall[0],
				positionOfBall[1] - speedOfBall[1],
				positionOfBall[0], positionOfBall[1], 0, 0);
	} else if (speedOfBall[0] < 0 && speedOfBall[1] > 0) {
	alt_up_pixel_buffer_dma_draw_box(
			pixel_buffer,
			positionOfBall[0] - speedOfBall[0],
			positionOfBall[1] - speedOfBall[1],
			positionOfBall[0] - speedOfBall[0] + BALL_WIDTH,
			positionOfBall[1], 0, 1);
	alt_up_pixel_buffer_dma_draw_box(
				pixel_buffer,
				positionOfBall[0] - speedOfBall[0],
				positionOfBall[1] - speedOfBall[1],
				positionOfBall[0] - speedOfBall[0] + BALL_WIDTH,
				positionOfBall[1], 0, 0);

	} else if (speedOfBall[0] > 0 && speedOfBall[1] < 0) {
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
			positionOfBall[0] - speedOfBall[0],
			positionOfBall[1] - speedOfBall[1],
			positionOfBall[0], positionOfBall[1]
					- speedOfBall[1] + BALL_HEIGHT, 0, 1);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
				positionOfBall[0] - speedOfBall[0],
				positionOfBall[1] - speedOfBall[1],
				positionOfBall[0], positionOfBall[1]
						- speedOfBall[1] + BALL_HEIGHT, 0, 0);

	} else {
	alt_up_pixel_buffer_dma_draw_box(
			pixel_buffer,
			positionOfBall[0] - speedOfBall[0],
			positionOfBall[1] - speedOfBall[1],
			positionOfBall[0] - speedOfBall[0] + BALL_WIDTH,
			positionOfBall[1] - speedOfBall[1]
					+ BALL_HEIGHT, 0, 1);
	alt_up_pixel_buffer_dma_draw_box(
			pixel_buffer,
			positionOfBall[0] - speedOfBall[0],
			positionOfBall[1] - speedOfBall[1],
			positionOfBall[0] - speedOfBall[0] + BALL_WIDTH,
			positionOfBall[1] - speedOfBall[1]
					+ BALL_HEIGHT, 0, 0);

	}

}

void gameErasePaddle1( int *xpaddleSpeed, int *xpaddleCurrentPosition, alt_up_pixel_buffer_dma_dev* pixel_buffer ){
	if (xpaddleSpeed[0] < 0) {
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
				xpaddleCurrentPosition[0] - xpaddleSpeed[0],
				PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition
						- xpaddleSpeed[0] + LENGTH_OF_PADDLE,
				PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE, 0, 1);
		} else if (xpaddleSpeed[0] > 0) {
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
				xpaddleCurrentPosition[0] - xpaddleSpeed[0],
				PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition[0]
						- xpaddleSpeed[0] + LENGTH_OF_PADDLE,
				PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE, 0, 1);
		} else {
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
				xpaddleCurrentPosition[0], PADDLE_Y_AXIS_POSITION,
				xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE,
				PADDLE_Y_AXIS_POSITION + HEIGHT_OF_PADDLE, 0, 1);
		}
	}


void gameErasePaddle2( int *xpaddle2Speed, int *xpaddle2CurrentPosition, alt_up_pixel_buffer_dma_dev* pixel_buffer ){
		if (xpaddle2Speed[0] < 0) {
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
						xpaddle2CurrentPosition[0] - xpaddle2Speed[0],
						PADDLE_2_Y_AXIS_POSITION, xpaddle2CurrentPosition[0]
								- xpaddle2Speed[0] + LENGTH_OF_PADDLE_2,
						PADDLE_2_Y_AXIS_POSITION + HEIGHT_OF_PADDLE_2, 0, 1);
			} else if (xpaddle2Speed[0] > 0) {
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
						xpaddle2CurrentPosition[0] - xpaddle2Speed[0],
						PADDLE_2_Y_AXIS_POSITION, xpaddle2CurrentPosition[0]
								- xpaddle2Speed[0] + LENGTH_OF_PADDLE_2,
						PADDLE_2_Y_AXIS_POSITION + HEIGHT_OF_PADDLE_2, 0, 1);
			} else {
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
						xpaddle2CurrentPosition[0], PADDLE_2_Y_AXIS_POSITION,
						xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE_2,
						PADDLE_2_Y_AXIS_POSITION + HEIGHT_OF_PADDLE_2, 0, 1);
			}
	}



int gameCheckIfBallHitBrick ( int **levelBricksToDraw, int *positionOfBall, int *speedOfBall, int *color, int *levelTotalBrickCount, alt_up_pixel_buffer_dma_dev* pixel_buffer){

	int rowToAccess;
	int columnToAccess;
	columnToAccess= positionOfBall[0] / BRICK_SIZE_WIDTH -1;
	rowToAccess= positionOfBall[1] / BRICK_SIZE_HEIGHT -1;
	int x=columnToAccess+3;
	int y=rowToAccess+3;
	if(x>19)
		x=19;
	if(y>29)
		y=29;
	int donald = 0;
	int valueToReturn=0;
	while ((rowToAccess < y) && (donald == 0)) {
		/*	if (ballInColumn == 0){
		 columnToAccess = 0;
		 }
		 else{
		 columnToAccess = ballInColumn - 3;
		 }*/
		//printf ("PositionOfBall[0]: %d, BallInRow: %d, RowToAccess: %d",positionOfBall[0],ballInRow,rowToAccess);
		//printf(" PositionOfBall[1]: %d, BallINColumn: %d, COlumnTOAccess: %d\n",positionOfBall[1], ballInColumn, columnToAccess);
		//for (rowToAccess = 0; rowToAccess < MAX_BLOCKS_PER_ROW; rowToAccess++){
		//while ((columnToAccess < ballInColumn + 4) && (donald == 0)) {
		//for(columnToAccess = 0; columnToAccess < MAX_BLOCKS_PER_COLUMN; columnToAccess++){
		//if the 2D array had a 1 for the brick then check the coordinates of the brick with ball
		columnToAccess = 0;
		while ((columnToAccess < MAX_BLOCKS_PER_COLUMN) && (donald == 0)) {
			//printf("%d ", levelBricksToDraw[rowToAccess][columnToAccess]);
			if (levelBricksToDraw[rowToAccess][columnToAccess] != NO_BRICK) {
				//printf("got to block\n");
				//if the ball is between x0,x1 and y0,y1 coordinates of the ball then check what direction is ball coming from


				//RIGHTNegative

				//if(positionOfBall[0] >= columnToAccess*BRICK_SIZE_WIDTH && positionOfBall[0] <= (columnToAccess*BRICK_SIZE_WIDTH)+BRICK_SIZE_WIDTH && (positionOfBall[1]  >= rowToAccess*BRICK_SIZE_HEIGHT && positionOfBall[1] <= (rowToAccess*BRICK_SIZE_HEIGHT)+BRICK_SIZE_HEIGHT) ){


				if ((positionOfBall[0] >= (columnToAccess
							* BRICK_SIZE_WIDTH) + BRICK_SIZE_WIDTH)
							&& (positionOfBall[0] + speedOfBall[0]
									>= columnToAccess
											* BRICK_SIZE_WIDTH
									&& positionOfBall[0]
											+ speedOfBall[0]
											<= (columnToAccess
													* BRICK_SIZE_WIDTH)
													+ BRICK_SIZE_WIDTH
									&& (positionOfBall[1] + speedOfBall[1]
											>= rowToAccess
													* BRICK_SIZE_HEIGHT
											&& positionOfBall[1] + speedOfBall[1]
													<= (rowToAccess
															* BRICK_SIZE_HEIGHT)
															+ BRICK_SIZE_HEIGHT))) {
						speedOfBall[0] = speedOfBall[0] * -1;
						donald = 1;
					}

					//Left

					else if ((positionOfBall[0] + 1
							<= columnToAccess * BRICK_SIZE_WIDTH)
							&& (positionOfBall[0] + 1
									+ speedOfBall[0]
									>= columnToAccess
											* BRICK_SIZE_WIDTH
									&& positionOfBall[0] + 1
											+ speedOfBall[0]
											<= (columnToAccess
													* BRICK_SIZE_WIDTH)
													+ BRICK_SIZE_WIDTH
									&& (positionOfBall[1] + speedOfBall[1]
											>= rowToAccess
													* BRICK_SIZE_HEIGHT
											&& positionOfBall[1] + speedOfBall[1]
													<= (rowToAccess
															* BRICK_SIZE_HEIGHT)
															+ BRICK_SIZE_HEIGHT))) {
						speedOfBall[0] = speedOfBall[0] * -1;
						donald = 1;
					}

					//Top Oringally plus 1

					else if ((positionOfBall[1] +1  <= (rowToAccess
							* BRICK_SIZE_HEIGHT)) &&

					(positionOfBall[0]+ speedOfBall[0] >= columnToAccess
							* BRICK_SIZE_WIDTH &&

					positionOfBall[0] + speedOfBall[0] <= (columnToAccess
							* BRICK_SIZE_WIDTH) + BRICK_SIZE_WIDTH
							&&

							(positionOfBall[1] + 1 + speedOfBall[1]
									>= rowToAccess
											* BRICK_SIZE_HEIGHT &&

							positionOfBall[1] + 1 + speedOfBall[1]
									<= (rowToAccess
											* BRICK_SIZE_HEIGHT)
											+ BRICK_SIZE_HEIGHT)))

					{
						speedOfBall[1] = speedOfBall[1] * -1;
						donald = 1;
					}

					//BottomNegative Originally plus nothing

					else if ((positionOfBall[1]   >= (rowToAccess
							* BRICK_SIZE_HEIGHT)
							+ BRICK_SIZE_HEIGHT)
							&& (positionOfBall[0] + speedOfBall[0] >= columnToAccess
									* BRICK_SIZE_WIDTH
									&& positionOfBall[0] + speedOfBall[0]
											<= (columnToAccess
													* BRICK_SIZE_WIDTH)
													+ BRICK_SIZE_WIDTH
									&& (positionOfBall[1]
											+ speedOfBall[1]
											>= rowToAccess
													* BRICK_SIZE_HEIGHT
											&& positionOfBall[1]
													+ speedOfBall[1]
													<= (rowToAccess
															* BRICK_SIZE_HEIGHT)
															+ BRICK_SIZE_HEIGHT))) {
						speedOfBall[1] = speedOfBall[1] * -1;
						donald = 1;
					}

				//if ball is coming from the left or right then change x direction of ball else if coming from top or bottom then change y direction of ball
				//if ((positionOfBall[0] - 1 < columnToAccess*BRICK_SIZE_WIDTH) || (positionOfBall[0] + 1 > (columnToAccess*BRICK_SIZE_WIDTH)+BRICK_SIZE_WIDTH)) {
				//speedOfBall[0] = speedOfBall[0] * -1;
				//}
				//else if ((positionOfBall[1] + 1 > (rowToAccess*BRICK_SIZE_HEIGHT)+BRICK_SIZE_HEIGHT) || (positionOfBall[1] - 1 < (rowToAccess*BRICK_SIZE_HEIGHT))){
				//speedOfBall[1] = speedOfBall[1] * -1;
				//}
				//Once the ball will hit the brick, draw an empty brick (black brick) and set the entry in array to 0 (brick is no more in level)

				if (donald == 1) {
					//play_wav(temp_array, audio_dev);
					valueToReturn=1;
					if(invincibility==1)
					{
						valueToReturn=levelBricksToDraw[rowToAccess][columnToAccess];
						levelTotalBrickCount[0] -= levelBricksToDraw[rowToAccess][columnToAccess];
						levelBricksToDraw[rowToAccess][columnToAccess]=0;
					}
					else
					{
						levelBricksToDraw[rowToAccess][columnToAccess]
								= levelBricksToDraw[rowToAccess][columnToAccess]
										- 1;
						levelTotalBrickCount[0] -= 1;

				if (donald == 1) {
					//play_wav(temp_array, audio_dev);

					levelTotalBrickCount[0] -= 1;
					levelBricksToDraw[rowToAccess][columnToAccess]
							= levelBricksToDraw[rowToAccess][columnToAccess]
									- 1;
					if ((levelBricksToDraw[rowToAccess][columnToAccess] < 5) && (levelBricksToDraw[rowToAccess][columnToAccess] > 0)){
						draw_brick( pixel_buffer,  rowToAccess, columnToAccess, levelBricksToDraw[rowToAccess][columnToAccess]);

					}
					else{
					int
							drawcolor =
									color[levelBricksToDraw[rowToAccess][columnToAccess]];
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
							columnToAccess * BRICK_SIZE_WIDTH, rowToAccess
									* BRICK_SIZE_HEIGHT, (columnToAccess
									* BRICK_SIZE_WIDTH) + BRICK_SIZE_WIDTH -1 ,
							(rowToAccess * BRICK_SIZE_HEIGHT)
									+ BRICK_SIZE_HEIGHT - 1, drawcolor, 1);
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer,
							columnToAccess * BRICK_SIZE_WIDTH, rowToAccess
									* BRICK_SIZE_HEIGHT, (columnToAccess
									* BRICK_SIZE_WIDTH) + BRICK_SIZE_WIDTH -1,
							(rowToAccess * BRICK_SIZE_HEIGHT)
									+ BRICK_SIZE_HEIGHT - 1, drawcolor, 0);
					}
					donald = 2;
					poweruprow1=rowToAccess;
					powerupcolumn1=columnToAccess;
					return valueToReturn;
				}
			}

			columnToAccess++;
		}
		rowToAccess++;
	}
	return 0;
}}

int gameBallHItPaddle1(int *positionOfBall, int *xpaddleCurrentPosition, int *speedOfBall){
	if ((positionOfBall[1] == PADDLE_Y_AXIS_POSITION -1 || positionOfBall[1] == PADDLE_Y_AXIS_POSITION -2)&& positionOfBall[0]
			>= xpaddleCurrentPosition[0] && positionOfBall[0]
			<= xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE && speedOfBall[1]
			>= 0)

	{
		speedOfBall[1] = -1;

		//Set x speed to -2
		if (positionOfBall[0] >= xpaddleCurrentPosition[0] && positionOfBall[0]
				< (xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE / 10.0)){

			speedOfBall[0] = -2;
			flag_inner_paddle = 7;
			count = 0;

		}

		//Set x speed to -1.5
		else if (positionOfBall[0] >= (xpaddleCurrentPosition[0]
				+ LENGTH_OF_PADDLE / 10.0)
				&& positionOfBall[0] <= (xpaddleCurrentPosition[0]
						+ LENGTH_OF_PADDLE * 20 / 100.0)) {


			speedOfBall[0] = -1;
			flag_inner_paddle = 1;
			count = 0;

		}

		//Set x speed to -1.2
		else if (positionOfBall[0] > (xpaddleCurrentPosition[0]
				+ LENGTH_OF_PADDLE * 20 / 100.0) && positionOfBall[0]
				< (xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE * 30/ 100.0))

		{
				speedOfBall[0] = -1;
				flag_inner_paddle = 3;
				count = 0;

		}

		//Set x speed to -1
		else if (positionOfBall[0] >= (xpaddleCurrentPosition[0]
				+ LENGTH_OF_PADDLE * 30 / 100.0)
				&& positionOfBall[0] < (xpaddleCurrentPosition[0]
						+ LENGTH_OF_PADDLE * 40 / 100.0)) {

			speedOfBall[0] = -1;
			flag_inner_paddle = 0;
			count = 0;

		}

		//Set x speed to 0.3/-0.3
		else if (positionOfBall[0] >= (xpaddleCurrentPosition[0]
		         + LENGTH_OF_PADDLE / 40.0)
		         && positionOfBall[0] < (xpaddleCurrentPosition[0]
		         + LENGTH_OF_PADDLE * 60 / 100.0)) {

			//Set x speed to 0.3
			if (speedOfBall[0] >= 0) {

				speedOfBall[0] = 0;
				flag_inner_paddle =5;
				count = 0;
			}

			//Set x speed to -0.3
			else {
				speedOfBall[0] = 0;
				flag_inner_paddle = 6;
				count = 0;
			}
		}

		else if (positionOfBall[0] >= (xpaddleCurrentPosition[0]
					+ LENGTH_OF_PADDLE / 60.0)
					&& positionOfBall[0] < (xpaddleCurrentPosition[0]
							+ LENGTH_OF_PADDLE * 70 / 100.0)) {


				speedOfBall[0] = 1;
				flag_inner_paddle = 0;
				count = 0;

			}

			else if (positionOfBall[0] >= (xpaddleCurrentPosition[0]
					+ LENGTH_OF_PADDLE * 70 / 100.0) && positionOfBall[0]
					<= (xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE * 80/ 100.0))

			{

					speedOfBall[0] = 1;
					flag_inner_paddle =4;
					count = 0;


			}

			else if (positionOfBall[0] > (xpaddleCurrentPosition[0]
					+ LENGTH_OF_PADDLE * 80 / 100.0)
					&& positionOfBall[0] <= (xpaddleCurrentPosition[0]
							+ LENGTH_OF_PADDLE * 90 / 100.0)) {

				speedOfBall[0] = 1;
				flag_inner_paddle = 2;
				count =0;

			}

			else if (positionOfBall[0] > (xpaddleCurrentPosition[0]
					+ LENGTH_OF_PADDLE * 90 / 100.0) && positionOfBall[0]
					<= (xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE)) {

				speedOfBall[0] = 2;
				flag_inner_paddle = 8;
				count = 0;
			}
		return 1;
	}

	return 0;
}

int gameBallHItPaddle2(int *positionOfBall, int *xpaddle2CurrentPosition, int *speedOfBall){
	if ((positionOfBall[1] == (PADDLE_2_Y_AXIS_POSITION
								+ HEIGHT_OF_PADDLE_2 +1 )) || (positionOfBall[1] == (PADDLE_2_Y_AXIS_POSITION
										+ HEIGHT_OF_PADDLE_2 +2 )) && positionOfBall[0]
								>= xpaddle2CurrentPosition[0] && positionOfBall[0]
								<= xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE_2
								&& speedOfBall[1] <= 0) {


			speedOfBall[1] = -1;

			//Set x speed to -2
			if (positionOfBall[0] >= xpaddle2CurrentPosition[0] && positionOfBall[0]
					< (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE / 10.0)){

				speedOfBall[0] = -2;
				flag_inner_paddle = 7;
				count = 0;

			}

			//Set x speed to -1.5
			else if (positionOfBall[0] >= (xpaddle2CurrentPosition[0]
					+ LENGTH_OF_PADDLE / 10.0)
					&& positionOfBall[0] <= (xpaddle2CurrentPosition[0]
							+ LENGTH_OF_PADDLE * 20 / 100.0)) {


				speedOfBall[0] = -1;
				flag_inner_paddle = 1;
				count = 0;

			}

			//Set x speed to -1.2
			else if (positionOfBall[0] > (xpaddle2CurrentPosition[0]
					+ LENGTH_OF_PADDLE * 20 / 100.0) && positionOfBall[0]
					< (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE * 30/ 100.0))

			{
					speedOfBall[0] = -1;
					flag_inner_paddle = 3;
					count = 0;

			}

			//Set x speed to -1
			else if (positionOfBall[0] >= (xpaddle2CurrentPosition[0]
					+ LENGTH_OF_PADDLE * 30 / 100.0)
					&& positionOfBall[0] < (xpaddle2CurrentPosition[0]
							+ LENGTH_OF_PADDLE * 40 / 100.0)) {

				speedOfBall[0] = -1;
				flag_inner_paddle = 0;
				count = 0;

			}

			//Set x speed to 0.3/-0.3
			else if (positionOfBall[0] >= (xpaddle2CurrentPosition[0]
			         + LENGTH_OF_PADDLE / 40.0)
			         && positionOfBall[0] < (xpaddle2CurrentPosition[0]
			         + LENGTH_OF_PADDLE * 60 / 100.0)) {

				//Set x speed to 0.3
				if (speedOfBall[0] >= 0) {

					speedOfBall[0] = 0;
					flag_inner_paddle =5;
					count = 0;
				}

				//Set x speed to -0.3
				else {
					speedOfBall[0] = 0;
					flag_inner_paddle = 6;
					count = 0;
				}
			}

			else if (positionOfBall[0] >= (xpaddle2CurrentPosition[0]
						+ LENGTH_OF_PADDLE / 60.0)
						&& positionOfBall[0] < (xpaddle2CurrentPosition[0]
								+ LENGTH_OF_PADDLE * 70 / 100.0)) {


					speedOfBall[0] = 1;
					flag_inner_paddle = 0;
					count = 0;

				}

				else if (positionOfBall[0] >= (xpaddle2CurrentPosition[0]
						+ LENGTH_OF_PADDLE * 70 / 100.0) && positionOfBall[0]
						<= (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE * 80/ 100.0))

				{

						speedOfBall[0] = 1;
						flag_inner_paddle =4;
						count = 0;


				}

				else if (positionOfBall[0] > (xpaddle2CurrentPosition[0]
						+ LENGTH_OF_PADDLE * 80 / 100.0)
						&& positionOfBall[0] <= (xpaddle2CurrentPosition[0]
								+ LENGTH_OF_PADDLE * 90 / 100.0)) {

					speedOfBall[0] = 1;
					flag_inner_paddle = 2;
					count =0;

				}

				else if (positionOfBall[0] > (xpaddle2CurrentPosition[0]
						+ LENGTH_OF_PADDLE * 90 / 100.0) && positionOfBall[0]
						<= (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE)) {

					speedOfBall[0] = 2;
					flag_inner_paddle = 8;
					count = 0;
				}
			return 1;
		}

		return 0;
	}

void gameDrawNewBallAndPaddle2Player(alt_up_pixel_buffer_dma_dev* pixel_buffer,
		int *xpaddleCurrentPosition, int *positionOfBall,
		int *xpaddle2CurrentPosition) {
	printf("hello printing paddle \n");


	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddleCurrentPosition[0],
			PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition[0]
					+ LENGTH_OF_PADDLE, PADDLE_Y_AXIS_POSITION
					+ HEIGHT_OF_PADDLE, 0x586EB8, 1);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, positionOfBall[0],
			positionOfBall[1], positionOfBall[0] + BALL_WIDTH,
			positionOfBall[1] + BALL_HEIGHT, 0x586EB8, 1);
	alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, PADDLE_Y_AXIS_POSITION, PADDLE_Y_AXIS_POSITION
				+ HEIGHT_OF_PADDLE, 0x586EB8, 0);
		alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, PADDLE_Y_AXIS_POSITION, PADDLE_Y_AXIS_POSITION
					+ HEIGHT_OF_PADDLE, 0x586EB8, 1);
		alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, PADDLE_2_Y_AXIS_POSITION, PADDLE_Y_AXIS_POSITION
					+ HEIGHT_OF_PADDLE_2, 0x586EB8, 0);
			alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, PADDLE_2_Y_AXIS_POSITION, PADDLE_Y_AXIS_POSITION
						+ HEIGHT_OF_PADDLE_2, 0x586EB8, 1);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddle2CurrentPosition[0],
			PADDLE_2_Y_AXIS_POSITION, xpaddle2CurrentPosition[0]
					+ LENGTH_OF_PADDLE_2, PADDLE_2_Y_AXIS_POSITION
					+ HEIGHT_OF_PADDLE_2, 0x586EB8, 1);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
}
void gameDrawNewBallAndPaddle1Player(alt_up_pixel_buffer_dma_dev* pixel_buffer, int *xpaddleCurrentPosition, int *positionOfBall){


	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, xpaddleCurrentPosition[0],
				PADDLE_Y_AXIS_POSITION, xpaddleCurrentPosition[0]
						+ LENGTH_OF_PADDLE, PADDLE_Y_AXIS_POSITION
						+ HEIGHT_OF_PADDLE, 15, 1);
	alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, PADDLE_Y_AXIS_POSITION, PADDLE_Y_AXIS_POSITION
			+ HEIGHT_OF_PADDLE, 0x586EB8, 0);
	alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, SCREEN_WIDTH_MAX_PIXEL, PADDLE_Y_AXIS_POSITION, PADDLE_Y_AXIS_POSITION
				+ HEIGHT_OF_PADDLE, 0x586EB8, 1);
//	draw_paddle( pixel_buffer, xpaddleCurrentPosition);

		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, positionOfBall[0],
				positionOfBall[1], positionOfBall[0] + BALL_WIDTH,
				positionOfBall[1] + BALL_HEIGHT, 0x586EB8, 1);

		alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
		while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
				;
}
void gamePaddle2NewPosition( int *xpaddle2Speed, int *xpaddle2CurrentPosition ){
	char direction = getmovement(2);
	if ((direction == DIRECTION_LEFT))
									xpaddle2Speed[0] = XPADDLE_2_MOVE_LEFT_1_PIXEL
											* DEFAULT_SPEED_OF_PADDLE;
								else if ((direction == DIRECTION_RIGHT))
									xpaddle2Speed[0] = XPADDLE_2_MOVE_RIGHT_1_PIXEL
											* DEFAULT_SPEED_OF_PADDLE;
								else
									xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;



	//if the paddle is at the edge then do not let the user go in that direction anymore
			if (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE == SCREEN_WIDTH_MAX_PIXEL){
				if (xpaddle2Speed[0] > 0){
					xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;
				}
			}
			else if ( xpaddle2CurrentPosition[0] == SCREEN_WIDTH_MIN_PIXEL){
				if(xpaddle2Speed[0] < 0){
					xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;
				}
			}

			//Set new position of paddle only if the user between the screen
			if (xpaddle2CurrentPosition[0] + xpaddle2Speed[0] < SCREEN_WIDTH_MIN_PIXEL){
				xpaddle2CurrentPosition[0] = SCREEN_WIDTH_MIN_PIXEL + 1;
			}

			else if (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE + xpaddle2Speed[0]
					<= SCREEN_WIDTH_MAX_PIXEL  && xpaddle2CurrentPosition[0]
					+ xpaddle2Speed[0] >= SCREEN_WIDTH_MIN_PIXEL ){
				xpaddle2CurrentPosition[0] += xpaddle2Speed[0];
			}


	}
void gamePaddle2NewPosition_AI( int *xpaddle2Speed, int *xpaddle2CurrentPosition, int *positionOfBall, int *speedOfBall ){

if(positionOfBall[1] -3 > PADDLE_2_Y_AXIS_POSITION + HEIGHT_OF_PADDLE_2 && speedOfBall[1] < 0 )
{

	if(xpaddle2CurrentPosition[0] + (LENGTH_OF_PADDLE_2/2) > positionOfBall[0]  )
	{
		xpaddle2Speed[0] = XPADDLE_2_MOVE_LEFT_1_PIXEL
													* DEFAULT_SPEED_OF_PADDLE ;
	}
	else if(xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE_2 - (LENGTH_OF_PADDLE_2/2)  < positionOfBall[0])
	{
		xpaddle2Speed[0] = XPADDLE_2_MOVE_RIGHT_1_PIXEL
													* DEFAULT_SPEED_OF_PADDLE ;
	}
	else xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;

	//if the paddle is at the edge then do not let the user go in that direction anymore
				if (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE == SCREEN_WIDTH_MAX_PIXEL){
					if (xpaddle2Speed[0] > 0){
						xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;
					}
				}
				else if ( xpaddle2CurrentPosition[0] == SCREEN_WIDTH_MIN_PIXEL){
					if(xpaddle2Speed[0] < 0){
						xpaddle2Speed[0] = XPADDLE_2_DO_NOT_MOVE;
					}
				}

				//Set new position of paddle only if the user between the screen
				if (xpaddle2CurrentPosition[0] + xpaddle2Speed[0] < SCREEN_WIDTH_MIN_PIXEL){
					xpaddle2CurrentPosition[0] = SCREEN_WIDTH_MIN_PIXEL + 1;
				}

				else if (xpaddle2CurrentPosition[0] + LENGTH_OF_PADDLE + xpaddle2Speed[0]
						<= SCREEN_WIDTH_MAX_PIXEL  && xpaddle2CurrentPosition[0]
						+ xpaddle2Speed[0] >= SCREEN_WIDTH_MIN_PIXEL ){
					xpaddle2CurrentPosition[0] += xpaddle2Speed[0];
				}
	}
}



void gamePaddle1NewPosition(int *xpaddleSpeed, int *xpaddleCurrentPosition ){
		char direction = getmovement(1);
		if(flip==0){
		if ((direction == DIRECTION_LEFT)
				|| (direction == DIRECTION_UP))
			xpaddleSpeed[0] = XPADDLE_MOVE_LEFT_1_PIXEL
					* DEFAULT_SPEED_OF_PADDLE;
		else if ((direction == DIRECTION_RIGHT) || (direction
				== DIRECTION_DOWN))
			xpaddleSpeed[0] = XPADDLE_MOVE_RIGHT_1_PIXEL
					* DEFAULT_SPEED_OF_PADDLE;
		else
			xpaddleSpeed[0] = XPADDLE_DO_NOT_MOVE;
		}
		else
		{
			if ((direction == DIRECTION_LEFT)
					|| (direction == DIRECTION_UP))
				xpaddleSpeed[0] = XPADDLE_MOVE_RIGHT_1_PIXEL
						* DEFAULT_SPEED_OF_PADDLE;
			else if ((direction == DIRECTION_RIGHT) || (direction
					== DIRECTION_DOWN))
				xpaddleSpeed[0] = XPADDLE_MOVE_LEFT_1_PIXEL
						* DEFAULT_SPEED_OF_PADDLE;
			else
				xpaddleSpeed[0] = XPADDLE_DO_NOT_MOVE;
		}

		//if the paddle is at the edge then do not let the user go in that direction anymore
		if (xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE == SCREEN_WIDTH_MAX_PIXEL){
			if (xpaddleSpeed[0] > 0){
				xpaddleSpeed[0] = XPADDLE_DO_NOT_MOVE;
			}
		}
		else if ( xpaddleCurrentPosition[0] == SCREEN_WIDTH_MIN_PIXEL){
			if(xpaddleSpeed[0] < 0){
				xpaddleSpeed[0] = XPADDLE_DO_NOT_MOVE;
			}
		}


		//Set new position of paddle only if the user between the screen
		if (xpaddleCurrentPosition[0] + xpaddleSpeed[0] < SCREEN_WIDTH_MIN_PIXEL){
			xpaddleCurrentPosition[0] = SCREEN_WIDTH_MIN_PIXEL + 1;
		}

		else if (xpaddleCurrentPosition[0] + LENGTH_OF_PADDLE + xpaddleSpeed[0]
				<= SCREEN_WIDTH_MAX_PIXEL  && xpaddleCurrentPosition[0]
				+ xpaddleSpeed[0] >= SCREEN_WIDTH_MIN_PIXEL ){
			xpaddleCurrentPosition[0] += xpaddleSpeed[0];
		}
}


int ballHitSideWalls(int *positionOfBall, int *speedOfBall){
	if (positionOfBall[0] + speedOfBall[0] <= SCREEN_WIDTH_MIN_PIXEL + 1
								|| positionOfBall[0] + speedOfBall[0] >= SCREEN_WIDTH_MAX_PIXEL - 1
										- BALL_WIDTH) {
							speedOfBall[0] = speedOfBall[0] * -1;
							return 1;
	}
	return 0;
}

int ballHitsTopWall(int *positionOfBall, int *speedOfBall){
	if (positionOfBall[1] + speedOfBall[1] <= SCREEN_HEIGHT_MIN_PIXEL
								+ BALL_HEIGHT + LEVEL_MIN_HEIGHT) {
							// play_wav(temp_array, audio_dev);

							speedOfBall[1] = speedOfBall[1] * -1;
							return 1;
	}
	return 0;
}

void cycleBallSpeedX(int *positionOfBall, int *speedOfBall) {

		if(flag_inner_paddle == 1) {

			if (speedOfBall[0] == -1){
			speedOfBall[0] = -2;
			}
			else if (speedOfBall[0] == -2){
			speedOfBall[0] = -1;
		 }
		}

			else if(flag_inner_paddle == 2) {

				if (speedOfBall[0] == 1) {
					speedOfBall[0] = 2; }

				else if (speedOfBall[0] == 2) {
					speedOfBall[0] = 1; }
			}

			else if(flag_inner_paddle == 3 ) {

				if(count < 4) {
					count++;
					return;
				}
				else if (speedOfBall[0] == -1) {
					speedOfBall[0] = -2; }

				else if (speedOfBall[0] == -2) {
					speedOfBall[0] = -1;
					count = 0;
				}
			}
			else if(flag_inner_paddle == 4) {

				if(count < 4) {
					count++;
					return;
				}
				else if (speedOfBall[0] == 1) {
					speedOfBall[0] = 2; }

				else if (speedOfBall[0] == 2) {
					speedOfBall[0] = 1;
					count = 0;
				}
			}
			else if(flag_inner_paddle == 5) {

				if(count < 3) {
					count++;
					return;
				}
				else if (speedOfBall[0] == 0) {
					speedOfBall[0] = 1; }

				else if (speedOfBall[0] == 1) {
					speedOfBall[0] = 0;
					count = 0;
				}
			}

			else if(flag_inner_paddle == 6) {

				if(count < 3) {
					count++;
					return;
				}
				else if (speedOfBall[0] == 0) {
					speedOfBall[0] = -1; }

				else if (speedOfBall[0] == -1) {
					speedOfBall[0] = 0;
					count = 0;
				}
			}
}

void cycleBallSpeedY(int *positionOfBall, int *speedOfBall) {

		if(flag_inner_paddle == 7) {

			if (speedOfBall[1] == -1){
			speedOfBall[1] = -2;
			}
			else if (speedOfBall[1] == -2){
			speedOfBall[1] = -1;
		 }
		}

			else if(flag_inner_paddle == 8) {

				if (speedOfBall[1] == -1) {
					speedOfBall[1] = -2; }

				else if (speedOfBall[1] == -2) {
					speedOfBall[1] = -1; }
			}

		if(flag_inner_paddle == 5) {

			if (speedOfBall[1] == -1){
			speedOfBall[1] = -2;
			}
			else if (speedOfBall[1] == -2){
			speedOfBall[1] = -1;
		 }
		}

			else if(flag_inner_paddle == 6) {

				if (speedOfBall[1] == -1) {
					speedOfBall[1] = -2; }

				else if (speedOfBall[1] == -2) {
					speedOfBall[1] = -1; }
			}
}
