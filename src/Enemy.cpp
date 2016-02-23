/* Copyright (C) 2016 William Breathitt Gray
 *
 * This file is part of Mission Accomplished.
 *
 * Mission Accomplished is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Mission Accomplished is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mission Accomplished.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <memory>
#include <chrono>
#include <vector>

#include "Camera.h"
#include "Character.h"
#include "Entity.h"
#include "Reticle.h"
#include "Texture.h"

#include "Enemy.h"

Enemy::Enemy(const unsigned x, const unsigned y, std::vector<std::shared_ptr<Texture>> poses, std::shared_ptr<Texture> weapon, std::shared_ptr<Texture> tracer) : Character(x, y, poses, weapon, tracer), rng(std::chrono::system_clock::now().time_since_epoch().count()), dis(0, 359) {}

bool Enemy::tick(std::vector<std::unique_ptr<Entity>>& tiles, const unsigned fps, Camera& camera, std::shared_ptr<Reticle> reticle, std::list<std::shared_ptr<Character>>& enemies){
	Character::tick(tiles, fps, camera, reticle, enemies);

	unsigned action = dis(rng);
	if(action < 9){
		vel.y = -160;
	}else if(action < 18){
		weapon->fire();
	}else if(action < 54){
		weapon->point(dis(rng));
	}else if(action < 180){
		vel.x = 0;
	}else if(action < 270){
		vel.x = -60;
	}else{
		vel.x = 60;
	}
}
