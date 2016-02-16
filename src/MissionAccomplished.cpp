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
#include <exception>
#include <iostream>
#include <string>

#include "SDL.h"

#include "World.h"

int main(){
	std::cout << "Please enter the map file path: ";
	std::string mapFilePath;
	std::cin >> mapFilePath;

	try{
		World world(mapFilePath);

		Uint32 lastFrame = 0;
		while(true){
			Uint32 currFrame = SDL_GetTicks();
			if(currFrame - lastFrame > 16){
				lastFrame = currFrame;

				if(world.tick()){
					break;
				}
			}
		}
	}catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << '\n';
	}

	return 0;
}
