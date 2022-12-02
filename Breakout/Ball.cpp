/**********************************************************************************
// Ball (Arquivo de Cabe�alho)
// 
// Cria��o:     22 Dez 2012
// Atualiza��o: 01 Dez 2022
// Compilador:  Visual C++ 2022
//
// Descri��o:   Bola do jogo Breakout
//
**********************************************************************************/

#include "Ball.h"
#include "Block.h"
#include "Breakout.h"

// ---------------------------------------------------------------------------------

Ball::Ball(Player * p)
{
    // guarda jogador
    player = p;

    // tamanho da bola � 12x12
    BBox(new Rect(-6, -6, 5, 5));
    
    // bounding box alternativa: experimente  
    // usar o c�rculo no lugar do ret�ngulo
    //BBox(new Circle(6));

    // cria sprite da bola
    sprite  = new Sprite("Resources/Ball.png");

    // metade do tamanho da bola
    halfW = sprite->Width() / 2.0f;
    halfH = sprite->Height() / 2.0f;

    // tamanho do player � 100x20
    MoveTo(player->X(), player->Y() - 16.0f, Layer::FRONT);

    // velocidades iniciais
    velX = 300.0f;
    velY = -300.0f;

    // tipo do objeto
    type = BALL;
}

// ---------------------------------------------------------------------------------

Ball::~Ball()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Ball::OnCollision(Object * obj)
{
    // bola colide com bloco
    if (obj->Type() == BLOCK)
        Breakout::scene->Delete(obj, STATIC);

    // experimente deixar o bloco cair em vez de remov�-lo da cena
        //((Block*) obj)->velY = 200.0f;
}

// ---------------------------------------------------------------------------------

void Ball::Update()
{
    if (player->state == PLAYING)
    {
        Translate(velX * gameTime, velY * gameTime);

        // se o jogador n�o rebater, a bola � reiniciada
        if (y + sprite->Height() > window->Height())
            player->state = STOPED;
    }
    else
    {
        // mova para posi��o acima do player e o acompanhe
        MoveTo(player->X(), player->Y() - 16.0f, Layer::FRONT);
    }    

    // mant�m a bola dentro da tela (tam. da bola: 12x12)
    if (x < halfW)
    {
        MoveTo(halfW, y);
        velX = -velX;
    }
    if (x + halfW > window->Width())
    {
        MoveTo(float(window->Width() - halfW), y);
        velX = -velX;
    }
    if (y < halfH)
    {
        MoveTo(x, halfH);
        velY = -velY;
    }
    if (y + halfH > window->Height())
    {
        MoveTo(x, float(window->Height() - halfH));
        velY = -velY;
    }
}

// ---------------------------------------------------------------------------------
