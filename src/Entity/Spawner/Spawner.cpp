#include "Spawner.h"
#include "../Enemy/Kirikiri/Kirikiri.h"
#include <iostream>


Spawner::Spawner(int spawnerCount)
{
	set_visible = true;
	set_active = true;
	alive = true;
	health = 20;
	curDeathFrame = 0;
	sf::Vector2f spawnerLocs[5] = { { 800.f, 32.f },{ 1011.f, 60.f },
		{ 1094.f, 120.f },{ 1281.f,50.f },{ 471.f, 102.f } };
	if (spawnerCount >= 0 && spawnerCount < 5) //ensure no out of bounds access
		position = spawnerLocs[spawnerCount];
	else
		position = { 0.f,0.f };

	texture = new sf::Texture();
	deathTexture = new sf::Texture();
	if (!texture->loadFromFile("../res/Levels/Round 1 wrapped with spawner locs.png"))
		std::cerr << "Fail loading Round 1 wrapped with spawner locs.png\n";
	if (!deathTexture->loadFromFile("../res/Enemies.png"))
		std::cerr << "Failed loading Enemies.png in spawner\n";
	sprite = new sf::Sprite(*texture);
	deathSprite = new sf::Sprite(*deathTexture);

	sf::IntRect flyZone({ 76,433 }, { 46, 23 });
	sf::IntRect groundZone({ 75, 406 }, { 48,25 });
	Animation* activeFly = new Animation(1, 1, flyZone);
	Animation* activeGround = new Animation(1, 1, groundZone);

	Animation* deathAnim = new Animation;
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));
	deathAnim->addFrame(sf::IntRect({ 21,417 }, { 12,12 }));
	deathAnim->addFrame(sf::IntRect({ 35,415 }, { 16,16 }));
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));

	animations[ACTIVEFLY] = activeFly;
	animations[ACTIVEGROUND] = activeGround;
	animations[DEATH] = deathAnim;
	curAction = ACTIVEFLY;

	sprite->setTexture(*texture);
	sprite->setTextureRect(*(animations[curAction]->getFrame(0)));
	sprite->setPosition(position);
	
	deathSprite->setTexture(*deathTexture);
	deathSprite->setTextureRect(*(animations[DEATH]->getFrame(0)));
	deathSprite->setPosition(position);

	ticks = 1;
	tickRate = 12;
	std::cout << "Spawner created at " << position.x << ", " << position.y << "\n";
}

Spawner::~Spawner() 
{
	delete texture;
	delete sprite;
}

void Spawner::updateHealth(int tick)
{
	if (health <= 0)
	{
		death();
	}
}

void Spawner::spawnEnemy(int tick)
{
	bool kirikiriDir;
	float playerCenter, spawnerCenter;
	spawnerDist = viewport->getCenter().x - position.x;
	//every 300 frames, spawn an enemy
	if (tick % spawn_rate == 0 && set_active == true &&
		125 >= spawnerDist && spawnerDist >= -125) 
	{
		playerCenter = player->getSprite()->getPosition().x + (player->getSprite()->getGlobalBounds().size.x * 0.5f);
		spawnerCenter = sprite->getPosition().x + (0.5f * sprite->getGlobalBounds().size.x);
		kirikiriDir = playerCenter > spawnerCenter;
		ticks = 0;
		std::shared_ptr<Kirikiri> dummy = std::make_shared<Kirikiri>(kirikiriDir, position);
		dummy->initialize();
	}
	if(ticks<spawn_rate)
		ticks++;
}

void Spawner::update(int input)
{
	if (alive)
	{
		updateHealth(ticks);
		spawnEnemy(ticks);
	}
	else if (!alive)
	{
		ticks++;
		if (ticks >= tickRate)
		{
			ticks = 0;
			if (curDeathFrame >= animations[DEATH]->getFrameCount())
			{
				set_active = false;
				set_visible = false;
			}
			else
			{
				//change sprite
				deathSprite->setTextureRect(*animations[DEATH]->getFrame(curDeathFrame));
				//set origin
				sf::FloatRect bounds = deathSprite->getLocalBounds();
				deathSprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
				//set position back regardless of change due to origin
				deathSprite->setPosition(deathPos);
				//advance to next death frame
				curDeathFrame++;
			}
		}
		return;
		//exit method so sprite doesn't get updated further
	}
}

void Spawner::death()
{
	curAction = DEATH;
	alive = false;
	deathPos = sprite->getGlobalBounds().getCenter();
}


sf::Sprite* Spawner::getSprite()
{
	if (alive)
		return sprite;
	else
		return deathSprite;
}