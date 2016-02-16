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
#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <vector>

#include "SDL.h"

#include "Entity.h"
#include "Texture.h"

class Character: public Entity{
	protected:
		std::vector<std::shared_ptr<Texture>>::size_type pose;
		std::vector<std::shared_ptr<Texture>> poses;

		struct{
			unsigned x;
			unsigned y;
		} velocity;

	public:
		Character(const unsigned X, const unsigned Y, std::vector<std::shared_ptr<Texture>> textures);

		void draw(SDL_Renderer *const rend);
		void tick(const unsigned fps);
};

#endif
