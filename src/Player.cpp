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
#include <list>
#include <memory>
#include <vector>

#include "SDL.h"

#include "Camera.h"
#include "Character.h"
#include "Reticle.h"
#include "Texture.h"

#include "Player.h"

Player::Player(const unsigned x, const unsigned y, std::vector<std::shared_ptr<Texture>> poses_textures, std::shared_ptr<Texture> weapon_texture, std::shared_ptr<Texture> tracer_texture, std::shared_ptr<Texture> reticle_texture) : Character(x, y, poses_textures, weapon_texture, tracer_texture) {
	reticle = std::shared_ptr<Reticle>(new Reticle(reticle_texture));
}

void Player::draw(SDL_Renderer *const rend, const SDL_Rect *const aperture){
	Character::draw(rend, aperture);
	reticle->draw(rend, aperture);
}

void Player::evaluate_event(const SDL_Event *const event){
	switch(event->type){
		case SDL_KEYDOWN:
			if(!event->key.repeat){
				switch(event->key.keysym.sym){
					case SDLK_SPACE:
						vel.y = -160;
						break;
					case SDLK_a:
						vel.x = -60;
						break;
					case SDLK_d:
						vel.x = 60;
						break;
				}
			}
			break;
		case SDL_KEYUP:
			switch(event->key.keysym.sym){
				case SDLK_a:
				case SDLK_d:
					vel.x = 0;
					break;
			}
			break;
		case SDL_MOUSEMOTION:
			reticle->evaluate_event(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			weapon->fire();
			break;
	}
}

bool Player::tick(std::vector<std::unique_ptr<Entity>>& tiles, const unsigned fps, Camera& camera, std::shared_ptr<Reticle> dummy_reticle, std::list<std::shared_ptr<Character>>& enemies){
	Character::tick(tiles, fps, camera, reticle, enemies);

	const int new_camera_x = position.x - camera.aperture.w/2;
	if(new_camera_x < 0){
		camera.aperture.x = 0;
	}else if(new_camera_x > camera.max_x){
		camera.aperture.x = camera.max_x;
	}else{
		camera.aperture.x = new_camera_x;
	}
}
