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
#include <stdexcept>
#include <memory>

#include "SDL.h"

#include "ImageSystem.h"
#include "Sprite.h"

#include "World.h"

World::World(){
	if(SDL_ShowCursor(SDL_DISABLE) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	if(SDL_RenderSetLogicalSize(windrend.renderer, 640, 480) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	if(SDL_SetRenderDrawColor(windrend.renderer, 0, 0, 0, 255) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	loadFiles();
}

void World::draw(){
	if(SDL_RenderClear(windrend.renderer) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	if(SDL_RenderCopy(windrend.renderer, background->texture, NULL, NULL) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	SDL_RenderPresent(windrend.renderer);
}

bool World::handleEvents(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						return true;
				}
				break;
			case SDL_QUIT:
				return true;
		}
	}

	return false;
}

void World::loadFiles(){
	ImageSystem imgsys;

	background = std::unique_ptr<Sprite>(new Sprite(windrend.renderer, "background.png", 640, 480));
}

bool World::tick(){
	if(handleEvents()){
		return true;
	}

	draw();

	return false;
}
