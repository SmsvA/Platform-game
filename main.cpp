#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


float offsetX=0, offsetY=0;


const int H = 25;
const int W = 150;
const int X = 32;
const int Y = 32;
String TileMap[H] = {
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                                                                                                    P",
"P                                                                     kKPPPkK                                  kK                                    P",
"P                                                                   kKPPPPPrR                                  rR                                    P",
"P                                    PPPPPPPPPP                     PPPPPPPrR                                  rR                                    P",
"P                                            PP                            rR                          PPPPPPPPrRPPPPPPPPP      PPP                  P",
"P                                            PP            kK              PP                                  rR                                    P",
"P                          kK                PP            rR                             kK                   rR                                    P",
"P                          rR                PP            rR                             PP                   rR                        kK          P",
"P                          rR                PP      PPPPPPPPPPPP             kK                               PP                        PP          P",
"P      kK                  rR              PPPP      kK      PPPP             rR                                                                     P",
"P      rR         kK       rR            PPPPPP      rR      PPPP             rR                                           kK                        P",
"P      rR         rR       rR          kKPPPPPP      rR      PPPP             rR  kK               kK                  PPPPrR                        P",
"P      rR         rR       rR       kKPPPPPPPPP      rR      PPPP     PP      rR  rRkK             rR                  PPPPrR                        P",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
};




class PLAYER {

public:

float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;

    PLAYER(Texture &image)
   {
	sprite.setTexture(image);
	rect = FloatRect(70,180,16,16);

	dx=dy=0.1;
	currentFrame = 0;
   }


   void update(float time)
   {

	 rect.left += dx * time;
     Collision(0);


	 if (!onGround) dy=dy+0.0005*time;
	 rect.top += dy*time;
	 onGround=false;
     Collision(1);


     currentFrame += time * 0.005;
     if (currentFrame > 3) currentFrame -= 3;


    if (dx>0) sprite.setTextureRect(IntRect(112+31*int(currentFrame),144,16,16));
	if (dx<0) sprite.setTextureRect(IntRect(112+31*int(currentFrame)+16,144,-16,16));


	 sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	 dx=0;
   }


   void Collision(int num)
{

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 {
				 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='k') || (TileMap[i][j]=='K') || (TileMap[i][j]=='r') || (TileMap[i][j]=='R'))
				                         {
												   if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }
											       if (dy<0 && num==1)
												   { rect.top = i*16 + 16;   dy=0;}
												   if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}
										 }

			 }

}

};



class ENEMY
{

public:
float dx,dy;
FloatRect rect;
Sprite sprite;
float currentFrame;
bool life;


   void set(Texture &image, int x, int y)
   {
	sprite.setTexture(image);
	rect = FloatRect(x,y,16,16);

    dx=0.05;
	currentFrame = 0;
	life=true;
   }

   void update(float time)
   {
	 rect.left += dx * time;

     Collision();


     currentFrame += time * 0.005;
     if (currentFrame > 2) currentFrame -= 2;

    sprite.setTextureRect(IntRect(18*int(currentFrame),   0, 16,16));
    if (!life) sprite.setTextureRect(IntRect(58, 0, 16,16));


	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

   }


   void Collision()
  {

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='K')|| (TileMap[i][j]=='k')|| (TileMap[i][j]=='r')|| (TileMap[i][j]=='R'))
			                           {
                                                    if (dx>0)
												   { rect.left =  j*16 - rect.width; dx*=-1; }
											        else if (dx<0)
												   { rect.left =  j*16 + 16;  dx*=-1; }

										}
  }

};



int main()
{

    RenderWindow window(VideoMode(32*15, 32*12), "SFML works!");

	Texture tileSet;
	Texture tileSet2;
	tileSet.loadFromFile("Mario_Tileset.png");
	tileSet2.loadFromFile("Ruin.png");


	PLAYER Mario(tileSet);
	ENEMY  enemy1, enemy2, enemy3, enemy4;
	enemy1.set(tileSet,18*32,21*16);
	enemy2.set(tileSet,44*32,21*16);
	enemy3.set(tileSet,54*32,21*16);
	enemy4.set(tileSet,64*32,21*16);


	Sprite tile(tileSet);
	Sprite tile2(tileSet2);

	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound sound(buffer);

    Music music;
    music.openFromFile("Mario_Theme.ogg");
    music.play();

	Clock clock;

    while (window.isOpen())
    {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // здесь регулируем скорость игры

		if (time > 20) time = 20;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))    Mario.dx=-0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Right))    Mario.dx=0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Up))	if (Mario.onGround) { Mario.dy=-0.35; Mario.onGround=false;  sound.play();}



		 Mario.update(time);
		 enemy1.update(time);
		 enemy2.update(time);
		 enemy3.update(time);
		 enemy4.update(time);


		 if  (Mario.rect.intersects( enemy1.rect ) )
		 {
			 if (enemy1.life) {
			 if (Mario.dy>0) { enemy1.dx=0; Mario.dy=-0.2; enemy1.life=false;}
			 else Mario.sprite.setColor(Color::Red);
			 }
		 }
		 if  (Mario.rect.intersects( enemy2.rect ) )
		 {
			 if (enemy2.life) {
			 if (Mario.dy>0) { enemy2.dx=0; Mario.dy=-0.2; enemy2.life=false;}
			 else Mario.sprite.setColor(Color::Red);
			 }
		 }
		 if  (Mario.rect.intersects( enemy3.rect ) )
		 {
			 if (enemy3.life) {
			 if (Mario.dy>0) { enemy3.dx=0; Mario.dy=-0.2; enemy3.life=false;}
			 else Mario.sprite.setColor(Color::Red);
			 }
		 }
		 if  (Mario.rect.intersects( enemy4.rect ) )
		 {
			 if (enemy4.life) {
			 if (Mario.dy>0) { enemy4.dx=0; Mario.dy=-0.2; enemy4.life=false;}
			 else Mario.sprite.setColor(Color::Red);
			 }
		 }


		 if (Mario.rect.left>200) offsetX = Mario.rect.left-200;           //смещение




		 window.clear(Color(107,140,255));

		 for (int i=0; i<H; i++)
			 for (int j=0; j<W; j++)
			  {
				if (TileMap[i][j]=='P')  tile2.setTextureRect( IntRect(32,35+64*3,X,Y) );
				if (TileMap[i][j]=='k')  tile2.setTextureRect( IntRect(32,840,X,Y) );
				if (TileMap[i][j]=='K')  tile2.setTextureRect( IntRect(64,840,X,Y) );
				if (TileMap[i][j]=='r')  tile2.setTextureRect( IntRect(32,872,X,Y) );
				if (TileMap[i][j]=='R')  tile2.setTextureRect( IntRect(64,872,X,Y) );

				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='0')) continue;

  			    tile2.setPosition(j*16-offsetX,i*16 - offsetY) ;
		        window.draw(tile2);
		     }



		window.draw(Mario.sprite);
	    window.draw(enemy1.sprite);
	    window.draw(enemy2.sprite);
	    window.draw(enemy3.sprite);
	    window.draw(enemy4.sprite);

		window.display();
    }

    return 0;
}
