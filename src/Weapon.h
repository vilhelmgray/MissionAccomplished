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
#ifndef WEAPON_H
#define WEAPON_H

#include <list>
#include <memory>
#include <vector>

#include "SDL.h"

#include "Entity.h"
#include "Projectile.h"
#include "Reticle.h"
#include "Texture.h"

class Weapon: public Entity{
		std::list<std::shared_ptr<Projectile>> projectiles;

		std::shared_ptr<Texture> tracer;
	public:
		Weapon(const unsigned x, const unsigned y, std::shared_ptr<Texture> weapon_texture, std::shared_ptr<Texture> tracer_texture);

		void draw(SDL_Renderer *const rend, const SDL_Rect *const aperture);
		void fire();
		void tick(const unsigned x, const unsigned y, std::shared_ptr<Reticle> reticle, const SDL_Rect *const aperture, std::vector<std::unique_ptr<Entity>>& tiles);
};

#endif
