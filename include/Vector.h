#pragma once
namespace df {
	class Vector
	{

	private:
		float x;
		float y;

	public:
		Vector(float init_x, float init_y);

		Vector();

		void setX(float new_x);
		float getX() const;

		void setY(float new_y);
		float getY() const;

		void setXY(float new_x, float new_y);

		float getMagnitude() const;

		void normalize();
		void scale(float s);

		Vector operator+(const Vector &other) const;
		bool operator==(const Vector & other) const;
		bool operator!=(const Vector & other) const;
	};
}

