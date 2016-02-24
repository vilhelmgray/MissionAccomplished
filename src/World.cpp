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
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "SDL.h"

#include "Character.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include "ImageSystem.h"
#include "Texture.h"

#include "World.h"

World::World(const std::string& mapFilePath) : camera() {
	if(SDL_ShowCursor(SDL_DISABLE) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	camera.aperture.w = 640;
	camera.aperture.h = 480;
	if(SDL_RenderSetLogicalSize(windrend.renderer, camera.aperture.w, camera.aperture.h) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	if(SDL_SetRenderDrawColor(windrend.renderer, 0, 0, 0, 255) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	loadFiles(mapFilePath);
}

void World::draw(){
	if(SDL_RenderClear(windrend.renderer) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	if(SDL_RenderCopy(windrend.renderer, background->texture, NULL, NULL) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	for(auto& tile : tiles){
		tile->draw(windrend.renderer, &camera.aperture);
	}

	for(auto& enemy : enemies){
		enemy->draw(windrend.renderer, &camera.aperture);
	}

	player->draw(windrend.renderer, &camera.aperture);

	SDL_RenderPresent(windrend.renderer);
}

bool World::gameOver(){
	if(SDL_RenderClear(windrend.renderer) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	if(SDL_RenderCopy(windrend.renderer, gameOverScreen->texture, NULL, NULL) < 0){
		throw std::runtime_error(SDL_GetError());
	}

	SDL_RenderPresent(windrend.renderer);

	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
			return true;
		}
	}

	return false;
}

bool World::handleEvents(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_ESCAPE){
					return true;
				}

				player->evaluate_event(&event);
				break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
				player->evaluate_event(&event);
				break;
			case SDL_QUIT:
				return true;
		}
	}

	return false;
}

void World::loadFiles(const std::string& mapFilePath){
	std::ifstream mapFile;
	mapFile.exceptions(mapFile.failbit | mapFile.badbit);

	mapFile.open(mapFilePath);

	std::string buffer;
	std::getline(mapFile, buffer);
	unsigned x;
	unsigned y;
	std::istringstream(buffer) >> x >> y;

	std::getline(mapFile, buffer);
	unsigned numCharacterPoses;
	std::istringstream(buffer) >> numCharacterPoses;
	if(!numCharacterPoses){
		throw std::runtime_error("Number of character poses sets must be greater than 0");
	}
	ImageSystem imgsys;
	std::vector<std::vector<std::shared_ptr<Texture>>> characterPoses;
	for(unsigned i = 0; i < numCharacterPoses; i++){
		std::vector<std::shared_ptr<Texture>> poses;

		std::getline(mapFile, buffer);
		unsigned numPoses;
		std::istringstream(buffer) >> numPoses;
		if(numPoses < 2){
			throw std::runtime_error("Number of poses in a set must be greater than 1");
		}
		for(unsigned j = 0; j < numPoses; j++){
			std::string poseFilePath;
			std::getline(mapFile, poseFilePath);

			poses.emplace_back(new Texture(windrend.renderer, poseFilePath.c_str()));
		}

		characterPoses.push_back(poses);
	}

	std::getline(mapFile, buffer);
	unsigned numWeapons;
	std::istringstream(buffer) >> numWeapons;
	if(!numWeapons){
		throw std::runtime_error("Number of weapons must be greater than 0");
	}
	std::vector<std::shared_ptr<Texture>> weapons;
	for(unsigned i = 0; i < numWeapons; i++){
		std::string weaponFilePath;
		std::getline(mapFile, weaponFilePath);

		weapons.emplace_back(new Texture(windrend.renderer, weaponFilePath.c_str()));
	}

	std::getline(mapFile, buffer);
	unsigned numTracers;
	std::istringstream(buffer) >> numTracers;
	if(!numTracers){
		throw std::runtime_error("Number of tracers must be greater than 0");
	}
	std::vector<std::shared_ptr<Texture>> tracers;
	for(unsigned i = 0; i < numTracers; i++){
		std::string tracerFilePath;
		std::getline(mapFile, tracerFilePath);

		tracers.emplace_back(new Texture(windrend.renderer, tracerFilePath.c_str()));
	}

	std::string reticleFilePath;
	std::getline(mapFile, reticleFilePath);
	std::shared_ptr<Texture> reticle = std::shared_ptr<Texture>(new Texture(windrend.renderer, reticleFilePath.c_str()));

	player = std::shared_ptr<Player>(new Player(x, y, characterPoses[0], weapons[0], tracers[0], reticle));

	std::getline(mapFile, buffer);
	unsigned numEnemies;
	std::istringstream(buffer) >> numEnemies;
	if(!numEnemies){
		throw std::runtime_error("Number of enemies must be greater than 0");
	}
	for(unsigned i = 0; i < numEnemies; i++){
		std::getline(mapFile, buffer);
		unsigned poses;
		unsigned weapon;
		unsigned tracer;
		std::istringstream(buffer) >> x >> y >> poses >> weapon >> tracer;

		poses = (poses >= characterPoses.size()) ? 0 : poses;
		weapon = (weapon >= weapons.size()) ? 0 : weapon;
		tracer = (tracer >= tracers.size()) ? 0 : tracer;

		enemies.emplace_back(new Enemy(x, y, characterPoses[poses], weapons[weapon], tracers[tracer]));
	}

	std::string bgFilePath;
	std::getline(mapFile, bgFilePath);
	background = std::unique_ptr<Texture>(new Texture(windrend.renderer, bgFilePath.c_str()));

	std::getline(mapFile, buffer);
	unsigned numTiles;
	unsigned solidTiles;
	std::istringstream(buffer) >> numTiles >> solidTiles;
	for(unsigned i = 0; i < numTiles; i++){
		std::string tileFilePath;
		std::getline(mapFile, tileFilePath);

		tile_textures.emplace_back(new Texture(windrend.renderer, tileFilePath.c_str()));
	}

	std::getline(mapFile, buffer);
	unsigned width;
	unsigned height;
	std::istringstream(buffer) >> width >> height;

	if(width*32 > camera.aperture.w){
		camera.max_x = width*32 - camera.aperture.w;
	}

	for(y = 0; y < height; y++){
		std::getline(mapFile, buffer);
		std::istringstream iss(buffer);
		for(x = 0; x < width; x++){
			unsigned id;
			iss >> id;
			if(id && id <= tile_textures.size()){
				tiles.emplace_back(new Entity(x*32, y*32, tile_textures[id-1], 0, id >= solidTiles));
			}
		}
	}

	std::string gameOverFilePath;
	std::getline(mapFile, gameOverFilePath);
	gameOverScreen = std::unique_ptr<Texture>(new Texture(windrend.renderer, gameOverFilePath.c_str()));
}

bool World::tick(const unsigned fps){
	if(handleEvents()){
		return true;
	}

	std::list<std::shared_ptr<Character>> ticked_enemies(enemies.begin(), enemies.end());
	if(player->tick(tiles, fps, camera, nullptr, ticked_enemies)){
		return true;
	}

	std::list<std::shared_ptr<Character>> ticked_player{player};
	for(auto enemy = enemies.begin(); enemy != enemies.end(); enemy++){
		if((*enemy)->tick(tiles, fps, camera, nullptr, ticked_player)){
			enemy = enemies.erase(enemy);
			enemy--;
		}
	}
	if(enemies.empty()){
		return true;
	}

	draw();

	return false;
}
