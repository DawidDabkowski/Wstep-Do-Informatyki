#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>

#define N 10

extern cairo_surface_t *surface;
extern unsigned int width;
extern unsigned int height;

extern double bg_color_r;
extern double bg_color_g;
extern double bg_color_b;

typedef struct vector{
	gdouble x;
	gdouble y;
} vector;

typedef struct ball_t {
	vector p;			// polozenie
	gdouble r;			// promien
	
	vector v;			// predkosc
	gdouble speedup;	// przyspieszenie	(standard 1) 
	gdouble mass;		// masa				(standard 1)

	gdouble rcolor;		// kolor czerwony
	gdouble gcolor;		// kolor zielony
	gdouble bcolor;		// kolor niebieski
} ball_t;

vector add(vector v1, vector v2)		// sumuje dwa wektory
{
	vector wynik;
	wynik.x=v1.x+v2.x;
	wynik.y=v1.y+v2.y;
	return wynik;
}
vector sub(vector v1, vector v2)		// odejmuje dwa wektory
{
	vector wynik;	
	wynik.x=v1.x-v2.x;
	wynik.y=v1.y-v2.y;
	return wynik;
}
gdouble mult(vector v1, vector v2)		// mnozy skalarnie dwa wektory
{
	gdouble wynik;
	wynik=v1.x*v2.x+v1.y*v2.y;
	return wynik;
}
vector scdiv(vector v1, gdouble a)		// dzieli wektor przez skalar
{
	vector wynik;
	wynik.x=v1.x/a;
	wynik.y=v1.y/a;
	return wynik;
}
vector scmult(gdouble a, vector v1)		// mnozy wektor przez skalar
{
	vector wynik;
	wynik.x=a*v1.x;
	wynik.y=a*v1.y;
	return wynik;
}
gdouble norm(vector v1)					// oblicza dlugosc wektora
{
	gdouble wynik;
	wynik=sqrt(v1.x*v1.x+v1.y*v1.y);
	return wynik;
}

void draw_circle(gdouble x, gdouble y, gdouble r, gdouble rcolor, gdouble gcolor, gdouble bcolor) 
{
	cairo_t *cr;
	cr = cairo_create(surface);
	cairo_arc(cr, x, y, r, 0, 2 * G_PI);
	cairo_set_source_rgb(cr, rcolor, gcolor, bcolor); 
	cairo_fill(cr);
	cairo_destroy (cr);
}

ball_t tab[N];

void ballinit(int i, gdouble px, gdouble py, gdouble r, gdouble vx, gdouble vy,		// tworzenie pilki
gdouble speedup, gdouble mass, gdouble rcolor, gdouble gcolor, gdouble bcolor)
{
	tab[i].p.x = px;			// polozenie x
	tab[i].p.y = py;			// polozenie y
	tab[i].r = r;				// promien
	tab[i].v.x = vx;			// predkosc x
	tab[i].v.y = vy;			// predkosc y
	tab[i].speedup = speedup;	// przyspieszenie
	tab[i].mass = mass;			// masa
	tab[i].rcolor = rcolor;		// kolor czerwony
	tab[i].gcolor = gcolor;		// kolor zielony
	tab[i].bcolor = bcolor;		// kolor niebieski
}

void prog_init() 
{
	bg_color_r = 0.7;
	bg_color_g = 0.7;
	bg_color_b = 0.7;

	ballinit(0,140,250,40,10,0,1,1,0.2,0.2,0.5);	// kulki newtona
	ballinit(1,320,250,40,0,0,1,1,0.2,0.2,0.5);
	ballinit(2,400,250,40,0,0,1,1,0.2,0.2,0.5);
	ballinit(3,480,250,40,0,0,1,1,0.2,0.2,0.5);
	ballinit(4,560,250,40,0,0,1,1,0.2,0.2,0.5);
	ballinit(5,140,400,30,10,0,1,1,0.2,0.5,0.2);
	ballinit(6,320,400,30,0,0,1,1,0.2,0.5,0.2);
	ballinit(7,400,400,30,0,0,1,1,0.2,0.5,0.2);
	ballinit(8,480,400,30,0,0,1,1,0.2,0.5,0.2);
	ballinit(9,640,400,30,10,0,1,1,0.2,0.5,0.2);

	/*ballinit(0,400,25,25,12,9,1,1,0.3,0.7,0.3);	// rozne masy i predkosci
	ballinit(1,775,285,25,-12,9,1,1,0.2,0.5,0.2);
	ballinit(2,400,545,25,-12,-9,1,1,0.3,0.7,0.3);
	ballinit(3,25,285,25,12,-9,1,1,0.2,0.5,0.2);
	ballinit(4,400,265,15,0,0,1,0.4,0.7,0.3,0.2);
	ballinit(5,425,285,15,0,0,1,0.4,0.6,0.3,0.2);
	ballinit(6,400,305,15,0,0,1,0.4,0.7,0.3,0.2);
	ballinit(7,375,285,15,0,0,1,0.4,0.6,0.3,0.2);
	ballinit(8,750,50,35,0,0,1,1.6,0.3,0.3,0.5);
	ballinit(9,50,520,35,0,0,1,1.6,0.3,0.3,0.5);*/
	
	/*ballinit(0,50,285,20,1,5,1.01,1,0.7,0.7,0.3);	// przyspieszenie i spowolnienie
	ballinit(1,380,400,20,0,0,0.99,1,0.4,0.4,0.6);
	ballinit(2,420,400,20,0,0,0.99,1,0.4,0.4,0.6);*/
}

void prog_update() 
{
	int i, j;
	int free_to_move;		// przyjmuje 1 jesli kula moze sie ruszyc lub 0 jesli jest zablokowana
	gdouble distance;		// odleglosc miedzy srodkami dwoch pilek, z malym naddatkiem	
	gdouble radius;			// suma promieni dwoch pilek
	for (i=0; i<N; i++)						
	{
		if (tab[i].p.x-tab[i].r+tab[i].v.x < 0)			// odbijanie sie od scian
			tab[i].v.x = -tab[i].v.x;
		if (tab[i].p.x+tab[i].r+tab[i].v.x > width)
			tab[i].v.x = -tab[i].v.x;
		if (tab[i].p.y-tab[i].r+tab[i].v.y < 0)
			tab[i].v.y = -tab[i].v.y;
		if (tab[i].p.y+tab[i].r+tab[i].v.y > height)
			tab[i].v.y = -tab[i].v.y;
			
		for (j=i+1; j<N; j++)							// odbijanie sie od innych pilek
		{
			distance = norm(sub(add(tab[i].p,tab[i].v),add(tab[j].p,tab[j].v)));
			radius = tab[i].r+tab[j].r;
			if (distance<radius)
			{
				// predkosc srodka masy:
				vector vs = scdiv(add(scmult(tab[i].mass,tab[i].v),scmult(tab[j].mass,tab[j].v)),(tab[i].mass+tab[j].mass));
				// przechodzimy do ukladu srodka masy:
				vector va = sub(tab[i].v,vs);
				vector vb = sub(tab[j].v,vs);
				// wersor w kierunku laczacym srodki kul:
				vector e = scdiv(sub(tab[i].p,tab[j].p),norm(sub(tab[i].p,tab[j].p)));
				// skladowa predkosci pierwszej kuli w kierunku wersora e:
				vector vay = scmult(mult(va,e),e);
				// skladowa prostopadla:
				vector vax = sub(va,vay);
				// analogicznie druga kula:
				vector vby = scmult(mult(vb,e),e);
				vector vbx = sub(vb,vby);
				// poniewaz jestesmy w ukladzie srodka masy skladowe vay i vby zmienia zwrot przy odbiciu.
				// ponownie konstruujemy wektory va i vb na podstawie skladowych:
				va = sub(vax,vay);
				vb = sub(vbx,vby);
				// wracamy z ukladu srodka masy:
				tab[i].v = add(va,vs);
				tab[j].v = add(vb,vs);
			}
		}
		free_to_move = 1;
		if (tab[i].p.x-tab[i].r+tab[i].v.x < 0)				// sprawdzanie czy pilka moze sie ruszyc
			free_to_move = 0;
		else if (tab[i].p.x+tab[i].r+tab[i].v.x > width)
			free_to_move = 0;
		else if (tab[i].p.y-tab[i].r+tab[i].v.y < 0)
			free_to_move = 0;
		else if (tab[i].p.y+tab[i].r+tab[i].v.y > height)
			free_to_move = 0;
		else for (j=0; j<N; j++)
		{	
			if (j!=i)
			{
				distance = norm(sub(add(tab[i].p,tab[i].v),add(tab[j].p,tab[j].v)));
				radius = tab[i].r+tab[j].r;
				if (distance < radius)
					free_to_move = 0;
			}
		}
		if (free_to_move == 1)							// aktualizacja polozenia
		{
			tab[i].p.x += tab[i].v.x;
			tab[i].p.y += tab[i].v.y;
		}										
		tab[i].v.x -= (1-tab[i].speedup)*tab[i].v.x;	// aktualizacja predkosci	
		tab[i].v.y -= (1-tab[i].speedup)*tab[i].v.y;
	}
}

void prog_draw() 
{
	int i = 0;
	for (i=0; i<N; i++)
		draw_circle(tab[i].p.x, tab[i].p.y, tab[i].r, tab[i].rcolor, tab[i].gcolor, tab[i].bcolor);
}
