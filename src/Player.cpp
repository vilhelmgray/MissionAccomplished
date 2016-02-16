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
#include <vector>

#include "SDL.h"

#include "Character.h"
#include "Texture.h"

#include "Player.h"

Player::Player(const unsigned X, const unsigned Y, std::vector<std::shared_ptr<Texture>> textures) : Character(X, Y, textures){}

void Player::evaluate_event(SDL_Event *const event){
	switch(event->type){
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym){
				case SDLK_SPACE:
					velocity.y = -5;
					break;
				case SDLK_a:
					face = 1;
					velocity.x = -5;
					break;
				case SDLK_d:
					face = 0;
					velocity.x = 5;
					break;
			}
			break;
		case SDL_KEYUP:
			switch(event->key.keysym.sym){
				case SDLK_a:
				case SDLK_d:
					velocity.x = 0;
					break;
			}
			break;
	}
}
