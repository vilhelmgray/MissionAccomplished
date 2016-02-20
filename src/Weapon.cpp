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
#include <memory>

#include "Entity.h"
#include "Reticle.h"
#include "Texture.h"

#include "Weapon.h"

Weapon::Weapon(const unsigned X, const unsigned Y, std::shared_ptr<Texture> weapon_texture) : Entity(X, Y, weapon_texture, 0) {}

void Weapon::tick(const unsigned X, const unsigned Y, std::shared_ptr<Reticle> reticle){
	position.x = X;
	position.y = Y;

	angle = (reticle) ? reticle->getBearing(&position) : 0;
}
