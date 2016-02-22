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
#include "Reticle.h"
#include "Texture.h"

#include "Weapon.h"

Weapon::Weapon(const unsigned x, const unsigned y, std::shared_ptr<Texture> weapon_texture, std::shared_ptr<Texture> tracer_texture) : Entity(x, y, weapon_texture, 0, 0), tracer(tracer_texture) {}

void Weapon::draw(SDL_Renderer *const rend, const SDL_Rect *const aperture){
	Entity::draw(rend, aperture);

	for(auto& projectile : projectiles){
		projectile->draw(rend, aperture);
	}
}

void Weapon::fire(){
	const double deg2rad = 0.01745329251994329576;
	const double x = position.x + 32 * std::cos(angle * deg2rad);
	const double y = position.y + 32 * std::sin(angle * deg2rad);

	projectiles.emplace_back(new Projectile(x, y, angle, tracer));
}

void Weapon::tick(const unsigned x, const unsigned y, std::shared_ptr<Reticle> reticle, const SDL_Rect *const aperture, std::vector<std::unique_ptr<Entity>>& tiles){
	for(auto projectile = projectiles.begin(); projectile != projectiles.end(); projectile++){
		if((*projectile)->tick(aperture, tiles)){
			projectile = projectiles.erase(projectile);
			projectile--;
		}
	}

	position.x = x;
	position.y = y;

	if(reticle){
		SDL_Rect relative_position = position;
		relative_position.x -= aperture->x;
		relative_position.y -= aperture->y;

		angle = reticle->getBearing(&relative_position);
	}
}
