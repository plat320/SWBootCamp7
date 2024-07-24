#include "snake.h"
#include "device_driver.h"
#include <stdlib.h>

static int snaek_mutex_id = -1;

void Snake_Init(void)
{
	int i, j;
	for (i = 1; i < GAME_WINDOW_ROW - 1; i++)
	{
		for (j = 1; j < GAME_WINDOW_COL - 1; j++)
		{
			snake_object.object_map[i][j] = EMPTY_ID;
		}
	}

	for (i = 0; i < GAME_WINDOW_ROW; i++)
	{
		snake_object.object_map[i][0] = BORDER_ID;
		snake_object.object_map[0][i] = BORDER_ID;
		snake_object.object_map[i][GAME_WINDOW_ROW-1] = BORDER_ID;
		snake_object.object_map[GAME_WINDOW_ROW-1][i] = BORDER_ID;
	}

//	Uart_Printf("===================\n");
//	for (i = 0; i < GAME_WINDOW_ROW; i++)
//	{
//		for (j = 0; j < GAME_WINDOW_COL; j++)
//		{
//			Uart_Printf("%d", snake_object.object_map[i][j]);
//		}
//		Uart_Printf("\n");
//	}
//	Uart_Printf("===================\n");

	snake_object.snake_head_dir = KEY_RIGHT;
	snake_object.snake_head_dir_pre = KEY_RIGHT;

	snake_object.queue_no = OS_Create_Queue(sizeof(POINT), SNAKE_MAX_LENGTH);

	POINT p1 = {4,5};		// tail - front
	POINT p2 = {5,5};		// head - rear
	POINT p3 = {-1,-1};
	enqueue(&queues[snake_object.queue_no], &p1);
	enqueue(&queues[snake_object.queue_no], &p2);
	snake_object.snake_head_pos = *((POINT*)queues[snake_object.queue_no].rear->data);
	snake_object.snake_tail_pos = p3;
	//Uart_Printf_From_Task("*** snake_object.queue_no: %d\n", snake_object.queue_no);

	snake_object.object_map[p1.y][p1.x] = SNAKE_ID;
	snake_object.object_map[p2.y][p2.x] = SNAKE_ID;

	Mutex_Init();
	snaek_mutex_id = Create_Mutex();

	Make_Target();
	draw_init();
	Lcd_Draw_Snake();
}

void draw_init(){
	Lcd_Draw_Border();
	Lcd_Draw_Grass();
}

void Lcd_Draw_Grass(){

	int i, j;

	// draw grass

    for ( i = 1; i < GAME_WINDOW_HIGHT / OBJECT_BLOCK_SIZE -1; i++) {

        for (j = 1; j < GAME_WINDOW_WIDTH / OBJECT_BLOCK_SIZE -1; j++) {

            Lcd_Draw_IMG(j*OBJECT_BLOCK_SIZE, i*OBJECT_BLOCK_SIZE,  20,  20,  grass_img);

        }

    }

    // draw score apple

    Lcd_Draw_IMG(13*OBJECT_BLOCK_SIZE+3, 1*OBJECT_BLOCK_SIZE,  40,  40,  big_apple_img);
}

void Lcd_Draw_Border(void){
	int i;
	for (i = 0; i < GAME_WINDOW_ROW; i++)
	{
		Lcd_Draw_Box(i * OBJECT_BLOCK_SIZE, 0, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
		Lcd_Draw_Box(0, i * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
		Lcd_Draw_Box(i * OBJECT_BLOCK_SIZE, (GAME_WINDOW_ROW - 1) * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
		Lcd_Draw_Box((GAME_WINDOW_ROW - 1) * OBJECT_BLOCK_SIZE, i * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
	}
}

void Lcd_Draw_Snake(void){
	Node* node = queues[snake_object.queue_no].rear;
	int head_dir = snake_object.snake_head_dir;
	int tail_pos_x = snake_object.snake_tail_pos.x;
	int tail_pos_y = snake_object.snake_tail_pos.y;
	int prev_head_pos_x;
	int prev_head_pos_y;
	int first_digit = snake_object.score%10;
	int second_digit = snake_object.score/10;
	u8* s = "Game Over";

	unsigned short rotated_head_img[400];

	// draw curr head  => ��Ӹ�
	POINT* p = (POINT*)node->data;

	rotate_image_array(snake_head_img, rotated_head_img, head_dir);
	Lcd_Draw_IMG(p->x*OBJECT_BLOCK_SIZE, p->y*OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE,  rotated_head_img);

	// draw prev head
	switch(head_dir){
	case KEY_UP:
		prev_head_pos_x = p->x;
		prev_head_pos_y = p->y +1;
		break;
	case KEY_DOWN:
		prev_head_pos_x = p->x;
		prev_head_pos_y = p->y -1;
		break;
	case KEY_RIGHT:
		prev_head_pos_x = p->x-1;
		prev_head_pos_y = p->y;
		break;
	case KEY_LEFT:
		prev_head_pos_x = p->x+1;
		prev_head_pos_y = p->y;
		break;
	default:
		Uart_Printf("WRONG KEY VALUE\n");
		return;
	}

	Lcd_Draw_Box(prev_head_pos_x*OBJECT_BLOCK_SIZE, prev_head_pos_y*OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE,  SNAKE_COLOR);

	// draw grass
	if (tail_pos_x != -1 && tail_pos_y != -1) {
		Lcd_Draw_IMG(tail_pos_x*OBJECT_BLOCK_SIZE, tail_pos_y*OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE,  grass_img);
	}
	// ��� ���� ��Ȳ�� �� draw apple
	else
	{
		Lcd_Draw_IMG(snake_object.snake_target_pos.x*OBJECT_BLOCK_SIZE, snake_object.snake_target_pos.y*OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE,  OBJECT_BLOCK_SIZE, apple_img);

		LCD_Show_Char(14 *OBJECT_BLOCK_SIZE+5, 3 *OBJECT_BLOCK_SIZE+5, 0x07e0,  0,  0x30 + first_digit, 16, 1);

		LCD_Show_Char(13 *OBJECT_BLOCK_SIZE+5, 3 *OBJECT_BLOCK_SIZE+5, 0x07e0,  0,  0x30 + second_digit, 16, 1);

		//LCD_Show_String(13 *OBJECT_BLOCK_SIZE, 5 *OBJECT_BLOCK_SIZE, 0x07e0,  0, 16, s, 1);

	}
}

void rotate_image_array(const unsigned short* image_array, unsigned short *temp, int direction) {
    int i, j;

    // direction ���� ���� ȸ�� ������ ����
    switch (direction) {
        case KEY_DOWN: // direction = 0�� �� (���� ����, ����)
            for (i = 0; i < OBJECT_BLOCK_SIZE; i++) {
                for (j = 0; j < OBJECT_BLOCK_SIZE; j++) {
                    temp[i*OBJECT_BLOCK_SIZE+j] = image_array[i*OBJECT_BLOCK_SIZE+j];
                }
            }
            break;
        case KEY_LEFT: // direction = 1�� �� (�ð� �������� 90�� ȸ��, ����)
            for (i = 0; i < OBJECT_BLOCK_SIZE; i++) {
                for (j = 0; j < OBJECT_BLOCK_SIZE; j++) {
                    temp[OBJECT_BLOCK_SIZE*j+OBJECT_BLOCK_SIZE - 1 - i] = image_array[OBJECT_BLOCK_SIZE*i+OBJECT_BLOCK_SIZE+j];
                }
            }
            break;
        case KEY_UP: // direction = 2�� �� (180�� ȸ��, �Ʒ���)
            for (i = 0; i < OBJECT_BLOCK_SIZE; i++) {
                for (j = 0; j < OBJECT_BLOCK_SIZE; j++) {
                    temp[(OBJECT_BLOCK_SIZE - 1 - i)*OBJECT_BLOCK_SIZE + OBJECT_BLOCK_SIZE - 1 - j] = image_array[i*OBJECT_BLOCK_SIZE+j];
                }
            }
            break;
        case KEY_RIGHT: // direction = 3�� �� (�ݽð� �������� 90�� ȸ��, ����)
            for (i = 0; i < OBJECT_BLOCK_SIZE; i++) {
                for (j = 0; j < OBJECT_BLOCK_SIZE; j++) {
                    temp[(OBJECT_BLOCK_SIZE - 1 - j)*OBJECT_BLOCK_SIZE+i] = image_array[i*OBJECT_BLOCK_SIZE+j];
                }
            }
            break;
        default: // �� ���� ���
//            printf("�߸��� �����Դϴ�.\n");
            return;
    }

    return;

//    // ȸ���� �̹����� ���� �̹��� �迭�� ����
//    for (i = 0; i < OBJECT_BLOCK_SIZE; i++) {
//        for (j = 0; j < OBJECT_BLOCK_SIZE; j++) {
//        	image_array[i*OBJECT_BLOCK_SIZE+j] = temp[i*OBJECT_BLOCK_SIZE+j];
//        }
//    }
}



void Add_Snake_Position(POINT* p)
{
	enqueue(&queues[snake_object.queue_no], p);
	snake_object.object_map[p->y][p->x] = SNAKE_ID;
//	Lcd_Draw_Box(p->x * OBJECT_BLOCK_SIZE, p->y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, SNAKE_COLOR);
}

void Remove_Snake_Position(void)
{
	POINT p;
	int ret = dequeue(&queues[snake_object.queue_no], &p, HAVE_PERMISSION);
	if (ret != DEQUEUE_SUCCESS)
	{
		Uart_Printf("Dequeue fail!\n");
	}
	snake_object.object_map[p.y][p.x] = EMPTY_ID;
//	Lcd_Draw_Box(p.x * OBJECT_BLOCK_SIZE, p.y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BACKGROUND_COLOR);
}

void Move_Snake_Position(int received_head_dir)
{
//	Uart_Printf("Move_Snake_Position Start\n");
	POINT* head_position = (POINT*)queues[snake_object.queue_no].rear->data;
	POINT new_head_position = {head_position -> x, head_position -> y};
//	POINT tail_position;

	// Task 1���� �̵�
	// ���� �� ���� ������ �ݴ� ������ �Է����� ������ �����ϰ� �׷��� ���� ��쿡�� �Է°����� ���� ������Ʈ
//	if (received_head_dir * snake_object.snake_head_dir != KEY_UP * KEY_DOWN
//			&& received_head_dir * snake_object.snake_head_dir != KEY_LEFT * KEY_RIGHT)
//	{
//		snake_object.snake_head_dir = received_head_dir;
//	}

	if (snake_object.snake_head_dir == KEY_UP)
	{
		new_head_position.y -= 1;
	}
	else if (snake_object.snake_head_dir == KEY_DOWN)
	{
		new_head_position.y += 1;
	}
	else if (snake_object.snake_head_dir == KEY_LEFT)
	{
		new_head_position.x -= 1;
	}
	else if (snake_object.snake_head_dir == KEY_RIGHT)
	{
		new_head_position.x += 1;
	}
//	Uart_Printf("before enqueue\n");
//	enqueue(&queues[snake_object.queue_no], &new_head_position);
//	Uart_Printf("after enqueue\n");
//	int ret = dequeue(&queues[snake_object.queue_no], &tail_position, HAVE_PERMISSION);
//	Uart_Printf("ret: %d\n", ret);
//	Uart_Printf("after dequeue\n");

	snake_object.snake_head_dir_pre = snake_object.snake_head_dir;

	int ret = Check_Snake_Position(new_head_position);

	if (ret == TARGET_ID)
	{
		POINT p = {-1,-1};
		snake_object.snake_head_pos = new_head_position;
		snake_object.snake_tail_pos = p;

		Add_Snake_Position(&new_head_position);
//		Remove_Snake_Position();
	}
	else if (ret == EMPTY_ID)
	{
		snake_object.snake_head_pos = new_head_position;
		snake_object.snake_tail_pos = *((POINT*)queues[snake_object.queue_no].front->data);

		Add_Snake_Position(&new_head_position);
		Remove_Snake_Position();
	}

//	snake_object.snake_head_pos = new_head_position;
//	snake_object.snake_tail_pos = *((POINT*)queues[snake_object.queue_no].front->data);
//
//	Add_Snake_Position(&new_head_position);
//	Remove_Snake_Position();

//	Lcd_Draw_New_Position(&new_head_position, &tail_position);
//	Uart_Printf("Move_Snake_Position End\n");
}

// �̵� ������ ��ġ Ȯ��
int Check_Snake_Position(POINT p)
{
	// TODO: Game Over
	// object map ���� �ʰ�
	if (p.x < 0 || p.x >= GAME_WINDOW_ROW || p.y < 0 || p.y >= GAME_WINDOW_COL)
	{
		Uart_Printf("Game Over!!\n");
		// Timer stop
		TIM4_Repeat_Interrupt_Enable(0, 600);
		return -1;
	}

//	int i, j;
//	Uart_Printf("===================\n");
//	for (i = 0; i < GAME_WINDOW_ROW; i++)
//	{
//		for (j = 0; j < GAME_WINDOW_COL; j++)
//		{
//			Uart_Printf("%d", snake_object.object_map[i][j]);
//		}
//		Uart_Printf("\n");
//	}
//	Uart_Printf("===================\n");

//	Uart_Printf("Check_Snake_Position\n");
//	Uart_Printf("snake_object.object_map[p.y][p.x]: %d\n", snake_object.object_map[p.y][p.x]);
//	Uart_Printf("p.y: %d, p.x: %d\n", p.y, p.x);

	switch (snake_object.object_map[p.y][p.x])
	{
		case SNAKE_ID:
			// TODO: Game over
			Uart_Printf("Game Over!!\n");
			// Timer stop
			TIM4_Repeat_Interrupt_Enable(0, 600);
			return SNAKE_ID;
		case BORDER_ID:
			// TODO: Game over
			Uart_Printf("Game Over!!\n");
			// Timer stop
			TIM4_Repeat_Interrupt_Enable(0, 600);
			return BORDER_ID;
		case TARGET_ID:
//			Uart_Printf("**************** ���� ���Գ�\n");
			snake_object.score += 1;
			Uart_Printf("score: %d\n", snake_object.score);
			Make_Target();
			return TARGET_ID;
		default:
			return EMPTY_ID;
	}
}

//void Lcd_Draw_New_Position(POINT* head_position, POINT* tail_position)
//{
////	Uart_Printf("Lcd_Draw_New_Position Start\n");
//	Lcd_Draw_Box(head_position->x * OBJECT_BLOCK_SIZE, head_position->y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, SNAKE_COLOR);
//	Lcd_Draw_Box(tail_position->x * OBJECT_BLOCK_SIZE, tail_position->y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BACKGROUND_COLOR);
////	Uart_Printf("Lcd_Draw_New_Position End\n");
//}

//void Calculate_Snake_Position(int head_direction)
//{
//	// TODO: ���� �ִ� ���� �ݴ� �������� ��ȯ�ϸ� ����
////	Uart_Printf("Calculate_Snake_Position Start\n");
//	POINT* head_position = (POINT*)queues[snake_object.queue_no].rear->data;
//	POINT new_head_position = {head_position -> x, head_position -> y};
////	POINT tail_position;
//	if (head_direction == KEY_UP)
//	{
//		new_head_position.y -= 1;
//	}
//	else if (head_direction == KEY_DOWN)
//	{
//		new_head_position.y += 1;
//	}
//	else if (head_direction == KEY_LEFT)
//	{
//		new_head_position.x -= 1;
//	}
//	else if (head_direction == KEY_RIGHT)
//	{
//		new_head_position.x += 1;
//	}
////	Uart_Printf("before enqueue\n");
////	enqueue(&queues[snake_object.queue_no], &new_head_position);
////	Uart_Printf("after enqueue\n");
////	int ret = dequeue(&queues[snake_object.queue_no], &tail_position, HAVE_PERMISSION);
////	Uart_Printf("ret: %d\n", ret);
////	Uart_Printf("after dequeue\n");
//
//	Add_Snake_Position(&new_head_position);
//	Remove_Snake_Position();
////	Lcd_Draw_New_Position(&new_head_position, &tail_position);
////	Uart_Printf("Calculate_Snake_Position End\n");
//}

void Make_Target(void)
{
//	srand(time(NULL));  // ���� �ʱ�ȭ
	int i, j;
	int validCount = 0;

//	typedef struct {
//		int row;
//		int column;
//	} Position;

//	Position valid_map[GAME_WINDOW_ROW * GAME_WINDOW_COL];
	POINT valid_map[GAME_WINDOW_ROW * GAME_WINDOW_COL];

	for (i=1; i<GAME_WINDOW_ROW - 1; i++){
		for (j=1; j<GAME_WINDOW_COL - 1; j++){
			if (snake_object.object_map[i][j] == EMPTY_ID) {
//				valid_map[validCount].row = i;
//				valid_map[validCount].column = j;
				valid_map[validCount].y = i;
				valid_map[validCount].x = j;
				++validCount;
			}
		}
	}
	// ��ȿ�� ��ġ�� �ϳ��� ���� ���
	if (validCount == 0) {
		return ;				// ���� Ŭ����
	}
	// �������� �ε��� ����
	int randomIndex = rand() % validCount;
	snake_object.object_map[valid_map[randomIndex].y][valid_map[randomIndex].x] = TARGET_ID;
	snake_object.snake_target_pos.y = valid_map[randomIndex].y;
	snake_object.snake_target_pos.x = valid_map[randomIndex].x;

	Uart_Printf_From_Task("rand_row: %d\n", valid_map[randomIndex].y);
	Uart_Printf_From_Task("rand_column: %d\n", valid_map[randomIndex].x);
//	Lcd_Draw_IMG(valid_map[randomIndex].column * OBJECT_BLOCK_SIZE, valid_map[randomIndex].row * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, apple_img);

//	srand(time(NULL));  // ���� �ʱ�ȭ
//	int rand_row, rand_column;
//	for (;;)
//	{
//		rand_row = rand() % GAME_WINDOW_ROW;
//		rand_column = rand() % GAME_WINDOW_COL;
//		if (snake_object.object_map[rand_row][rand_column] == EMPTY_ID)
//		{
//			break;
//		}
//	}
//	Uart_Printf("rand_row: %d\n", rand_row);
//	Uart_Printf("rand_column: %d\n", rand_column);
//	snake_object.object_map[rand_row][rand_column] = TARGET_ID;
//
//	POINT p = {rand_column, rand_row};
//	snake_object.snake_target_pos = p;

//	Uart_Printf("snake_object.object_map[rand_row][rand_column]: %d\n", snake_object.object_map[rand_row][rand_column]);

//	Lcd_Draw_Box(rand_column * OBJECT_BLOCK_SIZE, rand_row * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, TARGET_COLOR);
}

void Lcd_Draw_IMG(int xs,  int ys,  int w,  int h,  unsigned short *img)
{
	Take_Mutex(snaek_mutex_id, TASK_RELATED);
	unsigned int i;
	int xe, ye;
	xe = xs+w-1;
	ye = ys+h-1;
	if(xe >= 320) xe=319;
	if(ye >= 240) xe=239;

	Lcd_Set_Windows(xs,  ys,  xe,  ye);

	Lcd_CS_EN();
	Lcd_RS_REG();

	for(i=0; i < (xe - xs + 1) * (ye - ys + 1); i++)
	{
		_SPI1_Write_Byte(*img >> 8);
		_SPI1_Write_Byte(*img & 0xFF);
		img++;
	}

	Lcd_CS_DIS();
	Give_Mutex(snaek_mutex_id, TASK_RELATED);
}