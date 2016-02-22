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
#include <cmath>
#include <memory>
#include <vector>

#include "SDL.h"

#include "Entity.h"
#include "Texture.h"

#include "Projectile.h"

Projectile::Projectile(const double x, const double y, const double angle, std::shared_ptr<Texture> tracer_texture) : Entity(x, y, tracer_texture, angle, 1) {
	pos.x = x;
	pos.y = y;
}

bool Projectile::tick(const SDL_Rect *const aperture, std::vector<std::unique_ptr<Entity>>& tiles){
	const double deg2rad = 0.01745329251994329576;

	position.x = pos.x += 10 * std::cos(angle * deg2rad);
	position.y = pos.y += 10 * std::sin(angle * deg2rad);

	for(auto& tile : tiles){
		SDL_Rect collisionArea;
		if(tile->collision(&position, &collisionArea)){
			return true;
		}
	}

	return (position.x < aperture->x || position.y < aperture->y || position.x > aperture->x + aperture->w || position.y > aperture->y + aperture->h) ? true : false;
}
