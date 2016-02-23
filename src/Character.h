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
#ifndef CHARACTER_H
#define CHARACTER_H

#include <list>
#include <memory>
#include <vector>

#include "SDL.h"

#include "Camera.h"
#include "Entity.h"
#include "Reticle.h"
#include "Texture.h"
#include "Weapon.h"

class Weapon;

class Character: public Entity{
	protected:
		std::vector<std::shared_ptr<Texture>>::size_type pose;
		std::vector<std::shared_ptr<Texture>> poses;

		std::unique_ptr<Weapon> weapon;

		struct{
			double x;
			double y;
		} acc, vel, pos;

		unsigned hp;
		unsigned falling;

	public:
		Character(const unsigned x, const unsigned y, std::vector<std::shared_ptr<Texture>> poses_textures, std::shared_ptr<Texture> weapon_texture, std::shared_ptr<Texture> tracer_texture);

		bool collision(const SDL_Rect *const agent, SDL_Rect *const collisionArea);
		virtual void draw(SDL_Renderer *const rend, const SDL_Rect *const aperture);
		void jump();
		virtual bool tick(std::vector<std::unique_ptr<Entity>>& tiles, const unsigned fps, Camera& camera, std::shared_ptr<Reticle> reticle, std::list<std::shared_ptr<Character>>& enemies);
};

#endif
