#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

using namespace std;
const int W = 800;
const int H = 600;
const int FPS = 60;
int nivel=1;
enum KEYS { LEFT, RIGHT, SPACE,ENTER};
bool keys[3] = { false, false, false};

int pe[6]={100,400,400,775,150,500};

bool ped[6]={true,false,true,false,true,false};
int vel[2]={3,6};

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	if (y1 + h1 < y2
		|| y1 > y2 + h2
		|| x1 + w1 < x2
		|| x1 > x2 + w2) return false;
	return true;
}

class player {
	public:
		int x;
		int y;
		int w;
		int h;
		int hp;
		bool dead;
		int score;
		int speed;
		player(int x, int y)
		{
			this->x = x;
			this->y = y;
			this->hp = 3;
			this->dead = false;
			this->speed = 4;
			this->w = 45;
			this->h = 35;
			this->score = 0;
			this->speed=4;
		}

		void moveleft()
		{
			this->x -= speed;
			if ((this->x < 0) && (dead == false))
				this->x = 0;
		}

		void moveright()
		{
			this->x += speed;
			if ((this->x > W - this->w) && (dead==false))
			{	this->x = W - this->w;}
		}

		void print()
		{
			if (hp < 1)
			{
				dead = true;
			}

			if (dead == false)
			{
				//color(AZUL);
				al_draw_filled_rectangle(x, y, 5 + x, 20 + y, al_map_rgb(2, 65, 246));
				al_draw_filled_rectangle(5 + x, y - 5, 10 + x, 15 + y, al_map_rgb(2, 65, 246));
				al_draw_filled_rectangle(10 + x, y - 10, 15 + x, 10 + y, al_map_rgb(2, 65, 246));
				//color(VERDE);
				al_draw_filled_rectangle(15 + x, 5 + y, 20 + x, y - 5, al_map_rgb(2, 227, 99));
				al_draw_filled_rectangle(20 + x, 5 + y, 25 + x, y - 15, al_map_rgb(2, 227, 99));
				al_draw_filled_rectangle(25 + x, 5 + y, 30 + x, y - 5, al_map_rgb(2, 227, 99));
				//color(ROJO);
				al_draw_filled_rectangle(15 + x, 5 + y, 20 + x, 15 + y, al_map_rgb(255, 0, 0));
				al_draw_filled_rectangle(20 + x, 5 + y, 25 + x, 10 + y, al_map_rgb(255, 0, 0));
				al_draw_filled_rectangle(25 + x, 5 + y, 30 + x, 15 + y, al_map_rgb(255, 0, 0));
				//color(AZUL);
				al_draw_filled_rectangle(30 + x, y - 10, 35 + x, 10 + y, al_map_rgb(2, 65, 246));
				al_draw_filled_rectangle(35 + x, y - 5, 40 + x, 15 + y, al_map_rgb(2, 65, 246));
				al_draw_filled_rectangle(40 + x, y, 45 + x, 20 + y, al_map_rgb(2, 65, 246));
			}
		}


};

class enemigo {
public:
		int x;
		int y;
		int w;
		int h;
		bool dead;
		int speed;
		bool d;
		int count;

		enemigo(int x, int y,bool d,int speed)
		{
			this->x = x;
			this->y = y;
			this->w = 35;
			this->h = 30;
			this->dead = false;
			this->speed = speed;
			this->d = d;
			this->count=0;
		}

		void move() {

			count++;

			if ((this->x < 0) && (d==false) && (dead==false))
			{
				d = true;
			}
			else if ((this->x > W - this->w) && (d == true) && (dead == false))
			{
				d = false;
			}

			if (d == false)
			{
				this->x -= speed;
			}
			else
			{
				this->x += speed;
			}
		}

		void print()
		{
			if (dead == false)
			{
				//color(AZUL);
				al_draw_filled_rectangle(x, y, 5 + x, 15 + y, al_map_rgb(2, 65, 246));
				al_draw_filled_rectangle(30 + x, y, 35 + x, 15 + y, al_map_rgb(2, 65, 246));

				//color_rgb(255, 164, 32);
				al_draw_filled_rectangle(5 + x, y, 10 + x, 10 + y, al_map_rgb(255, 164, 32));
				al_draw_filled_rectangle(10 + x, y - 5, 15 + x, y + 5, al_map_rgb(255, 164, 32));
				al_draw_filled_rectangle(15 + x, y - 10, 20 + x, y, al_map_rgb(255, 164, 32));
				al_draw_filled_rectangle(20 + x, y - 5, 25 + x, 5 + y, al_map_rgb(255, 164, 32));
				al_draw_filled_rectangle(25 + x, y, 30 + x, 10 + y, al_map_rgb(255, 164, 32));
				al_draw_filled_rectangle(15 + x, 10 + y, 20 + x, 20 + y, al_map_rgb(255, 164, 32));

				//color(ROJO);
				al_draw_filled_rectangle(10 + x, 5 + y, 15 + x, 10 + y, al_map_rgb(255, 0, 0));
				al_draw_filled_rectangle(15 + x, y, 20 + x, 10 + y, al_map_rgb(255, 0, 0));
				al_draw_filled_rectangle(20 + x, 5 + y, 25 + x, 10 + y, al_map_rgb(255, 0, 0));
			}
		}
};

class bala {
public:
	int x;
	int y;
	int w;
	int h;
	int speed;
	bool isplayer;
	
	bala(int x, int y,bool isplayer)
	{
		this->x = x;
		this->y = y;
		this->w = 5;
		this->h = 10;
		this->speed = 5;
		this->isplayer = isplayer;
	}

	void print()
	{
		if (isplayer == true)
		{ 
			al_draw_filled_rectangle(x, y, x + w, y - h, al_map_rgb(255,0, 0));
		}
		else
		{
			al_draw_filled_rectangle(x, y, x + w, y - h, al_map_rgb(0, 255,0));
		}
	}

	void move()
	{
		if(isplayer==true)
		{ 
			this->y -= speed;
		}
		else
		{
			this->y += speed;
		}
	}

};

class jefe {
public:
	int x;
	int y;
	int w;
	int h;
	int speed;
	bool d;
	int count;
	bool dead;
	int hp;

	jefe(int x, int y, bool d, int speed)
	{
		this->x = x;
		this->y = y;
		this->w = 70;
		this->h = 60;
		this->dead = false;
		this->speed = speed;
		this->d = d;
		this->count=0;
		this->hp=10;
	}

	void move() {

		count++;

		if ((this->x < 0) && (d==false) && (dead==false))
		{
			d = true;
		}
		else if ((this->x > W - this->w) && (d == true) && (dead == false))
		{
			d = false;
		}

		if (d == false)
		{
			this->x -= speed;
		}
		else
		{
			this->x += speed;
		}
	}

	void print()
	{
		if (hp < 1)
		{
			dead = true;
		}

		if(hp < 6)
		{
			speed=6;
		}

		if (dead == false)
		{
			al_draw_filled_rectangle(x, y, 10 + x, 30 + y, al_map_rgb(2, 65, 246));
			al_draw_filled_rectangle(60 + x, y, 70 + x, 30 + y, al_map_rgb(2, 65, 246));

			//color_rgb(255, 164, 32);
			al_draw_filled_rectangle(10 + x, y, 20 + x, 20 + y, al_map_rgb(255, 164, 32));
			al_draw_filled_rectangle(20 + x, y - 10, 30 + x, y + 10, al_map_rgb(255, 164, 32));
			al_draw_filled_rectangle(30 + x, y - 20, 40 + x, y, al_map_rgb(255, 164, 32));
			al_draw_filled_rectangle(40 + x, y - 10, 50 + x, 10 + y, al_map_rgb(255, 164, 32));
			al_draw_filled_rectangle(50 + x, y, 60 + x, 20 + y, al_map_rgb(255, 164, 32));
			al_draw_filled_rectangle(30 + x, 20 + y, 40 + x, 40 + y, al_map_rgb(255, 164, 32));

			//color(ROJO);
			al_draw_filled_rectangle(20 + x, 10 + y, 30 + x, 20 + y, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(30 + x, y, 40 + x, 20 + y, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(40 + x, 10 + y, 50 + x, 20 + y, al_map_rgb(255, 0, 0));
		}
	}

};

class bala2 {
public:
	int x;
	int y;
	int w;
	int h;
	int vy;
	int vx;
	bala2(int x, int y, int vx)
	{
		this->x = x;
		this->y = y;
		this->w = 10;
		this->h = 15;
		this->vy = 5;
		this->vx = vx;
	}

	void print()
	{

		al_draw_filled_rectangle(x, y, x + w, y - h, al_map_rgb(120, 40, 140));
	}

	void move()
	{
		this->x += vx;
		this->y += vy;
	}

};


int main(void)
{
	const int FPS = 60;
	bool done = false;
	bool redraw = true;
	int cenemigos = 6;

	enemigo* e[6];
	e[0] = new enemigo(100, 100, true,3);
	e[1] = new enemigo(400, 100, false,3);
	e[2] = new enemigo(400, 150, true,3);
	e[3] = new enemigo(775, 150, false,3);
	e[4] = new enemigo(150, 200, true,3);
	e[5] = new enemigo(500, 200, false,3);


	bala* b[6];
	b[0] = new bala(900, 900, false);
	b[1] = new bala(900, 900, false);
	b[2] = new bala(900, 900, false);
	b[3] = new bala(900, 900, false);
	b[4] = new bala(900, 900, false);
	b[5] = new bala(900, 900, false);

	jefe* j[2];
	j[0] = new jefe(400,100,true,3);
	j[1] = new jefe(400,200,false,3);

	bala2 * s[6];
	s[0] = new bala2(900, 900, -1);
	s[1] = new bala2(900, 900, 0);
	s[2] = new bala2(900, 900, 1);
	s[3] = new bala2(900, 900, -1);
	s[4] = new bala2(900, 900, 0);
	s[5] = new bala2(900, 900, 1);

	//jugadores
	player p(400, 500);
	bala bp(900, -100, true);

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_SAMPLE *laser = NULL;
	ALLEGRO_SAMPLE *explosion = NULL;
	ALLEGRO_BITMAP  *background=NULL;


	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(W, H);			//create our display object

	if (!display)										//test display object
		return -1;

	//Allegro Module Init
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();


	al_reserve_samples(2);
	laser = al_load_sample("Laser_Gun.wav");
	explosion = al_load_sample("Big_Explosion.wav");

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	//Game Init

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *font24 = al_load_font("arial.ttf", 24, 0);

	background=al_load_bitmap("fondo.png");

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[LEFT])
				p.moveleft();
			if (keys[RIGHT])
				p.moveright();
			if ((keys[SPACE])&& (bp.y<0))
			{
				al_play_sample(laser, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				bp.x = p.x+20;
				bp.y = p.y-15;
			}
			if((keys[ENTER])&&(cenemigos <1)&&(p.dead==false)&&(nivel<4))
			{
                nivel=nivel+1;
                if(nivel==2){
    				for (int i = 0; i < 6; i++)
    				{
    					e[i]->x=pe[i];
    					e[i]->d=ped[i];
    					e[i]->dead=false;
    					e[i]->speed=6;
    					b[i]->x = 900;
						b[i]->y = 900;
    				}
    				keys[ENTER]=false;
    				cenemigos=6;
              }
              
              if(nivel==3){
              	cenemigos=2;
                keys[ENTER]=false;      
              }
			}
			else if((keys[ENTER])&&(p.dead==true))
			{
				p.hp=3;
				p.dead=false;
				p.score=0;
				if(nivel!=3){
					for (int i = 0; i < 6; i++)
	    				{
	    					e[i]->x=pe[i];
	    					e[i]->d=ped[i];
	    					e[i]->dead=false;
	    					e[i]->speed=6;
	    					e[i]->d=ped[i];
	    					e[i]->count=0;
	    					e[i]->speed=vel[nivel-1];
	    					b[i]->x = 900;
							b[i]->y = 900;
	    				}
	    				keys[ENTER]=false;
	    				cenemigos=6;
				}
				else if(nivel == 3)
				{
					for (int i = 0; i < 2; i++)
	    			{
	    				j[i]->x=400;
	    				j[i]->count=0;
	    				j[i]->hp=10;
	    				j[i]->dead=false;

	    				for(int j = 0;j<3;j++)
						{
							s[j+3*i]->x = 900;
							s[j+3*i]->y = 900;
						}
	    			}
				}
    			
			}

    		bp.move();

            if(nivel!=3){
    			for (int i = 0; i < 6; i++)
    			{
                    e[i]->move();
    				b[i]->move();
    
    				if ((e[i]->count > 120+2.5*i) && (e[i]->dead == false))
    				{
    					b[i]->x = e[i]->x + 15;
    					b[i]->y = e[i]->y + 30;
    					e[i]->count = 0;
    					al_play_sample(laser, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    				}
    			}
            }
            else if(nivel==3)
            {
            	for (int i = 0; i < 2; i++)
    			{
    				j[i]->move();
    				if ((j[i]->count > 80)&&(j[i]->dead==false))
    				{
    					s[0+3*i]->x= j[i]->x + 30;
    					s[1+3*i]->x= j[i]->x + 30;
    					s[2+3*i]->x= j[i]->x + 30;
    					s[0+3*i]->y= j[i]->y + 50;
    					s[1+3*i]->y= j[i]->y + 50;
    					s[2+3*i]->y= j[i]->y + 50;
    					j[i]->count=0;
    					al_play_sample(laser, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    				}
    				s[0+3*i]->move();
    				s[1+3*i]->move();
    				s[2+3*i]->move();
    			}
            	
            }

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_draw_bitmap(background,0,0,0);
			p.print();
            bp.print();
            
            if(nivel!=3)
            {
				for (int i = 0; i < 6; i++)
				{
					e[i]->print();
					b[i]->print();

					if (collision(e[i]->x, e[i]->y, e[i]->w, e[i]->h, bp.x, bp.y, bp.w, bp.h) && e[i]->dead == false)
					{
						e[i]->dead = true;
						cenemigos--;
						bp.x = 900;
						bp.y = -100;
						p.score += 100;
						al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					}

					if (collision(b[i]->x, b[i]->y, b[i]->w, b[i]->h, p.x, p.y, p.w, p.h) && p.dead == false)
					{
						b[i]->x = 900;
						b[i]->y = 900;
						p.hp--;
						al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
			else if(nivel==3)
			{
				for (int i = 0; i < 2; i++)
    			{
    				j[i]->print();

    				if (collision(j[i]->x, j[i]->y, j[i]->w, j[i]->h, bp.x, bp.y, bp.w, bp.h) && j[i]->dead == false)
					{
						bp.x = 900;
						bp.y = -100;
						j[i]->hp--;
						al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

						if(j[i]->hp==0)
						{
							p.score +=500;
							cenemigos--;
						}
					}
					for(int j = 0;j<3;j++)
					{
						s[j+3*i]->print();
						if (collision(s[j+3*i]->x, s[j+3*i]->y, s[j+3*i]->w, s[j+3*i]->h, p.x, p.y, p.w, p.h) && p.dead == false)
						{
							s[j+3*i]->x = 900;
							s[j+3*i]->y = 900;
							p.hp--;
							al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						}
					}
    			}
			}

			al_draw_textf(font24, al_map_rgb(255, 255, 255), 600, 10, 0, "SCORE: %d", p.score);
			al_draw_textf(font24, al_map_rgb(255, 255, 255), 10, 10, 0, "VIDAS: %d", p.hp);
			al_draw_textf(font24, al_map_rgb(255, 255, 255), 300, 10, 0, "NIVEL: %d", nivel);

			if ((cenemigos <1 )&&(p.dead==false)&&(nivel!=3)){
                al_draw_textf(font24, al_map_rgb(255, 255, 255), 225, 300, 0, "Presione ENTER para avanzar al nivel %d", nivel);
			}

			if((cenemigos <1 )&&(p.dead==false)&&(nivel==3))
			{
				al_draw_text(font24, al_map_rgb(255, 255, 255), 225, 300, 0, "Felicitaciones");
			}
			
			if(p.dead==true)
			{
                al_draw_text(font24, al_map_rgb(255, 255, 255), 225, 300, 0, "Presione Enter para reiniciar nivel");
            }
    

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	al_destroy_sample(laser);
	al_destroy_sample(explosion);
	al_destroy_bitmap(background);
	return 0;
}
