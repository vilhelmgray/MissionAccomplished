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
#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "Entity.h"
#include "SimpleDirectLayer.h"
#include "Texture.h"
#include "WindRend.h"

class World{
		SimpleDirectLayer sdl;
		WindRend windrend;

		std::unique_ptr<Texture> background;
		std::vector<std::shared_ptr<Texture>> tiles;

		std::vector<std::unique_ptr<Entity>> entities;

		void draw();
		bool handleEvents();
		void loadFiles();

	public:
		World();

		bool tick();
};

#endif
