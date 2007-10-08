/*
 * Really Slick XScreenSavers
 * Copyright (C) 2002-2006  Michael Chapman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *****************************************************************************
 *
 * This is a Linux port of the Really Slick Screensavers,
 * Copyright (C) 2002 Terence M. Welsh, available from www.reallyslick.com
 */
#ifndef _SPHERE_HH
#define _SPHERE_HH

#include <common.hh>

#include <vector.hh>

class Sphere {
private:
	Vector _center;
	float _scale;
	float _scaleSquared;
public:
	void setCenter(const Vector& center) {
		_center = center;
	}

	const Vector& getCenter() const {
		return _center;
	}

	void setScale(float scale) {
		_scale = scale;
		_scaleSquared = scale * scale;
	}

	float getScale() const {
		return _scale;
	}

	float value(const Vector& XYZ) {
		return _scaleSquared / (XYZ - _center).lengthSquared();
	}
};

#endif // _SPHERE_HH
