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
#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

#include "SDL.h"

#include "Texture.h"

class Entity{
	protected:
		SDL_Rect sprite;
		SDL_Rect position;

		std::shared_ptr<Texture> tex;

		unsigned face;
		unsigned solid;

	public:
		Entity(const unsigned X, const unsigned Y, std::shared_ptr<Texture> texture, const unsigned isSolid);

		bool collision(const SDL_Rect *const agent, SDL_Rect *const collisionArea);
		virtual void draw(SDL_Renderer *const rend);
};

#endif
