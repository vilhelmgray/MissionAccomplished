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
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>

#include "SDL.h"

#include "Entity.h"
#include "Texture.h"

class Projectile: public Entity{
		struct{
			double x;
			double y;
		} pos;

	public:
		Projectile(const double x, const double y, const double angle, std::shared_ptr<Texture> tracer_texture);

		bool tick(const SDL_Rect *const aperture);
};

#endif
