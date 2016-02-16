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
#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "SDL.h"

#include "Character.h"
#include "Texture.h"

class Player: public Character{
	public:
		Player(std::vector<std::shared_ptr<Texture>> textures, const unsigned X, const unsigned Y);

		void draw(SDL_Renderer *const rend);
		void evaluate_event(SDL_Event *const event);
};

#endif
