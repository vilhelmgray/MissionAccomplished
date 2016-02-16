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

#include "Character.h"

Character::Character(const unsigned X, const unsigned Y, std::vector<std::shared_ptr<Texture>> textures) : Entity(X, Y, textures[0]), pose(), poses(textures), velocity() {}

void Character::draw(SDL_Renderer *const rend){
	tex = poses[pose];

	Entity::draw(rend);
}

void Character::tick(const unsigned fps){
	position.x += velocity.x;
	position.y += velocity.y;

	static unsigned framesElapsed = 0;
	if(velocity.x){
		const unsigned numWalkPoses = poses.size() - 1;
		const unsigned walkPosePersistance = fps / numWalkPoses;

		pose = (framesElapsed / walkPosePersistance) + 1;

		framesElapsed = (framesElapsed + 1) % walkPosePersistance;
	}else{
		pose = 0;
		framesElapsed = 0;
	}
}
