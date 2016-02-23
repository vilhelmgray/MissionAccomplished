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
#include "Entity.h"
#include "Reticle.h"
#include "Texture.h"
#include "Weapon.h"

#include "Character.h"

Character::Character(const unsigned x, const unsigned y, std::vector<std::shared_ptr<Texture>> poses_textures, std::shared_ptr<Texture> weapon_texture, std::shared_ptr<Texture> tracer_texture) : Entity(x, y, poses_textures[0], 0, 1), pose(), poses(poses_textures), acc{0, 300}, vel(), hp(100), falling(1) {
	pos.x = position.x;
	pos.y = position.y;

	weapon = std::unique_ptr<Weapon>(new Weapon(position.x, position.y, weapon_texture, tracer_texture));
}

bool Character::collision(const SDL_Rect *const agent, SDL_Rect *const collisionArea){
	if(Entity::collision(agent, collisionArea)){
		hp = (hp <= 20) ? 0 : hp - 20;
		return true;
	}

	return false;
}

void Character::draw(SDL_Renderer *const rend, const SDL_Rect *const aperture){
	tex = poses[pose];

	Entity::draw(rend, aperture);
	weapon->draw(rend, aperture);

	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(rend, &r, &g, &b, &a);

	SDL_Rect hp_bar = { position.x - aperture->x + 16, position.y - 16, 16, 4};
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderFillRect(rend, &hp_bar);
	hp_bar.w *= hp/100.0;
	SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
	SDL_RenderFillRect(rend, &hp_bar);

	SDL_SetRenderDrawColor(rend, r, g, b, a);
}

void Character::jump(){
	if(!falling){
		vel.y = -acc.y;
		falling = 1;
	}
}

bool Character::tick(std::vector<std::unique_ptr<Entity>>& tiles, const unsigned fps, Camera& camera, std::shared_ptr<Reticle> reticle, std::list<std::shared_ptr<Character>>& enemies){
	if(!hp){
		return true;
	}

	if(acc.x > 0){
		face = 0;
	}else if(acc.x < 0){
		face = 1;
	}

	vel.y += acc.y / fps;
	if(!falling){
		if(acc.x){
			const double new_vel_x = vel.x + acc.x / fps;
			if(acc.x > 0){
				vel.x = (new_vel_x > 100) ? 100 : new_vel_x;
			}else if(acc.x < 0){
				vel.x = (new_vel_x < -100) ? -100 : new_vel_x;
			}
		}else if(vel.x > 0){
			const double delta_x = 300.0 / fps;
			vel.x = (vel.x > delta_x) ? vel.x - delta_x : 0;
		}else if(vel.x < 0){
			const double delta_x = 300.0 / fps;
			vel.x = (vel.x < -delta_x) ? vel.x + delta_x : 0;
		}
	}

	pos.x += vel.x / fps;
	pos.y += vel.y / fps;

	for(auto& tile : tiles){
		SDL_Rect attempt = position;
		attempt.x = pos.x;
		SDL_Rect collisionArea;
		if(tile->collision(&attempt, &collisionArea)){
			attempt.x = pos.x -= (vel.x > 0 ? 1 : -1) * collisionArea.w;
			vel.x = 0;
		}

		attempt.y = pos.y;
		if(tile->collision(&attempt, &collisionArea)){
			pos.y -= (vel.y > 0 ? 1 : -1) * collisionArea.h;
			vel.y = 0;
			falling = 0;
		}
	}

	const int x_bound_check = pos.x;
	const int max_x = camera.max_x + camera.aperture.w - 32;
	if(x_bound_check < 0){
		pos.x = 0;
		vel.x = 0;
	}else if(x_bound_check > max_x){
		pos.x = max_x;
		vel.x = 0;
	}

	position.x = pos.x;
	position.y = pos.y;

	static unsigned framesElapsed = 0;
	if(vel.x){
		const unsigned numWalkPoses = poses.size() - 1;
		const unsigned walkPosePersistance = fps / numWalkPoses;

		pose = (framesElapsed / walkPosePersistance) + 1;

		framesElapsed = (framesElapsed + 1) % fps;
	}else{
		pose = 0;
		framesElapsed = 0;
	}

	weapon->tick(position.x, position.y, reticle, &camera.aperture, tiles, enemies);

	return false;
}
