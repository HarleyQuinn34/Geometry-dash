#include<allegro5\allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include <iostream>
using namespace std;

//GLOBALS and constants
const int WIDTH = 700;
const int HEIGHT = 700;
bool keys[] = { false, false, false, false };
enum KEYS { UP, DOWN, LEFT, RIGHT };
bool doexit = false;
const int picture1_SIZE = 32;

//the map! 10 ROWS, 100 COLUMNS!
//legend: 1 = triangle, 2= platform

int map[10][100] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,1,2,2,1,2,2,1,2,2,1,2,2,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1,1,0,0,0,1,0,0,1,0,0,0
};

//function declaration
int collide(int x, int y, int map[10][100], int mapoffset);

int main()
{
	//game variables
	bool done = false;
	bool render = false;

	//allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *picture1 = NULL; //just sets up an empty variable to hold the pic
	ALLEGRO_BITMAP *square = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *sample2Instance = NULL;
	ALLEGRO_SAMPLE_INSTANCE *sample1Instance = NULL;
	//player vaiables
	float square_x = 32;
	float square_y = 65;
	float dx = 0;
	float dy = 0;
	bool doexit = false;

	double  picture1_x = 700;
	double  picture1_y = 100;

	// is true if the player is on the ground
	bool isOnSolidGround = false;
	bool mayjumpagain = false;
	//variable for map scrolling
	int mapoffset = -550;
	//program setup
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_install_audio();
	picture1 = al_load_bitmap("geo bg.jpg"); //this should be in your program folder
	al_convert_mask_to_alpha(picture1, al_map_rgb(255, 255, 255));

	//set up player
	square = al_create_bitmap(70, 70);
	al_set_target_bitmap(square);
	al_clear_to_color(al_map_rgb(255, 255, 255));


	//set up game stuff: display, event queue, timer, etc.
	display = al_create_display(WIDTH, HEIGHT);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	//////////////////////////////////////////////         SOUND
	al_reserve_samples(2);
	sample = al_load_sample("oof.wav");
	sample2 = al_load_sample("bg.wav");
	if (sample2 == NULL)cout << "oop";
	sample1Instance = al_create_sample_instance(sample2);
	al_set_sample_instance_playmode(sample1Instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(sample1Instance, al_get_default_mixer());

	sample2Instance = al_create_sample_instance(sample);
	al_set_sample_instance_playmode(sample2Instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(sample2Instance, al_get_default_mixer());
	////////////////////////////////////////////////////////////////////////////////
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	al_play_sample_instance(sample1Instance);
	//GAME LOOP
	while (!done)
	{


		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		//Keyboard Section////////////////////////////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)

		{
			//cout << "key pressed";
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;


			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;

				break;

			}
		}
		//TIMER SECTION/////////////////////////////////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			//player movement

			//scroll the map
			mapoffset += 5;
			if (mapoffset > 230 * 30)//this loops the map
				mapoffset = -250;

			//stop falling when you hit the bottom.
			if (square_y + 70 >= HEIGHT) {
				square_y = HEIGHT - 70;
				dy = 0;
				isOnSolidGround = true;
			}
			else {
				isOnSolidGround = false;
			}

			//stop falling if you're on a platform
			if (collide(square_x, square_y, map, mapoffset) == 2) {
				isOnSolidGround = true;
				dy = 0;
				//mapoffset = -550;
				cout << "platform collide";
			}

			if (collide(square_x, square_y, map, mapoffset) == 1) {
				square_x = 0;
				square_y = 0;
				mapoffset = -550;
				al_play_sample_instance(sample2Instance);
				cout << "oof" << endl;
			}

			//here's my check to stop my square from walking off the window (left, right, and top sides)
			if (square_x > WIDTH - 15)
				square_x = WIDTH - 15;
			if (square_x < 0)
				square_x = 0;
			if (square_y < 0)
				square_y = 0;


			//JUMPING
			//if the up button is pressed, increase y velocity until "jumping" runs out
			if (keys[UP] && isOnSolidGround == true && mayjumpagain == true) {
				dy = -14.0;
				mayjumpagain = false;

			}
			else
				mayjumpagain = true;

			//should we turn off left and right movement?
			//left

			////right

			//1111110011
			//gravity
			//if we're not on solid ground, we should be falling (remember, positive y is "down")
			//I changed this to gravity only happens if we let go of the up key...
			if (isOnSolidGround == false) {
				dy += .7;

			}

			//put a cap on how fast you can fall
			if (dy > 8)
				dy = 8;

			render = true;
		}

		//here's where your box's coordinates are acutally updated
		square_x += dx; //adding the component velocities to the actual positions
		square_y += dy;
		//cout << "dy is " << dy << " , square_y is " << square_y << endl;


		//RENDER SECTION//////////////////////////////////////////////////////////////////////
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(picture1, picture1_x, picture1_y, 0); //draws the image

																 //draw map
																 //remember, i is rows, j is columns
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 100; j++) {


					//ISAIAH! YOu had 50s here. if you have a game screen that's 700 tall and sliced into 10 rows, each row is 70 pixels high
					if (map[i][j] == 1)//platforms
						al_draw_filled_triangle(j * 70 - mapoffset, i * 70 + 70, j * 70 + 70 - mapoffset, i * 70 + 70, j * 70 + 70 - mapoffset, i * 70 - 15, al_map_rgb(80, 220, 120));
					else if (map[i][j] == 2) {//platforms
						al_draw_filled_rectangle(j * 70 - mapoffset, i * 70 + 70, j * 70 + 70 - mapoffset + 50, i * 70 + 70 + 30, al_map_rgb(255, 0, 0));
						//cout << "trying to print platform." << endl;
					}
				}
			}

			//draw player
			al_draw_bitmap(square, square_x, square_y, 0);


			al_flip_display();

		}
		//cout << "game loop" << endl;
	}//end game loop

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}

int collide(int x, int y, int map[10][100], int mapoffset) {
	//cout << "checkign map slot " << (x + 30 + 5 + offset) / 30 << " , " << (y + 30) / 30 << endl;



	//check for platform collision
	//check bottom right corner

	if ((map[(y + 30 + 2) / 70][(x + 30 + mapoffset) / 70] == 1)

		//check bottom left corner
		|| (map[(y + 30 + 5) / 70][(x + mapoffset) / 70] == 1)) {
		cout << "triangle collision (death)";
		return 1;
	}
	else if (
		//check bottom right corner
		(map[(y + 30 + 2) / 70][(x + 30 + mapoffset) / 70] == 2)

		//check bottom left corner
		|| (map[(y + 30 + 5) / 70][(x + mapoffset) / 70] == 2)) {
		cout << "platform collision.";
		return 2;
	}
	else
		cout << "ruh roh" << endl;
	return 3;

}