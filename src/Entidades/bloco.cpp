#include "bloco.hpp"

using namespace std;
using namespace sf;

Bloco::Bloco(int _x, int _y, float larg, float alt, TipoBloco tipo):
entidades::Entidade(_x, _y)
{
    setValido();
    id = 1;
    largura=larg;
    altura=alt;
    colisao.setSize(sf::Vector2f(largura, altura));
    colisao.setFillColor(sf::Color::White);
    colisao.setPosition(_x, _y);

    if (tipo==CHAO)
        inicializarSprite("assets/chao.png", 1, 64, 48, 0, 0, 0, sf::Vector2f(0.f, -4.f));
    else if (tipo==TETO)
        inicializarSprite("assets/teto.png", 1, 1408, 6, 0, 0, 0, sf::Vector2f(0.f, -4.f));
    else if (tipo==PAREDE)
        inicializarSprite("assets/parede.png", 1, 3, 550, 0, 0, 0, sf::Vector2f(0.f, -4.f));

}

Bloco::~Bloco()
{

}

void Bloco::executar()
{

}

void Bloco::colisaoBloco(Personagem* pP)
{
    if (pP == nullptr) return;

    // Pega as colisoes
    sf::FloatRect interseccao;
    sf::FloatRect personagem_colisao = pP->getColisao().getGlobalBounds();
    sf::FloatRect bloco_colisao = this->getColisao().getGlobalBounds();

    // Atribui a interseccao se houver colisão
    if (personagem_colisao.intersects(bloco_colisao, interseccao))
    {
        sf::Vector2f pos = pP->getXY();

        // Colisao vertical (eixo Y)
        if (interseccao.height < interseccao.width)
        {
            // Colisao por cima (jogador em cima do bloco)
            if (personagem_colisao.top < bloco_colisao.top)
            {
                pos.y -= interseccao.height;
                pP->setVelocidadeY(0.0f);
                pP->setNoChao(true);
            }
            // Colisao por baixo (jogador embaixo do bloco)
            else
            {
                pos.y += interseccao.height;
                pP->setVelocidadeY(0.0f);
            }
        }
        // Colisao horizontal (eixo X)
        else
        {
            // Colisao pela esquerda (jogador à esquerda do bloco)
            if (personagem_colisao.left < bloco_colisao.left)
            {
                pos.x -= interseccao.width;
            }
            // Colisao pela direita (jogador à direita do bloco)
            else
            {
                pos.x += interseccao.width;
            }
        }

        // Aplica a nova posição e atualiza a caixa de colisão do jogador
        pP->setXY(pos);
    }
}

void Bloco::colisaoBloco(Obstaculo* pO)
{
    if (pO==NULL) return;

    sf::FloatRect interseccao;
    sf::FloatRect obstaculo_colisao = pO->getColisao().getGlobalBounds();
    sf::FloatRect bloco_colisao = this->getColisao().getGlobalBounds();

    if (obstaculo_colisao.intersects(bloco_colisao, interseccao))
    {
        if (pO->getID() == 11)//é um lustre
        {
            pO->setInvalido();
            pO->setXY(sf::Vector2f(-100.f, -100.f));
        }
        else 
        {
            sf::Vector2f pos = pO->getXY();
            pos.y -= interseccao.height;  // empurra pra cima
            pO->setXY(pos);
            pO->setVelocidadeY(0.0f);
            pO->setNoChao(true);
        }
    }
}

void Bloco :: salvar(std::ofstream& arquivo)
{
    arquivo << id << " " << x << " " << y << std::endl;
}