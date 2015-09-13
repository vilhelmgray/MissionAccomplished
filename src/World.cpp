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
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

#include "SDL.h"

#include "Entity.h"
#include "ImageSystem.h"
#include "Texture.h"

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

	for(auto& entity : entities){
		entity->draw(windrend.renderer);
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
	std::ifstream mapFile;
	mapFile.exceptions(mapFile.failbit | mapFile.badbit);

	mapFile.open("level1.map");

	std::string bgFilePath;
	mapFile >> bgFilePath;

	ImageSystem imgsys;
	background = std::unique_ptr<Texture>(new Texture(windrend.renderer, bgFilePath.c_str()));

	unsigned numTiles;
	mapFile >> numTiles;
	for(unsigned i = 0; i < numTiles; i++){
		std::string tileFilePath;
		mapFile >> tileFilePath;

		tiles.emplace_back(tileFilePath);
	}

	for(auto& y : chunk ){
		for(auto& x : y){
			mapFile >> x;
			if(x > numTiles){
				x = 0;
			}
		}
	}

	for(unsigned y = 0; y < 15; y++){
		for(unsigned x = 0; x < 20; x++){
			if(chunk[y][x]){
				entities.emplace_back(new Entity(windrend.renderer, tiles[chunk[y][x]-1].c_str(), x*32, y*32));
			}
		}
	}
}

bool World::tick(){
	if(handleEvents()){
		return true;
	}

	draw();

	return false;
}
