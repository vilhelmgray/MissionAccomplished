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
#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <vector>

#include "Character.h"
#include "Texture.h"

class Enemy: public Character{
	public:
		Enemy(const unsigned x, const unsigned y, std::vector<std::shared_ptr<Texture>> poses, std::shared_ptr<Texture> weapon, std::shared_ptr<Texture> tracer);
};

#endif
