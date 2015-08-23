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
#include <memory>
#include <stdexcept>

#include "SDL.h"

#include "Entity.h"

Entity::Entity(SDL_Renderer *renderer, const char *file){
	tex = std::unique_ptr<Texture>(new Texture(renderer, file));

	sprite.x = 0;
	sprite.y = 0;
	sprite.w = 32;
	sprite.h = 32;

	position.x = 320;
	position.y = 240;
	position.w = 32;
	position.h = 32;
}

void Entity::draw(SDL_Renderer *renderer){
	if(SDL_RenderCopy(renderer, tex->texture, &sprite, &position) < 0){
		throw std::runtime_error(SDL_GetError());
	}
}
