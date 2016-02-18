/* Copyright (C) 2015 William Breathitt Gray
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
#include <vector>

#include "SDL.h"

#include "Entity.h"
#include "Texture.h"
#include "Weapon.h"

#include "Character.h"

Character::Character(const unsigned X, const unsigned Y, std::vector<std::shared_ptr<Texture>> poses_textures, std::shared_ptr<Texture> weapon_texture) : Entity(X, Y, poses_textures[0], 1), pose(), poses(poses_textures), vel() {
	pos.x = position.x;
	pos.y = position.y;

	weapon = std::unique_ptr<Weapon>(new Weapon(position.x, position.y, weapon_texture));
}

void Character::draw(SDL_Renderer *const rend){
	tex = poses[pose];

	Entity::draw(rend);
	weapon->draw(rend);
}

void Character::tick(std::vector<std::unique_ptr<Entity>>& tiles, const unsigned fps){
	vel.y += 160 / fps;

	pos.x += vel.x / fps;
	pos.y += vel.y / fps;

	for(auto& tile : tiles){
		SDL_Rect attempt = position;
		attempt.x = pos.x;
		SDL_Rect collisionArea;
		if(tile->collision(&attempt, &collisionArea)){
			attempt.x = pos.x -= (vel.x > 0 ? 1 : -1) * collisionArea.w;
		}

		attempt.y = pos.y;
		if(tile->collision(&attempt, &collisionArea)){
			pos.y -= (vel.y > 0 ? 1 : -1) * collisionArea.h;
			vel.y = 0;
		}
	}
	position.x = pos.x;
	position.y = pos.y;

	static unsigned framesElapsed = 0;
	if(vel.x){
		const unsigned numWalkPoses = poses.size() - 1;
		const unsigned walkPosePersistance = fps / numWalkPoses;

		pose = (framesElapsed / walkPosePersistance) + 1;

		framesElapsed = (framesElapsed + 1) % fps;
	}else{
		pose = 0;
		framesElapsed = 0;
	}

	weapon->tick(position.x, position.y);
}
