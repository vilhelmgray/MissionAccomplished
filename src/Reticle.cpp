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

#include "SDL.h"

#include "Entity.h"
#include "Texture.h"

#include "Reticle.h"

Reticle::Reticle(std::shared_ptr<Texture> texture) : Entity(0, 0, texture, 0, 0) {
	int x;
	int y;
	SDL_GetMouseState(&x, &y);

	position.x = x - 16;
	position.y = y - 16;
}

double Reticle::getBearing(const SDL_Rect *const point){
	const double rads2deg = 57.29577951308232087679;
	return std::atan2(position.y - point->y, position.x - point->x) * rads2deg;
}

void Reticle::draw(SDL_Renderer *const rend, const SDL_Rect *const aperture){
	if(SDL_RenderCopy(rend, tex->texture, &sprite, &position) < 0){
		throw std::runtime_error(SDL_GetError());
	}
}

void Reticle::evaluate_event(const SDL_Event *const event){
	if(event->type == SDL_MOUSEMOTION){
		position.x = event->motion.x - 16;
		position.y = event->motion.y - 16;
	}
}
